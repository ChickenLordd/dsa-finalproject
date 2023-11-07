#pragma once

#include "base_class_ui.cpp"
#include "data_class_students.cpp"
#include "data_class_courses.cpp"
#include "data_class_course_enrollments.cpp"
#include "data_class_course_grades.cpp"
#include "data_class_users.cpp"

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
    string name = UI::showInputText(labelText, 15);
 
    if (name == "q") {
        cout << endl << "Goodbye..." << endl << endl;
        exit(EXIT_SUCCESS);
    } else {
    
      string labelPwd = "Enter password";
      string password = UI::showInputPassword(labelPwd, 15);

      UI::showEmptyLine(1);

      // handle login here, if valid then redirectToMenu to proper menu depending on type of user (admin, or parent)
      // for debugging
      // cout << "DEBUG :: " << name << " : " << password << "!" << endl;
      // UI::showPressAnyKey();

      // depending on account type, redirectToMenu to different menu
      // right now default to MainMenu
      
      string user_type = "admin";

      if (user_type == "admin") {
        redirectToMenu("main");
      } else if (user_type == "parent") {
        redirectToMenu("users");
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
    UI::addMenuOption ( "5", "Manage Grade Assignment");
    UI::addMenuOption ( "6", "Sign Up Parents for access");
    UI::addMenuOption ( "0", "Sign Out");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      showLogin();
    } else if (choice == "1") {
      // redirectToMenu("students");
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

    // UI::addMenuOption ( "1", "View List of Students");
    // UI::addMenuOption ( "2", "View Student Academic Information");
    // UI::addMenuOption ( "3", "Add New Student");
    // UI::addMenuOption ( "4", "Update Student Information");
    // UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");
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

    // UI::addMenuOption ( "1", "View List of Students");
    // UI::addMenuOption ( "2", "View Student Academic Information");
    // UI::addMenuOption ( "3", "Add New Student");
    // UI::addMenuOption ( "4", "Update Student Information");
    // UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");
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

    string menuTitle = "Manage Course Grades";

    UI::initMenuOptions();

    // UI::addMenuOption ( "1", "View List of Students");
    // UI::addMenuOption ( "2", "View Student Academic Information");
    // UI::addMenuOption ( "3", "Add New Student");
    // UI::addMenuOption ( "4", "Update Student Information");
    // UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("course_grades");
    }
  }

  // showUsersMenu
  static void showUsersMenu () {
    showBanner();

    string menuTitle = "Manage Parent Access";

    UI::initMenuOptions();

    // UI::addMenuOption ( "1", "View List of Students");
    // UI::addMenuOption ( "2", "View Student Academic Information");
    // UI::addMenuOption ( "3", "Add New Student");
    // UI::addMenuOption ( "4", "Update Student Information");
    // UI::addMenuOption ( "5", "Remove an existing Student");
    UI::addMenuOption ( "0", "Back to Main Menu");

    string choice = UI::showMenuOptions(menuTitle);

    // menu handler
    if (choice == "0") {
      redirectToMenu("main");
    } else {
      // default handler
      string choice_label = UI::getMenuLabel (choice);
      showMenuDebug (choice, choice_label);
     
      redirectToMenu("users");
    }
  }
    
};
