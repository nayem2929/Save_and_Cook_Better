#pragma once
#include <string>

struct Recipe {
    int id = 0;
    std::string name;
    int minutes = 0;
    double rating = 0.0;
    int n_ingredients = 0;
    int n_steps = 0;
    double score = 0.0;

    void calculateScore() {
        if (n_ingredients <= 0) {
            score = 0.0;
            return;
        }
        // Base formula: higher rating, fewer ingredients -> higher score
        score = rating / static_cast<double>(n_ingredients);
    }
};