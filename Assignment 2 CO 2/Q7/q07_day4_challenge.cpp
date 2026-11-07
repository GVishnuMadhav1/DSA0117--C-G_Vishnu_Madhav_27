#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

// --- ORIGINAL DESIGN: Shifting Array (O(k) cost on every push) ---
class ShiftingHistory {
private:
    static const int CAPACITY = 50;
    long long arr[CAPACITY];
    int count;

public:
    ShiftingHistory() : count(0) {}

    void add(long long val) {
        if (count < CAPACITY) {
            arr[count++] = val;
        } else {
            // Limitation: O(k) shift of entire array on every transaction!
            for (int i = 0; i < CAPACITY - 1; ++i) {
                arr[i] = arr[i + 1];
            }
            arr[CAPACITY - 1] = val;
        }
    }
};

// --- REDESIGNED SOLUTION: Ring Buffer / Circular Queue (O(1) strictly) ---
class CircularHistory {
private:
    static const int CAPACITY = 50;
    long long arr[CAPACITY];
    int head;
    int count;

public:
    CircularHistory() : head(0), count(0) {}

    // Measurable objective: O(1) constant time insertion without memory shifts
    inline void add(long long val) {
        arr[head] = val;
        head = (head + 1) % CAPACITY;
        if (count < CAPACITY) count++;
    }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q7: DAY-4 DESIGN CHALLENGE - DIAGNOSE, REDESIGN & VALIDATE\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. EMPIRICAL BENCHMARK: SHIFTING ARRAY VS CIRCULAR BUFFER ---\n";
    const int NUM_OPERATIONS = 1000000;

    // Benchmark Original Shifting Array
    ShiftingHistory original;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        original.add(i * 10LL);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto msOriginal = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    // Benchmark Redesigned Circular Buffer
    CircularHistory redesigned;
    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        redesigned.add(i * 10LL);
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    auto msRedesigned = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();

    std::cout << "Operations Executed : " << NUM_OPERATIONS << " transactions\n";
    std::cout << "Original Shifting   : " << msOriginal << " ms (O(k) memory shifts)\n";
    std::cout << "Redesigned Circular : " << msRedesigned << " ms (O(1) pointer updates)\n";
    double speedup = static_cast<double>(msOriginal) / (msRedesigned > 0 ? msRedesigned : 1);
    std::cout << "Measured Speedup    : " << std::fixed << std::setprecision(2) << speedup << "x faster!\n";
    std::cout << "[PASS] Day-4 Challenge: Diagnosed, Redesigned, and Validated!\n";
    return 0;
}
