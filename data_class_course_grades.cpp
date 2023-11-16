#pragma once

#include "base_class_linkedlist.cpp"
#include "base_class_ui.cpp"
#include "data_class_students.cpp"
#include "data_class_courses.cpp"

#include "data_tree_academic.cpp"

using namespace std;

// table_rows placeholder for showTable related (used in traverse in addTableRow)
// wrapped in IF because it's also defined in other data classes
#ifndef _TABLE_ROWS_FOR_DISPLAY
vector<vector<string>> table_rows;
#define _TABLE_ROWS_FOR_DISPLAY
#endif

// Define a simple struct as an example of data
struct CourseGrade {
    string id; 
    string name;
    string course_id;
    string grade;
    int mathgrade;
    int chemgrade;
    int biograde;
    int physicgrade;
};
struct CourseGradeInfo {
    string info;
};

template <class T>
struct AcademicTreeNode {
    T data;
    LinkedList<AcademicTreeNode<T> > children; 
};

LinkedList<CourseGrade> course_grades_list;

class CourseGradesList {

public:

    // add data for quick test
    static void init() {

        addNew("S001","Alice", "10", 80 , 95 , 76 , 69);
        addNew("S002","Charlie", "10", 60 , 55 , 57 , 77);


        addNew("S004","Brandon", "11", 71 , 75 , 66 , 74);
        addNew("S005","David", "11", 94, 85 , 56 , 88);

        addNew("S007","Francis", "12", 68, 85 , 81 , 86);
        addNew("S008","George", "12", 74, 56 , 79 , 88);
    }
    

    // add new 
    static bool addNew(const string& id, const string& name, const string& grade, const int& mathgrade, const int& chemgrade, const int& biograde, const int& physicgrade) {
        bool exists = course_grades_list.nodeExists(id);

        if (!exists) {
            CourseGrade data = {id, name, grade};
            course_grades_list.addNode(id, data);

            Student student_data = StudentList::getData(id);

        string info = student_data.name + " / Grade: " + grade;

        AcademicTree::addCourseGrade(id, grade, name, info);

        return true;
    } else {
        return false;
    }
}

    // update existing
   static bool update(const string& studentID, const string& courseID, const string& newGrade) {
    bool exists = course_grades_list.nodeExists(studentID);

    if (exists) {
        Node<CourseGrade>* node = course_grades_list.findNode(studentID);
        CourseGrade& data = node->data;

        // Check if the course ID matches
        if (data.course_id == courseID) {
            string oldGrade = data.grade;
            data.grade = newGrade;

            UI::showLine("Grade for " + data.id + " in course " + courseID + " updated from " +
                         oldGrade + " to " + newGrade);
            return true;
        } else {
            return false; // Course ID does not match
        }
    } else {
        return false; // Student ID not found
    }
}

    // delete existing
     static bool remove(const string& id) {
        bool exists = course_grades_list.nodeExists(id);

        if (exists) {
            course_grades_list.deleteNode(id);
            AcademicTree::removeCourseGrade(id);
            return true;
        } else {
            return false;
        }
    }

    // exists
    static bool exists(const string& id) {
        return course_grades_list.nodeExists(id);
    }

    // get data
    static CourseGrade getData(const string& id) {
        bool exists = course_grades_list.nodeExists(id);
        Node<CourseGrade>* node;
        CourseGrade data;
        if (exists) {
            node = course_grades_list.findNode(id);
            data = node->data;
        }
        return data;
    }

    // showTable related
     static void tableInitRows() {
        table_rows.clear();
    }

    static void tableAddRow(Node<CourseGrade>* node) {
    CourseGrade data = node->data;

    vector<string> row;
    row.push_back(data.id);
    row.push_back(data.name);
    row.push_back(data.grade);
    row.push_back(to_string(data.mathgrade));  // Convert int to string
    row.push_back(to_string(data.biograde));  // Convert int to string
    row.push_back(to_string(data.chemgrade));  // Convert int to string
    row.push_back(to_string(data.physicgrade));  // Convert int to string

    table_rows.push_back(row);
}


    static void showTable(const string& title) {
        tableInitRows();
        course_grades_list.traverse(tableAddRow);

        const string headers[] = {"Student Id", "Name", "Grade", "Math", "Biology", "Chemistry", "Physics"};
        int col_sizes[] = {6, 10, 10, 6, 6, 6, 6};
        int num_cols = 7;

        UI::showEmptyLine(1);
        UI::showTable(title, headers, table_rows, col_sizes, num_cols);
        UI::showEmptyLine(1);
    }
};
