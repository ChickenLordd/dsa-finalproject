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
    string id; 
    string name;
    string course_id;
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

    // add new 
    static bool addNew(const string& id, const string& name, const int& grade_level, const int& mathgrade, const int& chemgrade, const int& biograde, const int& physicgrade) {
    bool exists = course_grades_list.nodeExists(id);

    if (!exists) {
        CourseGrade data = { id, name,"", grade_level, mathgrade, chemgrade, biograde, physicgrade };
        course_grades_list.addNode(id, data);

            Student student_data = StudentList::getData(id);

        string info = student_data.name + " / Grade: " + to_string(grade_level);

        AcademicTree::addCourseGrade(id, to_string(grade_level), name, info);

        return true;
    } else {
        return false;
    }
}
    //updateMathGrade
    static bool updateMathGrade(const string& id, const string& course_id, const string& newmathgrade, const int& mathgrade){
        bool exists = course_grades_list.nodeExists(id);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(id);
            CourseGrade& data = node->data;

            if(data.course_id == "CMAT10"){
                string oldmathgrade = to_string(data.mathgrade); 
                data.mathgrade = stoi(newmathgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldmathgrade + " to " + newmathgrade);
                return true;
            }else if(data.course_id == "CMAT11"){
                string oldmathgrade = to_string(data.mathgrade); 
                data.mathgrade = stoi(newmathgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldmathgrade + " to " + newmathgrade);
                return true;
            }else if(data.course_id == "CMAT12"){
                string oldmathgrade = to_string(data.mathgrade); 
                data.mathgrade = stoi(newmathgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldmathgrade + " to " + newmathgrade);
                return true;
            }else{
                return false;
            }}else{
                return false;
            }
        }

    //updateChemGrade
    static bool updateChemGrade(const string& id, const string& course_id, const string& newchemgrade, const int& chemgrade){
        bool exists = course_grades_list.nodeExists(id);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(id);
            CourseGrade& data = node->data;

            if(data.course_id == "CCHE10"){
                string oldchemgrade = to_string(data.chemgrade); 
                data.chemgrade = stoi(newchemgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldchemgrade + " to " + newchemgrade);
                return true;
            }else if(data.course_id == "CCHE11"){
                string oldchemgrade = to_string(data.chemgrade); 
                data.chemgrade = stoi(newchemgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldchemgrade + " to " + newchemgrade);
                return true;
            }else if(data.course_id == "CCHE12"){
                string oldchemgrade = to_string(data.chemgrade); 
                data.chemgrade = stoi(newchemgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
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
    static bool updateBioGrade(const string& id, const string& course_id, const string& newbiograde, const int& biograde){
        bool exists = course_grades_list.nodeExists(id);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(id);
            CourseGrade& data = node->data;

            if(data.course_id == "CBIO10" ){
                string oldbiograde = to_string(data.biograde); 
                data.biograde = stoi(newbiograde);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldbiograde + " to " + newbiograde);
                return true;
            }else if(data.course_id == "CBIO11" ){
                string oldbiograde = to_string(data.biograde); 
                data.biograde = stoi(newbiograde);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldbiograde + " to " + newbiograde);
                return true;
            }else if(data.course_id == "CBIO12" ){
                string oldbiograde = to_string(data.biograde); 
                data.biograde = stoi(newbiograde);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldbiograde + " to " + newbiograde);
                return true;
            }else{
                return false;
            }}else{
                return false;
            }
        }

    //updatePhysicsGrade
    static bool updatePhysicsGrade(const string& id, const string& course_id, const string& newphysicgrade, const int& physicgrade){
        bool exists = course_grades_list.nodeExists(id);

        if (exists) {
            Node<CourseGrade>* node = course_grades_list.findNode(id);
            CourseGrade& data = node->data;

            if(data.course_id == "CPHY10"){
                string oldphysicgrade = to_string(data.physicgrade); 
                data.physicgrade = stoi(newphysicgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldphysicgrade + " to " + newphysicgrade);
                return true;
            }else if(data.course_id == "CPHY11"){
                string oldphysicgrade = to_string(data.physicgrade); 
                data.physicgrade = stoi(newphysicgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldphysicgrade + " to " + newphysicgrade);
                return true;
            }else if(data.course_id == "CPHY12"){
                string oldphysicgrade = to_string(data.physicgrade); 
                data.physicgrade = stoi(newphysicgrade);
                UI::showLine("Grade for " + data.id + " in course " + course_id + " updated from " +
                            oldphysicgrade + " to " + newphysicgrade);
                return true;
            }else{
                return false;
            }}else{
                return false;
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

    // showTable related


      static void tableInitRows() {
        table_rows.clear();
    }

    static void tableAddRow(Node<CourseGrade>* node) {
    CourseGrade data = node->data;

    vector<string> row;
    row.push_back(data.id);
    row.push_back(data.name);
    row.push_back(to_string(data.grade_level));
    row.push_back(to_string(data.mathgrade));  // Convert int to string
    row.push_back(to_string(data.biograde));  // Convert int to string
    row.push_back(to_string(data.chemgrade));  // Convert int to string
    row.push_back(to_string(data.physicgrade));  // Convert int to string

    table_rows.push_back(row);
}
    // Update CourseGradesList::showTable
static bool filterid(const Node<CourseGrade>* node, const string& id) {
    return node->data.id == id;
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

static void showoneTable(const string& title, const string& id) {
    tableInitRows();

    Node<CourseGrade>* studentNode = course_grades_list.findNode(id);

    if (studentNode) {
        tableAddRow(studentNode);  // Add the student's data to the table
    } else {
        cout << "Error: Student with ID " << id << " not found." << endl;
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