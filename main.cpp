// g++ main.cpp -o main
// ./main

#include "data_class_students.cpp"
#include "data_class_courses.cpp"
#include "data_class_course_enrollments.cpp"
#include "data_class_course_grades.cpp"
#include "data_class_users.cpp"

#include "menu.cpp"

int main() {
    // init data
    StudentList::init();
    // CourseList::init();
    // CourseEnrollments::init();
    // CourseGrades::init();
    // Users::init();

    // show menu
    Menu::showLogin();
    return 0;
}