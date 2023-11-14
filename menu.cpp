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

class Menu {

  
public:

  // showBanner 9will be called before each menu is shown
  static void showBanner() {
    UI::clearScreen();

    UI::showRepeatChar('-', 80);

    // https://www.ascii-art-generator.org/
    string banner[] = {
        "    __  _______ ___    ___ ",
        "   / / / / ___//   |  /   |   WELCOME TO THE",
        "  / /_/ /\\__ \\/ /| | / /| |   High School", // need to escape the back slasshes
        " / __  /___/ / ___ |/ ___ |   Academic",
        "/_/ /_//____/_/  |_/_/  |_|   Administration System",
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
    } else {
      showMainMenu();
    }
  }

  // showLogin
  static void showLogin () {
    showBanner();
    
    cout << "Please Sign In" << endl << endl;
    cout << "(enter a 'q' as User Id to quit)" << endl << endl;

    string labelText = "Enter User Id";
    string id = UI::showInputText(labelText, 15);
 
    if (id == "q") {
        cout << endl << "Goodbye..." << endl << endl;
        exit(EXIT_SUCCESS);
    } else {
    
      string labelPwd = "Enter password";
      string password = UI::showInputPassword(labelPwd, 15);

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
        string user_type = info.user_type;

        if (user_type == "admin") {
          redirectToMenu("main");
        } else if (user_type == "parent") {
          redirectToMenu("users");
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

    UI::addMenuOption ( "1", "View List of Students");
    UI::addMenuOption ( "2", "View List of Courses");
    UI::addMenuOption ( "3", "View Academic Summary");
    UI::addMenuOption ( "4", "View Student Grades");
    UI::addMenuOption ( "5", "Update Student Grade");
    // UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("course_grades");

    } else if (choice == "1") {
      UI::clearScreen();
      showBanner();
      
      StudentList::showTable("List of Students");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_grades");
     
    } else if (choice == "2") {
      UI::clearScreen();
      showBanner();
      
      CourseList::showTable("List of Courses");
      
      UI::clearInputBuffer();
      UI::showPressAnyKey();
      redirectToMenu("course_grades");
    } else if(choice == "3"){

      UI::clearScreen();
              showBanner();
              
              AcademicTree::showTree();
              
              UI::clearInputBuffer();
              UI::showPressAnyKey();
              redirectToMenu("main");
    } else if(choice =="4"){


    } else if (choice=="5"){
      updateStudentCourseGrade();

    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("course_grades");
    } 
  }

 static void updateStudentCourseGrade() {
    string studentID, courseID, newGrade;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Course ID: ";
    cin >> courseID;
    cout << "Enter New Grade: ";
    cin >> newGrade;

    // Check if the grade is valid (you can add more validation logic if needed)

    // Update the grade
    bool updated = CourseGradesList::update(studentID, courseID, newGrade);

    if (updated) {
        // Show the table of grades for the updated student
        CourseGradesList::showTable("List of Student Grades");
    } else {
        cout << "Error: Student/course combination not found. Please check the entered IDs." << endl;
        UI::showPressAnyKey();
    }
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
  
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("users");
    }
  }

  };
    
