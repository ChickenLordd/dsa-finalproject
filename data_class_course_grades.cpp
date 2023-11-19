#pragma once

#include "base_class_linkedlist.cpp"
#include "base_class_ui.cpp"
#include "data_class_students.cpp"
#include "data_class_courses.cpp"
#include "data_class_course_enrollments.cpp"

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
    string studentID; 
    string name;
    string courseID;
    int grade_level;
    int mathgrade;
    int chemgrade;
    int biograde;
    int physicgrade;
    string oldmathgrade; 
    string oldchemgrade;
    string oldbiograde;
    string oldphysicgrade;
    string newmathgrade; 
    string newchemgrade;
    string newbiograde;
    string newphysicgrade;
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

        addNew("S001","Alice", 10, 80 , 95 , 76 , 69);
        addNew("S002","Charlie", 10, 60 , 55 , 57 , 77);


        addNew("S004","Brandon", 11, 71 , 75 , 66 , 74);
        addNew("S005","David", 11, 94, 85 , 56 , 88);

        addNew("S007","Francis", 12, 68, 85 , 81 , 86);
        addNew("S008","George", 12, 74, 56 , 79 , 88);
    }
    
     // StudentGrades
    static bool exists(const string& studentID) {
        return course_grades_list.nodeExists(studentID);
    }


    // get data
        static CourseGrade getData(const string& studentID) {
            bool exists = course_grades_list.nodeExists(studentID);
            Node<CourseGrade>* node;
            CourseGrade data;
            if (exists) {
                node = course_grades_list.findNode(studentID);
                data = node->data;
            }
            return data;
        }

    // add new 
    static bool addNew(const string& studentID, const string& name, const int& grade_level, const int& mathgrade, const int& chemgrade, const int& biograde, const int& physicgrade) {
    bool exists = course_grades_list.nodeExists(studentID);

    if (!exists) {
        CourseGrade data = { studentID, name,"", grade_level, mathgrade, chemgrade, biograde, physicgrade };
        course_grades_list.addNode(studentID, data);

            Student student_data = StudentList::getData(studentID);

        string info = student_data.name + " / Grade: " + to_string(grade_level);

        AcademicTree::addCourseGrade(studentID, to_string(grade_level), name, info);

        return true;
    } else {
        return false;
    }
}
    //updateMathGrade
    static bool updateMathGrade(const string& studentID, const string& courseID, const string& newmathgrade, const int& mathgrade){
        bool exists = course_grades_list.nodeExists(studentID);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(studentID);
            CourseGrade& data = node->data;

            if(data.courseID == "CMAT10"){
                string oldmathgrade = to_string(data.mathgrade); 
                data.mathgrade = stoi(newmathgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldmathgrade + " to " + newmathgrade);
                return true;
            }else if(data.courseID == "CMAT11"){
                string oldmathgrade = to_string(data.mathgrade); 
                data.mathgrade = stoi(newmathgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldmathgrade + " to " + newmathgrade);
                return true;
            }else if(data.courseID == "CMAT12"){
                string oldmathgrade = to_string(data.mathgrade); 
                data.mathgrade = stoi(newmathgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldmathgrade + " to " + newmathgrade);
                return true;
            }else{
                return false;
            }}else{
                return false;
            }
        }

    //updateChemGrade
    static bool updateChemGrade(const string& studentID, const string& courseID, const string& newchemgrade, const int& chemgrade){
        bool exists = course_grades_list.nodeExists(studentID);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(studentID);
            CourseGrade& data = node->data;

            if(data.courseID == "CCHE10"){
                string oldchemgrade = to_string(data.chemgrade); 
                data.chemgrade = stoi(newchemgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldchemgrade + " to " + newchemgrade);
                return true;
            }else if(data.courseID == "CCHE11"){
                string oldchemgrade = to_string(data.chemgrade); 
                data.chemgrade = stoi(newchemgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldchemgrade + " to " + newchemgrade);
                return true;
            }else if(data.courseID == "CCHE12"){
                string oldchemgrade = to_string(data.chemgrade); 
                data.chemgrade = stoi(newchemgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldchemgrade + " to " + newchemgrade);
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }

    //updateBioGrade
    static bool updateBioGrade(const string& studentID, const string& courseID, const string& newbiograde, const int& biograde){
        bool exists = course_grades_list.nodeExists(studentID);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(studentID);
            CourseGrade& data = node->data;

            if(data.courseID == "CBIO10" ){
                string oldbiograde = to_string(data.biograde); 
                data.biograde = stoi(newbiograde);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldbiograde + " to " + newbiograde);
                return true;
            }else if(data.courseID == "CBIO11" ){
                string oldbiograde = to_string(data.biograde); 
                data.biograde = stoi(newbiograde);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldbiograde + " to " + newbiograde);
                return true;
            }else if(data.courseID == "CBIO12" ){
                string oldbiograde = to_string(data.biograde); 
                data.biograde = stoi(newbiograde);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldbiograde + " to " + newbiograde);
                return true;
            }else{
                return false;
            }}else{
                return false;
            }
        }

    //updatePhysicsGrade
    static bool updatePhysicsGrade(const string& studentID, const string& courseID, const string& newphysicgrade, const int& physicgrade){
        bool exists = course_grades_list.nodeExists(studentID);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(studentID);
            CourseGrade& data = node->data;

            if(data.courseID == "CPHY10"){
                string oldphysicgrade = to_string(data.physicgrade); 
                data.physicgrade = stoi(newphysicgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldphysicgrade + " to " + newphysicgrade);
                return true;
            }else if(data.courseID == "CPHY11"){
                string oldphysicgrade = to_string(data.physicgrade); 
                data.physicgrade = stoi(newphysicgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldphysicgrade + " to " + newphysicgrade);
                return true;
            }else if(data.courseID == "CPHY12"){
                string oldphysicgrade = to_string(data.physicgrade); 
                data.physicgrade = stoi(newphysicgrade);
                UI::showLine("Grade for " + data.studentID + " in course " + courseID + " updated from " +
                            oldphysicgrade + " to " + newphysicgrade);
                return true;
            }else{
                return false;
            }}else{
                return false;
            }
        }
    // delete existing
    static bool remove(const string& studentID) {
        bool exists = course_grades_list.nodeExists(studentID);

        if (exists) {
            course_grades_list.deleteNode(studentID);
            AcademicTree::removeCourseGrade(studentID);
            return true;
        } else {
            return false;
        }
    }

    // showTable related


      static void tableInitRows() {
        table_rows.clear();
    }

    static void tableAddRow(Node<CourseGrade>* node) {
    CourseGrade data = node->data;

    vector<string> row;
    row.push_back(data.studentID);
    row.push_back(data.name);
    row.push_back(to_string(data.grade_level));
    row.push_back(to_string(data.mathgrade));  // Convert int to string
    row.push_back(to_string(data.biograde));  // Convert int to string
    row.push_back(to_string(data.chemgrade));  // Convert int to string
    row.push_back(to_string(data.physicgrade));  // Convert int to string

    table_rows.push_back(row);
}
    // Update CourseGradesList::showTable
static bool filterStudentID(const Node<CourseGrade>* node, const string& studentID) {
    return node->data.studentID == studentID;
}


// Update the existing showTable function to call the new one
static void showTable(const string& title) {
    tableInitRows();
    course_grades_list.traverse(tableAddRow);

    const string headers[] = {"Id", "Name", "Grade", "CMAT", "CBIO", "CCHE", "CPHY"};
    int col_sizes[] = {6, 20, 10, 10, 10, 10, 10};
    int num_cols = 7;

    UI::showEmptyLine(1);
    UI::showTable(title, headers, table_rows, col_sizes, num_cols);
    UI::showEmptyLine(1);
}

static void showoneTable(const string& title, const string& studentID) {
    tableInitRows();

    Node<CourseGrade>* studentNode = course_grades_list.findNode(studentID);

    if (studentNode) {
        tableAddRow(studentNode);  // Add the student's data to the table
    } else {
        cout << "Error: Student with ID " << studentID << " not found." << endl;
        UI::showPressAnyKey();
        return;  // Return without showing the table if the student is not found
    }

    const string headers[] = {"Id", "Name", "Grade", "CMAT", "CBIO", "CCHE", "CPHY"};
    int col_sizes[] = {6, 20, 10, 10, 10, 10, 10};
    int num_cols = 7;

    UI::showEmptyLine(1);
    UI::showTable(title, headers, table_rows, col_sizes, num_cols);
    UI::showEmptyLine(1);
}
};