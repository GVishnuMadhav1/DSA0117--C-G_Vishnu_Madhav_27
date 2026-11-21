// ============================================================================
// ASSIGNMENT 5: COURSE OUTCOME CO5
// TASK A2: UNDERSTAND RUNTIME BINDING, VTABLES, AND VIRTUAL DESTRUCTORS
// Student: G. Vishnu Madhav (192425192) | Batch 27
// Course: DSA0117 - Object-Oriented Programming with C++
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>

// Section 1: Predict the Output Program from Specification
struct Bill {
    virtual ~Bill() { std::cout << "~Bill "; }
    virtual double total() const = 0;
    void show() const { std::cout << total() << ' '; }
};

struct OPBill : Bill {
    ~OPBill() override { std::cout << "~OPBill "; }
    double total() const override { return 500; }
};

// Section 2: Virtual Destructor vs Non-Virtual Destructor Memory Demonstration
struct BaseNonVirtual {
    char data[32];
    ~BaseNonVirtual() { std::cout << "[BaseNonVirtual::~BaseNonVirtual] "; }
};

struct DerivedResource : public BaseNonVirtual {
    int* heapBuffer;
    DerivedResource() { heapBuffer = new int[1024]; }
    ~DerivedResource() {
        delete[] heapBuffer;
        std::cout << "[DerivedResource::~DerivedResource - Heap Freed] ";
    }
};

struct BaseVirtual {
    char data[32];
    virtual ~BaseVirtual() { std::cout << "[BaseVirtual::~BaseVirtual] "; }
};

struct DerivedSafe : public BaseVirtual {
    int* heapBuffer;
    DerivedSafe() { heapBuffer = new int[1024]; }
    ~DerivedSafe() override {
        delete[] heapBuffer;
        std::cout << "[DerivedSafe::~DerivedSafe - Heap Safely Freed] ";
    }
};

int main() {
    std::cout << "===================================================================\n";
    std::cout << " TASK A2: RUNTIME BINDING, VTABLE DISPATCH & VIRTUAL DESTRUCTORS\n";
    std::cout << " Student: G. Vishnu Madhav (192425192) | Batch 27 | Course: DSA0117\n";
    std::cout << "===================================================================\n\n";

    std::cout << "--- 1. PREDICT THE OUTPUT VERIFICATION (PAGE 4 SPECIFICATION) ---\n";
    std::cout << "Executing: Bill* b = new OPBill; b->show(); delete b;\n";
    std::cout << "Actual Program Output: ";
    {
        Bill* b = new OPBill;
        b->show();
        delete b;
        std::cout << '\n';
    }
    std::cout << "Predicted Output     : 500 ~OPBill ~Bill \n";
    std::cout << "[EXPLANATION] show() is non-virtual, but calls virtual total() on this->total().\n";
    std::cout << "Since this points to OPBill, late binding resolves to OPBill::total() (500).\n";
    std::cout << "delete b invokes virtual destructor: OPBill::~OPBill() runs first, then Bill::~Bill().\n\n";

    std::cout << "--- 2. VIRTUAL DESTRUCTOR VS NON-VIRTUAL DESTRUCTOR HAZARD ---\n";
    std::cout << "Case A: Polymorphic delete WITH virtual destructor:\n";
    BaseVirtual* safePtr = new DerivedSafe;
    delete safePtr;
    std::cout << "\n[PASS] Derived destructor executed cleanly; zero memory leaked.\n\n";

    std::cout << "Case B: Polymorphic delete WITHOUT virtual destructor:\n";
    BaseNonVirtual* leakPtr = new DerivedResource;
    delete leakPtr;
    std::cout << "\n[HAZARD] DerivedResource destructor was SKIPPED! Heap memory leaked!\n";
    std::cout << "Under -fsanitize=address, this triggers undefined behavior.\n\n";

    std::cout << "--- 3. MEMORY LAYOUT & VPTR INSPECTION ---\n";
    std::cout << "sizeof(BaseNonVirtual): " << sizeof(BaseNonVirtual) << " bytes (only data members)\n";
    std::cout << "sizeof(BaseVirtual)   : " << sizeof(BaseVirtual) << " bytes (data members + 8-byte vptr)\n";
    std::cout << "Virtual table pointer (vptr) added overhead: 8 bytes on 64-bit architecture.\n";

    return 0;
}
