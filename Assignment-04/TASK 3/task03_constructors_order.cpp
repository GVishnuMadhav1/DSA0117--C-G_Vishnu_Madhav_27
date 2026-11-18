/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 3: Constructors in Derived Classes and Member Classes - Construction & Destruction Ordering
 */

#include <iostream>
#include <string>

// ============================================================================
// PREDICT-THE-OUTPUT VERIFICATION
// ============================================================================
namespace Task3Predict {
    struct Engine {
        Engine() { std::cout << "Engine "; }
        ~Engine() { std::cout << "~Engine "; }
    };

    struct Vehicle {
        Vehicle() { std::cout << "Vehicle "; }
        ~Vehicle() { std::cout << "~Vehicle "; }
    };

    struct Car : Vehicle {
        Engine e;
        Car() { std::cout << "Car "; }
        ~Car() { std::cout << "~Car "; }
    };

    void run() {
        std::cout << "Predicted vs Actual Output: ";
        {
            Car c;
            std::cout << "| ";
        }
        std::cout << '\n';
    }
}

// ============================================================================
// COMPLETE-THE-CODE VERIFICATION (TODO 1)
// ============================================================================
namespace Task3CompleteCode {
    class PersonBase {
    protected:
        std::string name;
        int age;
    public:
        PersonBase(const std::string& n, int a) : name(n), age(a) {}
    };

    class Address {
        std::string city;
        int pin;
    public:
        Address(const std::string& c, int p) : city(c), pin(p) {}
        std::string str() const { return city + "-" + std::to_string(pin); }
    };

    class StudentDerived : public PersonBase {
        long long regNo;
        Address home;
    public:
        // TODO 1: Initialise PersonBase, regNo and home Address member in initializer list
        StudentDerived(const std::string& n, int a, long long r, const std::string& c, int p)
            : PersonBase(n, a), regNo(r), home(c, p) {}

        void print() const {
            std::cout << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
        }
    };

    void run() {
        std::cout << "Complete-the-Code Execution Result: ";
        StudentDerived s("Kavya", 19, 192311001, "Salem", 636001);
        s.print();
    }
}

// ============================================================================
// MEMBER CLASSES & CONSTRUCTION ORDER TRACING (Tasks 3.1, 3.2, 3.3)
// ============================================================================

class AddressMember {
private:
    std::string city;
    int pincode;
public:
    AddressMember(const std::string& c = "Chennai", int p = 600077)
        : city(c), pincode(p) {
        std::cout << "  [Construct] AddressMember: " << city << "-" << pincode << "\n";
    }
    ~AddressMember() {
        std::cout << "  [Destroy] ~AddressMember: " << city << "\n";
    }
    std::string getAddress() const { return city + " (" + std::to_string(pincode) + ")"; }
};

class CourseMember {
private:
    std::string courseCode;
    std::string title;
public:
    CourseMember(const std::string& code = "DSA0117", const std::string& t = "OOP with C++")
        : courseCode(code), title(t) {
        std::cout << "  [Construct] CourseMember: " << courseCode << " - " << title << "\n";
    }
    ~CourseMember() {
        std::cout << "  [Destroy] ~CourseMember: " << courseCode << "\n";
    }
    std::string getCourse() const { return courseCode + ": " + title; }
};

class PersonTraced {
protected:
    std::string name;
    AddressMember addr; // Member class (Composition)
public:
    PersonTraced(const std::string& n, const std::string& c, int p)
        : name(n), addr(c, p) {
        std::cout << " [Construct] PersonTraced: " << name << "\n";
    }
    virtual ~PersonTraced() {
        std::cout << " [Destroy] ~PersonTraced: " << name << "\n";
    }
};

class StudentTraced : virtual public PersonTraced {
protected:
    long long regNo;
    CourseMember enrolledCourse; // Member class (Composition)
public:
    StudentTraced(const std::string& n, const std::string& c, int p,
                  long long r, const std::string& cCode, const std::string& cTitle)
        : PersonTraced(n, c, p), regNo(r), enrolledCourse(cCode, cTitle) {
        std::cout << " [Construct] StudentTraced: Reg " << regNo << "\n";
    }
    ~StudentTraced() override {
        std::cout << " [Destroy] ~StudentTraced: Reg " << regNo << "\n";
    }
};

class StaffTraced : virtual public PersonTraced {
protected:
    std::string dept;
public:
    StaffTraced(const std::string& n, const std::string& c, int p, const std::string& d)
        : PersonTraced(n, c, p), dept(d) {
        std::cout << " [Construct] StaffTraced: Dept " << dept << "\n";
    }
    ~StaffTraced() override {
        std::cout << " [Destroy] ~StaffTraced: Dept " << dept << "\n";
    }
};

class TATraced : public StudentTraced, public StaffTraced {
private:
    int hours;
public:
    TATraced(const std::string& n, const std::string& c, int p,
             long long r, const std::string& cCode, const std::string& cTitle,
             const std::string& d, int h)
        // Most-derived class MUST call the virtual base constructor directly!
        : PersonTraced(n, c, p),
          StudentTraced(n, c, p, r, cCode, cTitle),
          StaffTraced(n, c, p, d),
          hours(h) {
        std::cout << " [Construct] TATraced: " << hours << " hrs\n";
    }
    ~TATraced() override {
        std::cout << " [Destroy] ~TATraced\n";
    }
};

// ============================================================================
// EXPERIMENT: NON-VIRTUAL VS VIRTUAL BASE SIZEOF & CONSTRUCTION (Task 3.4)
// ============================================================================
namespace NonVirtualExp {
    struct PersonNV { int pData = 10; };
    struct StudentNV : PersonNV { int sData = 20; };
    struct StaffNV : PersonNV { int stData = 30; };
    struct TANV : StudentNV, StaffNV { int taData = 40; };
}

namespace VirtualExp {
    struct PersonV { int pData = 10; };
    struct StudentV : virtual PersonV { int sData = 20; };
    struct StaffV : virtual PersonV { int stData = 30; };
    struct TAV : StudentV, StaffV { int taData = 40; };
}

// ============================================================================
// MAIN EXECUTION DRIVER
// ============================================================================

int main() {
    std::cout << "====================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 3\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 3: Order of Construction and Destruction with Member Classes\n";
    std::cout << "====================================================================\n\n";

    std::cout << ">>> 1. Predict-the-Output Code Execution:\n";
    Task3Predict::run();
    std::cout << "\n>>> 2. Complete-the-Code Execution (TODO 1 Initializer List):\n";
    Task3CompleteCode::run();

    std::cout << "\n>>> 3. Tracing Construction & Destruction Order for StudentTraced:\n";
    {
        StudentTraced st("Kavya", "Salem", 636001, 192311001, "DSA0117", "OOP with C++");
    }

    std::cout << "\n>>> 4. Tracing Construction & Destruction Order for TeachingAssistant (TATraced):\n";
    {
        TATraced ta("G Vishnu Madhav", "Chennai", 600077, 192425192,
                    "DSA0117", "OOP with C++", "Computer Science", 10);
    }

    std::cout << "\n>>> 5. Task 3.4 Experiment: sizeof Comparison (Virtual vs Non-Virtual):\n";
    std::cout << "Size of Non-Virtual TeachingAssistant (two Person subobjects): "
              << sizeof(NonVirtualExp::TANV) << " bytes\n";
    std::cout << "Size of Virtual TeachingAssistant (one Person subobject + vbptrs): "
              << sizeof(VirtualExp::TAV) << " bytes\n";

    std::cout << "\nRule Confirmed: Virtual bases -> Direct bases -> Members -> Derived body.\n";
    std::cout << "Destructors execute in exact reverse order.\n";
    std::cout << "====================================================================\n";

    return 0;
}
