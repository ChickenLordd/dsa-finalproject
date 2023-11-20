#pragma once

#include "base_class_ui.cpp"
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
    } else if (menu_type == "parent") {
      showParentMenu();
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
          redirectToMenu("parent");
        }
      }

    }
  }

  // use this to temporarily handle a menu choice that has not been developed yet
  static void showUnderDevelopmentResponse () {
      UI::showEmptyLine();
      UI::showLine ("This menu option is UNDER CONSTRUCTION");     
      UI::showEmptyLine();
      // UI::clearInputBuffer();
      // UI::showPressAnyKey();

      // redirectToMenu(menu_id);
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
      showUnderDevelopmentResponse ();
    }
  }

  // showParentMenu
  static void showParentMenu () {
    showBanner();

    string menuTitle = "Student's Parent Menu";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View Student Academic Summary");
    UI::addMenuOption ( "2", "View Student Information");
    UI::addMenuOption ( "0", "Sign Out");

    string choice = UI::showMenuOptions(menuTitle);
    string menu_label = UI::getMenuLabel(choice);
 
    UI::clearScreen();
    showBanner();

    UI::showLine(menu_label);
    UI::showEmptyLine();

    // get student id from curr_user_id (see showLogin)
    User data = UserList::getData (curr_user_id);
    string student_id = data.student_id;

    // menu handler
    if (choice == "0") {
      showLogin();

    } else if (choice == "1") {    
      AcademicTree::showStudentTree(student_id);

    } else if (choice == "2") {
      StudentList::showRecord ( student_id);
      
    } else {
      // default handler
      showUnderDevelopmentResponse ();
    }
    
    UI::showEmptyLine();

    UI::clearInputBuffer();
    UI::showPressAnyKey();
    redirectToMenu("parent");
  }

  // showStudentMenu
  static void showStudentMenu () {
    showBanner();

    string menuTitle = "Manage Students";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Students");
    UI::addMenuOption ( "2", "View Student Academic Information");
    UI::addMenuOption ( "3", "Add New Student");
    UI::addMenuOption ( "4", "Update Student Information");
    UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "6", "View Academic Summary");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);
    string menu_label = UI::getMenuLabel(choice);
 
    UI::clearScreen();
    showBanner();

    UI::showLine(menu_label);
    UI::showEmptyLine();

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      StudentList::showTable("List of Students");

    } else if (choice == "3") {  
      string id = UI::showInputText ("Enter Student Id", 20); // no spaces capture
      if (StudentList::exists(id)) {
        UI::showLine ("Student Id already exists.");

      } else {
        string name = UI::showInputTextLine ("Enter Name", 20); 
        int grade_level = UI::showInputInt("Enter Grade Level", 20); // no validation here
        string new_city = UI::showInputTextLine ("Enter City of Birth", 20); 

        UI::showEmptyLine();
        
        bool success = StudentList::addNew (id, name, grade_level, new_city);
        if (success) {
          UI::showEmptyLine();
          UI::showLine ("New Record added.");
          UI::showEmptyLine();
          StudentList::showRecord ( id);
        } else {
          UI::showEmptyLine();
          UI::showLine ("Record not added.");
        }
      }
 
    } else if ((choice == "2") || (choice == "4") || choice == "5") {
      // all these choices needs an id to operate on
      string id = UI::showInputText ("Enter Student Id", 20); // no spaces capture
          
      if (!StudentList::exists(id)) {
        UI::showEmptyLine();
        UI::showLine ("Student Id not found.");
      
      } else {
        UI::showEmptyLine();

        if (choice == "2") {
          // found, display
          StudentList::showRecord(id);
          UI::showEmptyLine();

          AcademicTree::showStudentTree(id);

        } else {
          // 4 or 5 (before update or remove, show old data)
          StudentList::showRecord(id);
          UI::showEmptyLine();

          if (choice == "4") {
            // update
            UI::showLine ("Enter information to update:");
            UI::showEmptyLine();

            string new_name = UI::showInputTextLine ("Enter Name", 20); 
            string new_city = UI::showInputTextLine ("Enter City of Birth", 20); 
    
            bool success = StudentList::update (id, new_name, new_city);
            if (success) {
              UI::showEmptyLine();
              UI::showLine("Record updated.");
              UI::showEmptyLine();
              StudentList::showRecord ( id);
            }

          } else if (choice == "5") {
            // remove
            UI::showLine ("Are you sure?");
            
            string sure = UI::showInputText ("Please answer (y if sure)", 20); 
            if (sure == "y") {
              StudentList::remove(id);
              UI::showEmptyLine();
              UI::showLine ("Record deleted.");
            }
          }
        }

        UI::showEmptyLine();
      }
 
    } else if (choice == "6") {
      UI::clearScreen();
      showBanner();
        
      AcademicTree::showTree();
        
    } else {
      // default handler
      showUnderDevelopmentResponse ();
    }
          
    UI::clearInputBuffer();
    UI::showPressAnyKey();
    redirectToMenu("students");

  }

  // showCoursesMenu
  static void showCoursesMenu () {
    showBanner();

    string menuTitle = "Manage Courses";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Courses");
    UI::addMenuOption ( "2", "Add New Course");
    UI::addMenuOption ( "3", "Update Course Information");
    UI::addMenuOption ( "4", "Remove an existing Course");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);
    string menu_label = UI::getMenuLabel(choice);

    UI::clearScreen();
    showBanner();
  
    UI::showLine(menu_label);
    UI::showEmptyLine();

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      CourseList::showTable("List of Courses");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("courses");

      UI::showEmptyLine();

    } else {
      // default handler
      showUnderDevelopmentResponse ();
    }

    UI::clearInputBuffer();
    UI::showPressAnyKey();
    redirectToMenu("courses");
  }

  // showCourseEnrollmentsMenu
  static void showCourseEnrollmentsMenu () {
    showBanner();

    string menuTitle = "Manage Course Enrollments";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Students");
    UI::addMenuOption ( "2", "View List of Courses");
    UI::addMenuOption ( "3", "View List of Course Enrollments");
    UI::addMenuOption ( "4", "Enroll Student To A Course");  // this is addNew, there's no need for update here
    UI::addMenuOption ( "5", "Remove A Student Course");
    UI::addMenuOption ( "6", "View Academic Summary");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);
    string menu_label = UI::getMenuLabel(choice);
 
    UI::clearScreen();
    showBanner();

    UI::showLine(menu_label);
    UI::showEmptyLine();
      
    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {
      StudentList::showTable("List of Students");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_enrollments");
     
      UI::showEmptyLine();

    } else if (choice == "6") {
        UI::clearScreen();
        showBanner();
        
        AcademicTree::showTree();
        
    } else {
      // default handler
      showUnderDevelopmentResponse ();
    }

    UI::clearInputBuffer();
    UI::showPressAnyKey();
    redirectToMenu("course_enrollments");
  }
    
  // showCourseGradesMenu
  static void showCourseGradesMenu () {
    showBanner();

    string menuTitle = "Manage Student Course Grades";

    UI::initMenuOptions();

    UI::addMenuOption ( "1", "View List of Course Enrollments");
    UI::addMenuOption ( "2", "View List of Course Grades");
    UI::addMenuOption ( "3", "Assign New Course Grade");
    UI::addMenuOption ( "4", "Update Student Course Grade");
    UI::addMenuOption ( "5", "Remove an existing Grade");
    UI::addMenuOption ( "6", "View Academic Summary");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);
    string menu_label = UI::getMenuLabel(choice);
 
    UI::clearScreen();
    showBanner();

    UI::showLine(menu_label);
    UI::showEmptyLine();

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");

    } else if (choice == "1") {      
      StudentList::showTable("List of Students");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_grades");
     
    } else if (choice == "2") {
      CourseList::showTable("List of Courses");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_grades");

    } else if (choice == "3") {
      UI::clearScreen();
              showBanner();
              CourseGradesList::showTable("Table of Student Grades");  
              UI::clearInputBuffer();
              UI::showPressAnyKey();
              redirectToMenu("course_grades");
    
    } else if (choice == "4") {
      updateStudentCourseGrade(); 
            
    } else if (choice == "5") {
            
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
    
     
      redirectToMenu("main");
    } 
  }
static void updateStudentCourseGrade() {
    UI::clearScreen();
    showBanner();
    cout << "Update Student Course Grade" << endl;

    string id, course_id;
    int newGrade, newmathgrade, newbiograde, newchemgrade, newphysicgrade;


    cout << "Enter Student ID: ";
    cin >> id;

    // Check if the student exists
    if (!CourseGradesList::exists(id)) {
        cout << "Error: Student with ID " << id << " not found." << endl;
        UI::showPressAnyKey();
        redirectToMenu("course_grades");
        return;
    }

    CourseGrade studentData = CourseGradesList::getData(id);
    CourseGradesList::showTable("List of Student Grades for " + studentData.name);

    cout << "Enter Course ID to update grade: ";
    cin >> course_id;

    // Collect new grade
    cout << "Enter New Grade for " << course_id << ": ";
    cin >> newGrade;

    // Update the grade
    bool updated = false;

    if (course_id.find("CMAT") != string::npos) {
        updated = CourseGradesList::updateMathGrade(id, course_id, to_string(newGrade),newmathgrade );
    } else if (course_id.find("CBIO") != string::npos) {
        updated = CourseGradesList::updateBioGrade(id, course_id, to_string(newGrade), newbiograde);
    } else if (course_id.find("CCHE") != string::npos) {
        updated = CourseGradesList::updateChemGrade(id, course_id, to_string(newGrade), newchemgrade);
    } else if (course_id.find("CPHY") != string::npos) {
        updated = CourseGradesList::updatePhysicsGrade(id, course_id, to_string(newGrade), newphysicgrade);
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
      // default handler
      showUnderDevelopmentResponse ();
    }

    UI::clearInputBuffer();
    UI::showPressAnyKey();
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
    string menu_label = UI::getMenuLabel(choice);
   
    UI::clearScreen();
    showBanner();

    UI::showLine(menu_label);
    UI::showEmptyLine();

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

      // check if exists here, see student for example how to handle

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
      showUnderDevelopmentResponse ();
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

    } else {
      // default handler
      showUnderDevelopmentResponse ();
    }
  
    UI::clearInputBuffer();
    UI::showPressAnyKey();
    redirectToMenu("users");
  }
    
};