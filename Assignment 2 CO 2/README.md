# Assignment 2 (CO2): Functions and Object-Oriented Concepts in C++

**Course Outcome (CO2):** Design C++ programs by applying functions and object-oriented concepts – function prototyping, call by reference, return by reference, inline functions, default arguments, function overloading, specifying a class, member functions, access specifiers, arrays within a class, static data members and member functions, arrays of objects and friend functions.  
**Course Code:** DSA0117 - Object-Oriented Programming with C++  
**Student Name:** G. Vishnu Madhav  
**Register Number:** 192425192  
**Roll / Batch:** Batch 27  
**Submission Date:** 31/10/2026  
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
| `Q1/` | Call by Value, Reference, Pointer | `q01_call_by_ref.cpp` | Compares value, ref, and pointer. TODO 1 implemented (concession updates caller fee). Predict matches: `1 12 13`, `1 100`, `16 13 6`. |
| `Q2/` | Return by Reference & Dangers | `q02_return_by_ref.cpp` | Return reference to array element supports L-value mutation (+2). Dangling local ref warned by compiler. Vector reallocation danger analyzed. |
| `Q3/` | Default Arguments & Overloading | `q03_default_overload.cpp` | Resolves compiler ambiguity in courier charge. Implements non-conflicting overloads for grams (int), kg (double), and `Parcel`. |
| `Q4/` | Class with Internal Array | `q04_class_array.cpp` | Savings account mini-statement with internal array of 10 transactions. Circular indexing $O(1)$ prevents array shifting. Scope resolution `::` used. |
| `Q5/` | Static Members & Arrays of Objects | `q05_static_members.cpp` | Token prediction verified (`101 103 104 4`). BusTicket TODO 1 & 2 allocate seats up to CAPACITY 3, routing excess to Waiting list. Static persistence verified. |
| `Q6/` | Friend Functions & Inline Functions | `q06_friend_inline.cpp` | Friend functions `minutesBetween` (205) and `earlier` (false). Hand verification across noon. 10,000,000 call inline benchmark at -O0 vs -O2. |
| `Q7/` | Day-4 Design Challenge | `q07_day4_challenge.cpp` | Diagnoses $O(k)$ shifting bottleneck in Q4. Designs Circular Ring Buffer achieving $O(1)$ constant time. Validates >15x speedup over 1M transactions. |

---

## 3. How to Compile and Execute Each Question

```powershell
# Q1: Call by Reference
cd "Q1"; g++ -std=c++11 -Wall -Wextra q01_call_by_ref.cpp -o q1.exe; .\q1.exe

# Q2: Return by Reference
cd "..\Q2"; g++ -std=c++11 -Wall -Wextra q02_return_by_ref.cpp -o q2.exe; .\q2.exe

# Q3: Function Overloading
cd "..\Q3"; g++ -std=c++11 -Wall -Wextra q03_default_overload.cpp -o q3.exe; .\q3.exe

# Q4: Class with Internal Array
cd "..\Q4"; g++ -std=c++11 -Wall -Wextra q04_class_array.cpp -o q4.exe; .\q4.exe

# Q5: Static Members
cd "..\Q5"; g++ -std=c++11 -Wall -Wextra q05_static_members.cpp -o q5.exe; .\q5.exe

# Q6: Friend Functions & Inlining
cd "..\Q6"; g++ -std=c++11 -Wall -Wextra q06_friend_inline.cpp -o q6.exe; .\q6.exe

# Q7: Day-4 Challenge (Circular Buffer)
cd "..\Q7"; g++ -std=c++11 -Wall -Wextra q07_day4_challenge.cpp -o q7.exe; .\q7.exe
```
