# CGPA Calculator (C++)

This project is a console-based CGPA Calculator built in C++ for CodeAlpha Task 1.

## Features

- Calculate GPA for one semester.
- Calculate CGPA across multiple semesters.
- Record course code, grade, and credit unit for each course.
- Validate grades and credit units.
- Display course grades, semester GPA, and final CGPA.
- Group semesters into academic years.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

Linux or macOS:

```bash
./build/CGPACalculator
```

Windows:

```bash
build\CGPACalculator.exe
```

## Menu Options

| Option | Action |
| --- | --- |
| 1 | Calculate GPA for a single semester |
| 2 | Calculate CGPA across semesters |
| 3 | Exit |

## Calculation Logic

- Grade Point = Grade Value x Credit Unit
- Semester GPA = Total Grade Points / Total Credit Units
- CGPA = Sum of Grade Points / Sum of Credit Units

## Limitations

- Results are not saved after the program exits.
- The grade scale is fixed at A-F.
