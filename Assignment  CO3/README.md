# Assignment 3 (CO3): Constructors, Destructors and Operator Overloading in C++

**Course Outcome (CO3):** Construct C++ programs using constructors, destructors and operator overloading to control object creation, destruction and operator behaviour – default, parameterised, overloaded, copy and dynamic constructors, destructors, defining and overloading operators, and the rules for operator overloading.  
**Course Code:** DSA0117 - Object-Oriented Programming with C++  
**Student Name:** G. Vishnu Madhav  
**Register Number:** 192425192  
**Roll / Batch:** Batch 27  
**Submission Date:** 07/11/2026  
**Bloom's Level Assessed:** K5 – Evaluate (All Questions)  
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

---

## 2. Progressive Task Structure & Implementation Summary

| Directory | Topic / Focus | Source File | Status & Key Finding |
|---|---|---|---|
| `Q1/` | Constructors & Overloading | `q01_constructors.cpp` | Library Book: default, parameterized, overloaded, and constructor delegation. Explicit constructor prevents narrowing/conversion. Non-negative copies verified. |
| `Q2/` | Deep Copy & Rule of Three | `q02_copy_constructor.cpp` | Hospital Prescription: demonstrates shallow copy crash (double delete). Implements deep copy constructor, copy assignment operator, and destructor (TODO 1-3). |
| `Q3/` | Dynamic Allocation & RAII | `q03_dynamic_constructors.cpp` | Auditorium seat map: 2D allocation with new/delete. RAII guarantees automatic deallocation. Logger prediction verified: `+A +B -B copyAc use -Ac +P -P end -A`. |
| `Q4/` | Overloading Arithmetic & Stream | `q04_operator_overloading.cpp` | Money: operator+, +=, ==, <<, >> storing paise in long long. TODO 1 & 2 verified: `Rs 200.00 
 true`. Carry test: Rs 0.75 + Rs 0.50 = Rs 1.25. |
| `Q5/` | Increment & Subscript Overloading | `q05_subscript_increment.cpp` | TrackTimer prefix vs postfix ++ with dummy int. Counter prediction verified (`5 7 7`). Playlist operator[] with const and non-const bounds checking. |
| `Q6/` | Rules of Operator Overloading | `q06_rules_operator_overload.cpp` | SMS Gateway Text: dynamic char[], operator+, ==, !=, <<. Non-overloadable operators evaluated (::, ., .*, ?:, sizeof). Self-assignment safe. |
| `Q7/` | Complex AC Circuit Impedance | `q07_complex_impedance.cpp` | Complex class from first principles. Series RLC (100 + 30j Ohm, 104.40 Ohm mag) and Parallel RC (3.85 - 19.23j Ohm, 19.61 Ohm mag). Division by zero trapped. |

---

## 3. How to Compile and Execute Each Question

```powershell
# Q1: Constructors & Delegation
cd "Q1"; g++ -std=c++11 -Wall -Wextra q01_constructors.cpp -o q1.exe; .\q1.exe

# Q2: Deep Copy Constructor & Rule of Three
cd "..\Q2"; g++ -std=c++11 -Wall -Wextra q02_copy_constructor.cpp -o q2.exe; .\q2.exe

# Q3: Dynamic Constructors & RAII
cd "..\Q3"; g++ -std=c++11 -Wall -Wextra q03_dynamic_constructors.cpp -o q3.exe; .\q3.exe

# Q4: Operator Overloading (+, ==, <<)
cd "..\Q4"; g++ -std=c++11 -Wall -Wextra q04_operator_overloading.cpp -o q4.exe; .\q4.exe

# Q5: Increment & Subscript Operators
cd "..\Q5"; g++ -std=c++11 -Wall -Wextra q05_subscript_increment.cpp -o q5.exe; .\q5.exe

# Q6: Rules of Operator Overloading
cd "..\Q6"; g++ -std=c++11 -Wall -Wextra q06_rules_operator_overload.cpp -o q6.exe; .\q6.exe

# Q7: AC Circuit Complex Calculator
cd "..\Q7"; g++ -std=c++11 -Wall -Wextra q07_complex_impedance.cpp -o q7.exe; .\q7.exe
```
