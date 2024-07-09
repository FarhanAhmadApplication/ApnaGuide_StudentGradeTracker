// Student Grade Tracker

// Build a program to manage student grades for a class.
// Allow users to input student information (name, ID) along with their grades for assignments and exams.
// Calculate and display overall grades, class averages, and perform basic statistical analysis. Display class toppers(Top 3).

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

vector<pair<int, double>> sortByVal(map<int, double> &percentage)
{
    vector<double> percentage1;
    vector<int> index1;
    vector<pair<int, double>> ma;
    for (auto it = percentage.begin(); it != percentage.end(); it++)
    {
        percentage1.push_back(it->second);
    }
    sort(percentage1.begin(), percentage1.end(), greater<double>());
    for (int i = 0; i < percentage1.size(); i++)
    {
        for (auto it = percentage.begin(); it != percentage.end(); it++)
        {
            if (it->second == percentage1[i])
            {
                index1.push_back(it->first);
            }
        }
    }
    percentage.clear();
    cout << endl;
    for (int i = 0; i < index1.size(); i++)
    {
        ma.emplace_back(index1[i], percentage1[i]);
    }
    return ma;
}

// Creating A StudentTracer Class
class StudentTracker
{
public:
    // Declaring attributes of class
    string name;                                 // To store name of student
    int id;                                      // To store id of student
    vector<double> grade_assignment, grade_exam; // To store grades of student in assignment and exam
    map<int, double> percentage;

    StudentTracker() {}

    // Constructor for Student Tracker Class
    StudentTracker(string name, int id, vector<double> grade_assignment, vector<double> grade_exam)
    {
        this->name = name;
        this->id = id;
        this->grade_assignment = grade_assignment;
        this->grade_exam = grade_exam;
    }
    // To print the corresponding vector
    template <class T>
    void print_vector(vector<T> &vec)
    {
        for (T grade : vec)
        {
            cout << grade << " ";
        }
        cout << endl;
    }

    // To display details of a students
    void display(vector<StudentTracker> studentdetails)
    {
        for (int i = 0; i < studentdetails.size(); i++)
        {
            cout << "Name of student " << (i + 1) << " is: " << studentdetails[i].name << endl;
            cout << "ID of student " << (i + 1) << " is: " << studentdetails[i].id << endl;
            cout << "Grade in assignment of student " << (i + 1) << " are: ";
            print_vector(studentdetails[i].grade_assignment);
            cout << "Grade in Exam of student " << (i + 1) << " are: ";
            print_vector(studentdetails[i].grade_exam);
            cout << endl;
        }
    }

    // To display average
    void show_average(vector<StudentTracker> &grade)
    {
        double avg = 0.0;
        double tot = 0.0;
        for (int i = 0; i < grade[0].grade_assignment.size(); i++)
        {
            for (int j = 0; j < grade.size(); j++)
            {
                tot += grade[j].grade_assignment[i] + grade[j].grade_exam[i];
            }
            avg = tot / grade.size();
            tot = 0;
            cout << "Average in subject " << i + 1 << " is " << avg << endl;
        }
        cout << endl;
    }

    void calculate_number_of_each_student(vector<StudentTracker> &vec, int x)
    {
        double tot = 0.0;
        for (int i = 0; i < vec.size(); i++)
        {
            for (int j = 0; j < vec[0].grade_exam.size(); j++)
            {
                tot += vec[i].grade_assignment[j] + vec[i].grade_exam[j];
            }
            percentage.insert(make_pair(i, tot / vec[0].grade_exam.size()));
            tot = 0;
        }
        show_topper(percentage, vec);
    }

    // To display Topper
    void show_topper(map<int, double> &percentage, vector<StudentTracker> na)
    {
        vector<int> values;
        vector<double> per;
        int count = 0;
        vector<pair<int, double>> vec;
        vec = sortByVal(percentage);
        for (auto &i : vec)
        {
            if (count < 3)
            {
                values.push_back(i.first);
                per.push_back(i.second);
                count++;
            }
        }
        for (int i = values.size() - 1; i >= 0; i--)
        {
            if (i == 0)
                cout << "Topper is " << endl;
            else if (i == 1)
                cout << "Second is" << endl;
            else
                cout << "Third is" << endl;
            cout << "Name: " << na[values[i]].name << endl;
            cout << "ID: " << na[values[i]].id << endl;
            cout << "Grade Assignments are: ";
            print_vector(na[values[i]].grade_assignment);
            cout << "Grade Exams are: ";
            print_vector(na[values[i]].grade_exam);
            cout << "Percentage is: " << per[i] << endl;
            cout << endl;
        }
    }
};

// End of class StudentTracker

int main()
{
    vector<StudentTracker> studentdetails; // Vector for StudentTracker class to store details of all students
    string name;                           // To take name as input
    int id;                                // To take id as input
    double grade;                          // To take input of grade in assignment and exam as input
    vector<double> ga, ge;                 // To store grade in assignment and exam with the input in grade
    char choice;                           // To check if user wants to insert more details of a student
    int n;                                 // To take no of subjects as inputs
    cout << "Enter how many subjects grade you want to insert ";
    cin >> n;

    // Loop for taking details of a student
    do
    {
        name = "";
        id = 0;
        ga.clear();
        ge.clear();
        cout << "Enter name of student ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter id of student ";
        cin >> id;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter grade assignment in subject " << i + 1 << " Please Enter numbers out of 20 " << endl;
            cin >> grade;
            if (grade > 20)
            {
                cout << "Please enter assignment grade out of 20 ";
                return 0;
            }
            ga.push_back(grade);
            cout << "Enter grade exam in subject " << i + 1 << " Please Enter numbers out of 80 " << endl;
            cin >> grade;
            if (grade > 80)
            {
                cout << "Please enter exam grade out of 80";
                return 0;
            }
            ge.push_back(grade);
        }
        StudentTracker st(name, id, ga, ge); // Invoking constructor of StudentTracker class
        studentdetails.push_back(st);        // To store details of students in vector <studentdetails>
        cout << "Do you want to give more details (y/n)" << endl;
        cin >> choice;
    } while (choice == 'y');
    StudentTracker st;
    cout << endl;
    cout << "Showing Details of every student: " << endl;
    cout << endl;
    st.display(studentdetails);
    cout << "Showing Average Marks in Each Subject " << endl;
    cout << endl;
    st.show_average(studentdetails);
    cout << "Showing Topper of Class " << endl;
    cout << endl;
    st.calculate_number_of_each_student(studentdetails, 1);
    return 0;
}