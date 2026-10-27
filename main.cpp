#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

#include "Recipe.h"
#include "MergeSort.h"
// #include "MinHeap.h"

// Load cleaned_recipes.csv into memory
std::vector<Recipe> loadDataset(const std::string& filename) {
    std::vector<Recipe> recipes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return recipes;
    }

    std::string line;
    // Skip header: recipe_id,name,minutes,rating,n_ingredients,n_steps
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        Recipe r;

        try {
            // recipe_id
            if (!std::getline(ss, token, ',')) continue;
            r.id = std::stoi(token);

            // name
            if (!std::getline(ss, r.name, ',')) continue;

            // minutes
            if (!std::getline(ss, token, ',')) continue;
            r.minutes = std::stoi(token);

            // rating
            if (!std::getline(ss, token, ',')) continue;
            r.rating = std::stod(token);

            // n_ingredients
            if (!std::getline(ss, token, ',')) continue;
            r.n_ingredients = std::stoi(token);

            // n_steps
            if (!std::getline(ss, token, ',')) continue;
            r.n_steps = std::stoi(token);

            r.calculateScore();
            recipes.push_back(r);
        } catch (...) {
            continue;
        }
    }

    return recipes;
}

void printRecipes(const std::vector<Recipe>& recipes, int count) {
    std::cout << "\n" << std::left 
              << std::setw(8)  << "ID" 
              << std::setw(35) << "Name" 
              << std::setw(10) << "Rating" 
              << std::setw(14) << "Ingredients"
              << std::setw(10) << "Minutes" 
              << std::setw(10) << "Score" << "\n";
    std::cout << std::string(87, '-') << "\n";

    int limit = std::min((int)recipes.size(), count);
    for (int i = 0; i < limit; i++) {
        const auto& r = recipes[i];
        std::string displayName = r.name.length() > 32 ? r.name.substr(0, 31) + "..." : r.name;
        std::cout << std::left 
                  << std::setw(8)  << r.id 
                  << std::setw(35) << displayName
                  << std::setw(10) << std::fixed << std::setprecision(2) << r.rating 
                  << std::setw(14) << r.n_ingredients 
                  << std::setw(10) << r.minutes 
                  << std::setw(10) << std::fixed << std::setprecision(4) << r.score << "\n";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Loading dataset..." << std::endl;
    std::vector<Recipe> all_recipes = loadDataset("cleaned_recipes.csv");
    std::cout << "Loaded " << all_recipes.size() << " recipes successfully.\n" << std::endl;

    int choice = 0;
    int topK = 10;
    int maxIngredients = 100;

    while (choice != 4) {
        std::cout << "=============================\n";
        std::cout << "    Save & Cook Better!      \n";
        std::cout << "=============================\n";
        std::cout << "1. Find Best # of recipes (Current: " << topK << ")\n";
        std::cout << "2. Choose Max ingredient # (Current: " << maxIngredients << ")\n";
        std::cout << "3. Compare Alg. Performance\n";
        std::cout << "4. Quit Program\n";
        std::cout << "Please choose an option: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string discard;
            std::cin >> discard;
            continue;
        }

        if (choice == 1) {
            std::cout << "Enter number of top recipes to retrieve: ";
            std::cin >> topK;
        } else if (choice == 2) {
            std::cout << "Enter maximum ingredient count: ";
            std::cin >> maxIngredients;
        } else if (choice == 3) {
            // Filter by maxIngredients
            std::vector<Recipe> filtered;
            for (const auto& r : all_recipes) {
                if (r.n_ingredients <= maxIngredients) {
                    filtered.push_back(r);
                }
            }

            std::cout << "\nFiltering complete: " << filtered.size() << " eligible recipes.\n";
            std::vector<Recipe> mergeList = filtered; //copy to run sorting on
            std::cout << "Running Merge Sort vs Min-Heap...\n";

            // 3. Benchmark Merge Sort
            std::cout << "Running Merge Sort on " << mergeList.size() << " recipes...\n";
            auto start = std::chrono::high_resolution_clock::now();

            runMergeSort(mergeList);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> mergeDuration = end - start;

            std::cout << "Merge Sort completed in: " << mergeDuration.count() << " ms\n";

            // 4. Display top-k from the sorted list
            std::cout << "\nTop " << topK << " Recipes via Merge Sort:";
            printRecipes(mergeList, topK);
            }
        }

    std::cout << "Exiting program. Goodbye!\n";
    return 0;
}