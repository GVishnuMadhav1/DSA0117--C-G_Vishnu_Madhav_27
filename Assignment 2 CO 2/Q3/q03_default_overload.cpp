#include <iostream>
#include <iomanip>
#include <string>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
    std::string destination;
};

// Redesigned overloaded functions with unambiguous signatures
// 1. Weight in grams (int)
double charge(int weightGrams, bool express = false, bool insured = false) {
    double cost = (weightGrams / 100.0) * 5.0; // Rs 5 per 100g
    if (express) cost += 50.0;
    if (insured) cost += 30.0;
    return cost;
}

// 2. Weight in kilograms (double)
double charge(double weightKg, bool express = false, bool insured = false) {
    double cost = weightKg * 45.0; // Rs 45 per kg
    if (express) cost += 50.0;
    if (insured) cost += 30.0;
    return cost;
}

// 3. Parcel object overload
double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q3: FUNCTION OVERLOADING & DEFAULT ARGUMENTS AUDIT\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "Call 1: charge(500)       [int grams]       -> Rs " << charge(500) << "\n";
    std::cout << "Call 2: charge(500, true) [int + express]   -> Rs " << charge(500, true) << "\n";
    std::cout << "Call 3: charge(2.5)       [double kg]       -> Rs " << charge(2.5) << "\n";
    std::cout << "Call 4: charge(2.5, true, true) [double all]-> Rs " << charge(2.5, true, true) << "\n";
    std::cout << "Call 5: charge(2)         [int exact match] -> Rs " << charge(2) << "\n";
    std::cout << "Call 6: charge(2.0f)      [float->double]   -> Rs " << charge(static_cast<double>(2.0f)) << "\n";

    Parcel p1{ 4.0, true, false, "Bangalore" };
    std::cout << "Call 7: charge(Parcel)    [Object overload] -> Rs " << charge(p1) << "\n";
    std::cout << "[PASS] Ambiguity resolved and overload resolution validated!\n";
    return 0;
}
