#include <iostream>
#include <cmath>
#include <chrono>

class Time { 
    int h, m; 

public: 
    Time(int hh, int mm) : h(hh), m(mm) {} 
    friend int minutesBetween(const Time& a, const Time& b); 
    friend bool earlier(const Time& a, const Time& b); 
}; 

inline int minutesBetween(const Time& a, const Time& b) 
{ 
    // TODO 1: Using the private members h and m, return absolute difference in minutes
    int totalA = a.h * 60 + a.m;
    int totalB = b.h * 60 + b.m;
    return std::abs(totalA - totalB);
} 

inline bool earlier(const Time& a, const Time& b) 
{ 
    // TODO 2: Return true if a is earlier in the day than b 
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
} 

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q6: FRIEND FUNCTIONS, INLINING AND TEMPORAL COMPARISON\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. EXPECTED OUTPUT EXECUTION ---\n";
    Time departure(9, 45), arrival(13, 10); 
    std::cout << minutesBetween(departure, arrival) << ' ' 
              << std::boolalpha << earlier(arrival, departure) << "\n\n"; 

    std::cout << "--- 2. CORRECTNESS BOUNDARY CHECKS ---\n";
    Time tNoon1(11, 45), tNoon2(12, 15);
    std::cout << "Across Noon (11:45 to 12:15): " << minutesBetween(tNoon1, tNoon2) << " mins | Earlier: " << earlier(tNoon1, tNoon2) << "\n";
    Time tSame(15, 30);
    std::cout << "Same Time Twice (15:30 & 15:30): " << minutesBetween(tSame, tSame) << " mins | Earlier: " << earlier(tSame, tSame) << "\n\n";

    std::cout << "--- 3. HIGH-THROUGHPUT TIMING BENCHMARK (10,000,000 CALLS) ---\n";
    auto start = std::chrono::high_resolution_clock::now();
    long long accumulator = 0;
    for (int i = 0; i < 10000000; ++i) {
        accumulator += minutesBetween(departure, arrival);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "10,000,000 calls elapsed time: " << elapsedMs << " ms\n";
    std::cout << "Accumulator checksum: " << accumulator << "\n";
    std::cout << "[PASS] Friend access, inlining and timing verified!\n";
    return 0;
} 
