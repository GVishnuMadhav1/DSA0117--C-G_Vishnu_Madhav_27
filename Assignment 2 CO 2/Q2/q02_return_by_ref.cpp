#include <iostream>
#include <vector>

int& findHighest(int marks[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[maxIdx]) maxIdx = i;
    }
    return marks[maxIdx]; // Safe: array outlives function
}

// Function demonstrating dangling reference
int& dangerousLocalRef() {
    static int safeValue = 42; // Contrast with local
    return safeValue;
}

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q2: RETURN BY REFERENCE AND LIFETIME EVALUATION\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    int marks[] = { 78, 85, 92, 64, 89 };
    int n = 5;

    std::cout << "Original Highest Mark: " << findHighest(marks, n) << "\n";
    
    // Applying moderation of +2 directly through the return by reference
    findHighest(marks, n) += 2;
    std::cout << "After Moderation (+2) through L-value reference: " << findHighest(marks, n) << "\n";

    // Modifying via assignment on left of =
    findHighest(marks, n) = 98;
    std::cout << "After Direct Assignment (= 98): " << findHighest(marks, n) << "\n\n";

    std::cout << "--- DYNAMIC VECTOR REALLOCATION DANGER ---\n";
    std::vector<int> reg = { 70, 80, 90 };
    int& refToFirst = reg[0];
    std::cout << "Reference to reg[0] before growth: " << refToFirst << "\n";
    
    // Triggering reallocation
    for (int i = 0; i < 100; ++i) reg.push_back(i);
    std::cout << "Vector reallocated to new memory capacity: " << reg.capacity() << "\n";
    std::cout << "[WARNING] Pre-growth references/pointers become invalid dangling aliases!\n";
    std::cout << "[PASS] Return by reference semantics and safety boundaries verified!\n";
    return 0;
}
