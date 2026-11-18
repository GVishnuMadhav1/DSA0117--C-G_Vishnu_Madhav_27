/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 2: From Requirement to Hierarchy - Diamond Inheritance Resolution & Access Control
 */

#include <iostream>
#include <iomanip>
#include <string>

// ============================================================================
// COMPOSITION MEMBER CLASS: Fellowship (has-a relationship)
// ============================================================================

class Fellowship {
private:
    std::string grantor;
    double monthlyStipend;
    std::string grantCode;

public:
    Fellowship(const std::string& g, double stipend, const std::string& code)
        : grantor(g), monthlyStipend(stipend), grantCode(code) {}

    std::string getGrantor() const { return grantor; }
    double getStipend() const { return monthlyStipend; }
    std::string getCode() const { return grantCode; }

    void display() const {
        std::cout << "Grant: " << grantCode << " (" << grantor << ") @ Rs. "
                  << std::fixed << std::setprecision(2) << monthlyStipend << "/month";
    }
};

// ============================================================================
// DIAMOND HIERARCHY WITH VIRTUAL BASE CLASS
// ============================================================================

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n = "Unknown", int i = 0, const std::string& p = "0000000000")
        : name(n), id(i), phone(p) {
        std::cout << "[Constructor] Person initialized: " << name << " (ID: " << id << ")\n";
    }

    virtual ~Person() {
        std::cout << "[Destructor] ~Person destroyed: " << name << "\n";
    }

    std::string getName() const { return name; }
    int getId() const { return id; }
    std::string getPhone() const { return phone; }

    virtual void display() const {
        std::cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone;
    }
};

// Intermediate class: Student inheriting virtually from Person
class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {
        std::cout << "[Constructor] Student initialized: " << programme << " (CGPA: " << cgpa << ")\n";
    }

    ~Student() override {
        std::cout << "[Destructor] ~Student destroyed: " << programme << "\n";
    }

    void display() const override {
        Person::display();
        std::cout << " | Prog: " << programme << " | CGPA: " << cgpa;
    }
};

// Intermediate class: Staff inheriting virtually from Person
class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double sal)
        : Person(n, i, p), department(dept), salary(sal) {
        std::cout << "[Constructor] Staff initialized: " << department << " (Salary: " << salary << ")\n";
    }

    ~Staff() override {
        std::cout << "[Destructor] ~Staff destroyed: " << department << "\n";
    }

    void display() const override {
        Person::display();
        std::cout << " | Dept: " << department << " | Salary: Rs. " << salary;
    }
};

// Multiple Inheritance: TeachingAssistant inherits from Student and Staff
// Resolves diamond via virtual inheritance - calls Person constructor directly!
class TeachingAssistant : public Student, public Staff {
private:
    int teachingLoadHours;

public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double c,
                      const std::string& dept, double sal, int load)
        // Most-derived class must initialize the virtual base Person directly:
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, dept, sal),
          teachingLoadHours(load) {
        std::cout << "[Constructor] TeachingAssistant initialized: " << teachingLoadHours << " teaching hours\n";
    }

    ~TeachingAssistant() override {
        std::cout << "[Destructor] ~TeachingAssistant destroyed\n";
    }

    void display() const override {
        std::cout << "--- Teaching Assistant Profile ---\n";
        Person::display(); // Unambiguous direct access to Person!
        std::cout << "\nProgramme: " << programme << " | CGPA: " << cgpa
                  << " | Dept: " << department << " | Salary: Rs. " << salary
                  << " | Teaching Load: " << teachingLoadHours << " hrs/week\n";
    }
};

// Multilevel Inheritance + Composition: ResearchScholar is-a Student, has-a Fellowship
class ResearchScholar : public Student {
private:
    std::string researchDomain;
    Fellowship fellowship; // Member class (Composition: has-a)

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double c,
                    const std::string& domain,
                    const std::string& grantor, double stipend, const std::string& code)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          researchDomain(domain),
          fellowship(grantor, stipend, code) {
        std::cout << "[Constructor] ResearchScholar initialized in domain: " << researchDomain << "\n";
    }

    ~ResearchScholar() override {
        std::cout << "[Destructor] ~ResearchScholar destroyed\n";
    }

    void display() const override {
        std::cout << "--- Research Scholar Profile ---\n";
        Student::display();
        std::cout << "\nDomain: " << researchDomain << " | ";
        fellowship.display();
        std::cout << "\n";
    }
};

// ============================================================================
// VERIFICATION OF PREDICT-THE-OUTPUT CODE
// ============================================================================

namespace PredictVerify {
    struct PersonPred { PersonPred() { std::cout << "Person "; } };
    struct StudentPred : virtual PersonPred { StudentPred() { std::cout << "Student "; } };
    struct StaffPred : virtual PersonPred { StaffPred() { std::cout << "Staff "; } };
    struct TAPred : StudentPred, StaffPred { TAPred() { std::cout << "TA "; } };

    void testPrediction() {
        std::cout << "Output of Predict-the-Output Code: ";
        TAPred ta;
        std::cout << '\n';
    }
}

// ============================================================================
// MAIN EXECUTION DRIVER
// ============================================================================

int main() {
    std::cout << "====================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 2\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 2: University People Management & Diamond Inheritance\n";
    std::cout << "====================================================================\n\n";

    std::cout << ">>> 1. Predict-the-Output Verification:\n";
    PredictVerify::testPrediction();
    std::cout << "Explanation: With virtual inheritance, Person is constructed exactly once.\n\n";

    std::cout << ">>> 2. Instantiating TeachingAssistant (Demonstrating Single Person Subobject):\n";
    {
        TeachingAssistant ta("Vishnu Madhav", 192425192, "9876543210",
                              "B.Tech AI-ML", 9.42,
                              "Computer Science", 28000.0, 12);
        std::cout << "\nDisplaying TA Details (Direct unambiguous member access):\n";
        ta.display();
        std::cout << "\nDestruction Trace upon block exit:\n";
    }

    std::cout << "\n>>> 3. Instantiating ResearchScholar (Inheritance + Fellowship Composition):\n";
    {
        ResearchScholar rs("Niharika Sharma", 192472335, "9123456780",
                           "Ph.D AI & Robotics", 9.85,
                           "Reinforcement Learning for Autonomous Drones",
                           "DST-SERB", 35000.0, "DST-2026-AI-042");
        std::cout << "\nDisplaying Research Scholar Details:\n";
        rs.display();
        std::cout << "\nDestruction Trace upon block exit:\n";
    }

    std::cout << "====================================================================\n";
    return 0;
}
