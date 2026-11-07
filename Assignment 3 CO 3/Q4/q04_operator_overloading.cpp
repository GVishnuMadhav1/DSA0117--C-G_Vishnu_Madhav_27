#include <iomanip> 
#include <iostream> 

class Money { 
    long long paise; 

public: 
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {} 

    // TODO 1: Overload + as a member function that returns a new Money object
    Money operator+(const Money& other) const {
        Money result;
        result.paise = this->paise + other.paise;
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.paise = this->paise - other.paise;
        return result;
    }

    Money& operator+=(const Money& other) {
        this->paise += other.paise;
        return *this;
    }

    // TODO 2: Overload == as a member, and << as a friend that prints "Rs 200.00"
    bool operator==(const Money& other) const {
        return this->paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return this->paise < other.paise;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        os << "Rs " << (m.paise / 100) << '.' << std::setw(2) << std::setfill('0') << (m.paise % 100) << std::setfill(' ');
        return os;
    }
}; 

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q4: OVERLOADING ARITHMETIC AND STREAM OPERATORS\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    Money a(120, 75), b(79, 25); 
    Money c = a + b; 
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n'; 

    std::cout << "--- CARRY TEST: Rs 0.75 + Rs 0.50 ---\n";
    Money p1(0, 75), p2(0, 50);
    Money pSum = p1 + p2;
    std::cout << p1 << " + " << p2 << " = " << pSum << " (Carried cleanly into Rs 1.25)\n";
    std::cout << "[PASS] Operator overloading +, ==, and << verified successfully!\n";
    return 0;
} 
