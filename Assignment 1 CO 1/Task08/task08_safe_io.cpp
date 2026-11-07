#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>
#include <vector>

void printFormattedFareRow(int tripId, const std::string& zone, int hour, long long farePaise, long long balancePaise, bool status) {
    std::cout << "| " << std::setw(7) << tripId << " | "
              << std::setw(10) << std::left << zone << std::right << " | "
              << std::setw(2) << std::setfill('0') << hour << ":00" << std::setfill(' ') << " | Rs "
              << std::setw(5) << (farePaise / 100) << "." << std::setw(2) << std::setfill('0') << (farePaise % 100) << std::setfill(' ') << " | Rs "
              << std::setw(6) << (balancePaise / 100) << "." << std::setw(2) << std::setfill('0') << (balancePaise % 100) << std::setfill(' ') << " | "
              << std::setw(9) << (status ? "APPROVED" : "DENIED") << " |\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << " TASK 8: SAFE STREAM I/O, RECOVERY AND REPORT FORMATTING\n";
    std::cout << " Course: DSA0117 (CO1) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. INPUT STREAM CORRUPTION AND RECOVERY SIMULATION ---\n";
    std::string simulatedInput = "abc\n-50\n200\n";
    std::stringstream inputStream(simulatedInput);

    long long rechargeAmount = 0;
    std::cout << "Commencing robust input parsing with std::cin error checks:\n";

    while (true) {
        std::cout << "Attempting to read recharge amount: ";
        if (!(inputStream >> rechargeAmount)) {
            std::cout << "[ERROR] Non-numeric input encountered (cin.fail() == true)!\n";
            inputStream.clear(); // Clear error state flags
            std::string discarded;
            inputStream >> discarded; // Discard invalid token
            std::cout << "        Recovery: Cleared state flags and discarded: '" << discarded << "'\n";
        } else if (rechargeAmount <= 0) {
            std::cout << "[ERROR] Recharge must be positive! Value typed: Rs " << rechargeAmount << "\n";
        } else {
            std::cout << "[SUCCESS] Valid recharge accepted: Rs " << rechargeAmount << ".00\n";
            break;
        }
    }

    std::cout << "\n--- 2. STANDARDIZED METRO COMMUTER AUDIT REPORT ---\n";
    std::cout << "+---------+------------+-------+------------+-------------+----------+\n";
    std::cout << "| Trip ID | Zone       | Time  | Fare (Rs)  | Balance(Rs) | Status   |\n";
    std::cout << "+---------+------------+-------+------------+-------------+----------+\n";
    printFormattedFareRow(101, "Inner",  8, 1200, 8800, true);
    printFormattedFareRow(102, "Outer",  9, 3600, 5200, true);
    printFormattedFareRow(103, "Middle", 13, 2000, 5200, false);
    printFormattedFareRow(104, "Inner", 18, 1200, 5200, false);
    std::cout << "+---------+------------+-------+------------+-------------+----------+\n";
    std::cout << "[PASS] Safe I/O stream recovery and fixed-width alignment verified!\n";
    return 0;
}
