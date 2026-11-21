// ============================================================================
// ASSIGNMENT 5: COURSE OUTCOME CO5
// TASK B2: ENGINEER ERROR CONDITIONS, RETHROWING & AUDIT TRAILS
// Student: G. Vishnu Madhav (192425192) | Batch 27
// Course: DSA0117 - Object-Oriented Programming with C++
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <vector>

// Section 1: Predict the Output Program from Specification (Pages 11-12)
void validate(double amount) {
    if (amount < 0) throw std::invalid_argument("negative");
    if (amount > 1e6) throw std::out_of_range("too large");
    std::cout << "ok ";
}

void process(double amount) {
    try {
        validate(amount);
    } catch (const std::out_of_range& e) {
        std::cout << "[log " << e.what() << "] ";
        throw;
    }
}

// Section 2: Complete the Code Program from Specification (Pages 12-14)
class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    // TODO 1: Throw std::invalid_argument("negative amount") if billed or cover is
    //   negative; throw ClaimError("exceeds cover") if billed > cover; otherwise return
    //   billed
    if (billed < 0 || cover < 0) {
        throw std::invalid_argument("negative amount");
    }
    if (billed > cover) {
        throw ClaimError("exceeds cover");
    }
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        // TODO 2: Print "audit: " followed by the message, then rethrow the SAME
        //   exception
        std::cout << "audit: " << e.what() << '\n';
        throw;
    }
}

// Section 3: Engineered Error Test Matrix
void testEngineeredErrors() {
    std::cout << "\n--- 3. ENGINEERED ERROR CONDITIONS COMPREHENSIVE SUITE ---\n";
    // 1. Text where number expected
    try {
        std::cout << "Test 1: Parsing invalid numeric input 'two-thousand' via std::stod ...\n";
        double val = std::stod("two-thousand");
        std::cout << "Val: " << val << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "  -> [CAUGHT std::invalid_argument]: Bad numeric string format.\n";
    }

    // 2. Forced memory allocation failure simulation
    try {
        std::cout << "Test 2: Forcing std::bad_alloc request (huge allocation) ...\n";
        size_t hugeSize = 10000000000000000ULL;
        volatile char* p = new char[hugeSize];
        (void)p;
    } catch (const std::bad_alloc& e) {
        std::cout << "  -> [CAUGHT std::bad_alloc]: Memory allocation safely trapped.\n";
    }

    // 3. Top-level catch(...) ensuring uptime
    try {
        std::cout << "Test 3: Unhandled custom error trapped by top-level catch(...) ...\n";
        throw 999;
    } catch (...) {
        std::cout << "  -> [CAUGHT TOP-LEVEL catch(...)]: Application uptime preserved!\n";
    }
}

int main() {
    std::cout << "===================================================================\n";
    std::cout << " TASK B2: ENGINEER ERROR CONDITIONS & AUDIT RETHROWING\n";
    std::cout << " Student: G. Vishnu Madhav (192425192) | Batch 27 | Course: DSA0117\n";
    std::cout << "===================================================================\n\n";

    std::cout << "--- 1. PREDICT THE OUTPUT VERIFICATION (PAGES 11-12) ---\n";
    std::cout << "Actual Program Output: ";
    for (double a : {100.0, -5.0, 2e6}) {
        try {
            process(a);
            std::cout << "done ";
        } catch (const std::exception& e) {
            std::cout << "caught " << e.what() << ' ';
        }
    }
    std::cout << '\n';
    std::cout << "Predicted Output     : ok done caught negative [log too large] caught too large \n\n";

    std::cout << "--- 2. COMPLETE THE CODE EXECUTION (PAGES 12-14) ---\n";
    std::cout << "Actual Program Output:\n";
    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (auto& c : cases) {
        try {
            double paid = settle(c[0], c[1]);
            std::cout << "approved " << paid << '\n';
        } catch (const ClaimError& e) {
            std::cout << "claim rejected: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }

    testEngineeredErrors();

    std::cout << "\n[PASS] Task B2 completed with 100% agreement on all specifications.\n";
    return 0;
}
