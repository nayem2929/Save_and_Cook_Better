#pragma once
#include <string>

using namespace std;

struct Recipe {
    int id = 0;
    string name;
    int minutes = 0;
    double rating = 0.0;
    int n_ingredients = 0;
    int n_steps = 0;
    double score = 0.0;

    void calculateScore(bool weekdayMeal = true) {
        if (weekdayMeal) {
            // Weekday meals should be quick and simple, while still rated well.
            score = rating * 10.0
                  - minutes * 0.10
                  - n_ingredients * 1.50
                  - n_steps * 0.75;
        } else {
            // Complex meals reward highly rated recipes with more ingredients
            // and more preparation steps.
            score = rating * 10.0
                  + n_ingredients * 1.50
                  + n_steps * 0.75;
        }
    }
};

// Keep rankings deterministic when two recipes have the same score.
bool recipeRanksHigher(const Recipe& left, const Recipe& right) {
    return left.score > right.score ||
           (left.score == right.score && left.id < right.id);
}
