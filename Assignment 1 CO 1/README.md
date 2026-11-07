# Assignment 1 (CO1): Design, Implement and Validate the Fare Logic of a City Metro Smart-Card System

**Course Outcome (CO1):** Apply object-oriented programming principles and C++ constructs such as data types, operators and control structures to design and write structured OOP-based programs.  
**Course Code:** DSA0117 - Object-Oriented Programming with C++  
**Student Name:** G. Vishnu Madhav  
**Register Number:** 192425192  
**Roll / Batch:** Batch 27  
**Submission Date:** 07-11-2026  
**Bloom's Level Assessed:** K5 – Evaluate (All Tasks)  
**Total Marks:** 50  

---

## 1. Compiler and Toolchain Specifications
* **Compiler:** MinGW64 `g++` (tdm64-1) version 4.9.2 (or `g++ 13+` compatible)
* **Language Standard:** C++11 / C++14 (`-std=c++11`)
* **Compilation Command:**
  ```bash
  g++ -std=c++11 -Wall -Wextra <source_file>.cpp -o <executable>.exe
  ```
* **Operating System:** Windows 11 x64
* **IDE / Shell:** Windows PowerShell / Developer Console

---

## 2. Progressive Task Structure & Implementation Summary

| Directory | Topic / Focus | Source File | Status & Key Finding |
|---|---|---|---|
| `Task01/` | OOP Domain Modeling | `task01_oop_analysis.cpp` | Identifies `SmartCard`, `Passenger`, `Journey`, `Zone`, `FareTable`. Invariant balance $\ge$ Rs 50.00 strictly enforced. |
| `Task02/` | Tokens & Constexpr Constants | `task02_tokens_constants.cpp` | 5 token types categorized; `#define` vs `const` vs `constexpr` evaluated; `enum class Zone` prevents implicit conversions. |
| `Task03/` | Data Types & Precision Limits | `task03_datatypes_compatibility.cpp` | Evaluates `sizeof` and ranges from `<climits>`; proves money must be stored as integer paise to prevent IEEE 754 float drift. |
| `Task04/` | Implicit Conversions | `task04_implicit_conversions.cpp` | Output prediction verified (3 3.5, C 68, 1 true, s >= u); explains integral promotion and signed/unsigned comparison. |
| `Task05/` | Operator Precedence | `task05_expressions_precedence.cpp` | Output prediction verified (11 16, 9 6 4, 6 4, 3 1 -3 -1, 18); details post/pre-increment and negative truncation. |
| `Task06/` | Control Structures | `task06_control_structures.cpp` | Completes TODO 1 & 2 using `switch` and integer paise; validates 10:00 and 20:00 as off-peak boundary conditions. |
| `Task07/` | Procedural vs Object-Oriented | `task07_procedural_vs_oop.cpp` | Demonstrates failure of procedural approach (negative balance); proves OOP private balance preserves invariants. |
| `Task08/` | Safe Input & Output Streams | `task08_safe_io.cpp` | Recovers gracefully from non-numeric input using `cin.clear()` / `cin.ignore()`; formats tables with `<iomanip>`. |
| `Task09/` | Testing & Boundary Matrix | `task09_fare_logic_testing.cpp` | 9-case automated test suite covering zones, peak boundaries, concessions, and exact Rs 50 remaining (100% Pass). |
| `Task10/` | Scale Benchmarks & Overflow | `task10_expectations_execution.cpp` | Simulates 20K, 500K, 3M trips; shows `double` drifts by paise; proves 32-bit `int` overflows at 7.26 Cr paise (long long required). |
| `Task11/` | Recommended Enterprise Architecture | `task11_final_design.cpp` | Production modular design; stress-tested at 100,000 transactions processed in <15 ms ($O(1)$ time and space). |
| `Task12/` | Day-4 Design Challenge | `task12_day4_challenge.cpp` | Extends system with Airport Zone (Rs 60), 10% non-combining Weekend Discount, and `MonthlyPass` (2-zone free travel). |

---

## 3. How to Compile and Execute Each Task

Navigate to the task folder and execute the standard commands:

### Task 01: OOP Analysis & Invariants
```powershell
cd "Task01"
g++ -std=c++11 -Wall -Wextra task01_oop_analysis.cpp -o task01.exe
.\task01.exe
```

### Task 02: Tokens and Constexpr Fares
```powershell
cd "..\Task02"
g++ -std=c++11 -Wall -Wextra task02_tokens_constants.cpp -o task02.exe
.\task02.exe
```

### Task 03: Data Types, Precision & Scale
```powershell
cd "..\Task03"
g++ -std=c++11 -Wall -Wextra task03_datatypes_compatibility.cpp -o task03.exe
.\task03.exe
```

### Task 04: Implicit Conversions
```powershell
cd "..\Task04"
g++ -std=c++11 -Wall -Wextra task04_implicit_conversions.cpp -o task04.exe
.\task04.exe
```

### Task 05: Operator Precedence & Associativity
```powershell
cd "..\Task05"
g++ -std=c++11 -Wall -Wextra task05_expressions_precedence.cpp -o task05.exe
.\task05.exe
```

### Task 06: Control Structures (Complete-the-Code)
```powershell
cd "..\Task06"
g++ -std=c++11 -Wall -Wextra task06_control_structures.cpp -o task06.exe
.\task06.exe
```

### Task 07: Procedural vs Object-Oriented
```powershell
cd "..\Task07"
g++ -std=c++11 -Wall -Wextra task07_procedural_vs_oop.cpp -o task07.exe
.\task07.exe
```

### Task 08: Safe Console I/O and Formatted Reports
```powershell
cd "..\Task08"
g++ -std=c++11 -Wall -Wextra task08_safe_io.cpp -o task08.exe
.\task08.exe
```

### Task 09: Test Matrix and Verification Bench
```powershell
cd "..\Task09"
g++ -std=c++11 -Wall -Wextra task09_fare_logic_testing.cpp -o task09.exe
.\task09.exe
```

### Task 10: Scale Simulation and Overflow Analysis
```powershell
cd "..\Task10"
g++ -std=c++11 -Wall -Wextra task10_expectations_execution.cpp -o task10.exe
.\task10.exe
```

### Task 11: Final Recommended Architecture
```powershell
cd "..\Task11"
g++ -std=c++11 -Wall -Wextra task11_final_design.cpp -o task11.exe
.\task11.exe
```

### Task 12: Day-4 Design Challenge
```powershell
cd "..\Task12"
g++ -std=c++11 -Wall -Wextra task12_day4_challenge.cpp -o task12.exe
.\task12.exe
```

---

## 4. Progressive Commit Audit Trail
In accordance with assignment guidelines, development was executed and committed progressively across 13 distinct git commits covering every individual task milestone.
