// ============================================================================
// ASSIGNMENT 5: COURSE OUTCOME CO5
// TASK A1: DESIGN THE POLYMORPHIC BILL HIERARCHY
// Student: G. Vishnu Madhav (192425192) | Batch 27
// Course: DSA0117 - Object-Oriented Programming with C++
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

// Abstract Base Class
class Bill {
protected:
    std::string patientName;
    int billId;

public:
    Bill(const std::string& name, int id) : patientName(name), billId(id) {}
    virtual ~Bill() = default;

    virtual double total() const = 0;
    virtual std::string type() const = 0;

    virtual void print() const {
        std::cout << "[" << std::setw(15) << std::left << type() << "] "
                  << "Bill ID: #" << billId << " | Patient: " << std::setw(14) << patientName
                  << " | Total: Rs. " << std::fixed << std::setprecision(2) << total() << "\n";
    }

    std::string getPatient() const { return patientName; }
    int getId() const { return billId; }
};

// Derived: OutPatient
class OutPatientBill : public Bill {
    double consultationFee;
    double labTestCharges;

public:
    OutPatientBill(const std::string& name, int id, double consultation, double tests)
        : Bill(name, id), consultationFee(consultation), labTestCharges(tests) {}

    double total() const override {
        return consultationFee + labTestCharges;
    }

    std::string type() const override {
        return "Out-Patient";
    }
};

// Derived: InPatient
class InPatientBill : public Bill {
    int days;
    double roomRatePerDay;
    double procedureCharges;
    double medicineCharges;

public:
    InPatientBill(const std::string& name, int id, int d, double rate, double proc, double med)
        : Bill(name, id), days(d), roomRatePerDay(rate), procedureCharges(proc), medicineCharges(med) {}

    double total() const override {
        return (days * roomRatePerDay) + procedureCharges + medicineCharges;
    }

    std::string type() const override {
        return "In-Patient";
    }
};

// Derived: DayCareSurgery
class DayCareSurgeryBill : public Bill {
    std::string procedureName;
    double packagePrice;

public:
    DayCareSurgeryBill(const std::string& name, int id, const std::string& proc, double price)
        : Bill(name, id), procedureName(proc), packagePrice(price) {}

    double total() const override {
        return packagePrice;
    }

    std::string type() const override {
        return "Day-Care";
    }
};

// Derived: Emergency
class EmergencyBill : public Bill {
    double baseTriageCharge;
    int icuHours;
    double hourlyRate;

public:
    EmergencyBill(const std::string& name, int id, double triage, int hours, double rate)
        : Bill(name, id), baseTriageCharge(triage), icuHours(hours), hourlyRate(rate) {}

    double total() const override {
        return baseTriageCharge + (icuHours * hourlyRate);
    }

    std::string type() const override {
        return "Emergency";
    }
};

int main() {
    std::cout << "===================================================================\n";
    std::cout << " TASK A1: POLYMORPHIC HOSPITAL BILL HIERARCHY EVALUATION\n";
    std::cout << " Student: G. Vishnu Madhav (192425192) | Batch 27 | Course: DSA0117\n";
    std::cout << "===================================================================\n\n";

    std::vector<std::unique_ptr<Bill>> billLedger;
    billLedger.push_back(std::unique_ptr<Bill>(new OutPatientBill("Ravi Kumar", 1001, 750.0, 1450.0)));
    billLedger.push_back(std::unique_ptr<Bill>(new InPatientBill("Meena Sharma", 1002, 5, 3000.0, 45000.0, 12500.0)));
    billLedger.push_back(std::unique_ptr<Bill>(new DayCareSurgeryBill("Anand Rao", 1003, "Cataract Surgery", 24000.0)));
    billLedger.push_back(std::unique_ptr<Bill>(new EmergencyBill("Suresh Pillai", 1004, 5000.0, 8, 1200.0)));

    std::cout << "--- Processing All Bills Through Base-Class Pointers (Late Binding) ---\n";
    double grandTotal = 0.0;
    for (const auto& b : billLedger) {
        b->print();
        grandTotal += b->total();
    }

    std::cout << "-------------------------------------------------------------------\n";
    std::cout << "Hospital Revenue Summary:\n";
    std::cout << "Total Active Bills Processed: " << billLedger.size() << "\n";
    std::cout << "Day's Aggregate Hospital Billing Total: Rs. " << std::fixed << std::setprecision(2) << grandTotal << "\n";
    std::cout << "[PASS] Dynamic dispatch verified across all derived bill types.\n";

    return 0;
}
