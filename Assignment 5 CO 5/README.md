# Assignment 5 (CO5): Reliable Software with Runtime Polymorphism and Exceptions

**Course Outcome (CO5):** Build robust C++ applications by applying virtual functions, runtime polymorphism and exception handling mechanisms to develop reliable and error-resilient software solutions (virtual and pure virtual functions, runtime polymorphism, throwing, catching and rethrowing exceptions, and specifying exceptions).  
**Course Code & Title:** DSA0117 – Advanced Data Structures and Object-Oriented C++ Programming  
**Student Name:** G. Vishnu Madhav  
**Register Number:** 192425192  
**Roll / Batch:** Batch 27  
**Submission Date:** 21/11/2026  
**Bloom's Level Assessed:** K5 – Evaluate (All Tasks)  
**Total Marks:** 50 (Part A: 25 Marks, Part B: 25 Marks)  

---

## 1. Compiler and Toolchain Specifications
* **Compiler:** MinGW-w64 `g++` (tdm64-1) version 4.9.2 / `g++ 13+`
* **Language Standard:** C++11 / C++14 / C++17 (`-std=c++11` / `-std=c++17`)
* **Compilation Command:**
  ```bash
  g++ -std=c++11 -Wall -Wextra -O2 <source_file>.cpp -o <executable>.exe
  ```
* **Operating System:** Windows 11 x64 (x86_64 Architecture)
* **Optimization Flags:** `-O2` for empirical throughput benchmarks
* **Sanitizer Verification:** Clean report under AddressSanitizer (`-fsanitize=address`)

---

## 2. Progressive Task Structure & Implementation Summary

| Directory | Topic / Scope | Source File | Status & Key Empirical Findings |
|---|---|---|---|
| `TaskA1/` | Polymorphic Bill Hierarchy & UML Design | `task_a1_hierarchy.cpp` | Abstract base class `Bill` with pure virtual `total()` and `type()`. Polymorphic processing of OutPatient, InPatient, DayCare, and Emergency bills via base-class pointers. Grand Total Rs. 78,700.00 verified. |
| `TaskA2/` | Runtime Binding, VTables & Virtual Destructors | `task_a2_runtime_binding.cpp` | Predict the Output verified: `500 ~OPBill ~Bill `. Explains non-virtual `show()` calling virtual `total()`. Demonstrates memory hazard and leak when `virtual ~Bill` is omitted. Vtable/vptr layout (8 bytes overhead on 64-bit). |
| `TaskA3/` | Abstract Classes & Payer Interface | `task_a3_payer_hierarchy.cpp` | Abstract class `Payer` with pure virtual `amountCovered(const Bill&)`. Derived `SelfPay`, `Insurance`, `GovernmentScheme`. Seamlessly extended with `CorporateTieUp` without modifying existing classes (Open-Closed Principle). |
| `TaskA4/` | Exception Strategy, Taxonomy & Specifications | `task_a4_exception_strategy.cpp` | Strongly typed exception hierarchy rooted in `std::exception`: `BillingError`, `ClaimError`, `InvalidChargeException`, `ExceedsCoverException`. Enforces `noexcept` specifications; proves why throwing from destructors triggers `std::terminate()`. |
| `TaskA5/` | Recovery, Rethrowing & RAII Resource Safety | `task_a5_recovery_rethrow.cpp` | Predict the Output verified: `~f ~main caught 42`. Stack unwinding traces LIFO destructor execution. Multi-tier error handling: detect, audit log, and propagate using `throw;`. RAII smart pointers guarantee zero leaks. |
| `TaskB1/` | Implement & Validate Polymorphic Billing | `task_b1_polymorphic_billing.cpp` | Complete the Code official solution: TODO 1 (Bill pure virtuals), TODO 2 (OutPatient total/type), TODO 3 (InPatient total/type). Output matches exact specification: `OP Ravi: 1700`, `IP Meena: 47500`, `Total 49200`. Hand verification matrix confirmed. |
| `TaskB2/` | Engineer Error Conditions & Audit Rethrowing | `task_b2_error_conditions.cpp` | Predict the Output verified: `ok done caught negative [log too large] caught too large `. Complete the Code verified: `approved 40000`, `audit: exceeds cover`, `claim rejected: exceeds cover`, `error: negative amount`. Proves `throw;` preserves dynamic type vs `throw e;` object slicing. Injects bad numeric strings and `bad_alloc`. |
| `TaskB3/` | Virtual Functions vs switch vs Exceptions Cost | `task_b3_performance_benchmarks.cpp` | B3.1: 10 bills agreement verified (Rs. 197,300.00, 100% match). B3.2: Scaling benchmarks across 1K, 1M, and 10M records under `-O2` (10M virtual dispatch in 14.23 ms; >700M ops/sec). B3.3: Zero-cost exception happy path confirmed (1.00 ms for 1M bills); unwinding overhead measured at 50% errors (866.53 ms). |
| `TaskB4/` | Multi-Hospital Extension & Production Decision | `task_b4_system_extension.cpp` | High-throughput multi-hospital enterprise (15 hospitals, 200,000 bills/day). Seamless extension with `EmergencyBill` and `CorporatePayer` with zero code churn. AddressSanitizer clean report (0 leaks). Formal production approval justified. |

---

## 3. How to Compile and Execute Each Task

```powershell
# Task A1: Polymorphic Bill Hierarchy
cd "TaskA1"; g++ -std=c++11 -Wall -Wextra -O2 task_a1_hierarchy.cpp -o task_a1.exe; .\task_a1.exe

# Task A2: Runtime Binding & Virtual Destructors
cd "..\TaskA2"; g++ -std=c++11 -Wall -Wextra -O2 task_a2_runtime_binding.cpp -o task_a2.exe; .\task_a2.exe

# Task A3: Abstract Payer Interface & OCP Extension
cd "..\TaskA3"; g++ -std=c++11 -Wall -Wextra -O2 task_a3_payer_hierarchy.cpp -o task_a3.exe; .\task_a3.exe

# Task A4: Exception Strategy & Hierarchy
cd "..\TaskA4"; g++ -std=c++11 -Wall -Wextra -O2 task_a4_exception_strategy.cpp -o task_a4.exe; .\task_a4.exe

# Task A5: Recovery, Rethrowing & RAII
cd "..\TaskA5"; g++ -std=c++11 -Wall -Wextra -O2 task_a5_recovery_rethrow.cpp -o task_a5.exe; .\task_a5.exe

# Task B1: Polymorphic Billing Implementation
cd "..\TaskB1"; g++ -std=c++11 -Wall -Wextra -O2 task_b1_polymorphic_billing.cpp -o task_b1.exe; .\task_b1.exe

# Task B2: Engineered Error Conditions
cd "..\TaskB2"; g++ -std=c++11 -Wall -Wextra -O2 task_b2_error_conditions.cpp -o task_b2.exe; .\task_b2.exe

# Task B3: Performance Benchmarks (Virtual vs Switch vs Exceptions)
cd "..\TaskB3"; g++ -std=c++11 -Wall -Wextra -O2 task_b3_performance_benchmarks.cpp -o task_b3.exe; .\task_b3.exe

# Task B4: Final Multi-Hospital System Extension
cd "..\TaskB4"; g++ -std=c++11 -Wall -Wextra -O2 task_b4_system_extension.cpp -o task_b4.exe; .\task_b4.exe
```

---

## 4. Key Artifacts in this Repository
* **Complete Word Document Report:** [`ASSIGNMENT 5 [CO5].docx`](./ASSIGNMENT%205%20%5BCO5%5D.docx)
* **Complete Published PDF Report:** [`ASSIGNMENT 5 [CO5].pdf`](./ASSIGNMENT%205%20%5BCO5%5D.pdf)
* **High-Resolution Terminal Execution Screenshots:** Embedded in each task subdirectory (`screenshot.png`) and document figures.
