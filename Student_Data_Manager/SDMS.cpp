#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Class to store student data
class Student
{
    int rollNumber;
    char fullName[50];
    int englishMarks, mathsMarks, scienceMarks, language2Marks, computerMarks;
    double averageMarks;
    char grade;

public:
    void inputData();
    void displayData() const;
    void calculateGrade();
    int getRollNumber() const;
};
// class ends here

void Student::calculateGrade()
{
    averageMarks = (englishMarks + mathsMarks + scienceMarks + language2Marks + computerMarks) / 5.0;
    if (averageMarks >= 90)
        grade = 'A';
    else if (averageMarks >= 75)
        grade = 'B';
    else if (averageMarks >= 50)
        grade = 'C';
    else
        grade = 'F';
}

void Student::inputData()
{
    cout << "Enter student's roll number: ";
    cin >> rollNumber;

    cout << "Enter student's full name: ";
    cin.ignore();
    cin.getline(fullName, 50);

    cout << "\n\nEnter Student's Marks (out of 100 for each subject)" << endl;

    cout << "English: ";
    cin >> englishMarks;

    cout << "Maths: ";
    cin >> mathsMarks;

    cout << "Science: ";
    cin >> scienceMarks;

    cout << "Second Language: ";
    cin >> language2Marks;

    cout << "Computer Science: ";
    cin >> computerMarks;

    calculateGrade();
}

void Student::displayData() const
{
    cout << "\nRoll Number: " << rollNumber;
    cout << "\nFull Name: " << fullName;
    cout << "\nEnglish: " << englishMarks;
    cout << "\nMaths: " << mathsMarks;
    cout << "\nScience: " << scienceMarks;
    cout << "\nSecond Language: " << language2Marks;
    cout << "\nComputer Science: " << computerMarks;
    cout << "\nAverage Marks: " << averageMarks;
    cout << "\nGrade: " << grade;
}

int Student::getRollNumber() const
{
    return rollNumber;
}

// Function declarations
void createStudent();
void displayStudent(int); // display particular record
void displayAllStudents(); // display all records
void deleteStudent(int); // delete particular record
void modifyStudent(int); // edit particular record

// Main Function
int main()
{
    char choice;
    cout << setprecision(2);

    do
    {
        int searchRoll;
        system("cls");
        cout << "Welcome to Student Data Management System" << endl;
        cout << "\nMENU" << endl;
        cout << "1. Create new student data" << endl;
        cout << "2. Search student data" << endl;
        cout << "3. Display all student data" << endl;
        cout << "4. Delete student data" << endl;
        cout << "5. Modify student data" << endl;
        cout << "6. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        system("cls");

        switch (choice)
        {
        case '1':
            createStudent();
            break;
        case '2':
            cout << "\n\n\tEnter the roll number: ";
            cin >> searchRoll;
            displayStudent(searchRoll);
            break;
        case '3':
            displayAllStudents();
            break;
        case '4':
            cout << "\n\n\tEnter the roll number: ";
            cin >> searchRoll;
            deleteStudent(searchRoll);
            break;
        case '5':
            cout << "\n\n\tEnter the roll number: ";
            cin >> searchRoll;
            modifyStudent(searchRoll);
            break;
        case '6':
            cout << "Exiting, Thank you!";
            exit(0);
        }
    } while (choice != '6');
    return 0;
}

// Write Student Details to File
void createStudent()
{
    Student stud;
    ofstream outFile("student.dat", ios::binary | ios::app);
    stud.inputData();
    outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    outFile.close();
    cout << "\nStudent's record has been created ";
    cin.ignore();
    cin.get();
}

// Read File Records
void displayAllStudents()
{
    Student stud;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened! Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        stud.displayData();
        cout << "\n\n====================================\n";
    }

    inFile.close();
    cin.ignore();
    cin.get();
}

// Read Specific Record Based on Roll Number
void displayStudent(int roll)
{
    Student stud;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened... Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        if (stud.getRollNumber() == roll)
        {
            stud.displayData();
            found = true;
        }
    }

    inFile.close();
    if (!found)
        cout << "\n\nRecord does not exist";
    cin.ignore();
    cin.get();
}

// Modify Record for Specified Roll Number
void modifyStudent(int roll)
{
    bool found = false;
    Student stud;
    fstream file("student.dat", ios::binary | ios::in | ios::out);
    if (!file)
    {
        cout << "File could not be opened. Press any key to exit...";
        cin.ignore();
        cin.get();
        return;
    }

    while (!file.eof() && !found)
    {
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char*>(&stud), sizeof(Student));
        if (stud.getRollNumber() == roll)
        {
            stud.displayData();
            cout << "\nEnter new student details:" << endl;
            stud.inputData();
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&stud), sizeof(Student));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }

    file.close();
    if (!found)
        cout << "\n\nRecord Not Found";
    cin.ignore();
    cin.get();
}

// Delete Record with Particular Roll Number
void deleteStudent(int roll)
{
    Student stud;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened... Press any key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile("Temp.dat", ios::out | ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        if (stud.getRollNumber() != roll)
        {
            outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}