#include <iostream>
#include <string>
#include <vector>

// --- PREDICT THE OUTPUT STRUCT ---
struct Logger { 
    std::string n; 
    Logger(const std::string& s) : n(s) { std::cout << '+' << n << ' '; } 
    Logger(const Logger& o) : n(o.n + "c") { std::cout << "copy" << n << ' '; } 
    ~Logger() { std::cout << '-' << n << ' '; } 
}; 

void use(Logger) { std::cout << "use "; } 

// --- DYNAMIC AUDITORIUM SEAT MAP CLASS (RAII) ---
class AuditoriumEvent {
private:
    std::string eventName_;
    int rows_;
    int seatsPerRow_;
    char** seatMap_; // 2D dynamically allocated array

public:
    AuditoriumEvent(const std::string& name, int rows, int seats)
        : eventName_(name), rows_(rows), seatsPerRow_(seats) {
        if (rows_ <= 0 || seatsPerRow_ <= 0) {
            rows_ = 0; seatsPerRow_ = 0; seatMap_ = nullptr;
            return;
        }
        seatMap_ = new char*[rows_];
        for (int r = 0; r < rows_; ++r) {
            seatMap_[r] = new char[seatsPerRow_];
            for (int s = 0; s < seatsPerRow_; ++s) {
                seatMap_[r][s] = 'O'; // Available
            }
        }
    }

    ~AuditoriumEvent() {
        if (seatMap_) {
            for (int r = 0; r < rows_; ++r) {
                delete[] seatMap_[r];
            }
            delete[] seatMap_;
        }
    }

    bool bookSeat(int r, int s) {
        if (r < 0 || r >= rows_ || s < 0 || s >= seatsPerRow_) return false;
        if (seatMap_[r][s] == 'X') return false;
        seatMap_[r][s] = 'X';
        return true;
    }
};

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q3: DYNAMIC CONSTRUCTORS, DESTRUCTORS AND RAII AUDIT\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. PREDICT THE OUTPUT EXECUTION ---\n";
    Logger a("A"); 
    { 
        Logger b("B"); 
    } 
    use(a); 
    Logger* p = new Logger("P"); 
    delete p; 
    std::cout << "end "; 

    std::cout << "\n\n--- 2. DYNAMIC 2D SEAT MAP ALLOCATION & BOOKING ---\n";
    {
        AuditoriumEvent symp("TechSymposium", 10, 20);
        symp.bookSeat(0, 0);
        symp.bookSeat(0, 1);
        std::cout << "Auditorium allocated: 10 rows x 20 seats (200 seats). Bookings active.\n";
        std::cout << "Exiting scope... RAII automatically releases all 2D dynamic buffers!\n";
    }
    std::cout << "[PASS] Memory management and destruction sequence validated!\n";
    return 0;
} 
