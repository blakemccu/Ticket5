#include <iostream>
#include <cassert>
#include "WorkoutCalendar.h" 

void test_addDate() {
    WorkoutCalendar calendar;
    Workout workout("Push Day", 60);

    // Test adding a workout
    assert(calendar.addDate("2025-03-07", workout) == true);
    
    // Test adding a workout to an existing date (repeat yourself)
    assert(calendar.addDate("2025-03-07", workout) == false);
}

void test_getDate() {
    WorkoutCalendar calendar;
    Workout workout("Leg Day", 75);
    calendar.addDate("2025-03-08", workout);

    // Test retrieving a workout
    Workout retrieved = calendar.getDate("2025-03-08");
    assert(retrieved.getName() == "Leg Day");
    assert(retrieved.getDuration() == 75);

    // Test getting a date with no workout (NULL/0 case)
    Workout emptyWorkout = calendar.getDate("2025-03-09");
    assert(emptyWorkout.getName() == "");
    assert(emptyWorkout.getDuration() == 0);
}

void test_importWorkout() {
    WorkoutCalendar calendar;

    // Test importing valid workout data
    bool success = calendar.importWorkout("workout_data.txt");
    assert(success == true);

    // Test importing from a non-existent file (NULL case)
    success = calendar.importWorkout("missing_file.txt");
    assert(success == false);
}

int main() {
    test_addDate();
    test_getDate();
    test_importWorkout();


    return 0;
}
