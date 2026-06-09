# CodeAlpha C++ Internship Projects

This repository contains three C++ console applications developed for the CodeAlpha C++ Internship Program.

Each project demonstrates object-oriented programming, input validation, file-backed persistence where needed, and menu-driven console interaction.

## Repository Structure

```text
Code Alpha C++/
|-- CodeAlpha-CGPA-Calculator/
|   |-- taskcode.cpp
|   |-- CMakeLists.txt
|   `-- README.md
|-- CodeAlpha-Login-Registration-System/
|   |-- taskcode.cpp
|   |-- CMakeLists.txt
|   `-- README.md
|-- CodeAlpha-Banking-System/
|   |-- taskcode.cpp
|   |-- CMakeLists.txt
|   `-- README.md
`-- README.md
```

## Projects

### Task 1: CGPA Calculator

Folder: `Code Alpha C++/CodeAlpha-CGPA-Calculator`

The CGPA Calculator computes student performance across one or more semesters.

Features:
- Calculate GPA for a single semester.
- Calculate CGPA across multiple semesters.
- Capture course code, grade, and credit unit for each course.
- Display course grades, semester GPA, and final CGPA.
- Group semesters into academic years.

### Task 2: Login and Registration System

Folder: `Code Alpha C++/CodeAlpha-Login-Registration-System`

The Login and Registration System lets users register and log in using stored credentials.

Features:
- Register users with username and password validation.
- Prevent duplicate usernames.
- Store password hashes in a local file.
- Verify login credentials.
- Show clear success and error messages.

### Task 4: Banking System

Folder: `Code Alpha C++/CodeAlpha-Banking-System`

The Banking System simulates common account operations.

Features:
- Create customer accounts.
- Deposit and withdraw funds.
- Transfer funds between accounts.
- View balances and customer details.
- Track timestamped transaction history.
- Validate input for account and transaction operations.

## Build Instructions

Build any project from its own folder:

```bash
cd "Code Alpha C++/<Project-Folder>"
cmake -S . -B build
cmake --build build
```

Run the generated executable from the `build` directory.

## Technologies

- C++17
- CMake
- Standard C++ libraries
- GCC, Clang, or MSVC-compatible compiler

## Author

GAURAV YADAV

C++ Intern at CodeAlpha
