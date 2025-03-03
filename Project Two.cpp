#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Course structure to hold course details
struct Course {
    string id;
    string title;
    vector<string> prerequisites;
};

// Node structure for Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Function prototypes
void LoadData(const string& fileName, Node*& root);
void InsertCourse(Node*& root, Course course);
void PrintAllCourses(Node* root);
void PrintCourse(Node* root, const string& courseId);
Node* SearchCourse(Node* root, const string& courseId);

// Function to load data from file
void LoadData(const string& fileName, Node*& root) {
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, prereq;
        getline(ss, id, ',');
        getline(ss, title, ',');
        Course course = {id, title, {}};
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }
        InsertCourse(root, course);
    }
    file.close();
    cout << "Data loaded successfully." << endl;
}

// Function to insert course into the BST
void InsertCourse(Node*& root, Course course) {
    if (!root) root = new Node(course);
    else if (course.id < root->course.id) InsertCourse(root->left, course);
    else InsertCourse(root->right, course);
}

// Function to print all courses in alphanumeric order
void PrintAllCourses(Node* root) {
    if (root) {
        PrintAllCourses(root->left);
        cout << root->course.id << ": " << root->course.title << endl;
        PrintAllCourses(root->right);
    }
}

// Function to search for a course
Node* SearchCourse(Node* root, const string& courseId) {
    if (!root || root->course.id == courseId) return root;
    else if (courseId < root->course.id) return SearchCourse(root->left, courseId);
    else return SearchCourse(root->right, courseId);
}

// Function to print course details
void PrintCourse(Node* root, const string& courseId) {
    Node* result = SearchCourse(root, courseId);
    if (result) {
        cout << result->course.id << ": " << result->course.title << endl;
        if (!result->course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const string& prereq : result->course.prerequisites) cout << prereq << " ";
            cout << endl;
        } else cout << "No prerequisites." << endl;
    } else cout << "Course not found." << endl;
}

// Main function with menu
int main() {
    Node* root = nullptr;
    string fileName;
    int choice;

    do {
        cout << "\n1: Load Data" << endl;
        cout << "2: Print All Courses" << endl;
        cout << "3: Print Course and Prerequisites" << endl;
        cout << "9: Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> fileName;
                LoadData(fileName, root);
                break;
            case 2:
                PrintAllCourses(root);
                break;
            case 3:
                string courseId;
                cout << "Enter Course ID: ";
                cin >> courseId;
                PrintCourse(root, courseId);
                break;
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
