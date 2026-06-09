# CodeAlpha C++ Internship Projects

This directory contains three C++ console applications developed for the CodeAlpha C++ Internship Program.

## Project Folders

```text
CodeAlpha-CGPA-Calculator/
|-- taskcode.cpp
|-- CMakeLists.txt
`-- README.md

CodeAlpha-Login-Registration-System/
|-- taskcode.cpp
|-- CMakeLists.txt
`-- README.md

CodeAlpha-Banking-System/
|-- taskcode.cpp
|-- CMakeLists.txt
`-- README.md
```

## Included Projects

### Task 1: CGPA Calculator

Calculates semester GPA and overall CGPA from course grades and credit units.

### Task 2: Login and Registration System

Registers users, validates passwords, stores password hashes in a local file, and verifies logins.

### Task 4: Banking System

Creates bank accounts, supports deposits, withdrawals, transfers, balance checks, customer details, and transaction history.

## Build Any Project

```bash
cd <Project-Folder>
cmake -S . -B build
cmake --build build
```

The executable is generated inside the `build` directory.
