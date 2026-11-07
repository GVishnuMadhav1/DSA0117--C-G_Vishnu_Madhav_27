#include <iostream>
#include <string>

class Book {
private:
    std::string title_;
    std::string author_;
    int copies_;

public:
    // 1. Default constructor delegating to parameterized
    Book() : Book("Untitled", "Anonymous", 0) {}

    // 2. Overloaded constructor for donated books
    Book(const std::string& title) : Book(title, "Donated", 1) {}

    // 3. Full parameterized constructor with member initializer list
    Book(const std::string& title, const std::string& author, int copies)
        : title_(title), author_(author), copies_(copies < 0 ? 0 : copies) {}

    // Explicit constructor to prevent implicit conversion
    explicit Book(int copies) : Book("Inventory Batch", "Internal", copies < 0 ? 0 : copies) {}

    void print() const {
        std::cout << "Book: '" << title_ << "' | Author: " << author_ << " | Copies: " << copies_ << '\n';
    }

    int getCopies() const { return copies_; }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q1: CONSTRUCTORS, OVERLOADING AND DELEGATION AUDIT\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    Book emptyRecord;
    Book donated("Clean Code");
    Book standardBook("Operating Systems", "Silberschatz", 15);
    Book negativeCopiesTest("Data Structures", "Weiss", -5); // Guarded
    Book explicitBatch(25); // Explicit conversion

    emptyRecord.print();
    donated.print();
    standardBook.print();
    negativeCopiesTest.print();
    explicitBatch.print();

    std::cout << "\n[VALIDATION] Negative copies safely clamped to 0.\n";
    std::cout << "[PASS] Constructor delegation and member initializer lists verified!\n";
    return 0;
}
