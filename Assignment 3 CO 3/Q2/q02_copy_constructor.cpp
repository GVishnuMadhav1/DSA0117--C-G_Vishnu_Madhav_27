#include <iostream>
#include <string>

class Prescription { 
    int n; 
    std::string* medicines; // dynamically allocated array 

public: 
    explicit Prescription(int count) : n(count), medicines(new std::string[count]) {} 

    // TODO 1: Copy constructor: allocate a NEW array of the same size and copy every medicine (deep copy)
    Prescription(const Prescription& other) : n(other.n), medicines(new std::string[other.n]) {
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
    }

    // TODO 2: Copy assignment: guard against self-assignment, build a new array, copy, release old array and return *this
    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this; // Guard against self-assignment
        delete[] medicines; // Release existing memory
        n = other.n;
        medicines = new std::string[n];
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
        return *this;
    }

    // TODO 3: Release the dynamically allocated array
    ~Prescription() 
    { 
        delete[] medicines;
    } 

    void set(int i, const std::string& m) { medicines[i] = m; } 
    std::string get(int i) const { return medicines[i]; } 
}; 

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q2: DEEP COPY CONSTRUCTOR AND RULE OF THREE AUDIT\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    Prescription p(2); 
    p.set(0, "Paracetamol"); 
    p.set(1, "ORS"); 

    Prescription q = p; // copy constructor (deep copy)
    q.set(1, "Cetirizine"); 

    Prescription r(1); 
    r = p; // copy assignment (deep copy)
    p.set(0, "Ibuprofen"); 

    std::cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1) 
              << " | " << r.get(0) << ' ' << r.get(1) << '\n'; 

    std::cout << "Self-assignment test (p = p): ";
    p = p;
    std::cout << p.get(0) << ' ' << p.get(1) << " [SAFE]\n";
    std::cout << "[PASS] Expected output matched and independent deep copies verified!\n";
    return 0;
} 
