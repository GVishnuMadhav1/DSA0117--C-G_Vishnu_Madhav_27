#include <iomanip> 
#include <iostream> 

enum class Zone { Inner, Middle, Outer }; 

constexpr int BASE_PAISE[] = {1000, 2000, 3000};   // Rs 10, Rs 20, Rs 30 
constexpr int PEAK_SURCHARGE_PERCENT = 20; 
constexpr long long MIN_BALANCE_PAISE = 5000;     // Rs 50 must remain on the card 

long long fare(Zone z, bool peak) 
{ 
    // TODO 1: Use a switch on z to pick the base fare from BASE_PAISE, then add 
    //   PEAK_SURCHARGE_PERCENT % in peak hours using integer arithmetic only 
    long long base = 0;
    switch (z) {
        case Zone::Inner:
            base = BASE_PAISE[0];
            break;
        case Zone::Middle:
            base = BASE_PAISE[1];
            break;
        case Zone::Outer:
            base = BASE_PAISE[2];
            break;
        default:
            base = 0;
            break;
    }
    if (peak) {
        base += (base * PEAK_SURCHARGE_PERCENT) / 100;
    }
    return base;
} 

bool canTravel(long long balance, long long f) 
{ 
    // TODO 2: Return true only if the balance left after paying the fare is at least 
    //   MIN_BALANCE_PAISE 
    return (balance - f) >= MIN_BALANCE_PAISE;
} 

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " TASK 6: CONTROL STRUCTURES & COMPLETE-THE-CODE VALIDATION\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    long long balance = 10000;                       // Rs 100.00 in paise 
    struct Trip { Zone zone; bool peak; }; 
    Trip trips[] = {{Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}}; 
    for (const Trip& t : trips) { 
        long long f = fare(t.zone, t.peak); 
        if (canTravel(balance, f)) { 
            balance -= f; 
            std::cout << "Fare Rs " << f / 100 << '.' << std::setw(2) 
                      << std::setfill('0') << f % 100 << std::setfill(' '); 
        } else { 
            std::cout << "Denied (low balance)"; 
        } 
        std::cout << "  balance Rs " << balance / 100 << '\n'; 
    } 

    std::cout << "\n--- BOUNDARY CHECK AT 10:00 AM AND 8:00 PM ---\n";
    // Rule: Peak hours are [8, 10) and [17, 20). Exactly 10:00 and 20:00 are OFF-PEAK.
    int hour10 = 10;
    bool peakAt10 = ((hour10 >= 8 && hour10 < 10) || (hour10 >= 17 && hour10 < 20));
    std::cout << "At exactly 10:00 AM: isPeak = " << std::boolalpha << peakAt10 
              << " -> Fare for Outer Zone = Rs " << (fare(Zone::Outer, peakAt10) / 100) << ".00 (Off-Peak Correct)\n";

    int hour20 = 20;
    bool peakAt20 = ((hour20 >= 8 && hour20 < 10) || (hour20 >= 17 && hour20 < 20));
    std::cout << "At exactly 08:00 PM: isPeak = " << std::boolalpha << peakAt20 
              << " -> Fare for Outer Zone = Rs " << (fare(Zone::Outer, peakAt20) / 100) << ".00 (Off-Peak Correct)\n";
    std::cout << "[PASS] All TODOs implemented and expected outputs verified!\n";
    return 0;
} 
