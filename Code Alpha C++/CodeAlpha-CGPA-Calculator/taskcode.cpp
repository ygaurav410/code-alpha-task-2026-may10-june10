#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int getInt(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        try
        {
            size_t processed = 0;
            int value = std::stoi(input, &processed);
            if (processed == input.size())
            {
                return value;
            }
        }
        catch (...)
        {
        }

        std::cout << "Invalid input! Try again.\n";
    }
}

std::string getString(const std::string &prompt)
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

char getGradeInput(const std::string &prompt)
{
    while (true)
    {
        std::string input = getString(prompt);
        if (!input.empty())
        {
            return static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));
        }

        std::cout << "Invalid input! Try again.\n";
    }
}

bool askToContinue()
{
    while (true)
    {
        std::string choice = getString("\nDo you want to perform another calculation? (y/n): ");

        if (choice == "y" || choice == "Y")
        {
            return true;
        }

        if (choice == "n" || choice == "N")
        {
            std::cout << "\nThank you for using the console app. Exiting...\n";
            return false;
        }

        std::cout << "Invalid choice! Please enter y or n.\n";
    }
}

std::string ordinalSuffix(int value)
{
    if (value % 100 >= 11 && value % 100 <= 13)
    {
        return "th";
    }

    switch (value % 10)
    {
    case 1:
        return "st";
    case 2:
        return "nd";
    case 3:
        return "rd";
    default:
        return "th";
    }
}

int getAcademicYears(int semesters)
{
    return (semesters + 1) / 2;
}

int gradeToPoint(char grade)
{
    switch (std::toupper(static_cast<unsigned char>(grade)))
    {
    case 'A':
        return 5;
    case 'B':
        return 4;
    case 'C':
        return 3;
    case 'D':
        return 2;
    case 'E':
        return 1;
    case 'F':
        return 0;
    default:
        return -1;
    }
}

class Course
{
private:
    std::string courseCode;
    char grade = 'F';
    int gradePoint = 0;
    int creditUnit = 0;

public:
    bool setGrade(char newGrade)
    {
        int point = gradeToPoint(newGrade);
        if (point < 0)
        {
            return false;
        }

        grade = static_cast<char>(std::toupper(static_cast<unsigned char>(newGrade)));
        gradePoint = point;
        return true;
    }

    char getGrade() const
    {
        return grade;
    }

    void setCreditUnit(int unit)
    {
        creditUnit = unit;
    }

    int getCreditUnit() const
    {
        return creditUnit;
    }

    void setCourseCode(const std::string &code)
    {
        courseCode = code;
    }

    std::string getCourseCode() const
    {
        return courseCode;
    }

    int getCreditPoints() const
    {
        return gradePoint * creditUnit;
    }
};

class Semester
{
private:
    std::vector<Course> courses;
    int totalCreditUnits = 0;
    int totalCreditPoints = 0;

public:
    void addCourse(const Course &course)
    {
        courses.push_back(course);
        totalCreditUnits += course.getCreditUnit();
        totalCreditPoints += course.getCreditPoints();
    }

    const std::vector<Course> &getCourses() const
    {
        return courses;
    }

    int getTotalCreditUnits() const
    {
        return totalCreditUnits;
    }

    int getTotalCreditPoints() const
    {
        return totalCreditPoints;
    }

    double getGPA() const
    {
        if (totalCreditUnits == 0)
        {
            return 0.0;
        }

        return static_cast<double>(totalCreditPoints) / totalCreditUnits;
    }
};

class AcademicSession
{
private:
    std::vector<Semester> semesters;

public:
    void addSemester(const Semester &semester)
    {
        semesters.push_back(semester);
    }

    const std::vector<Semester> &getSemesters() const
    {
        return semesters;
    }

    double getCGPA() const
    {
        int totalCreditUnits = 0;
        int totalCreditPoints = 0;

        for (const Semester &semester : semesters)
        {
            totalCreditUnits += semester.getTotalCreditUnits();
            totalCreditPoints += semester.getTotalCreditPoints();
        }

        if (totalCreditUnits == 0)
        {
            return 0.0;
        }

        return static_cast<double>(totalCreditPoints) / totalCreditUnits;
    }
};

Course inputCourse(int courseNumber)
{
    Course course;

    std::cout << "\n----------- Course " << courseNumber << " -----------\n";
    course.setCourseCode(getString("Course Code: "));

    while (true)
    {
        char grade = getGradeInput("Grade (A-F): ");
        if (course.setGrade(grade))
        {
            break;
        }

        std::cout << "Invalid grade! Enter A, B, C, D, E, or F.\n";
    }

    while (true)
    {
        int creditUnit = getInt("Credit Unit (1-6): ");
        if (creditUnit >= 1 && creditUnit <= 6)
        {
            course.setCreditUnit(creditUnit);
            break;
        }

        std::cout << "Credit unit must be between 1 and 6.\n";
    }

    return course;
}

Semester inputSemester(int semesterNumber)
{
    Semester semester;

    std::cout << "\n"
              << semesterNumber << ordinalSuffix(semesterNumber)
              << " Semester\n";

    int numberOfCourses = 0;
    while (numberOfCourses < 1)
    {
        numberOfCourses = getInt("Enter number of courses: ");
        if (numberOfCourses < 1)
        {
            std::cout << "You must enter at least one course.\n";
        }
    }

    for (int i = 1; i <= numberOfCourses; ++i)
    {
        semester.addCourse(inputCourse(i));
    }

    return semester;
}

void printSemesterResult(const Semester &semester)
{
    std::cout << "\n========================================\n";
    std::cout << "           SEMESTER RESULT\n";
    std::cout << "========================================\n";

    for (const Course &course : semester.getCourses())
    {
        std::cout << course.getCourseCode()
                  << "  ->  " << course.getGrade() << "\n";
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nGPA FOR THIS SEMESTER: " << semester.getGPA() << "\n";
}

void calculateGPA()
{
    std::cout << "\n========================================\n";
    std::cout << "        GPA CALCULATION (SEMESTER)\n";
    std::cout << "========================================\n";

    Semester semester = inputSemester(1);
    printSemesterResult(semester);
}

void calculateCGPA()
{
    std::cout << "\n==== CALCULATING CGPA FOR ACADEMIC SESSION ====\n";

    int numberOfSemesters = 0;
    while (numberOfSemesters < 1)
    {
        numberOfSemesters = getInt("\nEnter total number of semesters: ");
        if (numberOfSemesters < 1)
        {
            std::cout << "You must have at least one semester.\n";
        }
    }

    AcademicSession session;
    int academicYears = getAcademicYears(numberOfSemesters);

    for (int year = 1; year <= academicYears; ++year)
    {
        std::cout << "\n===== ACADEMIC YEAR " << year << " =====\n";

        for (int semesterInYear = 1; semesterInYear <= 2; ++semesterInYear)
        {
            int semesterNumber = (year - 1) * 2 + semesterInYear;
            if (semesterNumber > numberOfSemesters)
            {
                break;
            }

            Semester semester = inputSemester(semesterNumber);
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "\nGPA for this semester: " << semester.getGPA() << "\n";
            session.addSemester(semester);
        }
    }

    std::cout << "\n===== COMPLETE ACADEMIC RESULT =====\n";

    const std::vector<Semester> &semesters = session.getSemesters();
    for (size_t i = 0; i < semesters.size(); ++i)
    {
        std::cout << "\nSemester " << i + 1 << "\n";
        for (const Course &course : semesters[i].getCourses())
        {
            std::cout << course.getCourseCode()
                      << " -> " << course.getGrade() << "\n";
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nFINAL CGPA: " << session.getCGPA() << "\n";
}

int main()
{
    while (true)
    {
        std::cout << "\n========================================\n";
        std::cout << "        WELCOME TO CGPA CALCULATOR\n";
        std::cout << "========================================\n";

        std::cout << "\nSelect an option below:\n";
        std::cout << "----------------------------------------\n";
        std::cout << "  1. Calculate GPA (Single Semester)\n";
        std::cout << "  2. Calculate CGPA (Academic Session)\n";
        std::cout << "  3. Exit Application\n";
        std::cout << "----------------------------------------\n";

        int choice = getInt("Enter your choice (1-3): ");

        if (choice == 1)
        {
            calculateGPA();
            if (askToContinue())
            {
                continue;
            }
            break;
        }

        if (choice == 2)
        {
            calculateCGPA();
            if (askToContinue())
            {
                continue;
            }
            break;
        }

        if (choice == 3)
        {
            std::cout << "\n========================================\n";
            std::cout << "   Thank you for using CGPA Calculator\n";
            std::cout << "            Goodbye\n";
            std::cout << "========================================\n";
            break;
        }

        std::cout << "\nInvalid choice! Please select 1, 2 or 3.\n";
    }

    return 0;
}
