#pragma once

#include "base_class_linkedlist.cpp"
#include "base_class_ui.cpp"
#include "data_class_students.cpp"

using namespace std;

// table_rows placeholder for showTable related (used in traverse in addTableRow)
// wrapped in IF because it's also defined in other data classes
#ifndef _TABLE_ROWS_FOR_DISPLAY
vector<vector<string> > table_rows; 
#define _TABLE_ROWS_FOR_DISPLAY
#endif

// Define a simple struct as an example of data
struct Course {
    string id;
    string name;
};

LinkedList<Course> course_list;
   
class CourseList {

public:

    // add data for quick test
    static void init() {

        // Create initial data nodes
        addNew("CMAT10", "Math 10");
        addNew("CBIO10", "Biology 10");
        addNew("CPHY10", "Physics 10");
        addNew("CCHE10", "Chemistry 10");
        
        addNew("CMAT11", "Math 11");
        addNew("CBIO11", "Biology 11");
        addNew("CPHY11", "Physics 11");
        addNew("CCHE11", "Chemistry 11");
        
        addNew("CMAT12", "Math 12");
        addNew("CBIO12", "Biology 12");
        addNew("CPHY12", "Physics 12");
        addNew("CCHE12", "Chemistry 12");
    }

    // add new 
    static bool addNew (const string& id, const string& name) {
        bool exists = course_list.nodeExists (id);

        if (!exists) {
            Course data = {id, name};
            course_list.addNode (id, data);
            
            // should add course to tree (under student)
            
            return true;
        } else {
            return false; // node with the same id already exists
        }
    }

    // delete existing
    static bool remove (const string& id) {
        bool exists = course_list.nodeExists (id);

        if (exists) {
            course_list.deleteNode (id);
            return true;
        } else {
            return false; // node with that id does not exists
        }
    }

    // showTable related
    static void tableInitRows() {
        table_rows.clear();   
    }

    static void tableAddRow (Node<Course>* node ) {
        Course data = node->data;

        vector<string> row;
        row.push_back (data.id);
        row.push_back (data.name);

        table_rows.push_back(row); // add to rows
    }

    static void showTable(const string& title) {
        tableInitRows();

        // use anonymous callback function to build rows
        // add row one by one per node
        course_list.traverse ( tableAddRow );

        const string headers[] = {"Id", "Name"};
        int col_sizes[] = {6, 20};
        int num_cols = 2;
    
        // exit(EXIT_SUCCESS);

        UI::showEmptyLine(1);
        UI::showTable(title, headers, table_rows, col_sizes, num_cols);
        UI::showEmptyLine(1);
    }
    
};