/**
 * Course: Object-Oriented Programming with C++ (DSA0117)
 * Assignment 4 - CO4: Designing Reusable Class Hierarchies
 * Student Name: G Vishnu Madhav | Register Number: 192425192
 * Task 6: Design Challenge - Reusable Vehicle Rental Fleet Hierarchy
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// ============================================================================
// STAGE 2 & 4: MEMBER CLASS - Date (Composition in MotorVehicle)
// ============================================================================
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}

    std::string toString() const {
        std::string s = (day < 10 ? "0" : "") + std::to_string(day) + "/" +
                        (month < 10 ? "0" : "") + std::to_string(month) + "/" +
                        std::to_string(year);
        return s;
    }
};

// ============================================================================
// STAGE 2 & 4: ABSTRACT BASE CLASS - Vehicle
// ============================================================================
class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool isRented;
    int rentedDays;

public:
    Vehicle(const std::string& reg, double rate)
        : regNo(reg), dailyRate(rate), isRented(false), rentedDays(0) {}

    virtual ~Vehicle() = default;

    // Pure virtual functions (Mandatory interface for all derived vehicles)
    virtual double calculateRentalCharge(int actualDays, double returnLevel) const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string getVehicleType() const = 0;

    // Concrete polymorphic rental operations
    virtual bool rent(int days) {
        if (isRented) {
            std::cout << "  [RENTAL ERROR]: Vehicle " << regNo << " is already rented out!\n";
            return false;
        }
        if (days <= 0) {
            std::cout << "  [RENTAL ERROR]: Invalid rental duration (" << days << " days).\n";
            return false;
        }
        isRented = true;
        rentedDays = days;
        std::cout << "  [RENTED SUCCESS]: " << getVehicleType() << " [" << regNo 
                  << "] rented for " << days << " days at Rs. " << dailyRate << "/day.\n";
        return true;
    }

    virtual double processReturn(int actualDays, double returnLevel) {
        if (!isRented) {
            std::cout << "  [RETURN ERROR]: Vehicle " << regNo << " was not rented!\n";
            return 0.0;
        }
        double totalCharge = calculateRentalCharge(actualDays, returnLevel);
        isRented = false;
        rentedDays = 0;
        std::cout << "  [RETURN SUCCESS]: " << getVehicleType() << " [" << regNo << "]"
                  << " returned after " << actualDays << " days. Final Bill: Rs. " 
                  << std::fixed << std::setprecision(2) << totalCharge << "\n";
        return totalCharge;
    }

    // Accessors
    std::string getRegNo() const { return regNo; }
    double getDailyRate() const { return dailyRate; }
    bool getIsRented() const { return isRented; }
};

// ============================================================================
// CONCRETE DERIVED CLASS 1: Bicycle (Non-Motorized, Hierarchical Inheritance)
// ============================================================================
class Bicycle : public Vehicle {
private:
    std::string frameType; // e.g. Mountain, Road, Hybrid

public:
    Bicycle(const std::string& reg, double rate, const std::string& frame)
        : Vehicle(reg, rate), frameType(frame) {}

    std::string getVehicleType() const override { return "Bicycle (" + frameType + ")"; }

    double calculateRentalCharge(int actualDays, double /*returnLevel*/) const override {
        double baseCharge = dailyRate * actualDays;
        // Late surcharge: 50% extra per day if returned beyond agreed period
        if (actualDays > rentedDays && rentedDays > 0) {
            int lateDays = actualDays - rentedDays;
            double lateFee = lateDays * (dailyRate * 1.5);
            std::cout << "    * Late Return Notice: " << lateDays << " days overdue -> Late Fee: Rs. " 
                      << lateFee << "\n";
            baseCharge += lateFee;
        }
        return baseCharge;
    }

    void displayDetails() const override {
        std::cout << "  [Bicycle]       Reg: " << std::setw(12) << regNo 
                  << " | Rate: Rs. " << std::setw(7) << dailyRate << "/day"
                  << " | Frame: " << std::setw(8) << frameType
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE") << "\n";
    }
};

// ============================================================================
// INTERMEDIATE CLASS: MotorVehicle (Inherits Vehicle, Member: Date)
// ============================================================================
class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel; // Percentage (0.0 to 100.0)
    Date serviceDueDate;      // Member object (Composition)

public:
    MotorVehicle(const std::string& reg, double rate, double initialLevel, const Date& sDueDate)
        : Vehicle(reg, rate), fuelOrChargeLevel(initialLevel), serviceDueDate(sDueDate) {}

    double getFuelOrChargeLevel() const { return fuelOrChargeLevel; }
    std::string getServiceDueDate() const { return serviceDueDate.toString(); }
};

// ============================================================================
// CONCRETE DERIVED CLASS 2: TwoWheeler (Motorcycle / Scooter)
// ============================================================================
class TwoWheeler : public MotorVehicle {
private:
    int engineCc;

public:
    TwoWheeler(const std::string& reg, double rate, double level, const Date& sDate, int cc)
        : MotorVehicle(reg, rate, level, sDate), engineCc(cc) {}

    std::string getVehicleType() const override { return "Two-Wheeler (" + std::to_string(engineCc) + "cc)"; }

    double calculateRentalCharge(int actualDays, double returnLevel) const override {
        double baseCharge = dailyRate * actualDays;
        double lateFee = 0.0;
        if (actualDays > rentedDays && rentedDays > 0) {
            int lateDays = actualDays - rentedDays;
            lateFee = lateDays * (dailyRate * 1.5);
            std::cout << "    * Late Return Notice: " << lateDays << " days overdue -> Late Fee: Rs. " 
                      << lateFee << "\n";
        }

        // Fuel penalty: Rs. 110 per 10% deficit from 100% full
        double fuelFee = 0.0;
        if (returnLevel < 100.0) {
            double deficit = 100.0 - returnLevel;
            fuelFee = (deficit / 10.0) * 110.0;
            std::cout << "    * Fuel Deficit: Returned at " << returnLevel 
                      << "% (Required 100%) -> Refuel Charge: Rs. " << fuelFee << "\n";
        }
        return baseCharge + lateFee + fuelFee;
    }

    void displayDetails() const override {
        std::cout << "  [Two-Wheeler]   Reg: " << std::setw(12) << regNo 
                  << " | Rate: Rs. " << std::setw(7) << dailyRate << "/day"
                  << " | CC: " << std::setw(4) << engineCc
                  << " | Fuel: " << std::setw(5) << fuelOrChargeLevel << "%"
                  << " | Service Due: " << serviceDueDate.toString()
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE") << "\n";
    }
};

// ============================================================================
// CONCRETE DERIVED CLASS 3: Car (Passenger Sedan/SUV)
// ============================================================================
class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const std::string& reg, double rate, double level, const Date& sDate, int seats)
        : MotorVehicle(reg, rate, level, sDate), seatingCapacity(seats) {}

    std::string getVehicleType() const override { return "Car (" + std::to_string(seatingCapacity) + " Seater)"; }

    double calculateRentalCharge(int actualDays, double returnLevel) const override {
        double baseCharge = dailyRate * actualDays;
        // Luxury seating surcharge: Rs. 150 per seat per day above 4 seats
        double seatSurcharge = 0.0;
        if (seatingCapacity > 4) {
            seatSurcharge = (seatingCapacity - 4) * 150.0 * actualDays;
        }

        double lateFee = 0.0;
        if (actualDays > rentedDays && rentedDays > 0) {
            int lateDays = actualDays - rentedDays;
            lateFee = lateDays * (dailyRate * 1.5);
            std::cout << "    * Late Return Notice: " << lateDays << " days overdue -> Late Fee: Rs. " 
                      << lateFee << "\n";
        }

        double fuelFee = 0.0;
        if (returnLevel < 100.0) {
            double deficit = 100.0 - returnLevel;
            fuelFee = (deficit / 10.0) * 220.0; // Rs. 220 per 10% petrol deficit
            std::cout << "    * Fuel Deficit: Returned at " << returnLevel 
                      << "% -> Refuel Fee: Rs. " << fuelFee << "\n";
        }

        return baseCharge + seatSurcharge + lateFee + fuelFee;
    }

    void displayDetails() const override {
        std::cout << "  [Car]           Reg: " << std::setw(12) << regNo 
                  << " | Rate: Rs. " << std::setw(7) << dailyRate << "/day"
                  << " | Seats: " << std::setw(2) << seatingCapacity
                  << " | Fuel: " << std::setw(5) << fuelOrChargeLevel << "%"
                  << " | Service Due: " << serviceDueDate.toString()
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE") << "\n";
    }
};

// ============================================================================
// CONCRETE DERIVED CLASS 4: ElectricCar (Charged per kWh)
// ============================================================================
class ElectricCar : public MotorVehicle {
private:
    double batteryCapacityKwh;
    double ratePerKwh; // Charged per kWh instead of per litre

public:
    ElectricCar(const std::string& reg, double rate, double level, const Date& sDate, 
                double batteryKwh, double kwhRate)
        : MotorVehicle(reg, rate, level, sDate), 
          batteryCapacityKwh(batteryKwh), ratePerKwh(kwhRate) {}

    std::string getVehicleType() const override { return "Electric Car (" + std::to_string((int)batteryCapacityKwh) + " kWh)"; }

    double calculateRentalCharge(int actualDays, double returnLevel) const override {
        double baseCharge = dailyRate * actualDays;

        double lateFee = 0.0;
        if (actualDays > rentedDays && rentedDays > 0) {
            int lateDays = actualDays - rentedDays;
            lateFee = lateDays * (dailyRate * 1.5);
            std::cout << "    * Late Return Notice: " << lateDays << " days overdue -> Late Fee: Rs. " 
                      << lateFee << "\n";
        }

        // Energy consumption charge: based on battery capacity used
        double energyFee = 0.0;
        if (returnLevel < 100.0) {
            double usedKwh = ((100.0 - returnLevel) / 100.0) * batteryCapacityKwh;
            energyFee = usedKwh * ratePerKwh;
            std::cout << "    * EV Recharge Charge: " << usedKwh << " kWh used @ Rs. " 
                      << ratePerKwh << "/kWh -> Battery Recharge Fee: Rs. " << energyFee << "\n";
        }

        // Clean green environmental discount: 5% off base rental
        double greenDiscount = baseCharge * 0.05;

        return baseCharge + lateFee + energyFee - greenDiscount;
    }

    void displayDetails() const override {
        std::cout << "  [Electric Car]  Reg: " << std::setw(12) << regNo 
                  << " | Rate: Rs. " << std::setw(7) << dailyRate << "/day"
                  << " | Battery: " << std::setw(2) << (int)batteryCapacityKwh << " kWh"
                  << " | Charge: " << std::setw(4) << fuelOrChargeLevel << "%"
                  << " | Service Due: " << serviceDueDate.toString()
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE") << "\n";
    }
};

// ============================================================================
// STAGE 5 EXTENSION: ElectricBus (Extending without modifying existing classes!)
// ============================================================================
class ElectricBus : public MotorVehicle {
private:
    int passengerCapacity;
    double batteryCapacityKwh;
    double commercialPermitRate;

public:
    ElectricBus(const std::string& reg, double rate, double level, const Date& sDate,
                int passengers, double batteryKwh, double permitRate)
        : MotorVehicle(reg, rate, level, sDate),
          passengerCapacity(passengers), batteryCapacityKwh(batteryKwh), commercialPermitRate(permitRate) {}

    std::string getVehicleType() const override { return "Electric Bus (" + std::to_string(passengerCapacity) + " Pass.)"; }

    double calculateRentalCharge(int actualDays, double returnLevel) const override {
        double baseCharge = dailyRate * actualDays;
        double permitCharge = commercialPermitRate * actualDays;

        double lateFee = 0.0;
        if (actualDays > rentedDays && rentedDays > 0) {
            int lateDays = actualDays - rentedDays;
            lateFee = lateDays * (dailyRate * 1.5);
            std::cout << "    * Late Return Notice: " << lateDays << " days overdue -> Late Fee: Rs. " 
                      << lateFee << "\n";
        }

        double rechargeFee = 0.0;
        if (returnLevel < 100.0) {
            double usedKwh = ((100.0 - returnLevel) / 100.0) * batteryCapacityKwh;
            rechargeFee = usedKwh * 18.0; // Commercial depot rate: Rs. 18/kWh
            std::cout << "    * Heavy Vehicle EV Recharge: " << usedKwh << " kWh @ Rs. 18.0/kWh -> Rs. " 
                      << rechargeFee << "\n";
        }

        return baseCharge + permitCharge + lateFee + rechargeFee;
    }

    void displayDetails() const override {
        std::cout << "  [Electric Bus]  Reg: " << std::setw(12) << regNo 
                  << " | Rate: Rs. " << std::setw(7) << dailyRate << "/day"
                  << " | Pass: " << std::setw(3) << passengerCapacity
                  << " | Battery: " << std::setw(3) << (int)batteryCapacityKwh << " kWh"
                  << " | Service Due: " << serviceDueDate.toString()
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE") << "\n";
    }
};

// ============================================================================
// STAGE 3: FLEET MANAGEMENT SYSTEM (Array of Base-Class Pointers)
// ============================================================================
class RentalFleetManager {
private:
    static const int MAX_CAPACITY = 20;
    Vehicle* fleet[MAX_CAPACITY];
    int fleetSize;

public:
    RentalFleetManager() : fleetSize(0) {
        for (int i = 0; i < MAX_CAPACITY; ++i) fleet[i] = nullptr;
    }

    ~RentalFleetManager() {
        for (int i = 0; i < fleetSize; ++i) {
            delete fleet[i];
            fleet[i] = nullptr;
        }
    }

    bool addVehicle(Vehicle* v) {
        if (fleetSize >= MAX_CAPACITY) return false;
        fleet[fleetSize++] = v;
        return true;
    }

    void listFleet() const {
        std::cout << "----------------------------------------------------------------------------------------------------\n";
        std::cout << "                     SIMATS VEHICLE RENTAL FLEET INVENTORY STATUS\n";
        std::cout << "----------------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < fleetSize; ++i) {
            fleet[i]->displayDetails();
        }
        std::cout << "----------------------------------------------------------------------------------------------------\n";
    }

    Vehicle* findVehicle(const std::string& reg) {
        for (int i = 0; i < fleetSize; ++i) {
            if (fleet[i]->getRegNo() == reg) return fleet[i];
        }
        return nullptr;
    }

    bool rentVehicle(const std::string& reg, int days) {
        Vehicle* v = findVehicle(reg);
        if (!v) {
            std::cout << "  [ERROR]: Vehicle with registration " << reg << " not found!\n";
            return false;
        }
        return v->rent(days);
    }

    double returnVehicle(const std::string& reg, int actualDays, double returnLevel) {
        Vehicle* v = findVehicle(reg);
        if (!v) {
            std::cout << "  [ERROR]: Vehicle with registration " << reg << " not found!\n";
            return 0.0;
        }
        return v->processReturn(actualDays, returnLevel);
    }
};

// ============================================================================
// MAIN DEMONSTRATION FUNCTION
// ============================================================================
int main() {
    std::cout << "====================================================================================================\n";
    std::cout << " SIMATS ENGINEERING - OOP C++ (DSA0117) - ASSIGNMENT 4 TASK 6\n";
    std::cout << " Student: G Vishnu Madhav | Reg No: 192425192 | Section: AI-ML\n";
    std::cout << " Task 6: Design Challenge - Reusable Vehicle Rental Fleet Hierarchy\n";
    std::cout << "====================================================================================================\n\n";

    RentalFleetManager manager;

    // Populating fleet with diverse vehicle types
    manager.addVehicle(new Bicycle("TN-01-BK-101", 150.00, "Mountain"));
    manager.addVehicle(new TwoWheeler("TN-02-TW-202", 450.00, 100.0, Date(15, 12, 2026), 150));
    manager.addVehicle(new Car("TN-03-CR-303", 2200.00, 100.0, Date(20, 11, 2026), 7)); // 7-seater SUV
    manager.addVehicle(new ElectricCar("TN-04-EV-404", 1800.00, 100.0, Date(10, 1, 2027), 45.0, 15.0)); // 45 kWh, Rs. 15/kWh

    std::cout << ">>> 1. Initial Fleet Inventory:\n";
    manager.listFleet();
    std::cout << "\n";

    std::cout << ">>> 2. Executing Vehicle Rentals Across Categories:\n";
    manager.rentVehicle("TN-01-BK-101", 2); // Bicycle for 2 days
    manager.rentVehicle("TN-02-TW-202", 3); // Two-Wheeler for 3 days
    manager.rentVehicle("TN-03-CR-303", 4); // Car for 4 days
    manager.rentVehicle("TN-04-EV-404", 2); // Electric Car for 2 days
    std::cout << "\n";

    std::cout << ">>> 3. Fleet Status After Rentals:\n";
    manager.listFleet();
    std::cout << "\n";

    std::cout << ">>> 4. Demonstrating Vehicle Returns (Normal vs Late Charges & Energy Penalties):\n";
    
    // Bicycle: On-time return (2 days)
    std::cout << "--- Return 1: Bicycle On-Time Return ---\n";
    manager.returnVehicle("TN-01-BK-101", 2, 0.0);
    std::cout << "\n";

    // Two-Wheeler: Returned on time (3 days) but fuel level reduced to 60% (40% deficit)
    std::cout << "--- Return 2: Two-Wheeler Return with Fuel Deficit ---\n";
    manager.returnVehicle("TN-02-TW-202", 3, 60.0);
    std::cout << "\n";

    // Car: Late return (rented for 4 days, returned on day 6 = 2 days late) and 20% fuel deficit
    std::cout << "--- Return 3: 7-Seater Car with 2 Days LATE Penalty & Fuel Refill ---\n";
    manager.returnVehicle("TN-03-CR-303", 6, 80.0);
    std::cout << "\n";

    // Electric Car: On time (2 days), 50% battery consumed (22.5 kWh used), charged per kWh
    std::cout << "--- Return 4: Electric Car with Energy Consumption Charge & Green Discount ---\n";
    manager.returnVehicle("TN-04-EV-404", 2, 50.0);
    std::cout << "\n";

    std::cout << ">>> 5. STAGE 5 EXTENSION DEMONSTRATION:\n";
    std::cout << "Adding NEW vehicle type 'ElectricBus' WITHOUT modifying any existing vehicle classes:\n";
    ElectricBus* bus = new ElectricBus("TN-05-EB-505", 5500.00, 100.0, Date(25, 2, 2027), 42, 250.0, 1200.0);
    manager.addVehicle(bus);

    std::cout << "  New Vehicle Added Successfully to Fleet:\n";
    manager.listFleet();
    std::cout << "\n";

    std::cout << "Renting and Returning New ElectricBus (Demonstrating Polymorphic Extensibility):\n";
    manager.rentVehicle("TN-05-EB-505", 5);
    manager.returnVehicle("TN-05-EB-505", 5, 70.0); // 30% battery consumed (75 kWh)
    std::cout << "\n";

    std::cout << ">>> 6. Alternative Concept & Complexity Analysis:\n";
    std::cout << "  ----------------------------------------------------------------------------------------\n";
    std::cout << "  Dimension             | Abstract Base Class + Virtual    | Single Class with Switch\n";
    std::cout << "  ----------------------+----------------------------------+-------------------------------\n";
    std::cout << "  Time Complexity       | O(1) constant vtable lookup      | O(1) jump table / switch\n";
    std::cout << "  Space Overhead        | 8 bytes (vptr); 0 unused fields  | Up to 65% wasted memory (unused\n";
    std::cout << "                        | (exact size per derived type)    | fields for all vehicle types)\n";
    std::cout << "  Open/Closed Principle | Fully Compliant (OCP adhered):   | Violates OCP: Adding new type\n";
    std::cout << "                        | New types added via inheritance  | requires editing core class,\n";
    std::cout << "                        | with zero edits to working code  | enum, and all switch branches\n";
    std::cout << "  Extensibility Cost    | Zero regression risk in existing | High regression risk across\n";
    std::cout << "                        | tested classes or fleet managers | entire monolithic codebase\n";
    std::cout << "  ----------------------------------------------------------------------------------------\n\n";

    std::cout << "====================================================================================================\n";
    std::cout << " Task 6 Demonstration Complete.\n";
    std::cout << "====================================================================================================\n";
    return 0;
}
