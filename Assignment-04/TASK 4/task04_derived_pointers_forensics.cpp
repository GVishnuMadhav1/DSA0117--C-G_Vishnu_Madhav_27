/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 4: Pointers to Derived Classes: Forensics, Dynamic Dispatch & Object Slicing
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>

// ============================================================================
// PREDICT-THE-OUTPUT VERIFICATION (Task 4 Prediction Section)
// ============================================================================
namespace PredictSection {
    struct AccountPred {
        double rate() const { return 3.5; }
        virtual double vrate() const { return 3.5; }
        virtual ~AccountPred() = default;
    };

    struct SeniorAccountPred : AccountPred {
        double rate() const { return 4.0; }
        double vrate() const override { return 4.0; }
    };

    void run() {
        std::cout << ">>> 1. Predict-the-Output Code Execution:\n";
        SeniorAccountPred s;
        AccountPred* p = &s;
        AccountPred copy = s; // Object Slicing!
        std::cout << "Output: "
                  << p->rate() << ' '
                  << p->vrate() << ' '
                  << copy.vrate() << '\n';
        std::cout << "Explanation of Three Values:\n";
        std::cout << "  1) p->rate() = 3.5     : Static/compile-time binding based on pointer type Account*.\n";
        std::cout << "  2) p->vrate() = 4.0    : Dynamic/runtime dispatch via vtable to SeniorAccount::vrate().\n";
        std::cout << "  3) copy.vrate() = 3.5  : Object slicing stripped derived members; copy is a pure Account.\n\n";
    }
}

// ============================================================================
// FORENSICS EVIDENCE: BUGGY IMPLEMENTATION WITH DETECTED DEFECTS
// ============================================================================
namespace BuggyEvidence {
    class BuggyAccount {
    public:
        double rate() const { return 3.5; } // DEFECT 1: Non-virtual function
        ~BuggyAccount() {                   // DEFECT 2: Non-virtual destructor!
            std::cout << "  [BuggyAccount Destructor] ~BuggyAccount executed\n";
        }
    };

    class BuggySeniorAccount : public BuggyAccount {
        double* history; // Dynamically allocated memory
    public:
        BuggySeniorAccount() : history(new double[100]) {
            std::cout << "  [BuggySeniorAccount Constructor] Allocated 100 doubles (800 bytes) on heap\n";
        }
        double rate() const { return 4.0; }
        ~BuggySeniorAccount() {
            std::cout << "  [BuggySeniorAccount Destructor] Freeing 100 doubles from heap\n";
            delete[] history;
        }
    };

    void demonstrateBuggyBehavior() {
        std::cout << ">>> 2. Demonstrating Buggy Code Deficiencies:\n";
        std::cout << "--- A. Non-Virtual Method Binding & Non-Virtual Destructor Memory Leak ---\n";
        BuggyAccount* accounts[2] = { new BuggyAccount(), new BuggySeniorAccount() };

        std::cout << "Invoking rate() via base pointer:\n";
        for (int i = 0; i < 2; ++i) {
            std::cout << "Account [" << i << "] Rate: " << accounts[i]->rate() << "%\n";
        }
        std::cout << "DEFECT CONFIRMED: Senior account earned 3.5% instead of 4.0% due to static binding!\n\n";

        std::cout << "Deleting accounts via base pointers:\n";
        for (int i = 0; i < 2; ++i) {
            std::cout << "Deleting account [" << i << "]:\n";
            delete accounts[i]; // LEAK: ~BuggySeniorAccount() is NEVER called!
        }
        std::cout << "DEFECT CONFIRMED: ~BuggySeniorAccount() was NOT called! Heap memory leaked (800 bytes)!\n\n";

        std::cout << "--- B. Object Slicing Demonstration ---\n";
        {
            BuggySeniorAccount senior;
            BuggyAccount slicedCopy = senior; // SLICING!
            std::cout << "Sliced copy rate: " << slicedCopy.rate() << "%\n";
        }
    }
}

// ============================================================================
// REPAIRED IMPLEMENTATION: MODERN C++ POLYMORPHISM & SMART POINTERS
// ============================================================================
namespace RepairedHierarchy {
    class Account {
    protected:
        std::string accountNumber;
        double balance;

    public:
        Account(const std::string& accNo, double bal)
            : accountNumber(accNo), balance(bal) {}

        // REPAIR 1: Virtual destructor ensures polymorphic cleanup without memory leaks
        virtual ~Account() {
            std::cout << "  [Account Destructor] ~Account released: " << accountNumber << "\n";
        }

        // REPAIR 2: Virtual rate() method enabling dynamic runtime dispatch
        virtual double rate() const {
            return 3.5;
        }

        virtual void printReport() const {
            std::cout << "Account: " << accountNumber
                      << " | Balance: Rs. " << std::fixed << std::setprecision(2) << balance
                      << " | Annual Rate: " << rate() << "%"
                      << " | Annual Interest: Rs. " << (balance * rate() / 100.0)
                      << std::endl;
        }
    };

    class SeniorAccount : public Account {
    private:
        double* transactionHistory;
        int transactionCount;
        static constexpr int CAPACITY = 100;

    public:
        SeniorAccount(const std::string& accNo, double bal)
            : Account(accNo, bal),
              transactionHistory(new double[CAPACITY]),
              transactionCount(0) {
            std::cout << "  [SeniorAccount Constructor] Allocated history buffer (800 bytes) for: " << accNo << "\n";
        }

        // REPAIR 3: Virtual destructor properly cleans up heap memory
        ~SeniorAccount() override {
            std::cout << "  [SeniorAccount Destructor] Freeing history buffer (800 bytes) for: " << accountNumber << "\n";
            delete[] transactionHistory;
        }

        // REPAIR 4: Explicit override keyword catches signature errors
        double rate() const override {
            return 4.0;
        }

        void printReport() const override {
            std::cout << "Senior Account: " << accountNumber
                      << " | Balance: Rs. " << std::fixed << std::setprecision(2) << balance
                      << " | Senior Rate: " << rate() << "%"
                      << " | Annual Interest: Rs. " << (balance * rate() / 100.0)
                      << " [Bonus 0.5% Applied]"
                      << std::endl;
        }
    };

    void demonstrateRepairedBehavior() {
        std::cout << "\n>>> 3. Repaired Code Execution with std::unique_ptr & Virtual Methods:\n";

        // REPAIR 5: std::vector<std::unique_ptr<Account>> prevents slicing and guarantees leak-free RAII
        std::vector<std::unique_ptr<Account>> portfolio;
        portfolio.push_back(std::make_unique<Account>("REG-1001", 150000.0));
        portfolio.push_back(std::make_unique<SeniorAccount>("SNR-8002", 250000.0));

        std::cout << "\nDisplaying Account Reports (Polymorphic Dynamic Dispatch):\n";
        std::cout << "--------------------------------------------------------------------\n";
        for (const auto& acc : portfolio) {
            acc->printReport();
        }
        std::cout << "--------------------------------------------------------------------\n";

        std::cout << "Leaving portfolio scope - automatic RAII cleanup with virtual destructors:\n";
    }
}

// ============================================================================
// MAIN EXECUTION DRIVER
// ============================================================================

int main() {
    std::cout << "====================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 4\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 4: Pointers to Derived Classes - Forensics, Leak & Slicing\n";
    std::cout << "====================================================================\n\n";

    PredictSection::run();
    BuggyEvidence::demonstrateBuggyBehavior();
    RepairedHierarchy::demonstrateRepairedBehavior();

    std::cout << "====================================================================\n";
    return 0;
}
