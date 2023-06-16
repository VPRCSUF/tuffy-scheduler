// Vincent Phillip Rodriguez CPSC121-09

#include "scheduler.hpp"
#include <fstream>
#include <iostream>

int main()
{
  bool valid_file;
  std::string file_name;

  int num_of_courses = 100;

  CourseSchedule * course_schedule;

  ScheduleManager manager;

  std::cout << "Welcome to Tuffy Scheduler!\n";
  std::cout << "Please enter the file name containing the list of classes: ";
  std::cin >> file_name;
  course_schedule = manager.best_schedule(file_name);

  // File is valid. Display the courses and their information.
  if (course_schedule != nullptr)
  {
    std::cout << "The schedule below accommodates the most number of courses without conflicts from the file you provided:\n";
    std::cout << course_schedule->num_courses() << std::endl;
    course_schedule->display();
  }

  std::cout << "Thank you for using Tuffy Scheduler.\n";

  return 0;
}
