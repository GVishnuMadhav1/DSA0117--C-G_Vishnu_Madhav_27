# Assignment 4 (CO4): Designing Reusable Class Hierarchies in C++

**Course Title:** Object-Oriented Programming with C++  
**Course Code:** DSA0117  
**Course Outcome (CO4):** Analyse and implement C++ applications using inheritance, types of inheritance, virtual base classes, abstract classes, pointers and polymorphism to design reusable and extensible programs (constructors in derived classes, member classes, pointers to objects, the `this` pointer and pointers to derived classes).  
**Student Name:** G. Vishnu Madhav  
**Register Number:** 192425192  
**Roll / Batch:** Batch 27  
**Department / Section:** Artificial Intelligence & Machine Learning (AI-ML)  
**Nature of Assignment:** Individual Laboratory Assignment  
**Bloom's Level Assessed:** K5 – Evaluate (All Tasks)  
**Total Marks:** 50  
**GitHub Repository Link:** [https://github.com/GVishnuMadhav1/DSA0117--C-G_Vishnu_Madhav_27/tree/main/Assignment%204](https://github.com/GVishnuMadhav1/DSA0117--C-G_Vishnu_Madhav_27/tree/main/Assignment%204)  

---

## 1. Compiler and Toolchain Specifications
* **Compiler:** MinGW-W64 `g++` (x86_64-posix-seh-rev0, Built by MinGW-W64 project) version 8.1.0 / GNU C++17 compatible
* **Language Standard:** ISO C++17 (`-std=c++17`)
* **Standard Compilation Flags:**
  ```bash
  g++ -std=c++17 -Wall -Wextra <source_file>.cpp -o <executable>.exe
  ```
* **Operating System:** Windows 11 x64
* **Shell Environment:** Windows PowerShell / Developer Console

---

## 2. Progressive Task Structure & Mark Distribution

| Task | Task Title & Coverage | Max Marks | Status | Directory |
| :---: | :--- | :---: | :---: | :---: |
| **Task 1** | **Class Design Review:** Diagnose and Repair Duplicated Classes | 6 | Completed | [`Task01/`](./Task01/) |
| **Task 2** | **From Requirement to Hierarchy:** University People Management & Diamond Problem | 8 | Completed | [`Task02/`](./Task02/) |
| **Task 3** | **Constructors in Derived & Member Classes:** Order of Construction and Destruction | 9 | Completed | [`Task03/`](./Task03/) |
| **Task 4** | **Pointers to Derived Classes (Forensics):** Virtual Methods, Slicing & Destructors | 7 | Completed | [`Task04/`](./Task04/) |
| **Task 5** | **Pointers to Objects & `this` Pointer:** Method Chaining & Pointer Arithmetic | 7 | Completed | [`Task05/`](./Task05/) |
| **Task 6** | **Design Challenge:** Extensible Vehicle Rental Fleet Hierarchy | 13 | Completed | [`Task06/`](./Task06/) |
| **Total** | **Comprehensive Course Outcome 4 (CO4) Evaluation** | **50** | **100% Verified** | |

---

## 3. Summary of Tasks & Key Technical Implementations

### Task 1: Class Design Review (6 Marks)
* **Objective:** Review three independently written, uncoordinated payroll classes (`Professor`, `LabAssistant`, `GuestFaculty`) and refactor them into a clean, reusable inheritance hierarchy.
* **Diagnosed Deficiencies:**
  1. *Repeated fields & logic:* Duplicated `name`, `id`, `basic`, and `da` violating DRY principle.
  2. *Repeated calculation rules:* `basic + basic * 0.42` hardcoded in multiple places.
  3. *Encapsulation violation:* All data members exposed as `public`.
  4. *Inconsistent naming:* `name`/`id` in full-time vs `nm`/`code` in guest faculty.
  5. *Dead fields & magic numbers:* Unused `da` field and raw literal `0.42`.
  6. *Extensibility failure:* Adding a new category requires copying an entire class.
  7. *Polymorphism absent:* Cannot iterate over all employees in a single unified loop.
* **Repaired Architecture:**
  - Common polymorphic base class `Staff` with `protected` data members and virtual `pay()` method.
  - Derived classes `Professor`, `LabAssistant`, and `GuestFaculty` overriding `pay()`.
  - Batch payroll processing using `std::vector<std::unique_ptr<Staff>>`.
* **Alternative Analysis:** Comparing single `Staff` class with `enum StaffType` and `switch` statement vs OOP hierarchy. Both evaluate `pay()` in $O(1)$ time, but single-class design wastes space on unused fields and violates the Open/Closed Principle (OCP).

### Task 2: From Requirement to Hierarchy (8 Marks)
* **Objective:** Model a university people management system resolving diamond inheritance ambiguity.
* **Domain Relationships:**
  - `Student is-a Person` (Single Inheritance)
  - `Staff is-a Person` (Single Inheritance)
  - `TeachingAssistant is-a Student` AND `is-a Staff` (Multiple / Diamond Hybrid Inheritance)
  - `ResearchScholar is-a Student` (Multilevel Inheritance)
  - `ResearchScholar has-a Fellowship` (Object Composition)
* **Diamond Resolution:**
  - Without `virtual`, `TeachingAssistant` contains two copies of `Person`, causing `ambiguous request for member 'name'` compiler errors.
  - Resolved using `virtual public Person` in `Student` and `Staff`. A single shared `Person` subobject is instantiated.
* **Predict the Output:**
  - With `virtual`: `Person Student Staff TA `
  - Without `virtual`: `Person Student Person Staff TA `
* **Access Table:** Evaluated visibility of public, protected, and private members across public, protected, and private derivation modes.

### Task 3: Constructors in Derived Classes and Member Classes (9 Marks)
* **Objective:** Master member initializer lists, virtual base class constructor delegation, and construction/destruction ordering rules.
* **Core Rules:**
  1. Virtual base classes are constructed first, invoked directly by the most-derived class (`TeachingAssistant`).
  2. Non-virtual direct base classes are constructed in the order they appear in the class-head derivation list.
  3. Member objects are constructed in the exact order of their declaration in the class definition.
  4. Derived constructor body executes last.
  5. Destructors execute in exact reverse order of construction.
* **Predict the Output:**
  - Program with `Car` containing `Engine e` derived from `Vehicle`:
    Output: `Vehicle Engine Car | ~Car ~Engine ~Vehicle `
* **Complete the Code:** Completed TODO 1 in `Student` constructor using initializer list. Evaluated compiler warning `-Wreorder` when member initialization order differs from declaration order.
* **Alternative Analysis:** Dynamic pointer `Address* home` vs member object composition. Evaluated heap allocator latency, pointer footprint (8 bytes), and enforcement of the Rule of Five.

### Task 4: Pointers to Derived Classes: Forensics (7 Marks)
* **Objective:** Forensic analysis of dynamic dispatch, non-virtual destructor memory leaks, and object slicing in banking software.
* **Forensic Diagnoses:**
  1. *Rate defect:* `rate()` was non-virtual in base class, causing early/static binding to `Account::rate()` (3.5%) instead of `SeniorAccount::rate()` (4.0%).
  2. *Memory leak:* Non-virtual destructor in base `Account` caused `delete a;` to skip `~SeniorAccount()`, leaking the dynamic `double* history` array (800 bytes).
  3. *Object slicing:* Assigning `SeniorAccount` to an `Account` value sliced away the derived members and reset dynamic dispatch to `Account`.
* **Predict the Output:**
  - Code: `std::cout << p->rate() << ' ' << p->vrate() << ' ' << copy.vrate();`
  - Output: `3.5 4 3.5`
* **Repaired Program:** Enforced `virtual ~Account() = default;`, `virtual double rate() const`, `override`, and smart pointers (`std::unique_ptr<Account>`).

### Task 5: Pointers to Objects and the `this` Pointer (7 Marks)
* **Objective:** Implement grocery app shopping cart with method chaining and pointer arithmetic.
* **Four Ways to Access Objects:**
  1. Directly by name (Stack)
  2. Through pointer via `->`
  3. Through reference alias via `.`
  4. Dynamically on heap via `new` / `delete`
* **`this` Pointer Mechanics:**
  - Returning `*this` by reference (`Cart&`) enables fluid method chaining: `c.add("Rice", 60).add("Dal", 120).setDiscount(10);`
  - Explaining returning `Cart` by value: Modifies temporary discarded copies, leaving original cart empty.
  - Parameter disambiguation: `this->discount = discount;`
* **Highest Total Search:** Pointer arithmetic `*(activeCarts + i)` finding maximum value cart in an array of pointers in $O(n)$ time.
* **Alternative Analysis:** Array of pointers vs `std::vector<Cart>`. Highlighted pointer invalidation vulnerability during vector capacity reallocation.

### Task 6: Design Challenge – Vehicle Rental Fleet (13 Marks)
* **Objective:** Design and implement a robust, extensible Vehicle Rental Fleet hierarchy adhering strictly to the Open/Closed Principle (OCP).
* **Hierarchy Architecture:**
  - `Vehicle` (Abstract Base Class with pure virtual `calculateRentalCharge`, `displayDetails`, `getVehicleType`)
  - `Bicycle` : public `Vehicle` (Non-motorized)
  - `MotorVehicle` : public `Vehicle` (Member: `Date serviceDueDate`, attribute: `fuelOrChargeLevel`)
  - `TwoWheeler` : public `MotorVehicle` (Refueling deficit penalty)
  - `Car` : public `MotorVehicle` (Seating capacity luxury tax + refueling penalty)
  - `ElectricCar` : public `MotorVehicle` (Charged per kWh, battery capacity, green discount)
  - `ElectricBus` : public `MotorVehicle` (Stage 5 extension demonstrating zero-modification extensibility)
* **Fleet Management System:** Polymorphic fleet array `Vehicle* fleet[MAX_CAPACITY]` executing rentals, returns, late charge calculations (50% surcharge), and detailed billing reports.

---

## 4. Verification and Execution Steps

To compile and execute any task independently, open a terminal in the respective task directory and execute:

```powershell
# Example: Running Task 01
cd "C:\c++\DSA0117--C-G_Vishnu_Madhav_27\Assignment 4\Task01"
g++ -std=c++17 -Wall -Wextra task01_class_design_review.cpp -o task01.exe
.\task01.exe

# Example: Running Task 06 (Design Challenge)
cd "C:\c++\DSA0117--C-G_Vishnu_Madhav_27\Assignment 4\Task06"
g++ -std=c++17 -Wall -Wextra task06_vehicle_rental_fleet.cpp -o task06.exe
.\task06.exe
```

All 6 programs compile cleanly with **0 warnings and 0 errors** under `g++ -std=c++17 -Wall -Wextra`. Full execution logs and terminal screenshots are available in each task folder.
