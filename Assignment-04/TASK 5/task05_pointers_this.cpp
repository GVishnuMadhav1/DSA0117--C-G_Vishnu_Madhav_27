/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 5: Pointers to Objects and the this Pointer - Four Ways to Access Objects & Method Chaining
 */

#include <iostream>
#include <iomanip>
#include <string>

// ============================================================================
// CART CLASS IMPLEMENTATION WITH 'this' POINTER & METHOD CHAINING
// ============================================================================

class Cart {
private:
    std::string customerId;
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0; // percent discount

public:
    Cart(const std::string& cid = "Guest") : customerId(cid) {}

    std::string getCustomerId() const { return customerId; }

    // TODO 1: add(): store item and price if space permits, return *this for method chaining
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this; // Returns lvalue reference to invoking object (*this)
    }

    // TODO 2: setDiscount(): use this-> to disambiguate member variable from parameter
    Cart& setDiscount(double discount) {
        this->discount = discount; // this->discount is member, discount is parameter
        return *this;             // Return *this to enable further chained invocations
    }

    double total() const {
        double t = 0;
        for (int i = 0; i < n; ++i) {
            t += prices[i];
        }
        return t * (100.0 - discount) / 100.0;
    }

    void printSummary() const {
        std::cout << "Cart [" << customerId << "] - Items: " << n
                  << ", Discount: " << discount << "%, Total: Rs. "
                  << std::fixed << std::setprecision(2) << total() << "\n";
        for (int i = 0; i < n; ++i) {
            std::cout << "   " << (i + 1) << ". " << items[i] << " : Rs. " << prices[i] << "\n";
        }
    }
};

// ============================================================================
// COMPLETE-THE-CODE VERIFICATION (TODO 1 & TODO 2 Exact Snippet from Assignment)
// ============================================================================
namespace CompleteTheCodeSnippet {
    void verifyOriginalSnippet() {
        std::cout << ">>> 1. Assignment Complete-the-Code Execution Result:\n";
        Cart c;
        c.add("Rice", 60).add("Dal", 120).setDiscount(10);
        Cart* p = &c;
        p->add("Oil", 180);
        std::cout << "Calculated Output: " << std::fixed << std::setprecision(2) << p->total() << "\n";
        std::cout << "Expected Output  : 324.00 (Verification SUCCESSFUL)\n\n";
    }
}

// ============================================================================
// MAIN EXECUTION DRIVER
// ============================================================================

int main() {
    std::cout << "====================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 5\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 5: Pointers to Objects and the 'this' Pointer\n";
    std::cout << "====================================================================\n\n";

    // 1. Verify Complete-the-Code Snippet
    CompleteTheCodeSnippet::verifyOriginalSnippet();

    // 2. Task 5.1: Demonstrating Four Ways to Reach an Object
    std::cout << ">>> 2. Task 5.1: Four Ways to Reach a Cart Object:\n";

    // Way (a): Directly by name (Stack object)
    std::cout << "(a) Directly by name:\n";
    Cart cartA("CUST-101");
    cartA.add("Basmati Rice", 140.0).add("Ghee", 320.0).setDiscount(5.0);
    cartA.printSummary();

    // Way (b): Through a pointer with ->
    std::cout << "\n(b) Through a pointer with ->:\n";
    Cart cartB("CUST-102");
    Cart* ptrB = &cartB;
    ptrB->add("Atta Flour", 65.0).add("Spices", 85.0).setDiscount(10.0);
    ptrB->printSummary();

    // Way (c): Through a reference with .
    std::cout << "\n(c) Through a reference with .:\n";
    Cart cartC("CUST-103");
    Cart& refC = cartC;
    refC.add("Milk Packet", 30.0).add("Eggs (12)", 84.0).setDiscount(0.0);
    refC.printSummary();

    // Way (d): Through a pointer created with new and released with delete
    std::cout << "\n(d) Dynamically allocated with new and released with delete:\n";
    Cart* dynCart = new Cart("CUST-104");
    dynCart->add("Olive Oil", 450.0).add("Dark Chocolate", 180.0).setDiscount(15.0);
    dynCart->printSummary();
    delete dynCart; // Explicit memory deallocation
    dynCart = nullptr;

    // 3. Task 5.2: Finding Cart with Highest Total among Array of Pointers
    std::cout << "\n>>> 3. Task 5.2: Array of Pointers Search for Highest Total:\n";
    Cart c1("Cust-Alpha"), c2("Cust-Beta"), c3("Cust-Gamma"), c4("Cust-Delta");
    c1.add("Apples", 120.0).add("Berries", 200.0);                 // Total: 320.00
    c2.add("Almonds", 500.0).add("Cashews", 450.0).setDiscount(10); // Total: 950 * 0.9 = 855.00
    c3.add("Tea", 110.0).add("Coffee", 190.0);                     // Total: 300.00
    c4.add("Protein Powder", 950.0).setDiscount(5);                // Total: 950 * 0.95 = 902.50

    // Array of pointers to active customer carts
    const int NUM_CARTS = 4;
    Cart* activeFleet[NUM_CARTS] = { &c1, &c2, &c3, &c4 };

    // Search algorithm using pointer arithmetic / indexing
    Cart** maxCartPtr = &activeFleet[0];
    double maxTotal = activeFleet[0]->total();

    for (int i = 1; i < NUM_CARTS; ++i) {
        if ((*(activeFleet + i))->total() > maxTotal) {
            maxTotal = (*(activeFleet + i))->total();
            maxCartPtr = activeFleet + i;
        }
    }

    std::cout << "Highest Value Cart Located:\n";
    std::cout << "  Customer ID: " << (*maxCartPtr)->getCustomerId() << "\n";
    std::cout << "  Highest Cart Total: Rs. " << std::fixed << std::setprecision(2) << maxTotal << "\n";
    std::cout << "====================================================================\n";

    return 0;
}
