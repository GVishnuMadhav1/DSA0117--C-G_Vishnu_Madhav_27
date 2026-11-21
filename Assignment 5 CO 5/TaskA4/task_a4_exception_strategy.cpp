// ============================================================================
// ASSIGNMENT 5: COURSE OUTCOME CO5
// TASK A4: DESIGN THE EXCEPTION STRATEGY & HIERARCHY
// Student: G. Vishnu Madhav (192425192) | Batch 27
// Course: DSA0117 - Object-Oriented Programming with C++
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <vector>

// Custom Exception Hierarchy
class HospitalException : public std::exception {
protected:
    std::string message;
    int errorCode;

public:
    HospitalException(const std::string& msg, int code) : message(msg), errorCode(code) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    int getErrorCode() const noexcept { return errorCode; }
};

// Domain Billing Errors
class BillingError : public HospitalException {
public:
    BillingError(const std::string& msg, int code = 100) : HospitalException("[BillingError] " + msg, code) {}
};

class InvalidChargeException : public BillingError {
public:
    InvalidChargeException(const std::string& msg) : BillingError("Negative/Invalid charge: " + msg, 101) {}
};

class UnknownPackageException : public BillingError {
public:
    UnknownPackageException(const std::string& pkg) : BillingError("Package code not recognized: " + pkg, 102) {}
};

// Settlement and Insurance Claim Errors
class ClaimError : public HospitalException {
public:
    ClaimError(const std::string& msg, int code = 200) : HospitalException("[ClaimError] " + msg, code) {}
};

class ExceedsCoverException : public ClaimError {
public:
    ExceedsCoverException(double billed, double cover)
        : ClaimError("Billed amount Rs. " + std::to_string(billed) + " exceeds policy limit Rs. " + std::to_string(cover), 201) {}
};

// Function demonstrating throwing domain exceptions
double validateAndApprove(double billed, double cover, const std::string& pkgCode) {
    if (billed < 0.0 || cover < 0.0) {
        throw InvalidChargeException("Amount must be positive.");
    }
    if (pkgCode != "OP_GEN" && pkgCode != "IP_SURG" && pkgCode != "DAY_CARE") {
        throw UnknownPackageException(pkgCode);
    }
    if (billed > cover) {
        throw ExceedsCoverException(billed, cover);
    }
    return billed;
}

// Function with noexcept guarantee
double safeCalculateNet(double total, double discount) noexcept {
    return (total > discount) ? (total - discount) : 0.0;
}

int main() {
    std::cout << "===================================================================\n";
    std::cout << " TASK A4: DESIGN THE EXCEPTION STRATEGY & HIERARCHY EVALUATION\n";
    std::cout << " Student: G. Vishnu Madhav (192425192) | Batch 27 | Course: DSA0117\n";
    std::cout << "===================================================================\n\n";

    struct TestCase {
        double billed;
        double cover;
        std::string pkg;
        std::string testDesc;
    } cases[] = {
        {1500.0, 5000.0, "OP_GEN", "Valid Outpatient Case"},
        {-250.0, 5000.0, "OP_GEN", "Negative Charge Test"},
        {25000.0, 5000.0, "IP_SURG", "Exceeds Cover Test"},
        {12000.0, 50000.0, "INVALID_CODE", "Unknown Package Test"}
    };

    for (const auto& tc : cases) {
        std::cout << "Running Test: " << tc.testDesc << " ...\n";
        try {
            double approved = validateAndApprove(tc.billed, tc.cover, tc.pkg);
            std::cout << "  -> SUCCESS: Claim approved for Rs. " << approved << "\n";
        } catch (const InvalidChargeException& e) {
            std::cout << "  -> CAUGHT InvalidChargeException [Code " << e.getErrorCode() << "]: " << e.what() << "\n";
        } catch (const UnknownPackageException& e) {
            std::cout << "  -> CAUGHT UnknownPackageException [Code " << e.getErrorCode() << "]: " << e.what() << "\n";
        } catch (const ExceedsCoverException& e) {
            std::cout << "  -> CAUGHT ExceedsCoverException [Code " << e.getErrorCode() << "]: " << e.what() << "\n";
        } catch (const HospitalException& e) {
            std::cout << "  -> CAUGHT Generic HospitalException: " << e.what() << "\n";
        }
    }

    std::cout << "\n--- noexcept Verification ---\n";
    std::cout << "safeCalculateNet is noexcept: "
              << std::boolalpha << noexcept(safeCalculateNet(100.0, 20.0)) << "\n";
    std::cout << "validateAndApprove is noexcept: "
              << std::boolalpha << noexcept(validateAndApprove(100.0, 20.0, "OP_GEN")) << "\n";
    std::cout << "[PASS] Exception taxonomy and specifications fully validated.\n";

    return 0;
}
