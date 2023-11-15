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
    string id; // Format: student_id:course_id
    string student_id;
    string course_id;
    string grade;
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
        // Add sample course grades
        addNew("S001:CMAT10", "S001", "CMAT10", "A");
        addNew("S002:CBIO10", "S002", "CBIO10", "B");
        addNew("S003:CPHY10", "S003", "CPHY10", "C");
        addNew("S004:CCHE10", "S004", "CCHE10", "A");
    }

    // add new 
    static bool addNew(const string& id, const string& student_id, const string& course_id, const string& grade) {
        bool exists = course_grades_list.nodeExists(id);

        if (!exists) {
            CourseGrade data = {id, student_id, course_id, grade};
            course_grades_list.addNode(id, data);

            // Update the academic tree with the grade information
            Student student_data = StudentList::getData(student_id);
            Course course_data = CourseList::getData(course_id);

            string info = student_data.name + " / " + course_data.name + " / Grade: " + grade;

            // Should add course grade to tree (under course enrollment)
            AcademicTree::addCourseGrade(student_id, course_id, id, info);

            return true;
        } else {
            return false; // Node with the same id already exists
        }
    }

    // update existing
   static bool update(const string& student_id, const string& course_id, const string& new_grade) {
    string id = student_id + ":" + course_id;
    bool exists = course_grades_list.nodeExists(id);

    if (exists) {
        Node<CourseGrade>* node = course_grades_list.findNode(id);
        CourseGrade& data = node->data;

        // Save the old grade for display purposes
        string old_grade = data.grade;

        // Update the grade
        data.grade = new_grade;

        // Display the update information
        UI::showLine("Grade for " + data.id + " (Student ID: " + data.student_id +
                     ", Course ID: " + data.course_id + ") updated from " +
                     old_grade + " to " + new_grade);
        return true;
    } else {
        return false; // Node with that id does not exist
    }
}



    // delete existing
    static bool remove(const string& id) {
        bool exists = course_grades_list.nodeExists(id);

        if (exists) {
            course_grades_list.deleteNode(id);

            // Also remove from tree
            AcademicTree::removeCourseGrade(id);
            return true;
        } else {
            return false; // Node with that id does not exist
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
        row.push_back(data.student_id);
        row.push_back(data.course_id);
        row.push_back(data.grade);

        table_rows.push_back(row); // add to rows
    }

    static void showTable(const string& title) {
        tableInitRows();

        // use anonymous callback function to build rows
        // add row one by one per node
        course_grades_list.traverse(tableAddRow);

        const string headers[] = {"Id", "Student Id", "Course Id", "Grade"};
        int col_sizes[] = {6, 10, 10, 6};
        int num_cols = 4;

        UI::showEmptyLine(1);
        UI::showTable(title, headers, table_rows, col_sizes, num_cols);
        UI::showEmptyLine(1);
    }

};
