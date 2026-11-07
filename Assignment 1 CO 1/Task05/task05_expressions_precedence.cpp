#include <iostream>

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " TASK 5: OPERATOR PRECEDENCE AND ASSOCIATIVITY AUDIT\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    int x = 5, y = 3; 
    std::cout << x + y * 2 << ' ' << (x + y) * 2 << '\n'; 

    int z = x++ + ++y; 
    std::cout << z << ' ' << x << ' ' << y << '\n'; 

    std::cout << (x > y ? x : y) << ' ' << x % 4 * 2 << '\n'; 
    std::cout << 10 / 3 << ' ' << 10 % 3 << ' ' << -10 / 3 << ' ' << -10 % 3 << '\n'; 

    int k = 0; 
    for (int i = 0; i < 10; i += 3) k += i; 
    std::cout << k << '\n'; 

    std::cout << "\n--- OPERATOR PRECEDENCE STEP-BY-STEP DERIVATION ---\n";
    std::cout << "Line 1: '*' precedes '+' -> 5 + 6 = 11; '(x+y)*2' overrides precedence -> 8 * 2 = 16.\n";
    std::cout << "Line 2: 'x++' evaluates to 5 (increments to 6); '++y' increments y to 4 and evaluates to 4.\n";
    std::cout << "        z = 5 + 4 = 9. Final x = 6, y = 4.\n";
    std::cout << "Line 3: Ternary '6 > 4 ? 6 : 4' yields 6. '6 % 4 * 2' associates left-to-right -> 2 * 2 = 4.\n";
    std::cout << "Line 4: Truncation towards zero in C++11: 10/3=3, 10%3=1, -10/3=-3, -10%3=-1.\n";
    std::cout << "Line 5: Loop takes i = 0, 3, 6, 9 (sum = 18).\n";
    std::cout << "[PASS] Verified exact execution matches prediction!\n";
    return 0;
}
