#include <iostream>
#include <string>
using namespace std;

class Course;
class Department;
class Student;
class Attendance;
class Employee;
class Result;
class Library;
class Book;
class Fees;

class Course 
{
public:
    int courseID;
    string courseName;
    int credits;
    Department* department;
    Student* studs_enrolled[100]; 
    int students_num;

    Course(int id, string name, int cr) : courseID(id), courseName(name), credits(cr), students_num(0) {}

    void addStudent(Student* student) 
    {
        if (students_num < 100) 
        {
            studs_enrolled[students_num++] = student;
        }
    }

    void removeStudent(Student* student) 
    {
        for (int i = 0; i < students_num; ++i) 
        {
            if (studs_enrolled[i] == student) 
            {
                studs_enrolled[i] = studs_enrolled[--students_num];
                break;
            }
        }
    }
};

class Department 
{
public:
    int deptID;
    string deptName;
    Course* courses[50]; 
    Employee* employees[50]; 
    int courseCount;
    int employee_num;

    Department(int id, string name) : deptID(id), deptName(name), courseCount(0), employee_num(0) {}

    void addCourse(Course* course) 
    {
        if (courseCount < 50) 
        {
            courses[courseCount++] = course;
            course->department = this;
        }
    }

    void addEmployee(Employee* employee) 
    {
        if (employee_num < 50) 
        {
            employees[employee_num++] = employee;
        }
    }
};

class Student 
{
public:
    int studentID;
    string name;
    string address;
    string phone;
    string dob;
    Course* courses[10]; 
    int courseCount;

    Student(int id, string name, string address, string phone, string dob) : studentID(id), name(name), address(address), phone(phone), dob(dob), courseCount(0) {}

    void take_course(Course* course) 
    {
        if (courseCount < 10) 
        {
            courses[courseCount++] = course;
            course->addStudent(this);
        }
    }

    void updateAddress(string newAddress) 
    {
        address = newAddress;
    }
};

class Attendance 
{
public:
    int attendanceID;
    Student* student;
    Course* course;
    string date;
    bool present;

    Attendance(int id, Student* stud, Course* crs, string date, bool pres) : attendanceID(id), student(stud), course(crs), date(date), present(pres) {}

};

class Employee 
{
public:
    int employeeID;
    string name;
    string address;
    string phone;
    string dob;
    double salary;

    Employee(int id, string name, string address, string phone, string dob, double salary) : employeeID(id), name(name), address(address), phone(phone), dob(dob), salary(salary) {}

    void updateSalary(double newSalary) 
    {
        salary = newSalary;
    }

    void updateAddress(string newAddress) 
    {
        address = newAddress;
    }
};

class Result 
{
public:
    Student* student;
    Course* course;
    double marks;
    string grade;
    int cgpa;

    Result(Student* stud, Course* crs, double mrk) : student(stud), course(crs), marks(mrk) {}

    string grads(Student* student, Course* course, double marks) 
    {
        if (marks>50 && marks<100)
        {
            grade="A";
            return grade;
        }
        else 
        {
            grade='B';
            return grade;
        }  

    }

    float cal_cgpa(Student* student, Course* course, double marks)
    {
        cgpa = marks/10.0;
        return cgpa;
    }
};

class Library 
{
public:
    int libID;
    string libraryName;
    Student* studs_registered[100];
    Book* books[1000]; 
    int students_num;
    int bookCount;

    Library(int id, string name) : libID(id), libraryName(name), students_num(0), bookCount(0) {}

    void registerStudent(Student* student) 
    {
        if (students_num < 100) 
        {
            studs_registered[students_num++] = student;
        }
    }

    void addBook(Book* book) 
    {
        if (bookCount < 1000) 
        {
            books[bookCount++] = book;
        }
    }
};

class Book 
{
public:
    int bookID;
    string title;
    string author;
    Library* library;

    Book(int id, string title, string author) : bookID(id), title(title), author(author), library(nullptr) {}

    void choose_lib(Library* lib) 
    {
        library = lib;
    }
};

class Fees 
{
public:
    int feeID;
    Student* student;
    double amount;
    string dueDate;
    bool paid;

    Fees(int id, Student* stud, double amt, string date) : feeID(id), student(stud), amount(amt), dueDate(date), paid(false) {}

    void payment(double amt) 
    {
        if (amt >= amount) 
        {
            paid = true;
        }
    }
};

class Factory 
{
public:
    static Student* createStudent(int id, string name, string address, string phone, string dob) 
    {
        return new Student(id, name, address, phone, dob);
    }

    static Course* createCourse(int id, string name, int credits) 
    {
        return new Course(id, name, credits);
    }

    static Department* createDepartment(int id, string name) 
    {
        return new Department(id, name);
    }
};

int main() 
{

    Student* student = Factory::createStudent(1, "Ram", "Jainagar", "58975665", "2000-01-01");
    Course* course = Factory::createCourse(101, "Integration", 3);
    Department* department = Factory::createDepartment(10, "Mathematics");

    Fees* fees = new Fees(1, student, 500.0, "2022-05-01");
    Library* library = new Library(1001, "KLE_Library");
    Book* book = new Book(1001, "C++", "Charles");
    Attendance* attendance = new Attendance(1, student, course, "2022-05-01", true);
    Employee* employee = new Employee(1, "Shyam", "Vidyanagar", "78965423", "2024-11-25", 50000.0);
    Result* result = new Result(student, course, 50.0);

    string res = result->grads(student, course, 50.0);
    float cg = result->cal_cgpa(student, course, 25);

    student->take_course(course);
    department->addCourse(course);

    Student* student2 = Factory::createStudent(2, "Laxman", "Vijaynagar", "522875665", "2005-03-21");
    course->addStudent(student2);

    cout << "----------------------------------------------------------------" << endl;
    cout << "Student1 Details:" << endl;
    cout << "ID: " << student->studentID << endl;
    cout << "Name: " << student->name << endl;
    cout << "Address: " << student->address << endl;
    cout << "Phone: " << student->phone << endl;
    cout << "Date of Birth: " << student->dob << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Student2 Details:" << endl;
    cout << "ID: " << student2->studentID << endl;
    cout << "Name: " << student2->name << endl;
    cout << "Address: " << student2->address << endl;
    cout << "Phone: " << student2->phone << endl;
    cout << "Date of Birth: " << student2->dob << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Course Details:" << endl;
    cout << "ID: " << course->courseID << endl;
    cout << "Name: " << course->courseName << endl;
    cout << "Credits: " << course->credits << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Department Details:" << endl;
    cout << "ID: " << department->deptID << endl;
    cout << "Name: " << department->deptName << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Fee Details:" << endl;
    cout << "Amount: " << fees->amount << endl;
    cout << "Due Date: " << fees->dueDate << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Library Details:" << endl;
    cout << "ID: " << library->libID << endl;
    cout << "Name: " << library->libraryName << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Book Details:" << endl;
    cout << "ID: " << book->bookID << endl;
    cout << "Title: " << book->title << endl;
    cout << "Author: " << book->author << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Attendance Details:" << endl;
    cout << "Date: " << attendance->date << endl;
    cout << "Present: " << attendance->present << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Employee Details:" << endl;
    cout << "ID: " << employee->employeeID << endl;
    cout << "Name: " << employee->name << endl;
    cout << "Address: " << employee->address << endl;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Result Details:" << endl;
    cout << "Marks: " << result->marks << endl;
    cout << "Grade: " << res << endl;
    cout << "CGPA: " << cg << endl;

    return 0;
}