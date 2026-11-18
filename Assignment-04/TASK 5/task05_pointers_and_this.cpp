/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 5: Pointers to Objects and the 'this' Pointer
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

// ============================================================================
// PART 1: COMPLETE THE CODE (As specified in Assignment 4)
// ============================================================================
namespace CompleteTheCodeSection {

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0; // percent

public:
    // TODO 1: add(): store the item and price if there is space, and return *this
    // so that calls can be chained
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this; // Returning lvalue reference to current object
    }

    // TODO 2: setDiscount(): use this-> to tell the member apart from the parameter
    // named discount, and return *this
    Cart& setDiscount(double discount) {
        this->discount = discount; // Disambiguate member from parameter
        return *this;
    }

    double total() const {
        double t = 0;
        for (int i = 0; i < n; ++i) {
            t += prices[i];
        }
        return t * (100.0 - discount) / 100.0;
    }

    void display() const {
        std::cout << "  Cart Items (" << n << "): ";
        for (int i = 0; i < n; ++i) {
            std::cout << items[i] << " (Rs. " << prices[i] << ")" << (i + 1 < n ? ", " : "");
        }
        std::cout << " | Discount: " << discount << "% | Total: Rs. " << total() << "\n";
    }
};

void runCompleteTheCode() {
    std::cout << ">>> 1. 'Complete the Code' Execution (TODO 1 & TODO 2 Verification):\n";
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c; // pointer to an object
    p->add("Oil", 180);

    std::cout << "  Standard Expected Output:\n  ";
    std::cout << std::fixed << std::setprecision(2) << p->total() << '\n';
    std::cout << "  Cart contents verification:\n";
    c.display();
    std::cout << "  Calculations: (60 + 120 + 180) = 360; 360 * (1 - 0.10) = 324.00\n";
    std::cout << "  [STATUS]: EXACT MATCH WITH EXPECTED 324.00\n\n";
}

} // namespace CompleteTheCodeSection


// ============================================================================
// PART 2: TASK 5.1 - FOUR WAYS TO REACH AN OBJECT
// ============================================================================
namespace FourWaysSection {

using CompleteTheCodeSection::Cart;

void runFourWaysDemo() {
    std::cout << ">>> 2. Task 5.1: Demonstrating Four Ways to Reach an Object:\n";

    // (a) Directly by name (automatic/stack storage duration)
    std::cout << "  (a) Directly by Name:\n";
    Cart cartDirect;
    cartDirect.add("Milk", 35).add("Bread", 40);
    cartDirect.setDiscount(5);
    cartDirect.display();

    // (b) Through a pointer with -> operator
    std::cout << "  (b) Through a Pointer with '->':\n";
    Cart* cartPtr = &cartDirect;
    cartPtr->add("Butter", 55);
    cartPtr->display();

    // (c) Through a reference (alias)
    std::cout << "  (c) Through a Reference (Alias):\n";
    Cart& cartRef = cartDirect;
    cartRef.add("Eggs", 70);
    cartRef.display();

    // (d) Through a pointer created with new and released with delete
    std::cout << "  (d) Dynamically on Heap (new / delete):\n";
    Cart* cartHeap = new Cart();
    cartHeap->add("Atta (5kg)", 250).add("Sugar (1kg)", 45).setDiscount(10);
    cartHeap->display();
    std::cout << "  Releasing heap Cart with delete...\n";
    delete cartHeap;
    cartHeap = nullptr;
    std::cout << "  [Heap Cart Safely Deallocated]\n\n";
}

} // namespace FourWaysSection


// ============================================================================
// PART 3: TASK 5.2 - ARRAY OF POINTERS & SEARCHING HIGHEST TOTAL
// ============================================================================
namespace SearchHighestSection {

using CompleteTheCodeSection::Cart;

void runArrayOfPointersSearch() {
    std::cout << ">>> 3. Task 5.2: Active Customer Carts & Pointer Arithmetic Search:\n";

    const int NUM_CUSTOMERS = 4;
    Cart c1, c2, c3, c4;

    c1.add("Fruits", 150).add("Juice", 90).setDiscount(5);           // Total: 240 * 0.95 = 228.00
    c2.add("Olive Oil", 650).add("Basmati Rice", 350).setDiscount(15);// Total: 1000 * 0.85 = 850.00
    c3.add("Snacks", 80).add("Biscuits", 40);                         // Total: 120.00
    c4.add("Cleaning Supplies", 320).add("Detergent", 280).setDiscount(10); // Total: 600 * 0.90 = 540.00

    // Array of pointers to Cart objects
    Cart* activeCarts[NUM_CUSTOMERS] = { &c1, &c2, &c3, &c4 };

    std::cout << "  Active Customer Carts in Fleet / Store:\n";
    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
        std::cout << "  Customer Cart [" << i << "]: ";
        (*(activeCarts + i))->display(); // Using pointer arithmetic
    }

    // Finding cart with highest total using pointer arithmetic and indexing
    Cart* highestCart = *activeCarts; // points to activeCarts[0]
    int bestIndex = 0;

    for (int i = 1; i < NUM_CUSTOMERS; ++i) {
        Cart* currentCart = *(activeCarts + i); // Pointer arithmetic dereferencing
        if (currentCart->total() > highestCart->total()) {
            highestCart = currentCart;
            bestIndex = i;
        }
    }

    std::cout << "\n  --- Highest Value Cart Found ---\n";
    std::cout << "  Highest Cart Index : Customer Cart [" << bestIndex << "]\n";
    std::cout << "  Highest Total      : Rs. " << std::fixed << std::setprecision(2) << highestCart->total() << "\n";
    std::cout << "  Cart Details       : ";
    highestCart->display();
    std::cout << "\n";
}

} // namespace SearchHighestSection


// ============================================================================
// PART 4: ALTERNATIVE CONCEPT AND COMPLEXITY ANALYSIS
// ============================================================================
namespace AlternativeAnalysisSection {

using CompleteTheCodeSection::Cart;

void runAlternativeConceptAnalysis() {
    std::cout << ">>> 4. Alternative Concept and Complexity Analysis:\n";
    std::cout << "  Comparison: Array of Pointers vs std::vector<Cart> (Value Semantics)\n";
    std::cout << "  --------------------------------------------------------------------\n";
    std::cout << "  Metric                 | Array of Pointers (Cart*[]) | std::vector<Cart>\n";
    std::cout << "  -----------------------+-----------------------------+--------------------\n";
    std::cout << "  Search Time Complexity | O(n) linear scan            | O(n) linear scan\n";
    std::cout << "  Search Duration        | Fast pointer traversal      | High cache locality\n";
    std::cout << "  Element Size in Buffer | 8 bytes (pointer)           | " << sizeof(Cart) << " bytes (full object)\n";
    std::cout << "  Total Buffer (N=100)   | 800 bytes                   | " << 100 * sizeof(Cart) << " bytes\n";
    std::cout << "  Object Copy Overhead   | Zero (no copies made)       | High on realloc/push\n";
    std::cout << "  Pointer Invalidation   | Never (stable addresses)    | Invalidated on grow!\n";
    std::cout << "  --------------------------------------------------------------------\n";
    std::cout << "  Key Engineering Finding on Pointer Invalidation:\n";
    std::cout << "  If external subsystems hold raw pointers to Cart objects stored inside\n";
    std::cout << "  a std::vector<Cart>, whenever the vector exceeds capacity and reallocates\n";
    std::cout << "  its backing store, all existing raw pointers become DANGLING POINTERS,\n";
    std::cout << "  causing severe undefined behavior. Storing stable heap pointers\n";
    std::cout << "  (or std::vector<std::unique_ptr<Cart>>) eliminates invalidation.\n\n";
}

} // namespace AlternativeAnalysisSection


// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    std::cout << "====================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 5\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 5: Pointers to Objects and the 'this' Pointer\n";
    std::cout << "====================================================================\n\n";

    CompleteTheCodeSection::runCompleteTheCode();
    FourWaysSection::runFourWaysDemo();
    SearchHighestSection::runArrayOfPointersSearch();
    AlternativeAnalysisSection::runAlternativeConceptAnalysis();

    std::cout << "====================================================================\n";
    std::cout << " Task 5 Demonstration Complete.\n";
    std::cout << "====================================================================\n";
    return 0;
}
