#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

//--------------------------------------------
// 1) Define NutritionTracker inline
//--------------------------------------------
struct FoodItem {
    std::string name;
    int calories;
    double protein;
    double carbs;
    double fats;
};

class NutritionTracker {
public:
    // Return true if the item is valid and was added
    bool addFood(const FoodItem& food) {
        // Simple "validity" check: name must not be empty, calories >= 0
        if (food.name.empty() || food.calories < 0) {
            return false;
        }
        foodLog.push_back(food);
        return true;
    }

    // Return true if removed, false otherwise
    bool removeFood(const std::string& name) {
        for (auto it = foodLog.begin(); it != foodLog.end(); ++it) {
            if (it->name == name) {
                foodLog.erase(it);
                return true;
            }
        }
        return false;
    }

    double totalCalories() const {
        double sum = 0;
        for (const auto& food : foodLog) {
            sum += food.calories;
        }
        return sum;
    }

private:
    std::vector<FoodItem> foodLog;
};

//--------------------------------------------
// 2) Unit Tests
//--------------------------------------------
TEST(NutritionTrackerTest, AddFood_ValidItem) {
    NutritionTracker tracker;
    FoodItem apple {"Apple", 95, 0.3, 25.0, 0.2};
    // Expect addFood to succeed
    EXPECT_TRUE(tracker.addFood(apple));
    // totalCalories should reflect the new item
    EXPECT_DOUBLE_EQ(tracker.totalCalories(), 95.0);
}

TEST(NutritionTrackerTest, AddFood_InvalidItem) {
    NutritionTracker tracker;
    FoodItem invalid {"", -5, 0.3, 5.0, 0.1};
    // Expect addFood to fail
    EXPECT_FALSE(tracker.addFood(invalid));
    // totalCalories should remain at 0
    EXPECT_DOUBLE_EQ(tracker.totalCalories(), 0.0);
}

TEST(NutritionTrackerTest, RemoveFood_Existing) {
    NutritionTracker tracker;
    FoodItem banana {"Banana", 100, 1.3, 27.0, 0.3};
    tracker.addFood(banana);
    // Removing "Banana" should succeed
    EXPECT_TRUE(tracker.removeFood("Banana"));
    // totalCalories should be 0
    EXPECT_DOUBLE_EQ(tracker.totalCalories(), 0.0);
}

TEST(NutritionTrackerTest, RemoveFood_NonExisting) {
    NutritionTracker tracker;
    FoodItem yogurt {"Yogurt", 59, 10.0, 3.6, 0.4};
    tracker.addFood(yogurt);
    // Removing something that doesn't exist should fail
    EXPECT_FALSE(tracker.removeFood("Pizza"));
    // totalCalories should still be 59
    EXPECT_DOUBLE_EQ(tracker.totalCalories(), 59.0);
}

//--------------------------------------------
// 3) main() - Takes Input, Prints Pass/Fail,
//    Then runs the tests
//--------------------------------------------
int main(int argc, char** argv) {
    // PART A: Simple input check that prints "Passed!" or "Failed!"
    std::cout << "Enter a food name: ";
    std::string userInput;
    std::cin >> userInput;

    // Create tracker and a simple test FoodItem
    NutritionTracker tracker;
    FoodItem userFood {userInput, 100, 5.0, 10.0, 2.0};

    if (tracker.addFood(userFood)) {
        std::cout << "Passed!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }

    // PART B: Run all Google Tests
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
