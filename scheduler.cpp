// Vincent Phillip Rodriguez CPSC121-09

#include "scheduler.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

const int HOUR_LIMIT = 23;
const int MINUTES_LIMIT = 59;

void CourseSchedule::display() const
{
  for (int i = 0; i < num_courses_; i++)
  {
    // Display each course object's information.
    course_[i]->display();
    std::cout << "\n";
  }
}

bool CourseSchedule::add(std::string name, std::string location,
                         std::string schedule, int start, int end)
{
  TimeSpan time(start, end);

  Course * ptr_course;
  ptr_course = new Course;

  ptr_course->set_course_name(name);
  ptr_course->set_location(location);
  ptr_course->set_weekly_schedule(schedule);
  ptr_course->set_time(time);

  if (remove_conflicts_ == true)
  {
    if (has_conflict(ptr_course))
    {
      delete ptr_course;
      return false;
    }

    course_[num_courses_] = ptr_course;
    num_courses_++;
    return true;
  }
  else if (remove_conflicts_ == false)
  {
    course_[num_courses_] = ptr_course;
    num_courses_++;
  }

  return true;
}

bool CourseSchedule::add(Course * course)
{
  return add(course->course_name(), course->location(),
             course->weekly_schedule(), course->time().start_time(),
             course->time().end_time());
}

bool Course::intersects(Course * course)
{
  bool day_intersects = false;
  std::string longer = weekly_schedule_;
  std::string shorter = course->weekly_schedule();

  if (weekly_schedule_.length() < course->weekly_schedule().length())
  {
    longer = course->weekly_schedule();
    shorter = weekly_schedule_;
  }

  for (int i = 0; i < longer.length(); i++)
  {
    for (int j = 0; j < shorter.length(); j++)
    {
      if (longer[i] == shorter[j])
      {
        day_intersects = true;
      }
    }
  }

  // No intersection
  if (day_intersects == false || (time() < course->time() ||
      time() > course->time()))
  {
    return false;
  }

  return true;
}

void Course::display()
{
  std::cout << "Course name: " << course_name() << std::endl;
  std::cout << "Location: " << location() << std::endl;
  std::cout << "Weekly schedule: " << weekly_schedule() << std::endl;
  time_.display();
}

// Overload < operator
bool TimeSpan::operator<(TimeSpan a)
{
  if (end_time() < a.start_time())
  {
    return true;
  }

  return false;
}

// Overload > operator
bool TimeSpan::operator>(TimeSpan a)
{
  if (start_time() > a.end_time())
  {
    return true;
  }

  return false;
}

void TimeSpan::display()
{
  int start_hour = start_time_ / 100;
  int start_minutes = start_time_ - (start_hour * 100);
  int end_hour = end_time_ / 100;
  int end_minutes = end_time_ - (end_hour * 100);

  std::cout << "Start time: " << start_hour << ":";

  // Add the leading zero to the minutes to display xx:00.
  std::cout << std::setfill('0') << std::setw(2) << start_minutes << "\n";
  std::cout << "End time: " << end_hour << ":";
  std::cout << std::setfill('0') << std::setw(2) << end_minutes << "\n";
}

bool ScheduleManager::load_schedule(std::string file_name)
{
  // Open file.
  std::ifstream in_file;
  in_file.open(file_name);

  char colon;
  char end_time_colon;

  int start;
  int start_hour;
  int start_minutes;
  int end;
  int end_hour;
  int end_minutes;
  int num_of_courses = 0;

  std::string course;
  std::string course_name;
  std::string course_number;
  std::string location;
  std::string schedule;

  // Check if the file exists.
  if (!in_file)
  {
    std::cout << "Error: File does not exist.\n";
    std::cout << "Invalid file.\n";
    return false;
  }

  int i = 0;
  while (in_file)
  {
    // Obtain the course name.
    // Obtain the course number.
    // Create the full course name (ex. CPSC 121)
    // Add the course name to the course object i.
    if (in_file >> course_name)
    {
      std::getline(in_file, course_number);
      course = course_name + course_number;

      // Obtain the course location.
      // Add the course location to the course object i.
      if (std::getline(in_file, location))
      {

        // Obtain the course weekly schedule.
        // Check if the schedule follows the correct format.
        // Add the course schedule to the course object i.
        if (std::getline(in_file, schedule))
        {
          if (schedule == "M" || schedule == "T" || schedule == "W" ||
              schedule == "H" || schedule == "F" || schedule == "S" ||
              schedule == "MW" || schedule == "MF" || schedule == "TH")
          {

            // Check and obtain the start time hour.
            // Obtain the start time minutes.
            // Reads the colon.
            if (in_file >> start_hour)
            {
              in_file >> colon;
              in_file >> start_minutes;

              // Make sure the start time hour and minutes follow military time
              // format.
              // Convert the start hour and minutes into a single integer.
              // Add the start time to the course object i.
              if ((start_hour >= 0 && start_hour <= HOUR_LIMIT) &&
                  (start_minutes >= 0 && start_minutes <= MINUTES_LIMIT))
              {
                // Check and obtain the end time hour.
                // Read the end time colon.
                // Obtain the end time minutes.
                if (in_file >> end_hour)
                {
                  in_file >> end_time_colon;
                  in_file >> end_minutes;

                  // Check that the end time hour and minutes follow military
                  // time format.
                  // Convert the end hour and minutes into a single integer.
                  // Add the end time to the course object i.
                  if ((end_hour >= 0 && end_hour <= HOUR_LIMIT) &&
                      (end_minutes >= 0 && end_minutes <= MINUTES_LIMIT))
                  {
                    start = (start_hour * 100) + start_minutes;
                    end = (end_hour * 100) + end_minutes;

                    complete_schedule_.add(course, location, schedule, start, end);
                    num_of_courses++;

                    // Make sure the start time starts before the end time.

                    // ERROR STATEMENTS-----------------------------------------
                    if (start_hour >= end_hour)
                    {
                      if (start_minutes > end_minutes)
                      {
                        std::cout << "Error: The start time " << end_hour << ":"
                                  << end_minutes
                                  << " should happen before the end time "
                                  << start_hour << ":" << start_minutes
                                  << ".\n";
                        std::cout << "Invalid file.\n";
                        return false;
                      }

                      std::cout << "Error: The start time " << end_hour << ":"
                                << end_minutes
                                << " should happen before the end time "
                                << start_hour << ":" << start_minutes << ".\n";
                      std::cout << "Invalid file.\n";
                      return false;
                    }
                  }
                  else
                  {
                    std::cout << "Error: Unable to get a valid end time.\n";
                    std::cout << "Error: " << end_hour << ":" << end_minutes
                              << " is an invalid end time.\n";
                    std::cout << "Invalid file.\n";
                    return false;
                  }
                }
                else
                {
                  std::cout << "Error: Unable to get a valid end time.\n";
                  std::cout << "Invalid file.\n";
                  return false;
                }
              }
              else
              {
                std::cout << "Error: Unable to get a valid start time.\n";
                std::cout << "Error: " << start_hour << ":" << start_minutes
                          << " is an invalid start time.\n";
                std::cout << "Invalid file.\n";
                return false;
              }
            }
            else
            {
              std::cout << "Error: Unable to get a valid start time.\n";
              std::cout << "Invalid file.\n";
              return false;
            }
          }
          else
          {
            std::cout << "Invalid weekly schedule symbol " << schedule << "\n";
            std::cout << "Invalid file.\n";
            return false;
          }
        }
        else
        {
          std::cout << "Error: Unable to get a weekly schedule.\n";
          std::cout << "Invalid file.\n";
          return false;
        }
      }
      else
      {
        std::cout << "Error: Unable to get a location.\n";
        std::cout << "Invalid file.\n";
        return false;
      }
    }
    else
    {
      return true;
    }

    i++;
  }

  // Close file.
  in_file.close();

  return true;
}

CourseSchedule * ScheduleManager::best_schedule(std::string filename)
{
  // #1
  load_schedule(filename);

  // #2
  if (!load_schedule(filename))
  {
    return nullptr;
  }

  int num = complete_schedule_.num_courses();

  // #3
  Course * courses[num];

  for (int i = 0; i < num; i++)
  {
    courses[i] = complete_schedule_.course(i);
  }

  int num_check = 0;

  do
  {
    CourseSchedule schedule;
    for (int i = 0; i < num; i++)
    {
      schedule.add(courses[i]);
    }

    if (schedule.num_courses() > num_check)
    {
      best_schedule_ = &schedule;

      num_check = schedule.num_courses();
    }

  } while (std::next_permutation(courses, courses + num));

  std::cout << best_schedule_->num_courses() << std::endl;

  return best_schedule_;
}
