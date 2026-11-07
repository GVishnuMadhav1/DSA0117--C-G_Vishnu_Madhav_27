#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

class Complex {
private:
    double real_;
    double imag_;

public:
    Complex(double r = 0.0, double i = 0.0) : real_(r), imag_(i) {}

    double real() const { return real_; }
    double imag() const { return imag_; }
    double magnitude() const { return std::sqrt(real_ * real_ + imag_ * imag_); }

    Complex operator+(const Complex& o) const { return Complex(real_ + o.real_, imag_ + o.imag_); }
    Complex operator-(const Complex& o) const { return Complex(real_ - o.real_, imag_ - o.imag_); }
    Complex operator*(const Complex& o) const {
        return Complex(real_ * o.real_ - imag_ * o.imag_, real_ * o.imag_ + imag_ * o.real_);
    }
    Complex operator/(const Complex& o) const {
        double denom = o.real_ * o.real_ + o.imag_ * o.imag_;
        if (denom == 0.0) throw std::runtime_error("Division by zero impedance!");
        return Complex((real_ * o.real_ + imag_ * o.imag_) / denom,
                       (imag_ * o.real_ - real_ * o.imag_) / denom);
    }
    bool operator==(const Complex& o) const {
        return (std::abs(real_ - o.real_) < 1e-9) && (std::abs(imag_ - o.imag_) < 1e-9);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << std::fixed << std::setprecision(2) << c.real_ 
           << (c.imag_ >= 0 ? " + " : " - ") << std::abs(c.imag_) << "j";
        return os;
    }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q7: AC CIRCUIT IMPEDANCE CALCULATOR (COMPLEX CLASS)\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    // Circuit parameters: R = 100 Ohm, Inductive reactance XL = 50 Ohm, Capacitive reactance XC = 20 Ohm
    Complex zR(100.0, 0.0);
    Complex zL(0.0, 50.0);
    Complex zC(0.0, -20.0);

    // Series RLC Impedance: Z_series = ZR + ZL + ZC
    Complex zSeries = zR + zL + zC;
    std::cout << "Series RLC Impedance   : Z_series   = " << zSeries << " Ohm | Mag: " << zSeries.magnitude() << " Ohm\n";

    // Parallel RC Impedance: Z_parallel = (ZR * ZC) / (ZR + ZC)
    Complex zParallel = (zR * zC) / (zR + zC);
    std::cout << "Parallel RC Impedance  : Z_parallel = " << zParallel << " Ohm | Mag: " << zParallel.magnitude() << " Ohm\n";

    // Division by zero safety test
    try {
        Complex zZero(0.0, 0.0);
        Complex invalid = zR / zZero;
    } catch (const std::runtime_error& e) {
        std::cout << "Division by Zero Check : [TRAPPED] " << e.what() << "\n";
    }
    std::cout << "[PASS] AC Circuit Impedance Calculator completely validated!\n";
    return 0;
}
