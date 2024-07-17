#include <iostream>
#include <string>
using namespace std;

const int maxCourses = 10;
const int maxSemesters = 10;

class Course
{
    string courseName;
    char grade;
    int credits;

public:
    void setCourseName(string courseName) { this->courseName = courseName; }
    void setGrade(char grade) { this->grade = grade; }
    void setCredits(int credits) { this->credits = credits; }
    string getCourseName() { return courseName; }
    char getGrade() { return grade; }
    int getCredits() { return credits; }

    void displayCourse()
    {
        cout << "Course Name: " << courseName << ", Credits: " << credits << ", Grade: " << grade << endl;
    }

    double getGradePoints()
    {
        switch (grade)
        {
        case 'A':
        case 'a':
            return 4.0;
        case 'B':
        case 'b':
            return 3.0;
        case 'C':
        case 'c':
            return 2.0;
        case 'D':
        case 'd':
            return 1.0;
        default:
            return 0.0;
        }
    }
};

class Semester
{
    int numCourses;
    Course courses[maxCourses];

public:
    void setNumCourses(int numCourses) { this->numCourses = numCourses; }
    void addCourse(Course c, int index) { courses[index] = c; }
    int getNumCourses() { return numCourses; }
    Course getCourse(int index) { return courses[index]; }

    void displayCourses()
    {
        for (int i = 0; i < numCourses; i++)
        {
            cout << "Course " << i + 1 << ": ";
            courses[i].displayCourse();
        }
    }

    double calculateGPA()
    {
        double totalCredits = 0;
        double totalGradePoints = 0;

        for (int i = 0; i < numCourses; i++)
        {
            Course c = courses[i];
            totalCredits += c.getCredits();
            totalGradePoints += c.getCredits() * c.getGradePoints();
        }

        return totalGradePoints / totalCredits;
    }
};

class Student
{
    string name;
    int numSemesters;
    Semester semesters[maxSemesters];

public:
    void setName(string name) { this->name = name; }
    void setNumSemesters(int numSemesters) { this->numSemesters = numSemesters; }
    void addSemester(Semester s, int index) { semesters[index] = s; }
    string getName() { return name; }
    int getNumSemesters() { return numSemesters; }
    Semester getSemester(int index) { return semesters[index]; }

    void displaySemesters()
    {
        for (int i = 0; i < numSemesters; i++)
        {
            cout << "Semester " << i + 1 << ":\n";
            semesters[i].displayCourses();
            cout << "GPA of Semester " << i + 1 << ": " << semesters[i].calculateGPA() << endl;
        }
    }

    double calculateCGPA()
    {
        double totalGPA = 0;
        double totalCredits = 0;
        for (int i = 0; i < numSemesters; i++)
        {
            Semester s = semesters[i];
            totalGPA += s.calculateGPA(); // Summing up GPA of all semesters
            totalCredits += 1;            // Counting all the semester
        }
        return totalGPA / totalCredits;
    }
};

class CGPACalculator
{
    Student student;

public:
    void setStudent(Student s) { student = s; }

    void displayCGPA()
    {
        double cgpa = student.calculateCGPA();
        cout << "CGPA of " << student.getName() << ": " << cgpa << endl;
    }

    void displaySemesters()
    {
        student.displaySemesters();
    }
};

void enterCourseDetails(Semester &semester)
{
    cout << "Enter number of courses: ";
    int numCourses;
    cin >> numCourses;
    if (numCourses > maxCourses)
    {
        cout << "Number of courses exceeds the maximum allowed (" << maxCourses << ")." << endl;
        return;
    }
    semester.setNumCourses(numCourses);

    // Clear the input buffer before using getline after cin
    cin.ignore();

    for (int i = 0; i < numCourses; i++)
    {
        Course course;
        cout << "Enter course name: ";
        string courseName;
        getline(cin, courseName);
        course.setCourseName(courseName);

        cout << "Enter course credits: ";
        int credits;
        cin >> credits;
        course.setCredits(credits);

        cout << "Enter course grade: ";
        char grade;
        cin >> grade;
        course.setGrade(grade);

        semester.addCourse(course, i);

        // Clear the input buffer before using getline after cin
        cin.ignore();
    }
}

void enterSemesterDetails(Student &student)
{
    cout << "Enter number of semesters: ";
    int numSemesters;
    cin >> numSemesters;
    if (numSemesters > maxSemesters)
    {
        cout << "Number of semesters exceeds the maximum allowed (" << maxSemesters << ")." << endl;
        return;
    }
    student.setNumSemesters(numSemesters);

    for (int i = 0; i < numSemesters; i++)
    {
        Semester semester;
        cout << "Entering details for semester " << i + 1 << ":" << endl;
        enterCourseDetails(semester);
        student.addSemester(semester, i);
    }
}

int main()
{
    Student student;
    CGPACalculator calculator;

    cout << "Enter student name: ";
    string name;
    getline(cin, name);
    student.setName(name);

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Enter semester details\n";
        cout << "2. Display individual course details\n";
        cout << "3. Calculate and display CGPA\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            enterSemesterDetails(student);
            calculator.setStudent(student);
            break;
        case 2:
            calculator.displaySemesters();
            break;
        case 3:
            calculator.displayCGPA();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
