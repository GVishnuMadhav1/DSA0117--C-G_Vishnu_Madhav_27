/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 1: Class Design Review - Diagnosing and Repairing Duplicated Payroll Classes
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

// ============================================================================
// REPAIRED DESIGN: Unified Abstract Base Class & Inheritance Hierarchy
// ============================================================================

class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(const std::string& empName, int empId)
        : name(empName), id(empId) {}

    virtual ~Staff() = default;

    std::string getName() const { return name; }
    int getId() const { return id; }

    // Pure virtual function enforcing polymorphic salary calculation
    virtual double pay() const = 0;

    // Polymorphic display function for standardized pay slip generation
    virtual void printSlip() const {
        std::cout << std::left << std::setw(8) << id
                  << std::setw(20) << name
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2) << pay()
                  << std::endl;
    }
};

// Intermediate class for staff receiving basic pay with Dearness Allowance (DA)
class SalariedStaff : public Staff {
protected:
    double basic;
    static constexpr double DA_RATE = 0.42; // Centralized constexpr constant (42% DA)

public:
    SalariedStaff(const std::string& empName, int empId, double basicPay)
        : Staff(empName, empId), basic(basicPay) {}

    double getBasic() const { return basic; }
    static constexpr double getDaRate() { return DA_RATE; }

    double pay() const override {
        return basic + (basic * DA_RATE);
    }
};

// Derived class for Professors with research allowance
class Professor : public SalariedStaff {
private:
    double research;

public:
    Professor(const std::string& empName, int empId, double basicPay, double researchAllowance)
        : SalariedStaff(empName, empId, basicPay), research(researchAllowance) {}

    double getResearch() const { return research; }

    double pay() const override {
        return SalariedStaff::pay() + research;
    }

    void printSlip() const override {
        std::cout << std::left << std::setw(8) << id
                  << std::setw(20) << (name + " (Prof)")
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2) << pay()
                  << "  [Basic: " << basic << ", DA: " << (basic * DA_RATE) << ", Research: " << research << "]"
                  << std::endl;
    }
};

// Derived class for Lab Assistants
class LabAssistant : public SalariedStaff {
public:
    LabAssistant(const std::string& empName, int empId, double basicPay)
        : SalariedStaff(empName, empId, basicPay) {}

    void printSlip() const override {
        std::cout << std::left << std::setw(8) << id
                  << std::setw(20) << (name + " (Lab Asst)")
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2) << pay()
                  << "  [Basic: " << basic << ", DA: " << (basic * DA_RATE) << "]"
                  << std::endl;
    }
};

// Derived class for Guest Faculty (hourly rate compensation)
class GuestFaculty : public Staff {
private:
    double hours;
    double rate;

public:
    GuestFaculty(const std::string& empName, int empId, double lectureHours, double hourlyRate)
        : Staff(empName, empId), hours(lectureHours), rate(hourlyRate) {}

    double getHours() const { return hours; }
    double getRate() const { return rate; }

    double pay() const override {
        return hours * rate;
    }

    void printSlip() const override {
        std::cout << std::left << std::setw(8) << id
                  << std::setw(20) << (name + " (Guest Fac)")
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2) << pay()
                  << "  [Hours: " << hours << ", Rate: " << rate << "]"
                  << std::endl;
    }
};

// ============================================================================
// EXECUTION & VALIDATION DRIVER
// ============================================================================

int main() {
    std::cout << "====================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 1\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 1: Class Design Review - Payroll Hierarchy & Polymorphism\n";
    std::cout << "====================================================================\n\n";

    // Polymorphic collection of staff members managed through base-class pointers
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Dr. R. Raman", 101, 75000.0, 15000.0));
    payroll.push_back(std::make_unique<LabAssistant>("Mr. K. Suresh", 205, 32000.0));
    payroll.push_back(std::make_unique<GuestFaculty>("Ms. A. Priya", 309, 45.0, 1200.0));
    payroll.push_back(std::make_unique<Professor>("Dr. M. Swaminathan", 104, 82000.0, 20000.0));

    std::cout << "--- Standardized Monthly Payroll Processing (Single Unified Loop) ---\n";
    std::cout << std::left << std::setw(8) << "Emp ID"
              << std::setw(20) << "Employee Name"
              << std::right << std::setw(14) << "Total Pay (Rs)"
              << "  Breakdown Details\n";
    std::cout << "--------------------------------------------------------------------\n";

    double grandTotal = 0.0;
    for (const auto& emp : payroll) {
        emp->printSlip();
        grandTotal += emp->pay();
    }

    std::cout << "--------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(28) << "Grand Total Payroll Disbursement:"
              << "Rs. " << std::fixed << std::setprecision(2) << grandTotal << "\n";
    std::cout << "====================================================================\n";

    return 0;
}
