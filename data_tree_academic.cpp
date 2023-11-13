#pragma once

#include "base_class_tree.cpp"
#include "base_class_ui.cpp"

using namespace std;

#ifndef _ACADEMIC_TREE
TreeNode* academic_root = new TreeNode("root", "root");
#define _ACADEMIC_TREE
#endif
  
// Callback function to display nodes with indentation
void displayNodeDebug(TreeNode* TreeNode, int level) {
    // ignore root, level = 0
    if (level > 0) {
        for (int i = 1; i < level; i++) {
            std::cout << "   "; // Two spaces for each level of indentation
        }
        std::cout << "L:" << level << " :: " << TreeNode->type << " : " << TreeNode->id << "  (" << TreeNode->data << ")" << std::endl;
    }
}

void displayNode(TreeNode* TreeNode, int level) {
    // ignore root, level = 0
    if (level > 0) {
        for (int i = 1; i < level; i++) {
            std::cout << "   "; // Two spaces for each level of indentation
        }

        if (TreeNode->type == "grade_level") {
            std::cout << TreeNode->data << std::endl;

        } else if (TreeNode->type == "student") {
            std::cout << TreeNode->data << std::endl;

        } else {
            std::cout << TreeNode->id << " - " << TreeNode->data << std::endl;
        }
    }
}

class AcademicTree {

public:

    // add data for quick test
    static void init() {

        // initialize Tree structure: Grade Level -> Student -> Course -> Grade
        TreeNode* gradeG10 = new TreeNode("grade_level", "G10", "Grade 10");
        TreeNode* gradeG11 = new TreeNode("grade_level", "G11", "Grade 11");
        TreeNode* gradeG12 = new TreeNode("grade_level", "G12", "Grade 12");
    
        academic_root->addChild(gradeG10);
        academic_root->addChild(gradeG11);
        academic_root->addChild(gradeG12);
    }

    // showTree
    static void showTree() {
        UI::showLine ("Academic (Tree) Summary Information");
        // Traverse the tree and display nodes with indentation using the callback function
        Tree::traverse(academic_root, displayNode);
    }

    // showTreeDebug
    static void showTreeDebug() {
        UI::showLine ("DEBUG :: Academic (Tree) Summary Information");
        // Traverse the tree and display nodes with indentation using the callback function
        Tree::traverse(academic_root, displayNodeDebug);
    }

    // tree node operations
    
    // ASSUMPTIONS: when doing tree operations it is ASSUMMED that the data passed are VALID 
    // because usually it's called from data (LinkedList addNew or remove methods that are already validated)

    // add tree node (generic method)
    static void addChildToParentNode ( const string& p_node_type, const string& p_node_id,  const string& c_node_type, const string& c_node_id, const string& c_data="" ) {
        // find parent node
        TreeNode* p_node = Tree::findNode (academic_root, p_node_type, p_node_id);

        // attach child node
        TreeNode* c_node = new TreeNode(c_node_type, c_node_id, c_data);
        p_node->addChild (c_node);
    }

    // addStudent
    static void addStudent (const int& grade_level, const string& student_id, const string& data="") {
        // parent to find
        string p_node_type = "grade_level";
        string p_node_id = "G" + to_string(grade_level); 

        // child to attach
        string c_node_type = "student";
        string c_node_id = student_id;

        // attach
        addChildToParentNode ( p_node_type, p_node_id, c_node_type, c_node_id, data );
    }

    // addCourseEnrollment
    static void addCourseEnrollment (const string& student_id, const string& course_enrollment_id, const string& data="") {
        // parent to find
        string p_node_type = "student";
        string p_node_id = student_id; 

        // child to attach
        string c_node_type = "course_enrollment";
        string c_node_id = course_enrollment_id;

        // attach
        addChildToParentNode ( p_node_type, p_node_id, c_node_type, c_node_id, data );
    }

    // addCourseGrade
    // static void addCourseGrade (const string& student_id, const string& course_id) {
    //     // parent to find
    //     string p_node_type = "student";
    //     string p_node_id = student_id; 

    //     // child to attach
    //     string c_node_type = "course";
    //     string c_node_id = course_id;

    //     // attach
    //     addChildToParentNode ( p_node_type, p_node_id, c_node_type, c_node_id );
    // }

    // removeStudent
    static void removeStudent ( const string& student_id ) {
        Tree::removeNode (academic_root, "student", student_id );
    }

    // removeCourseEnrollment
    static void removeCourseEnrollment ( const string& course_enrollment_id ) {
        Tree::removeNode (academic_root, "course_enrollment", course_enrollment_id );
    }

    
};