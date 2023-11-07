#pragma once

#include "base_class_linkedlist.cpp"
#include "base_class_ui.cpp"

using namespace std;

// Define a simple Student struct as an example of data
struct Student {
    string id;
    string name;
    int grade_level;
    string city_of_birth;
};

LinkedList<Student> student_list;
// Data type: LinkedList
// Node type: Student
// Variable name: student_list 

// table_rows placeholder for showTable related (used in traverse in addTableRow)
vector<vector<string> > table_rows;   
   
class StudentList {
public:

    // add data for quick test
    static void init() {

        // Create initial data nodes
        Student student1 = {"S001", "Alice", 10, "Surabaya"};
        Student student2 = {"S002", "Bob", 11, "Semarang"};
        Student student3 = {"S003", "Charlie", 12, "Jakarta"};
        
        Student student4 = {"S004", "Brandon", 10, "Yogyakarta"};
        Student student5 = {"S005", "Amelia", 11, "Surakarta"};
        Student student6 = {"S006", "David", 12, "Malang"};

        Student student7 = {"S007", "Francis", 10, "Denpasar"};
        Student student8 = {"S008", "George", 11, "Bogor"};
        Student student9 = {"S009", "Robert", 12, "Bandung"};

        // Add nodes to the linked list
        student_list.addNode(student1.id, student1);
        student_list.addNode(student2.id, student2);
        student_list.addNode(student3.id, student3);

        student_list.addNode(student4.id, student4);
        student_list.addNode(student5.id, student5);
        student_list.addNode(student6.id, student6);

        student_list.addNode(student7.id, student7);
        student_list.addNode(student8.id, student8);
        student_list.addNode(student9.id, student9);
    }

    // add new 
    static bool addNew (const string& id, const Student& data) {
        bool exists = student_list.nodeExists (id);

        if (!exists) {
            student_list.addNode (id, data);
            return true;
        } else {
            return false; // node with the same id already exists
        }
    }

    // delete existing
    static bool remove (const string& id) {
        bool exists = student_list.nodeExists (id);

        if (exists) {
            student_list.deleteNode (id);
            return true;
        } else {
            return false; // node with that id does not exists
        }
    }

    // showTable related
    static void tableInitRows() {
        table_rows.clear();   
    }

    static void tableAddRow (Node<Student>* node ) {
        Student data = node->data;

        vector<string> row;
        row.push_back (data.id);
        row.push_back (data.name);
        row.push_back (to_string(data.grade_level));
        row.push_back (data.city_of_birth);

        // // debug
        // cout << endl << "DEBUG ROW" << endl;
        // for (size_t i = 0; i < row.size(); i++) {
        //     cout << row[i] << endl;
        // }

        table_rows.push_back(row); // add to rows
    }

    static void showTable(const string& title) {
        tableInitRows();

        // use anonymous callback function to build rows
        // add row one by one per node
        student_list.traverse ( tableAddRow );

        const string headers[] = {"Id", "Name", "Grade Level", "City of birth"};
        int col_sizes[] = {6,15, 12, 20};
        int num_cols = 4;
    
        // exit(EXIT_SUCCESS);

        UI::showEmptyLine(1);
        UI::showTable(title, headers, table_rows, col_sizes, num_cols);
        UI::showEmptyLine(1);
    }

    // // this is optional, not needed if never used
    // // showNode as compact string line
    // static void showNodeAsLine (Node<Student>* node ) {
    //     Student data = node->data;
    //     string line = UI::strPadEnd(data.id,6) + 
    //         UI::strPadEnd(data.name, 15) +  
    //         UI::strPadEnd(to_string(data.grade_level),4) + 
    //         UI::strPadEnd(data.city_of_birth, 20);
    //     cout << line << endl; 
    // }

    // // simple compact list without header
    // static void showList () {
    //     student_list.traverse ( showNodeAsLine );
    // }
    
};
