#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// Struct to represent a single workout plan
struct Workout {
    string name;
    vector<string> movements;
    string videoLink;
};

// Builds and eturns a weekly workout schedule
map<string, Workout> generateWeeklySchedule() {
    map<string, Workout> schedule;

    // Load the map with each days workout. Use the number in front of the day to maintain day order
    schedule["1Monday"] = {"Upper Body Strength", {"Bench Press", "Pull-ups", "Shoulder Press"}, "https://fitness.monday"};
    schedule["2Tuesday"] = {"Cardio Blast", {"Jumping Jacks", "Run", "Burpees"}, "https://fitness.tuesday"};
    schedule["3Wednesday"] = {"Core Crusher", {"Sit-ups", "Plank", "Russian Twists"}, "https://fitness.wednesday"};
    schedule["4Thursday"] = {"Leg Day", {"Squats/Split Squats", "Weighted Lunges", "Quads/Hamstrings Extensions"}, "https://fitness.thursday"};
    schedule["5Friday"] = {"Full Body", {"Mountain Climbers", "Burpees", "Squat Jumps"}, "https://fitness.friday"};
    schedule["6Saturday"] = {"Stretch & Recover", {"Yoga Poses", "Hamstring Stretch", "Foam Rolling"}, "https://fitness.saturday"};
    schedule["7Sunday"] = {"Rest Day", {"Light Walk", "Meditation", "Deep Breathing"}, "https://fitness.sunday"};

    return schedule;
}

// Display the full weekly schedule
void displayWeeklySchedule(const map<string, Workout>& schedule) {
    cout << "\n======== Weekly Workout Schedule ========\n";   // Header line
    for (const auto& day : schedule) {                         // Daily workouts formatted 
        cout << "\n📅 " << day.first.substr(1) << " - " << day.second.name << "\n";  // Strip the 1st character of the day
        cout << "🔗 Video Guide: " << day.second.videoLink << "\n";
        cout << "💪 Movements:\n";
        for (const string& move : day.second.movements) {
            cout << "  - " << move << "\n";
        }
    }
    cout << "=========================================\n";
}

int main() {
    // Generate and display the weekly schedule
    map<string, Workout> weeklySchedule = generateWeeklySchedule();
    displayWeeklySchedule(weeklySchedule);

    return 0;
}
