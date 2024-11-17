#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <limits> // Add this line to include the <limits> header
#include<fstream>
using namespace std;

// Structure to hold student information
//node to hold result of students

struct Student {
    int id;
    string name;
    int age;
    vector<int> results;
};
// Node structure for binary tree
struct Node {//binary search tree
    Student data;
    Node* left;
    Node* right;
};

// Function to enroll a new student
// Function to enroll a new student
void enrollStudent(Node*& root, stack<Node*>& stack) {
    Node* newNode = new Node;
    cout << "Enter student ID: ";
    cin >> newNode->data.id;

    // Clear input buffer
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter student name: ";
    getline(cin, newNode->data.name);
    cout << "Enter student age: ";
    cin >> newNode->data.age;

    //Clear input buffer
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter student results (separated by spaces): or letter to stop";
    int result;
    while (cin >> result) {
        newNode->data.results.push_back(result);

    }

    // Clear input buffer
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    newNode->left = nullptr;
    newNode->right = nullptr;
    // Insert the student in the binary tree
    if (root == nullptr) {
        root = newNode;
    } else {
        Node* current = root;
        while (true) {
            if (newNode->data.id < current->data.id) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }

    // Push the student in the stack
    stack.push(newNode);

    cout << "Student enrolled successfully!\n";
}

// Function to display all enrolled students using a breadth-first search traversal
void displayStudents(Node* root) {
    cout << "Enrolled Students:\n";
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        cout << "ID: " << current->data.id << ", Name: " << current->data.name << ", Age: " << current->data.age << "\n";
        if (current->left != nullptr) {
            queue.push(current->left);
        }
        if (current->right != nullptr) {
            queue.push(current->right);
        }
    }
}

// Function to search for a student by ID using binary search

// Function to search for a student by ID using binary search
// Function to search for a student by ID using binary search
Node* searchStudent(Node* root, int targetID) {
    Node* current = root;
    while (current != nullptr && current->data.id != targetID) {
        if (targetID < current->data.id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}


// Inorder traversal of the binary tree to retrieve all students
void inorderTraversal(Node* root, vector<Student>& students) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, students);
    students.push_back(root->data);
    inorderTraversal(root->right, students);
}

// Function to calculate the average result for a student
double calculateAverageResult(const Student& student) {
    int sum = 0;
    for (int result : student.results) {
        sum += result;
    }
    return static_cast<double>(sum) / student.results.size();
}

// Function to display the average result for each student
void displayAverageResults(const vector<Student>& students) {
    cout << "Average Results:\n";
    for (const auto& student : students) {
        double average = calculateAverageResult(student);
        cout << "ID: " << student.id << ", Name: " << student.name << ", Average Result: " << average << "\n";
    }
}
void display(){
    cout<<"\n\n\n\n";
cout << "\t\tStudent Management System\n";
        cout << "\t\t\t1. Enroll Student\n";
        cout << "\t\t\t2. Display Students\n";
        cout << "\t\t\t3. Search Student by ID\n";
        cout << "\t\t\t4. Sort Students by ID\n";
        cout << "\t\t\t5. Display Average Results\n";
        cout<<"\t\t\t6. About\n";
        cout<<"\t\t\t7. Developer\n";
        cout << "\t\t\t8. Exit\n";
        cout << "\t\t\tEnter your choice: ";

}
void about();
void Developer();
int main() {
    Node* root = nullptr; // Binary tree root node
    stack<Node*> stack; // Stack to store student nodes
    vector<Student> students; // Vector to store student records

    int choice;

    do {
        // Display menu
        display();
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                cout<<"\n\t\t\tAdd a student\n\n";
                enrollStudent(root, stack);
                break;
            case 2:
                displayStudents(root);
                break;
            case 3: {
                int targetID;
                cout << "Enter student ID to search: ";
                cin >> targetID;
                cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Node* foundStudent = searchStudent(root, targetID);
                if (foundStudent != nullptr) {
                    cout << "Student found! ID: " << foundStudent->data.id << ", Name: " << foundStudent->data.name << ", Age: " << foundStudent->data.age << "\n";
                } else {
                    cout << "Student not found!\n";
                }
                break;
            }
            case 4:
                inorderTraversal(root, students);
                //sortStudentsByID(students);
                cout << "Students sorted by ID:\n";
                for (const auto& student : students) {
                    cout << "ID: " << student.id << ", Name: " << student.name << ", Age: " << student.age << "\n";
                }
                break;
            case 5:
                inorderTraversal(root, students);
                displayAverageResults(students);
                break;
            case 6:
                about();
                break;
            case 7:
                Developer();
                break;
            case 8:
                cout << "Exiting the program...\n";
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 8);

    // Clean up dynamically allocated memory
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        delete node;
    }
    root = nullptr;

    return 0;
}

void about(){
string about = R"(This code is a C++ program that implements a Student Management System.
It allows you to enroll students, display enrolled students, search for students by ID, sort students by ID,
and display the average results for each student.

Here's a breakdown of the code:

The program includes several header files, such as
<iostream>, <string>, <vector>, <stack>, <queue>, <cstdlib>, <limits>, and <fstream>, which provide necessary functionalities.
The program defines two structures: Result and Student. The Result structure holds the data for each result of a student,
and the Student structure holds the information for each student, including ID, name, age, and a vector of results.

The program also defines a structure called Node for implementing a binary search tree. Each node contains a Student
object as data and pointers to the left and right child nodes.

The main function consists of a menu-driven program loop that allows you to perform various operations.

The enrollStudent function is used to enroll a new student. It prompts the user to enter
 student details, including ID, name, age, and results.

The displayStudents function performs a breadth-first search traversal
of the binary tree to display all enrolled students.

The searchStudent function searches for a student by ID using a binary
search algorithm and returns a pointer to the found student node.

The inorderTraversal function performs an inorder traversal of the
binary tree to retrieve all students and stores them in a vector.

The sortStudentsByID function uses the selection sort algorithm to
sort the students in the vector by their ID.

The calculateAverageResult function calculates the average result for a given student.

The displayAverageResults function displays the average result for each student.

The main function uses a switch-case statement to handle the user's menu choices.
It calls the corresponding functions based on the selected option.

At the end of the program, dynamically allocated memory is cleaned up by deleting
the nodes in the binary tree.

Overall, this program provides basic functionality for managing student records,
including enrollment, searching, sorting, and displaying average results.
)"
;
cout<<about;
}

