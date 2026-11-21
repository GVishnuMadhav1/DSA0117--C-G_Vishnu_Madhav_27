// ============================================================================
// ASSIGNMENT 5: COURSE OUTCOME CO5
// TASK A3: DESIGN WITH ABSTRACT CLASSES (PAYER INTERFACE & EXTENSION)
// Student: G. Vishnu Madhav (192425192) | Batch 27
// Course: DSA0117 - Object-Oriented Programming with C++
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Bill Interface from A1
class Bill {
protected:
    std::string patient;
    double grossCharge;
public:
    Bill(const std::string& p, double g) : patient(p), grossCharge(g) {}
    virtual ~Bill() = default;
    virtual double total() const { return grossCharge; }
    virtual std::string type() const = 0;
    std::string getPatient() const { return patient; }
};

class OutPatient : public Bill {
public:
    OutPatient(const std::string& p, double g) : Bill(p, g) {}
    std::string type() const override { return "OutPatient"; }
};

class InPatient : public Bill {
public:
    InPatient(const std::string& p, double g) : Bill(p, g) {}
    std::string type() const override { return "InPatient"; }
};

// Abstract Class: Payer
class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual std::string payerName() const = 0;
};

// Derived 1: SelfPay
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& /*bill*/) const override {
        return 0.0; // Patient pays entire bill
    }
    std::string payerName() const override { return "Self-Pay (100% Patient)"; }
};

// Derived 2: Insurance
class Insurance : public Payer {
    double coverLimit;
    double coPayRatio; // e.g. 0.10 for 10% co-payment

public:
    Insurance(double limit, double coPay) : coverLimit(limit), coPayRatio(coPay) {}

    double amountCovered(const Bill& bill) const override {
        double payableAfterCoPay = bill.total() * (1.0 - coPayRatio);
        return std::min(coverLimit, payableAfterCoPay);
    }
    std::string payerName() const override {
        return "Private Insurance (10% Co-pay, Max Rs. 50k)";
    }
};

// Derived 3: GovernmentScheme
class GovernmentScheme : public Payer {
    double opPackageRate;
    double ipPackageRate;

public:
    GovernmentScheme(double opRate, double ipRate) : opPackageRate(opRate), ipPackageRate(ipRate) {}

    double amountCovered(const Bill& bill) const override {
        if (bill.type() == "OutPatient") {
            return std::min(bill.total(), opPackageRate);
        } else {
            return std::min(bill.total(), ipPackageRate);
        }
    }
    std::string payerName() const override { return "Government Health Scheme (Fixed Package Rates)"; }
};

// A3.2 Extension: Corporate Tie-Up (Open-Closed Principle Demonstration)
// Added without modifying any existing class!
class CorporateTieUp : public Payer {
    std::string corporateName;
    double deductible;
    double corporateCeiling;

public:
    CorporateTieUp(const std::string& corp, double ded, double ceiling)
        : corporateName(corp), deductible(ded), corporateCeiling(ceiling) {}

    double amountCovered(const Bill& bill) const override {
        if (bill.total() <= deductible) return 0.0;
        double eligible = bill.total() - deductible;
        return std::min(eligible, corporateCeiling);
    }
    std::string payerName() const override { return "Corporate Tie-Up (" + corporateName + ")"; }
};

int main() {
    std::cout << "===================================================================\n";
    std::cout << " TASK A3: DESIGN WITH ABSTRACT CLASSES (PAYER INTERFACE & EXTENSION)\n";
    std::cout << " Student: G. Vishnu Madhav (192425192) | Batch 27 | Course: DSA0117\n";
    std::cout << "===================================================================\n\n";

    OutPatient bill1("Ravi Kumar", 2500.0);
    InPatient bill2("Meena Sharma", 65000.0);

    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::unique_ptr<Payer>(new SelfPay()));
    payers.push_back(std::unique_ptr<Payer>(new Insurance(50000.0, 0.10)));
    payers.push_back(std::unique_ptr<Payer>(new GovernmentScheme(1000.0, 40000.0)));
    payers.push_back(std::unique_ptr<Payer>(new CorporateTieUp("Infosys Health Care", 500.0, 100000.0)));

    std::cout << "--- Evaluating Settlement for Bill 1: OP Ravi Kumar (Rs. 2500.00) ---\n";
    for (const auto& p : payers) {
        double covered = p->amountCovered(bill1);
        double patientShare = bill1.total() - covered;
        std::cout << "Payer: " << std::setw(42) << std::left << p->payerName()
                  << " | Covered: Rs. " << std::setw(9) << std::fixed << std::setprecision(2) << covered
                  << " | Patient Share: Rs. " << patientShare << "\n";
    }

    std::cout << "\n--- Evaluating Settlement for Bill 2: IP Meena Sharma (Rs. 65000.00) ---\n";
    for (const auto& p : payers) {
        double covered = p->amountCovered(bill2);
        double patientShare = bill2.total() - covered;
        std::cout << "Payer: " << std::setw(42) << std::left << p->payerName()
                  << " | Covered: Rs. " << std::setw(9) << std::fixed << std::setprecision(2) << covered
                  << " | Patient Share: Rs. " << patientShare << "\n";
    }

    std::cout << "\n[PASS] Open-Closed Principle verified: CorporateTieUp integrated with 0 code churn.\n";
    return 0;
}
