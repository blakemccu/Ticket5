/*Spencer King
Working as a member of Group J: Cade Ward, Jax Donlon, 
James Cunningham, Spencer King, Jay Patel, Bryce Freeman, 
Blake McCullough
Prof. Abdulhak
CS 3203 Spring 2025
28/3/2025
Workout Calendar Unit Tests 
*/
#include <iostream>
#include <cassert>
#include <string>
#include <map>
#include <fstream>

class Workout 
{
public:
    Workout(std::string name = "", int duration = 0) : name(name), duration(duration) {}
    std::string getName() 
    const {return name;}
    int getDuration() 
    const {return duration;}
private:
    std::string name;
    int duration;
};

class WorkoutCalendar 
{
public:

    //Adds a date to the workout calendar. Prevents duplicate entries. 
    bool addDate(const std::string& date, const Workout& workout) 
    {
        if (calendar.find(date) != calendar.end() || date.length() != 10) return false; 
        calendar[date] = workout;
        return true;
    }

    //Gets the information of a date and returns whether or not it has a workout
    Workout getDate(const std::string& date) 
    {
        if (calendar.find(date) != calendar.end()) 
        {
            return calendar[date];
        }
        return Workout(); 
    }

    //Imports a workout from a file
    bool importWorkout(const std::string& filename) 
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        
        std::string date, name;
        int duration;
        while (file >> date >> name >> duration) 
        {
            addDate(date, Workout(name, duration));
        }
        if(date.length() == 10)
        return true;
        else
        return false;
    }

private:
    std::map<std::string, Workout> calendar;
};

// Tests the add date function by checking duplicate dates and invalid date format
void test_addDate() 
{
    WorkoutCalendar calendar;
    Workout workout("Push Day", 60);

    assert(calendar.addDate("2025-03-27", workout) == true);
    assert(calendar.addDate("2025-03-27", workout) == false);
    assert(calendar.addDate("11111", workout) == false);
}

//Tests get date with both a added and empty date
void test_getDate() 
{
    WorkoutCalendar calendar;
    Workout workout("Leg Day", 75);
    calendar.addDate("2025-03-28", workout);

    Workout retrieved = calendar.getDate("2025-03-28");
    assert(retrieved.getName() == "Leg Day");
    assert(retrieved.getDuration() == 75);

    Workout emptyWorkout = calendar.getDate("2025-03-29");
    assert(emptyWorkout.getName() == "");
    assert(emptyWorkout.getDuration() == 0);
}

//Tests import workout. Code will fail if workout_data.txt is formatted incorrectly or missing. Assures that missing files return false.
void test_importWorkout() 
{
    WorkoutCalendar calendar;

    bool success = calendar.importWorkout("workout_data.txt");
    if (!success) 
    {
        std::cerr << "Failed to import workout data. Check if the file exists and its name and contents are formatted correctly.\n";
        exit(1);
    }
    assert(success == true);

    success = calendar.importWorkout("missing_file.txt");
    assert(success == false);
}

//Runs tests and prints to console if they were all passed
int main() 
{
    test_addDate();
    test_getDate();
    test_importWorkout();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
