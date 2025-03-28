#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

struct ActivityLog {
    std::vector<std::string> meals;
    std::map<std::string, std::string> mealTimes;
    std::vector<std::string> exercises;
};

struct Recommendation {
    std::map<std::string, std::string> vitamins;     // vitamin -> quantity
    std::vector<std::string> supplements;
    std::string mealSuggestion;
    std::string exerciseSuggestion;
};

std::vector<std::string> mealOptions = {
    "Grilled salmon with broccoli",
    "Tofu stir-fry with quinoa",
    "Oatmeal with almonds and blueberries",
    "Lentil soup with whole grain bread",
    "Greek yogurt bowl with fruit and honey"
};

std::vector<std::string> exerciseOptions = {
    "Try 20 minutes of yoga",
    "Go for a 30-minute walk",
    "Do a 15-minute bodyweight HIIT routine",
    "Stretch for flexibility and posture",
    "Light cycling for 25 minutes"
};

Recommendation recommendSupplements(const ActivityLog& log) {
    Recommendation rec;
    bool didCardio = false;
    bool skippedBreakfast = (log.mealTimes.find("breakfast") == log.mealTimes.end());

    for (const auto& ex : log.exercises) {
        if (ex == "running" || ex == "cycling" || ex == "HIIT" || ex == "jogging") {
            didCardio = true;
        }
    }

    if (didCardio) {
        rec.vitamins["Vitamin B12"] = "2.4 mcg";
        rec.supplements.push_back("Electrolyte tablets");
    }

    if (skippedBreakfast) {
        rec.vitamins["Vitamin D"] = "1000 IU";
        rec.supplements.push_back("Multivitamin");
    }

    // Random meal and exercise suggestion
    rec.mealSuggestion = mealOptions[rand() % mealOptions.size()];
    rec.exerciseSuggestion = exerciseOptions[rand() % exerciseOptions.size()];

    return rec;
}

std::vector<std::string> splitInput(const std::string& input) {
    std::stringstream ss(input);
    std::string word;
    std::vector<std::string> result;
    while (ss >> word) result.push_back(word);
    return result;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    ActivityLog log;
    std::string input, meal, time;

    std::cout << "What meals did you have today? (e.g., breakfast lunch dinner): ";
    std::getline(std::cin, input);
    log.meals = splitInput(input);

    for (const auto& meal : log.meals) {
        std::cout << "What time did you eat " << meal << "? (e.g., 08:00): ";
        std::getline(std::cin, time);
        log.mealTimes[meal] = time;
    }

    std::cout << "What exercises did you do today? (e.g., running push-ups): ";
    std::getline(std::cin, input);
    log.exercises = splitInput(input);

    Recommendation rec = recommendSupplements(log);

    std::cout << "\n🧠 Based on your activity today, here's your recommendation:\n";
    std::cout << "-------------------------------------------------------------\n";

    if (!rec.vitamins.empty()) {
        std::cout << "🔋 Vitamins you might need:\n";
        for (const auto& vit : rec.vitamins) {
            std::cout << " - " << vit.first << ": " << vit.second << "\n";
        }
    } else {
        std::cout << "✅ You seem nutritionally balanced today!\n";
    }

    if (!rec.supplements.empty()) {
        std::cout << "💊 Suggested Supplements: ";
        for (const auto& supp : rec.supplements) {
            std::cout << supp << " ";
        }
        std::cout << "\n";
    }

    std::cout << "🍽️  Meal suggestion: " << rec.mealSuggestion << "\n";
    std::cout << "🏃 Exercise suggestion: " << rec.exerciseSuggestion << "\n";
    std::cout << "-------------------------------------------------------------\n";

    return 0;
}
