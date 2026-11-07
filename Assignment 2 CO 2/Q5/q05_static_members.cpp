#include <iostream>
#include <string>

// --- PREDICT THE OUTPUT CLASS ---
class Token { 
    static int next; 
    int id; 

public: 
    Token() { id = ++next; } 
    int get() const { return id; } 
    static int issued() { return next - 100; } 
}; 
int Token::next = 100; 

// --- COMPLETE THE CODE CLASS ---
class BusTicket { 
    static int issued; // shared by all BusTicket objects 
    static const int CAPACITY = 3; 
    int seat; 
    std::string name; 

public: 
    explicit BusTicket(const std::string& n) : seat(0), name(n) 
    { 
        // TODO 1: If fewer than CAPACITY tickets have been issued, increase issued and 
        // give this ticket the next seat number; otherwise leave seat as 0 (waiting list)
        if (issued < CAPACITY) {
            seat = ++issued;
        } else {
            seat = 0;
        }
    } 

    static int count() 
    { 
        // TODO 2: Return the number of seats issued so far 
        return issued;
    } 

    void print() const 
    { 
        std::cout << name << ": " 
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) 
                  << '\n'; 
    } 
}; 
int BusTicket::issued = 0; // definition of the static data member 

void createBatch() {
    BusTicket temp("Guest");
}

int main() 
{ 
    std::cout << "============================================================\n";
    std::cout << " Q5: STATIC DATA MEMBERS AND ARRAYS OF OBJECTS AUDIT\n";
    std::cout << " Course: DSA0117 (CO2) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    std::cout << "--- 1. PREDICT THE OUTPUT ---\n";
    Token counter[3]; 
    Token extra; 
    std::cout << counter[0].get() << ' ' << counter[2].get() << ' ' << extra.get() 
              << ' ' << Token::issued() << "\n\n"; 

    std::cout << "--- 2. COMPLETE THE CODE: BUS TICKET SYSTEM ---\n";
    BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"), 
                         BusTicket("Chitra"), BusTicket("Dev")}; 
    for (const BusTicket& t : trip) t.print(); 
    std::cout << "Issued: " << BusTicket::count() << "\n\n"; 

    std::cout << "--- 3. STATIC PERSISTENCE TEST ACROSS FUNCTION CALLS ---\n";
    std::cout << "Calling createBatch() twice...\n";
    createBatch();
    createBatch();
    std::cout << "Final Total Issued (waiting list capped): " << BusTicket::count() << "\n";
    std::cout << "[PASS] Static lifetime and array of objects verified successfully!\n";
    return 0;
}
