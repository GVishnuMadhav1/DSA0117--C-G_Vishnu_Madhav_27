#include <iostream>
#include <iomanip>
#include <climits>
#include <cfloat>

int main() {
    std::cout << "============================================================\n";
    std::cout << " TASK 3: DATA TYPES, PRECISION, AND SIZEOF SPECIFICATION\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. FUNDAMENTAL DATA TYPE SIZES AND RANGES ON THIS SYSTEM ---\n";
    std::cout << "| Data Type    | Size (Bytes) | Minimum Limit               | Maximum Limit               |\n";
    std::cout << "|--------------|--------------|-----------------------------|-----------------------------|\n";
    std::cout << "| bool         | " << sizeof(bool) << "            | 0                           | 1                           |\n";
    std::cout << "| char         | " << sizeof(char) << "            | " << CHAR_MIN << "                        | " << CHAR_MAX << "                         |\n";
    std::cout << "| int          | " << sizeof(int) << "            | " << INT_MIN << "                 | " << INT_MAX << "                  |\n";
    std::cout << "| unsigned int | " << sizeof(unsigned int) << "            | 0                           | " << UINT_MAX << "                  |\n";
    std::cout << "| long long    | " << sizeof(long long) << "            | " << LLONG_MIN << "        | " << LLONG_MAX << "         |\n";
    std::cout << "| float        | " << sizeof(float) << "            | " << FLT_MIN << "                 | " << FLT_MAX << "                 |\n";
    std::cout << "| double       | " << sizeof(double) << "            | " << DBL_MIN << "                | " << DBL_MAX << "                |\n\n";

    std::cout << "--- 2. WHY MONEY MUST BE STORED IN INTEGER PAISE (NOT DOUBLE) ---\n";
    double doubleBalance = 0.0;
    long long paiseBalance = 0;
    const double tripFareRupees = 20.20; // Rs 20 and 20 paise
    const long long tripFarePaise = 2020;  // Exact 2020 paise

    int numTrips = 100000;
    for (int i = 0; i < numTrips; ++i) {
        doubleBalance += tripFareRupees;
        paiseBalance += tripFarePaise;
    }

    double convertedFromPaise = static_cast<double>(paiseBalance) / 100.0;
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Accumulated across " << numTrips << " journeys of Rs 20.20:\n";
    std::cout << "  Double Rupee Total : Rs " << doubleBalance << "\n";
    std::cout << "  Exact Integer Paise: Rs " << convertedFromPaise << " (" << paiseBalance << " paise)\n";
    std::cout << "  Floating Discrepancy: Rs " << (doubleBalance - convertedFromPaise) << " (paisa drift!)\n\n";

    std::cout << "--- 3. NETWORK SCALE OVERFLOW ANALYSIS (3,000,000 JOURNEYS/DAY) ---\n";
    long long dailyJourneys = 3000000LL;
    long long avgFarePaise = 2500LL; // Rs 25.00
    long long dailyRevenuePaise = dailyJourneys * avgFarePaise; // 7,500,000,000 paise (Rs 7.5 Crore)

    std::cout << "Daily Network Revenue: Rs " << (dailyRevenuePaise / 100) << " = " << dailyRevenuePaise << " paise\n";
    std::cout << "32-bit INT_MAX       : " << INT_MAX << " paise (~Rs " << (INT_MAX / 100) << ")\n";
    if (dailyRevenuePaise > INT_MAX) {
        std::cout << "[CRITICAL RISK] 32-bit 'int' overflows in less than ONE day!\n";
        std::cout << "[SOLUTION] 'long long' (limit ~9.22 x 10^18 paise) is mathematically mandatory!\n";
    }
    return 0;
}
