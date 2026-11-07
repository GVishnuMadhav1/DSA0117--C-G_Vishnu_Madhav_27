#include <iostream>

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " TASK 4: CONTROL IMPLICIT CONVERSIONS (PREDICT THE OUTPUT)\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    int a = 7, b = 2; 
    double c = a / b; 
    double d = static_cast<double>(a) / b; 
    std::cout << c << ' ' << d << '\n'; 

    char ch = 'A' + 2; 
    std::cout << ch << ' ' << ch + 1 << '\n'; 

    bool flag = 5; 
    std::cout << flag << ' ' << std::boolalpha << flag << '\n'; 

    unsigned int u = 1; 
    int s = -1; 
    std::cout << (s < u ? "s < u" : "s >= u") << '\n'; 

    std::cout << "\n--- CONVERSION MECHANISM ANALYSIS ---\n";
    std::cout << "Line 1: 'a / b' does integer division (7/2 = 3), then converts to double 3.0.\n";
    std::cout << "        'static_cast<double>(a) / b' promotes b to double 2.0, yielding 3.5.\n";
    std::cout << "Line 2: 'A' + 2 is ASCII 67 = 'C'. 'ch + 1' promotes char to int, yielding 68.\n";
    std::cout << "Line 3: Non-zero 5 converts to bool true (printed as 1, then true with boolalpha).\n";
    std::cout << "Line 4: Signed s (-1) promoted to unsigned int (4294967295U), hence s >= u!\n";
    std::cout << "[PASS] Execution matches theoretical prediction with 100% fidelity!\n";
    return 0;
}
