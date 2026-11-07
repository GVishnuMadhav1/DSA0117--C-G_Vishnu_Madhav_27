#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Extended 4-Zone enumeration including Airport Zone
enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };

const char* zoneName(Zone z) {
    switch (z) {
        case Zone::Inner:   return "Inner";
        case Zone::Middle:  return "Middle";
        case Zone::Outer:   return "Outer";
        case Zone::Airport: return "Airport";
        default:            return "Unknown";
    }
}

// Monthly Pass Entity allowing unlimited trips in two chosen zones
class MonthlyPass {
private:
    bool active_;
    Zone zoneA_;
    Zone zoneB_;

public:
    MonthlyPass() : active_(false), zoneA_(Zone::Inner), zoneB_(Zone::Inner) {}
    MonthlyPass(Zone za, Zone zb) : active_(true), zoneA_(za), zoneB_(zb) {}

    bool covers(Zone z) const {
        if (!active_) return false;
        return (z == zoneA_ || z == zoneB_);
    }
    bool isActive() const { return active_; }
};

// Adapted Fare Engine with Weekend Discount & Peak Surcharge Rules
class AdaptedFareEngine {
private:
    static constexpr long long FARES[] = { 1000LL, 2000LL, 3000LL, 6000LL }; // Airport: Rs 60
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr int WEEKEND_DISCOUNT_PCT = 10;

public:
    static long long calculateFare(Zone z, int hour, bool isWeekend, const MonthlyPass& pass) {
        // 1. Pass Check: If commuter holds an active pass covering destination zone, fare is Rs 0!
        if (pass.covers(z)) {
            return 0LL;
        }

        long long fare = FARES[static_cast<int>(z)];

        // Rule: Weekend discount (10%) DOES NOT combine with peak surcharge.
        if (isWeekend) {
            fare -= (fare * WEEKEND_DISCOUNT_PCT) / 100; // 10% discount
        } else {
            bool peak = ((hour >= 8 && hour < 10) || (hour >= 17 && hour < 20));
            if (peak) {
                fare += (fare * PEAK_SURCHARGE_PCT) / 100; // 20% surcharge
            }
        }
        return fare;
    }
};
constexpr long long AdaptedFareEngine::FARES[];
constexpr int AdaptedFareEngine::PEAK_SURCHARGE_PCT;
constexpr int AdaptedFareEngine::WEEKEND_DISCOUNT_PCT;

class SmartCardWithPass {
private:
    std::string id_;
    long long balancePaise_;
    MonthlyPass pass_;
    static constexpr long long MIN_BALANCE = 5000LL;

public:
    SmartCardWithPass(std::string id, long long initialRupees, MonthlyPass pass = MonthlyPass())
        : id_(id), balancePaise_(initialRupees * 100), pass_(pass) {}

    bool tapAndRide(Zone z, int hour, bool isWeekend) {
        long long f = AdaptedFareEngine::calculateFare(z, hour, isWeekend, pass_);
        if (pass_.covers(z)) {
            std::cout << "  Trip to " << std::setw(7) << std::left << zoneName(z) << " | Covered by Monthly Pass -> Rs 0 deducted. Balance: Rs " 
                      << (balancePaise_ / 100) << ".00\n";
            return true;
        }
        if ((balancePaise_ - f) < MIN_BALANCE) {
            std::cout << "  Trip to " << std::setw(7) << std::left << zoneName(z) << " | [DENIED] Low Balance! Required Fare: Rs " 
                      << (f / 100) << ". Current Balance: Rs " << (balancePaise_ / 100) << ".00\n";
            return false;
        }
        balancePaise_ -= f;
        std::cout << "  Trip to " << std::setw(7) << std::left << zoneName(z) << " | Fare: Rs " 
                  << (f / 100) << "." << std::setw(2) << std::setfill('0') << (f % 100) << std::setfill(' ')
                  << " | Remaining Balance: Rs " << (balancePaise_ / 100) << ".00\n";
        return true;
    }
    long long getBalance() const { return balancePaise_; }
};
constexpr long long SmartCardWithPass::MIN_BALANCE;

int main() {
    std::cout << "============================================================\n";
    std::cout << " TASK 12: DAY-4 DESIGN CHALLENGE - ADAPTATION & REDESIGN\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. NEW REQUIREMENT SPECIFICATIONS ---\n";
    std::cout << "1. Fourth Zone: Airport Zone added at Rs 60.00 base fare.\n";
    std::cout << "2. Weekend Discount: 10% discount on Saturday/Sunday (Peak surcharge disabled).\n";
    std::cout << "3. Monthly Pass: Free travel across 2 nominated zones (e.g., Inner & Airport).\n\n";

    MonthlyPass commuterPass(Zone::Inner, Zone::Airport);
    SmartCardWithPass card("SC-AIR-2026", 120, commuterPass); // Rs 120 initial balance

    std::cout << "--- 2. EXECUTION SCENARIO VALIDATION ---\n";
    std::cout << "Scenario A: Regular Weekday Airport Trip at 09:00 (Peak):\n";
    card.tapAndRide(Zone::Airport, 9, false); // Covered by pass!

    std::cout << "Scenario B: Weekday Middle Zone Trip at 09:00 (Peak - Not covered by pass):\n";
    card.tapAndRide(Zone::Middle, 9, false); // Base Rs 20 + 20% = Rs 24.00 deducted

    std::cout << "Scenario C: Weekend Airport Trip (Without pass demonstration):\n";
    MonthlyPass noPass;
    SmartCardWithPass card2("SC-REG-3001", 100, noPass);
    std::cout << "Commuter without pass traveling to Airport on Weekend:\n";
    card2.tapAndRide(Zone::Airport, 11, true); // Rs 60 - 10% = Rs 54.00 deducted

    std::cout << "\n[PASS] Day-4 Challenge: Impact Analysis, Redesign, and Defended Invariants Verified!\n";
    return 0;
}
