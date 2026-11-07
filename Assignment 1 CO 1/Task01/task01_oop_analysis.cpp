#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Enumeration for Metro Network Zones
enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

const char* zoneToString(Zone z) {
    switch (z) {
        case Zone::Inner:  return "Inner";
        case Zone::Middle: return "Middle";
        case Zone::Outer:  return "Outer";
        default:           return "Unknown";
    }
}

// Passenger category
enum class PassengerCategory { Regular, Student, SeniorCitizen };

// FareTable class encapsulating base fares and surcharge rates
class FareTable {
private:
    static constexpr long long BASE_FARES[] = {1000, 2000, 3000}; // in paise (Rs 10, 20, 30)
    static constexpr int PEAK_SURCHARGE_PCT = 20;
public:
    static long long calculateFare(Zone z, bool isPeak, PassengerCategory cat) {
        long long fare = BASE_FARES[static_cast<int>(z)];
        if (isPeak) {
            fare += (fare * PEAK_SURCHARGE_PCT) / 100;
        }
        if (cat == PassengerCategory::Student) {
            fare = fare / 2; // 50% concession
        } else if (cat == PassengerCategory::SeniorCitizen) {
            fare = (fare * 75) / 100; // 25% concession
        }
        return fare;
    }
};
constexpr long long FareTable::BASE_FARES[];
constexpr int FareTable::PEAK_SURCHARGE_PCT;

// SmartCard Class encapsulating balance and invariant rules
class SmartCard {
private:
    std::string cardId_;
    std::string commuterName_;
    PassengerCategory category_;
    long long balancePaise_; // Stored in exact integer paise
    static constexpr long long MIN_BALANCE_PAISE = 5000; // Rs 50.00 required invariant

public:
    SmartCard(std::string id, std::string name, PassengerCategory cat, long long initialRupees)
        : cardId_(id), commuterName_(name), category_(cat), balancePaise_(initialRupees * 100) {}

    const std::string& getCardId() const { return cardId_; }
    const std::string& getName() const { return commuterName_; }
    PassengerCategory getCategory() const { return category_; }
    long long getBalancePaise() const { return balancePaise_; }

    bool canTravel(long long farePaise) const {
        return (balancePaise_ - farePaise) >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise_ -= farePaise;
        return true;
    }

    void recharge(long long amountRupees) {
        if (amountRupees > 0) balancePaise_ += amountRupees * 100;
    }
};
constexpr long long SmartCard::MIN_BALANCE_PAISE;

// Journey Entity
class Journey {
public:
    int journeyId;
    Zone destinationZone;
    int hour;
    bool isPeak;

    Journey(int id, Zone z, int h) : journeyId(id), destinationZone(z), hour(h) {
        isPeak = ((hour >= 8 && hour < 10) || (hour >= 17 && hour < 20));
    }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << " TASK 1: OBJECT-ORIENTED METRO SMART-CARD AUDIT SYSTEM\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    SmartCard card("SC-KA-10294", "G. Vishnu Madhav", PassengerCategory::Regular, 100); // Rs 100
    std::cout << "Card Issued: " << card.getCardId() << " | Commuter: " << card.getName() 
              << " | Initial Balance: Rs " << (card.getBalancePaise() / 100) << ".00\n\n";

    std::vector<Journey> batch = {
        Journey(1, Zone::Inner, 7),   // 07:00 Off-peak, Rs 10.00
        Journey(2, Zone::Outer, 9),   // 09:00 Peak,     Rs 36.00
        Journey(3, Zone::Middle, 14), // 14:00 Off-peak, Rs 20.00
        Journey(4, Zone::Outer, 18)   // 18:00 Peak,     Rs 36.00 (Should be denied)
    };

    for (const auto& j : batch) {
        long long fare = FareTable::calculateFare(j.destinationZone, j.isPeak, card.getCategory());
        std::cout << "Journey #" << j.journeyId << " to Zone: " << std::setw(6) << std::left << zoneToString(j.destinationZone)
                  << " | Time: " << std::setw(2) << std::setfill('0') << j.hour << ":00" << std::setfill(' ')
                  << " (" << (j.isPeak ? "PEAK    " : "OFF-PEAK") << ")"
                  << " | Fare: Rs " << std::setw(2) << (fare / 100) << "." << std::setw(2) << std::setfill('0') << (fare % 100) << std::setfill(' ');

        if (card.deduct(fare)) {
            std::cout << " | [GRANTED] Balance: Rs " << (card.getBalancePaise() / 100) << "." 
                      << std::setw(2) << std::setfill('0') << (card.getBalancePaise() % 100) << std::setfill(' ') << "\n";
        } else {
            std::cout << " | [DENIED] Low Balance (Min Rs 50 required). Current: Rs " 
                      << (card.getBalancePaise() / 100) << "." 
                      << std::setw(2) << std::setfill('0') << (card.getBalancePaise() % 100) << std::setfill(' ') << "\n";
        }
    }
    std::cout << "\nFinal Card Balance: Rs " << (card.getBalancePaise() / 100) << "." 
              << std::setw(2) << std::setfill('0') << (card.getBalancePaise() % 100) << "\n";
    std::cout << "Validation: Invariant Balance >= Rs 50.00 is strictly preserved!\n";
    return 0;
}
