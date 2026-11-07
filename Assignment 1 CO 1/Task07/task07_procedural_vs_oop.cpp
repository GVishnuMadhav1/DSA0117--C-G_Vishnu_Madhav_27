#include <iostream>
#include <iomanip>
#include <string>

// --- PROCEDURAL APPROACH (Vulnerable to invariant violations) ---
struct ProceduralCard {
    long long balancePaise; // Publicly accessible: any part of code can corrupt it
};

bool canTravelProcedural(long long balance, long long fare, long long minBalance) {
    return (balance - fare) >= minBalance;
}

void deductProcedural(long long& balance, long long fare) {
    balance -= fare; // Does NOT verify invariant - permits negative balance!
}

// --- OBJECT-ORIENTED APPROACH (Encapsulated, invariant preserving) ---
class SmartCard {
private:
    std::string cardId_;
    long long balancePaise_;
    static constexpr long long MIN_BALANCE_PAISE = 5000; // Rs 50.00 Invariant

public:
    SmartCard(std::string id, long long initialRupees)
        : cardId_(id), balancePaise_(initialRupees * 100) {}

    long long getBalancePaise() const { return balancePaise_; }
    const std::string& getId() const { return cardId_; }

    bool canTravel(long long farePaise) const {
        return (balancePaise_ - farePaise) >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) {
            return false; // Invariant protected! Negative balance impossible.
        }
        balancePaise_ -= farePaise;
        return true;
    }

    void recharge(long long rupees) {
        if (rupees > 0) balancePaise_ += (rupees * 100);
    }
};
constexpr long long SmartCard::MIN_BALANCE_PAISE;

int main() {
    std::cout << "============================================================\n";
    std::cout << " TASK 7: PROCEDURAL VS OBJECT-ORIENTED PARADIGM COMPARISON\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. PROCEDURAL FAILURE DEMONSTRATION ---\n";
    ProceduralCard pCard{6000}; // Rs 60.00
    long long tripFare = 3600;  // Rs 36.00
    deductProcedural(pCard.balancePaise, tripFare); // Balance drops to Rs 24.00 (below Rs 50 min!)
    deductProcedural(pCard.balancePaise, tripFare); // Balance drops to -Rs 12.00 (NEGATIVE BALANCE!)
    std::cout << "Procedural Card Balance after 2 unverified deductions: Rs " 
              << (pCard.balancePaise / 100) << "." << std::abs(pCard.balancePaise % 100) 
              << " [SECURITY FLAW: Negative balance created!]\n\n";

    std::cout << "--- 2. OBJECT-ORIENTED INVARIANT PROTECTION ---\n";
    SmartCard oopCard("SC-9901", 60); // Rs 60.00
    std::cout << "OOP Card Initial Balance: Rs " << (oopCard.getBalancePaise() / 100) << ".00\n";
    
    std::cout << "Attempt 1 (Rs 36.00): ";
    if (oopCard.deduct(3600)) {
        std::cout << "Approved | Balance: Rs " << (oopCard.getBalancePaise() / 100) << ".00\n";
    } else {
        std::cout << "[DENIED] Invariant Rs 50.00 preserved! Current: Rs " << (oopCard.getBalancePaise() / 100) << ".00\n";
    }

    std::cout << "Attempt 2 (Rs 10.00): ";
    if (oopCard.deduct(1000)) {
        std::cout << "Approved | Balance: Rs " << (oopCard.getBalancePaise() / 100) << ".00\n";
    } else {
        std::cout << "[DENIED] Invariant Rs 50.00 preserved! Current: Rs " << (oopCard.getBalancePaise() / 100) << ".00\n";
    }

    std::cout << "\n[PASS] Object-Oriented encapsulation eliminates negative balance bugs completely!\n";
    return 0;
}
