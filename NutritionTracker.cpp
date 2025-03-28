#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;  // allows cin, cout, string, etc. without std::

struct FoodItem {
    string name;
    int calories;
    double protein;
    double carbs;
    double fats;
};

class NutritionTracker {
public:
    // Throws runtime_error if the item is invalid
    void addFood(const FoodItem& food) {
        if (food.name.empty() || food.calories < 0) {
            throw runtime_error("Invalid food item: name is empty or calories are negative.");
        }
        foodLog.push_back(food);
    }

    // Throws runtime_error if we don't find the item
    void removeFood(const string& foodName) {
        for (auto it = foodLog.begin(); it != foodLog.end(); ++it) {
            if (it->name == foodName) {
                foodLog.erase(it);
                return;
            }
        }
        throw runtime_error("Food item not found: " + foodName);
    }

    double totalCalories() const {
        double sum = 0;
        for (auto& item : foodLog) {
            sum += item.calories;
        }
        return sum;
    }

private:
    vector<FoodItem> foodLog;
};

//---------------------------------------------
// Test 1: AddFood_ValidItem
//  - We expect no exception => “Passed!”
//  - If an exception is thrown => “Failed!”
//---------------------------------------------
void testAddFoodValid() {
    cout << "\n--- Test 1: AddFood_ValidItem ---\n"
         << "(Enter a non-empty name and >= 0 calories to pass.)\n";

    string name;
    int cal;
    double protein, carbs, fats;

    cout << "Enter food name: ";
    getline(cin, name);

    cout << "Enter calories (>= 0): ";
    cin >> cal;

    cout << "Enter protein, carbs, fats: ";
    cin >> protein >> carbs >> fats;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear leftover

    NutritionTracker tracker;
    try {
        FoodItem item { name, cal, protein, carbs, fats };
        tracker.addFood(item);
        // If we get here, no exception
        cout << "Passed! (No exception thrown, item accepted)\n";
    } catch (const exception& e) {
        cout << "Failed! (Exception thrown: " << e.what() << ")\n";
    }
}

//---------------------------------------------
// Test 2: AddFood_InvalidItem
//  - We expect an exception => “Passed!”
//  - If no exception => “Failed!”
//---------------------------------------------
void testAddFoodInvalid() {
    cout << "\n--- Test 2: AddFood_InvalidItem ---\n"
         << "(Enter an empty name OR negative calories to pass.)\n";

    string name;
    int cal;
    double protein, carbs, fats;

    cout << "Enter food name: ";
    getline(cin, name);

    cout << "Enter calories: ";
    cin >> cal;

    cout << "Enter protein, carbs, fats: ";
    cin >> protein >> carbs >> fats;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    NutritionTracker tracker;
    try {
        FoodItem item { name, cal, protein, carbs, fats };
        tracker.addFood(item);
        // No exception => Fail
        cout << "Failed! (No exception thrown but we expected one.)\n";
    } catch (const exception& e) {
        cout << "Passed! (Exception thrown: " << e.what() << ")\n";
    }
}

//---------------------------------------------
// Test 3: RemoveFood_Existing
//  - We add “Banana” to the tracker
//  - If the user enters “Banana” => no exception => “Passed!”
//  - Otherwise => “Failed!”
//---------------------------------------------
void testRemoveFoodExisting() {
    cout << "\n--- Test 3: RemoveFood_Existing ---\n"
         << "We have added 'Banana' (100 cal) to the tracker.\n"
         << "(Enter 'Banana' to pass, anything else => fails)\n";

    NutritionTracker tracker;
    FoodItem banana { "Banana", 100, 1.3, 27.0, 0.3 };
    tracker.addFood(banana);

    string foodToRemove;
    cout << "Enter the item name to remove: ";
    getline(cin, foodToRemove);

    try {
        tracker.removeFood(foodToRemove);
        // No exception => success
        cout << "Passed! (No exception thrown, item removed.)\n";
    } catch (const exception& e) {
        cout << "Failed! (Exception thrown: " << e.what() << ")\n";
    }
}

//---------------------------------------------
// Test 4: RemoveFood_NonExisting
//  - We add “Yogurt” (59 cal) to the tracker
//  - If user enters something else => throws => “Passed!”
//  - If user enters “Yogurt” => no throw => “Failed!”
//---------------------------------------------
void testRemoveFoodNonExisting() {
    cout << "\n--- Test 4: RemoveFood_NonExisting ---\n"
         << "We have added 'Yogurt' (59 cal) to the tracker.\n"
         << "(Enter something else => pass, 'Yogurt' => fail)\n";

    NutritionTracker tracker;
    FoodItem yogurt { "Yogurt", 59, 10.0, 3.6, 0.4 };
    tracker.addFood(yogurt);

    string foodToRemove;
    cout << "Enter the item name to remove: ";
    getline(cin, foodToRemove);

    try {
        tracker.removeFood(foodToRemove);
        // If no exception, that’s a fail for this test
        cout << "Failed! (No exception thrown but we expected one.)\n";
    } catch (const exception& e) {
        // Threw => pass
        cout << "Passed! (Exception thrown: " << e.what() << ")\n";
    }
}

//---------------------------------------------
// Main: run all the tests in sequence
//---------------------------------------------
int main() {
    cout << "Welcome to the simple try/catch NutritionTracker tests!\n";
    cout << "We’ll run 4 tests in sequence.\n"
         << "Follow the prompts carefully.\n";

    testAddFoodValid();
    testAddFoodInvalid();
    testRemoveFoodExisting();
    testRemoveFoodNonExisting();

    cout << "\nAll tests completed!\n";
    return 0;
}
