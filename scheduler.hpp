// Vincent Phillip Rodriguez CPSC121-09

#include <iomanip>
#include <iostream>

class TimeSpan
{
private:
  int start_time_;
  int end_time_;

public:
  // default constructor
  TimeSpan() : start_time_(0000), end_time_(0000) {}

  // non-default constructor
  TimeSpan(const int & start, const int & end)
      : start_time_(start), end_time_(end)
  {
  }

  void set_start_time(const int & start_time) { start_time_ = start_time; }
  void set_end_time(const int & end_time) { end_time_ = end_time; }

  int start_time() { return start_time_; }
  int end_time() { return end_time_; }

  bool operator<(TimeSpan a);
  bool operator>(TimeSpan a);

  void display();
};

// -----------------------------------------------------------------------------

class Course
{
private:
  std::string course_name_;
  std::string location_;
  std::string weekly_schedule_;
  TimeSpan time_;

public:
  // default constructor
  Course()
      : course_name_(""), location_(""), weekly_schedule_(""), time_(TimeSpan())
  {
  }

  // non-default constructor
  Course(const std::string & name, const std::string & location,
         const std::string & schedule, const TimeSpan & time)
      : course_name_(name), location_(location), weekly_schedule_(schedule),
        time_(time)
  {
  }

  void set_course_name(const std::string & course_name)
  {
    course_name_ = course_name;
  }
  void set_location(const std::string & location) { location_ = location; }
  void set_weekly_schedule(const std::string & weekly_schedule)
  {
    weekly_schedule_ = weekly_schedule;
  }

  void set_time(const TimeSpan & time) { time_ = time; }
  void display();

  std::string course_name() const { return course_name_; }
  std::string location() const { return location_; }
  std::string weekly_schedule() const { return weekly_schedule_; }
  TimeSpan time() const { return time_; }
  bool intersects(Course * course);
};

// -----------------------------------------------------------------------------

class CourseSchedule
{
private:
  Course * course_[100];
  int num_courses_;
  bool remove_conflicts_;

  bool has_conflict(Course * course)
  {
    for (int i = 0; i < num_courses(); i++)
    {
      // intersects
      if (course->intersects(course_[i]))
      {
        return true;
      }
    };
    return false;
  }

public:
  // default constructor
  CourseSchedule() : CourseSchedule(true) {}

  // non-default constructor
  CourseSchedule(bool remove) : remove_conflicts_(remove), num_courses_(0) {}

  int num_courses() { return num_courses_; }

  bool add(std::string name, std::string location, std::string schedule,
           int start, int end);

  bool add(Course * course);

  Course * course(int course_element) { return course_[course_element]; }

  void display() const;

  ~CourseSchedule()
  {
    for (int i = 0; i < num_courses(); i++)
    {
      delete course_[i];
    }
  }
};

//------------------------------------------------------------------------------

class ScheduleManager
{
private:
  CourseSchedule complete_schedule_;
  CourseSchedule * best_schedule_;

  bool load_schedule(std::string file_name);
public:
  // default constructor
  ScheduleManager() : complete_schedule_(CourseSchedule(false)), best_schedule_(nullptr) {}

  CourseSchedule * best_schedule(std::string filename);

  ~ScheduleManager()
  {
    delete best_schedule_;
    best_schedule_ = nullptr;
  }
};
