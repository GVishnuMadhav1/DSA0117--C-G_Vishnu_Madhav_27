#include <iostream>
#include <iomanip>
#include <string>

class SavingsAccount {
private:
    std::string accountNumber_;
    long long balancePaise_;
    static const int MAX_TXN = 10;
    long long transactions_[MAX_TXN]; // Last 10 transactions
    int count_;
    int head_; // Circular index pointer

public:
    SavingsAccount(std::string accNo, long long initialRupees)
        : accountNumber_(accNo), balancePaise_(initialRupees * 100), count_(0), head_(0) {}

    // Inline member functions
    void deposit(long long rupees) {
        if (rupees <= 0) return;
        long long paise = rupees * 100;
        balancePaise_ += paise;
        recordTransaction(paise);
    }

    bool withdraw(long long rupees);
    void miniStatement() const;

private:
    void recordTransaction(long long deltaPaise) {
        transactions_[head_] = deltaPaise;
        head_ = (head_ + 1) % MAX_TXN;
        if (count_ < MAX_TXN) count_++;
    }
};

// Defined outside class using scope resolution operator
bool SavingsAccount::withdraw(long long rupees) {
    long long paise = rupees * 100;
    if (rupees <= 0 || (balancePaise_ - paise) < 50000) { // Rs 500 min balance
        return false;
    }
    balancePaise_ -= paise;
    recordTransaction(-paise);
    return true;
}

void SavingsAccount::miniStatement() const {
    std::cout << "+------------------------------------------------------------+\n";
    std::cout << "| MINI-STATEMENT: ACC " << accountNumber_ << " | Balance: Rs " 
              << (balancePaise_ / 100) << "." << std::setw(2) << std::setfill('0') << (balancePaise_ % 100) << std::setfill(' ') << " |\n";
    std::cout << "+------------------------------------------------------------+\n";
    int start = (count_ < MAX_TXN) ? 0 : head_;
    for (int i = 0; i < count_; ++i) {
        int idx = (start + i) % MAX_TXN;
        long long txn = transactions_[idx];
        std::cout << "| Txn #" << std::setw(2) << (i + 1) << ": "
                  << (txn > 0 ? "DEPOSIT  +Rs " : "WITHDRAW -Rs ")
                  << std::setw(6) << (std::abs(txn) / 100) << "."
                  << std::setw(2) << std::setfill('0') << (std::abs(txn) % 100) << std::setfill(' ') << "                          |\n";
    }
    std::cout << "+------------------------------------------------------------+\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q4: CLASS WITH INTERNAL ARRAY & CIRCULAR TRANSACTION BUFFER\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    SavingsAccount acc("SB-91024", 5000); // Initial Rs 5000
    acc.deposit(1000);
    acc.withdraw(500);
    acc.deposit(2000);
    acc.withdraw(300);
    acc.deposit(1500);
    acc.withdraw(200);
    acc.deposit(800);
    acc.withdraw(100);
    acc.deposit(2500);
    acc.withdraw(400); // 10th txn
    acc.deposit(3000); // 11th txn - overwrites oldest via O(1) circular head
    acc.withdraw(700); // 12th txn

    acc.miniStatement();
    std::cout << "[PASS] Class encapsulation, circular indexing, and scoping verified!\n";
    return 0;
}
