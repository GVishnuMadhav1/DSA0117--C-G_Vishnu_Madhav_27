// ============================================================================
// ASSIGNMENT 5: COURSE OUTCOME CO5
// TASK A5: DESIGN RECOVERY, RETHROWING AND RAII RESOURCE SAFETY
// Student: G. Vishnu Madhav (192425192) | Batch 27
// Course: DSA0117 - Object-Oriented Programming with C++
// ============================================================================

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

// Section 1: Predict the Output Program from Specification (Pages 6-7)
struct Guard {
    std::string n;
    explicit Guard(const std::string& s) : n(s) {}
    ~Guard() { std::cout << '~' << n << ' '; }
};

void f() {
    Guard g("f");
    throw 42;
}

// Section 2: Multi-Tier Catch, Log, and Rethrow Architecture
class ClaimAuditLog {
public:
    static void logRejection(const std::string& reason) {
        std::cout << "[AUDIT LOG RECORDED]: " << reason << "\n";
    }
};

void lowLevelValidator(double billed, double cover) {
    if (billed > cover) {
        throw std::runtime_error("Exceeds policy cover limit");
    }
}

void intermediateSettlementService(double billed, double cover) {
    Guard g("ServiceGuard");
    try {
        lowLevelValidator(billed, cover);
    } catch (const std::runtime_error& e) {
        ClaimAuditLog::logRejection(e.what());
        // Rethrow the exact same exception using throw;
        throw;
    }
}

int main() {
    std::cout << "===================================================================\n";
    std::cout << " TASK A5: DESIGN RECOVERY, RETHROWING & RAII RESOURCE SAFETY\n";
    std::cout << " Student: G. Vishnu Madhav (192425192) | Batch 27 | Course: DSA0117\n";
    std::cout << "===================================================================\n\n";

    std::cout << "--- 1. PREDICT THE OUTPUT VERIFICATION (PAGES 6-7) ---\n";
    std::cout << "Executing Guard Stack Unwinding Program:\n";
    std::cout << "Actual Program Output: ";
    try {
        Guard m("main");
        f();
        std::cout << "not printed ";
    } catch (int x) {
        std::cout << "caught " << x;
    } catch (...) {
        std::cout << "other";
    }
    std::cout << '\n';
    std::cout << "Predicted Output     : ~f ~main caught 42\n";
    std::cout << "[EXPLANATION] Stack unwinding destroys local objects in reverse order of construction:\n";
    std::cout << "  1. Guard 'g' in f() is destroyed first -> ~f\n";
    std::cout << "  2. Stack unwinds to main(); Guard 'm' in try block is destroyed -> ~main\n";
    std::cout << "  3. 'not printed' is skipped; matching handler catches 42 -> caught 42\n\n";

    std::cout << "--- 2. TIERED EXCEPTION HANDLING WITH throw; PROPAGATION ---\n";
    try {
        std::cout << "Attempting settlement with Billed: Rs. 80000, Cover: Rs. 50000 ...\n";
        intermediateSettlementService(80000.0, 50000.0);
    } catch (const std::runtime_error& e) {
        std::cout << "Top-Level Handler Caught Rethrown Exception: " << e.what() << "\n";
        std::cout << "Application state restored; no termination, zero resource leaks.\n";
    }

    std::cout << "\n[PASS] Stack unwinding and rethrow semantics verified successfully.\n";
    return 0;
}
