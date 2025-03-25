//============================================================================
// Name        : ProjectOneVector.cpp
// Author      : Dennis Ward
// Version     : 1.0
//============================================================================
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

struct Course {
    string courseId;
    string description;
    vector<string> preReq;

    void print() const {
        cout << "Course Department: " << courseId << endl;
        cout << "Description: " << description << endl;
        if (preReq.size() > 0) {
            cout << "Pre-requisites: ";
            for (const auto& i : preReq) {
                cout << i;
                if (i != preReq.back()) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

int partition(vector<Course>& courses, int begin, int end) {
    // set low and high equal to begin and end
    int lowIndex = begin;
    int highIndex = end;
    // pick the middle element as pivot point
    Course pivot = courses[lowIndex + (highIndex - lowIndex) / 2];
    // while not done
    while (lowIndex <= highIndex) {
        while (courses[lowIndex].courseId <
            pivot.courseId) { // keep incrementing low index while courses[low]
            // <courses[pivot]
            ++lowIndex;
        }
        while (pivot.courseId <
            courses[highIndex].courseId) { // keep decrementing high index
            --highIndex;
        }
        if (lowIndex <= highIndex) {
            std::swap(courses[lowIndex],
                courses[highIndex]); // else swap the low and high courses
            ++lowIndex;                    // move low and high closer ++low, --high
            --highIndex;
        }
    }
    return lowIndex; // return high;
}

/**
 * Perform a quick sort on bid courseId
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param courses address of the vector<Course> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Course>& courses, int begin, int end) {
    if (begin >= end) {
        return;
    }
    int p = partition(courses, begin, end); // final index of pivot
    quickSort(courses, begin,
        p - 1);           // recursively sort low partition (begin to mid-1)
    quickSort(courses, p, end); // recursively sort high partition (mid to end)
}

Course search(vector<Course>& courses, string courseId) {
    // Iterate through the courses vector
    for (const Course& course : courses) {
        if (course.courseId == courseId) {
            return course;
            break;
        }
    }
    Course course;
    return course; // Return an empty Course object if no matching course is found
}

string getUserInput(string message) {
    string inp;
    cout << message;
    getline(cin, inp);
    return inp;
}
/*******************************************************************/
string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}
/// read file into vector
void readInFileVector(const string& filename, vector<Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
    }
    string line;
    while (getline(file, line)) {
        Course course;
        stringstream ss(line);
        getline(ss, course.courseId, ',');
        getline(ss, course.description, ',');
        string preReq;
        while (getline(ss, preReq, ',')) {
            course.preReq.push_back(trim(preReq));
        }
        courses.push_back(course);
    }
}

bool validateVector(vector<Course>& courses) {
    bool adjusted = false;
    for (int i = 0; i < courses.size();) {
        const auto& course = courses[i];
        if (course.courseId.empty() || course.description.empty()) { // check fields
            // cout << "Invalid course: " << course.courseId << endl;
            courses.erase(courses.begin() + i); // remove and decrement
            adjusted = true;
            i--;
            continue; // next iteration
        }
        for (const auto& preReq : course.preReq) { // iterate through prereqs
            if (!preReq.empty()) {
                bool found = false;
                for (const auto& c : courses) { // check if course exists
                    if (c.courseId == preReq) {   // if found->true->break
                        found = true;
                        break;
                    }
                }
                if (!found) { // if !found print, remove, decrement and break
                    // cout << "Error: Course " << course.courseId << " has a prerequisite
                    // " << preReq << " which does not exist" << endl;
                    courses.erase(courses.begin() + i);
                    adjusted = true;
                    --i;
                    break;
                }
            }
        }
        ++i; // next course
    }
    return adjusted;
}

int main() {
    vector<Course> courses;
    string filename = "info.csv";

    clock_t ticks;
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Print Courses" << endl;
        cout << "  3. Search Courses" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            
            cin.ignore();
            filename = getUserInput("Enter filename: ");
            ticks = clock();
            readInFileVector(filename, courses);
            bool adjusted = validateVector(courses);
            while (adjusted) {
                adjusted = validateVector(courses);
            }

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            cout << "File loaded" << endl;
            break;
        }
        case 2: {
            cout << endl;
            quickSort(courses, 0, courses.size() - 1);
            for (const auto& course : courses) {
                course.print();
            }
            break;
        }
        case 3: {
            cin.ignore();
            Course course =
                search(courses, getUserInput("Please input course ID of course to search: "));
            cout << endl;
            if (course.courseId.empty()) {
                cout << "Course not found" << endl;
            }
            else {
                course.print();
            }
            break;
        }
        case 4: {
            cout << "We will run the Load and Validate 1000 times" << endl;
            clock_t total_ticks = 0;
            // add get file name
            for (int i = 0; i < 1000; i++) {
                courses.clear();//this ensures the proccess doesn count growing to a large number
                ticks = clock();
                readInFileVector("info.csv", courses);
                bool adjusted = validateVector(courses);
                while (adjusted) {
                    adjusted = validateVector(courses);
                }
                ticks = clock() - ticks;
                total_ticks += ticks;
            }
            cout << "Total ticks Taken: " << total_ticks << endl;
            break;
        }
        case 9: {
            cout << "Good Bye!" << endl;
            return 0;
            break;
        }
        }
    }
    cout << "Good Bye!" << endl;
    return 0;
}
