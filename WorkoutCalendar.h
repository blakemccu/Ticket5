#include <string>
#include <map>

class Workout {
private:
    std::string name;
    int duration; // Duration in minutes

public:
    Workout() : name(""), duration(0) {}
    Workout(std::string name, int duration) : name(name), duration(duration) {}
    
    std::string getName() const { return name; }
    int getDuration() const { return duration; }
};

class WorkoutCalendar {
private:
    std::map<std::string, Workout> calendar;

public:
    bool addDate(const std::string& date, const Workout& workout);
    Workout getDate(const std::string& date) const;
    bool importWorkout(const std::string& filename);
};