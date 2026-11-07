#include <iostream>

void change(int a, int& b, int* c) 
{ 
    a += 10; 
    b += 10; 
    *c += 10; 
} 

int& bigger(int& p, int& q) { return p > q ? p : q; } 

void show(int x, int y = 5, int z = 10) { std::cout << x + y + z << ' '; } 

void applyByValue(long long fee, int percent) 
{ 
    fee -= fee * percent / 100; // changes only the local copy 
} 

void applyConcession(long long& fee, int percent) 
{ 
    // TODO 1: Reduce the caller's fee by percent using integer arithmetic (call by reference)
    fee -= (fee * percent) / 100;
} 

void applyByPointer(long long* feePtr, int percent)
{
    if (feePtr) {
        *feePtr -= (*feePtr * percent) / 100;
    }
}

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q1: CALL BY VALUE, BY REFERENCE AND BY POINTER\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. PREDICT THE OUTPUT EXECUTION ---\n";
    int a = 1, b = 2, c = 3; 
    change(a, b, &c); 
    std::cout << a << ' ' << b << ' ' << c << '\n'; 

    bigger(a, c) = 100; 
    std::cout << a << ' ' << c << '\n'; 

    show(1); 
    show(1, 2); 
    show(1, 2, 3); 
    std::cout << "\n\n"; 

    std::cout << "--- 2. COMPLETE THE CODE: HOSTEL CONCESSION UPDATER ---\n";
    long long hostelFee = 45000; 
    applyByValue(hostelFee, 10); 
    std::cout << "after call by value    : " << hostelFee << '\n'; 
    applyConcession(hostelFee, 10); 
    std::cout << "after call by reference: " << hostelFee << '\n'; 

    long long sportsFee = 45000;
    applyByPointer(&sportsFee, 15);
    std::cout << "after call by pointer  : " << sportsFee << '\n';
    std::cout << "[PASS] Q1 verified successfully!\n";
    return 0;
} 
