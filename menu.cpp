#pragma once

#include "base_class_ui.cpp"
#include "base_class_linkedlist.cpp"
#include "data_class_students.cpp"
#include "data_class_courses.cpp"
#include "data_class_course_enrollments.cpp"
#include "data_class_course_grades.cpp"
#include "data_class_users.cpp"

#include "data_tree_academic.cpp"

using namespace std;

#ifndef _CURR_USER
string curr_user_id = "";
string curr_user_name = "";
string curr_user_type = "";
#define _CURR_USER
#endif

class Menu {

  
public:

  // showBanner 9will be called before each menu is shown
  static void showBanner() {
    UI::clearScreen();

    UI::showRepeatChar('-', 80);

    int padding = 28;
    string date = UI::strPadStart(UI::getCurrentDate(), padding);
    string id = UI::strPadStart(curr_user_id, padding); // + " (" + curr_user_type + ")"
    string name = UI::strPadStart(curr_user_name, padding);

    // https://www.ascii-art-generator.org/
    string banner[] = {
        "    __  _______ ___    ___ ",
        "   / / / / ___//   |  /   |   WELCOME TO THE       " + date,
        "  / /_/ /\\__ \\/ /| | / /| |   High School         ", // need to escape the back slashes
        " / __  /___/ / ___ |/ ___ |   Academic             " + id,
        "/_/ /_//____/_/  |_/_/  |_|   Administration System" + name,
        " "
    };

    UI::showLines(banner);

    UI::showRepeatChar('-', 80);
    UI::showEmptyLine(1);
  }

  // redirectToMenu
  static void redirectToMenu ( const string& menu_type ) {
    if (menu_type == "main") {
      showMainMenu();
    } else if (menu_type == "login") {
      showLogin();
    } else if (menu_type == "students") {
      showStudentMenu();
    } else if (menu_type == "courses") {
      showCoursesMenu();
    } else if (menu_type == "course_enrollments") {
      showCourseEnrollmentsMenu();
    } else if (menu_type == "course_grades") {
      showCourseGradesMenu();
    } else if (menu_type == "users") {
      showUsersMenu();
    } else if (menu_type == "parents") {
      showParentsMenu();
    } else {
      showMainMenu();
    }
  }

  // showLogin
  static void showLogin () {
    // reset curr user
    curr_user_id = "";
    curr_user_name = "";
    curr_user_type = "";

    showBanner();
    
    cout << "Please Sign In" << endl << endl;
    cout << "(enter a 'q' as User Id to quit)" << endl << endl;

    string labelText = "Enter User Id";
    string id = UI::showInputText(labelText, 15);
    string password;
    string user_type;
 
    if (id == "q") {
        cout << endl << "Goodbye..." << endl << endl;
        exit(EXIT_SUCCESS);
    } else {
    
      string labelPwd = "Enter password";
      password = UI::showInputPassword(labelPwd, 15);

      UI::showEmptyLine(1);

      // depending on validity or account type, redirectToMenu to different menu
      UserInfo info = UserList::login(id, password);

      if (!info.valid) {
        // error occured
        UI::showEmptyLine(1);
        cout << "ERROR :: " << info.message << "!" << endl;
        
        UI::showPressAnyKey();
        redirectToMenu("login");

      } else {
        // valid
        user_type = info.user_type;

        // set global var
        curr_user_id = id;
        curr_user_name = info.name;
        curr_user_type = user_type;

        if (user_type == "admin") {
          redirectToMenu("main");
        } else if (user_type == "parent") {
          redirectToMenu("parents");
        }
      }

    }
  }

  // use this to temporarily handle a menu choice that has not been developed yet
  static void showMenuDebug (const string& choice, const string& choice_label) {
      UI::clearInputBuffer();
      UI::showEmptyLine(1);
      cout << "UNDER CONSTRUCTION :: " << choice << " : " << choice_label << endl;
      UI::showPressAnyKey();
  }  

  // showMainMenu
  static void showMainMenu () {
    showBanner();

    string menuTitle = "Main Menu";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View Academic Summary");
    UI::addMenuOption ( "2", "Manage Students");
    UI::addMenuOption ( "3", "Manage Courses");
    UI::addMenuOption ( "4", "Manage Course Enrollments");
    UI::addMenuOption ( "5", "Manage Student Course Grades");
    UI::addMenuOption ( "6", "Manage User Access");
    UI::addMenuOption ( "0", "Sign Out");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      showLogin();
    } else if (choice == "1") {
        UI::clearScreen();
        showBanner();
        
        AcademicTree::showTree();
        
        UI::clearInputBuffer();
        UI::showPressAnyKey();
        redirectToMenu("main");

    } else if (choice == "2") {
      redirectToMenu("students");

    } else if (choice == "3") {
      redirectToMenu("courses");

    } else if (choice == "4") {
      redirectToMenu("course_enrollments");

    } else if (choice == "5") {
      redirectToMenu("course_grades");

    } else if (choice == "6") {
      redirectToMenu("users");

    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("main");
    }
  }

// showMenu
  static void showStudentMenu () {
    showBanner();

    string menuTitle = "Manage Students";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Students");
    UI::addMenuOption ( "2", "View Student Academic Information");
    UI::addMenuOption ( "3", "Add New Student");
    UI::addMenuOption ( "4", "Update Student Information");
    UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      UI::clearScreen();
      showBanner();
      
      StudentList::showTable("List of Students");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("students");

  } else if (choice == "2") {
      UI::clearScreen();
      showBanner();
      
      string id = UI::showInputText ("Enter Student Id", 20); // no spaces capture
    
      UI::showEmptyLine();
      AcademicTree::showStudentTree(id);

      UI::showEmptyLine();
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("students");

    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("students");
    }
  }

  // showCoursesMenu
  static void showCoursesMenu () {
    showBanner();

    string menuTitle = "Manage Courses";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Courses");
    UI::addMenuOption ( "3", "Add New Course");
    UI::addMenuOption ( "4", "Update Course Information");
    UI::addMenuOption ( "5", "Remove an existing Course");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      UI::clearScreen();
      showBanner();
      
      CourseList::showTable("List of Courses");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("courses");

    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("courses");
    }
  }

  // showCourseEnrollmentsMenu
  static void showCourseEnrollmentsMenu () {
    showBanner();

    string menuTitle = "Manage Course Enrollments";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Students");
    UI::addMenuOption ( "2", "View List of Courses");
    // UI::addMenuOption ( "2", "View Student Academic Information");
    // UI::addMenuOption ( "3", "Add New Student");
    // UI::addMenuOption ( "4", "Update Student Information");
    // UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      UI::clearScreen();
      showBanner();
      
      StudentList::showTable("List of Students");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_enrollments");
     
    } else if (choice == "2") {
      UI::clearScreen();
      showBanner();
      
      CourseList::showTable("List of Courses");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_enrollments");
       
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("course_enrollments");
    }
  }
    
  // showCourseGradesMenu
  static void showCourseGradesMenu () {
    showBanner();

    string menuTitle = "Manage Student Course Grades";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View Academic Summary");
    UI::addMenuOption ( "2", "View Student Academic Information");
    UI::addMenuOption ( "3", "Update Student Grade");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      UI::clearScreen();
              showBanner();
              CourseGradesList::showTable("Table of Student Grades");  
              UI::clearInputBuffer();
              UI::showPressAnyKey();
              redirectToMenu("course_grades");
     
    } else if (choice == "2") {
      cout << "Under Construction" << endl;
        UI::clearInputBuffer();
        UI::showPressAnyKey();
        redirectToMenu("main");
    } else if(choice == "3"){
      updateStudentCourseGrade();
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("main");
    } 
  }


static void updateStudentCourseGrade() {
    UI::clearScreen();
    showBanner();
    cout << "Update Student Course Grade" << endl;

    string studentID, courseID;
    int newGrade, newmathgrade, newbiograde, newchemgrade, newphysicgrade;

    cout << "Enter Student ID: ";
    cin >> studentID;

    // Check if the student exists
    if (!StudentList::exists(studentID)) {
        cout << "Error: Student with ID " << studentID << " not found." << endl;
        UI::showPressAnyKey();
        redirectToMenu("course_grades");
        return;
    }

    CourseGrade studentData = CourseGradesList::getData(studentID);
    CourseGradesList::showoneTable("List of Student Grades for " + studentData.name, studentID);

    cout << "Enter Course ID to update grade: ";
    cin >> courseID;

    if (!CourseList::exists(courseID)) {
        cout << "Error: Course with ID " << courseID << " does not exist." << endl;
        UI::showPressAnyKey();
        redirectToMenu("course_grades");
        return;
    }

    cout << "Enter New Grade for " << courseID << ": ";
    cin >> newGrade;

    // Update the grade
    bool updated = false;

    if (courseID == "CMAT") {
        updated = CourseGradesList::updateMathGrade(studentID, courseID, to_string(newGrade), newmathgrade );
    } else if (courseID == "CBIO") {
        updated = CourseGradesList::updateBioGrade(studentID, courseID, to_string(newGrade),  newbiograde);
    } else if (courseID == "CCHE") {
        updated = CourseGradesList::updateChemGrade(studentID, courseID, to_string(newGrade), newchemgrade );
    } else if (courseID == "CPHY") {
        updated = CourseGradesList::updatePhysicsGrade(studentID, courseID, to_string(newGrade), newphysicgrade);
    } else {
        cout << "Error: Invalid Course ID." << endl;
        UI::showPressAnyKey();
        redirectToMenu("course_grades");
        return;
    }

     if (updated) {
        // Show the updated table of grades for the student
        UI::clearScreen();
        showBanner();
        CourseGradesList::showTable("List of Student Grades for " + studentData.name);
        UI::showPressAnyKey();
    } else {
        cout << "Error: Unable to update grade. Please check the entered Course ID." << endl;
        UI::showPressAnyKey();
    }

    redirectToMenu("course_grades");
}


  // showUsersMenu
  static void showUsersMenu () {
    showBanner();

    string menuTitle = "Manage User Access";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Users");
    UI::addMenuOption ( "2", "View List of Students");
    UI::addMenuOption ( "3", "Add New User");
    UI::addMenuOption ( "4", "Update User Information");
    UI::addMenuOption ( "5", "Remove an existing User");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      UI::clearScreen();
      showBanner();
      
      UserList::showTable("List of Users");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("users");

    } else if (choice == "2") {
      UI::clearScreen();
      showBanner();
      
      StudentList::showTable("List of Students");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("users");

    } else if (choice == "3") {
      UI::clearScreen();
      showBanner();
      
      UI::showLine("Add New User");
      UI::showEmptyLine();

      string id = UI::showInputText ("Enter User Id", 20); // no spaces capture
      string name = UI::showInputTextLine ("Enter User Name", 20); // captur etext incl spaces
      string password = UI::showInputText ("Enter User Password", 20); // do not hide chars (do not use showInputPassword)
    
      UI::showEmptyLine();

      string choiceLabel = "Choose User Type";
      UI::initChoices();
      UI::addChoice("A", "Admin");
      UI::addChoice("P", "Parent of Student");

      string selected = UI::showChoices(choiceLabel, 20);
    
      string user_type;
      string student_id = ""; // default to empty 
    
      if (selected == "A") {
        user_type = "admin";
      } else {
        user_type = "parent";
        UI::showEmptyLine();
        string s_id = UI::showInputText ("Enter Student Id", 20);

        // if we need to validate to see if student_id is valid, use StudentList::exists and StidentList::getData
        // currently it's not validated, assume user enter the CORRECT student_id

        student_id = s_id;
      }

      // save
      UserList::addNew ( id, name, password, user_type, student_id );
  
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("users");

   } else if (choice == "4") {
        UI::clearScreen();
        showBanner();

        UserList::init();

        // Display the list of users
        UserList::showTable("List of Users");

        string idToUpdate = UI::showInputText("Enter User Id to Update", 20);

        if (UserList::userExists(idToUpdate)) {

            UI::showLine("Update User Information");

            // Allow user to update information
            string newId = UI::showInputText("Enter New User Id", 20);
            string name = UI::showInputTextLine("Enter New User Name", 20); // capture text including spaces
            string password = UI::showInputText("Enter New User Password", 20); // do not hide chars
            string userType = UI::showInputText("Enter New User Type", 20); // capture text including spaces
            string studentId = UI::showInputText("Enter New Student Id", 20); // capture text including spaces

            // Update user data
            UserList::updateUser(idToUpdate, newId, name, password, userType, studentId);
        } else {
            UI::showLine("User with Id " + idToUpdate + " does not exist.");
        }

        // Display updated user list
        UserList::showTable("List of Users (After Update)");

        UI::clearInputBuffer();
        UI::showPressAnyKey();
        redirectToMenu("users");
   
  
    } else if (choice == "5") {

      // remove user
      UI::clearScreen();
      showBanner();
      
      UserList::init();

      UserList::showTable("User List (Before Removal)");
      UserList::removeUserById();
      UserList::showTable("User List (After Removal)");

    // save
      string id;
      UserList::removeUser (id);
  
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("users");
  
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("users");
    }
  }

    // showParentsMenu
    static void showParentsMenu () {
    showBanner();

    string menuTitle = "Parent Dashboard";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View Student's Academic Info");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("parents");

    } else if (choice == "1") {
      UI::clearScreen();
      showBanner();
      
      string id = UI::showInputText ("Enter Student Id", 20); // no spaces capture
    
      UI::showEmptyLine();
      AcademicTree::showStudentTree(id);

      UI::showEmptyLine();
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("parents");
    }
  }
};