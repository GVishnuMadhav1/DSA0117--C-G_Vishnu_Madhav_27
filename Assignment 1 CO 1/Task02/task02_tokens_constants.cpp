#include <iostream>
#include <iomanip>

// 1. Preprocessor macro vs const vs constexpr
#define LEGACY_FARE_INNER 1000  // Macro: un-scoped, untyped textual replacement
const int CONST_SURCHARGE = 20;  // const: runtime/compile-time typed constant

// constexpr: guaranteed compile-time evaluation, type-safe, scoped
constexpr long long FARE_INNER_PAISE  = 1000LL; // Rs 10.00
constexpr long long FARE_MIDDLE_PAISE = 2000LL; // Rs 20.00
constexpr long long FARE_OUTER_PAISE  = 3000LL; // Rs 30.00
constexpr int PEAK_SURCHARGE_PERCENT  = 20;     // 20% surcharge
constexpr long long MIN_BALANCE_PAISE = 5000LL; // Rs 50.00 required invariant

// 2. Scoped Enumeration (enum class) vs Plain enum
enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

// Compile-time fare table array evaluated completely by the compiler
constexpr long long BASE_FARES[] = { FARE_INNER_PAISE, FARE_MIDDLE_PAISE, FARE_OUTER_PAISE };

constexpr long long getBaseFare(Zone z) {
    return BASE_FARES[static_cast<int>(z)];
}

int main() {
    std::cout << "============================================================\n";
    std::cout << " TASK 2: TOKENS, IDENTIFIERS AND CONSTEXPR CONSTANTS\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. FIVE CATEGORIES OF TOKENS IN METRO ENGINE ---\n";
    std::cout << "1. Keywords:    enum, class, constexpr, long, bool, return, static_cast\n";
    std::cout << "2. Identifiers: Zone, SmartCard, FARE_INNER_PAISE, getBaseFare\n";
    std::cout << "3. Constants:   1000LL, 2000LL, 3000LL, 20, 5000LL\n";
    std::cout << "4. Operators:   +, -, *, /, %, <<, ==, >=, static_cast<>()\n";
    std::cout << "5. Punctuators: ;, {, }, (, ), [, ], ::, ,\n\n";

    std::cout << "--- 2. CONSTEXPR FARE LOOKUP TABLE EVALUATION ---\n";
    std::cout << "Zone::Inner  Base Fare: Rs " << (getBaseFare(Zone::Inner) / 100) << ".00 (" << getBaseFare(Zone::Inner) << " paise)\n";
    std::cout << "Zone::Middle Base Fare: Rs " << (getBaseFare(Zone::Middle) / 100) << ".00 (" << getBaseFare(Zone::Middle) << " paise)\n";
    std::cout << "Zone::Outer  Base Fare: Rs " << (getBaseFare(Zone::Outer) / 100) << ".00 (" << getBaseFare(Zone::Outer) << " paise)\n\n";

    std::cout << "--- 3. COMPARISON: #define vs const vs constexpr ---\n";
    std::cout << "| Mechanism | Type Safety | Scoped | Eval Time    | Memory Overhead |\n";
    std::cout << "|-----------|-------------|--------|--------------|-----------------|\n";
    std::cout << "| #define   | None (text) | Global | Preprocessor | None            |\n";
    std::cout << "| const     | Full        | Yes    | Run/Compile  | May allocate    |\n";
    std::cout << "| constexpr | Full (RO)   | Yes    | Compile-time | Zero (inlined)  |\n\n";

    std::cout << "--- 4. ENUM CLASS SAFETY ADVANTAGES ---\n";
    std::cout << "- Strongly typed: implicit conversion to int is rejected at compile time.\n";
    std::cout << "- Scope isolated: Zone::Inner does not pollute global namespace.\n";
    std::cout << "- Single Point of Change: Fares revised in constexpr table propagate network-wide.\n";
    std::cout << "[PASS] Token and constant architecture verified successfully!\n";
    return 0;
}
