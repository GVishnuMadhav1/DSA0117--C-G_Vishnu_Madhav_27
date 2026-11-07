#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// --- PREDICT THE OUTPUT COUNTER ---
struct Counter { 
    int v; 
    Counter& operator++() { ++v; return *this; }                     // prefix 
    Counter operator++(int) { Counter old = *this; ++v; return old; } // postfix 
}; 

// Track Timer with Prefix and Postfix ++
class TrackTimer {
private:
    int hours_;
    int minutes_;
    int seconds_;

public:
    TrackTimer(int h = 0, int m = 0, int s = 0) : hours_(h), minutes_(m), seconds_(s) {}

    // Prefix ++: returns reference to updated object
    TrackTimer& operator++() {
        if (++seconds_ >= 60) {
            seconds_ = 0;
            if (++minutes_ >= 60) {
                minutes_ = 0;
                hours_++;
            }
        }
        return *this;
    }

    // Postfix ++: returns copy of old object
    TrackTimer operator++(int) {
        TrackTimer old = *this;
        ++(*this); // reuse prefix
        return old;
    }

    void print() const {
        std::cout << hours_ << ':' << minutes_ << ':' << seconds_ << '\n';
    }
};

// Playlist with Overloaded []
class Playlist {
private:
    std::vector<std::string> tracks_;

public:
    Playlist(std::initializer_list<std::string> list) : tracks_(list) {}

    // Non-const subscript
    std::string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks_.size())) {
            throw std::out_of_range("Playlist index out of range!");
        }
        return tracks_[index];
    }

    // Const subscript
    const std::string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks_.size())) {
            throw std::out_of_range("Playlist index out of range!");
        }
        return tracks_[index];
    }

    int size() const { return static_cast<int>(tracks_.size()); }
};

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q5: OVERLOADING INCREMENT AND SUBSCRIPT OPERATORS\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. PREDICT THE OUTPUT ---\n";
    Counter c{5}; 
    Counter a = c++; 
    Counter b = ++c; 
    std::cout << a.v << ' ' << b.v << ' ' << c.v << "\n\n"; 

    std::cout << "--- 2. ROLLOVER TEST: 00:59:59 -> 01:00:00 ---\n";
    TrackTimer timer(0, 59, 59);
    std::cout << "Before Increment : "; timer.print();
    ++timer;
    std::cout << "After Prefix ++  : "; timer.print();

    std::cout << "\n--- 3. PLAYLIST SUBSCRIPT [] WITH RANGE CHECK ---\n";
    Playlist pl = { "Track 1: Classical", "Track 2: Symphony", "Track 3: Rhapsody" };
    std::cout << "pl[0]: " << pl[0] << "\n";
    std::cout << "pl[2]: " << pl[2] << "\n";
    try {
        std::cout << "Accessing pl[-1]: ";
        std::cout << pl[-1] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "[CAUGHT] " << e.what() << "\n";
    }
    std::cout << "[PASS] Increment, subscript and bounds safety verified!\n";
    return 0;
} 
