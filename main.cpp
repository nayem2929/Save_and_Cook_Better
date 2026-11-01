#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <limits>

#include "recipe.h"
#include "MergeSort.h"
#include "MinHeap.h"

using namespace std;

void printMemory(int bytes) {
    constexpr double bytesPerKiB = 1024.0;
    constexpr double bytesPerMiB = bytesPerKiB * 1024.0;
    cout << "Estimated extra working memory: ";
    if (bytes >= bytesPerMiB) {
        cout << fixed << setprecision(2)
                  << bytes / bytesPerMiB << " MiB\n";
    } else {
        cout << fixed << setprecision(2)
                  << bytes / bytesPerKiB << " KiB\n";
    }
}

// Load cleaned_recipes.csv into memory
vector<Recipe> loadDataset(const string& filename) {
    vector<Recipe> recipes;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return recipes;
    }

    string line;
    // Skip header: recipe_id,name,minutes,rating,n_ingredients,n_steps
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        Recipe r;

        try {
            // recipe_id
            if (!getline(ss, token, ',')) continue;
            r.id = stoi(token);

            // name
            if (!getline(ss, r.name, ',')) continue;

            // minutes
            if (!getline(ss, token, ',')) continue;
            r.minutes = stoi(token);

            // rating
            if (!getline(ss, token, ',')) continue;
            r.rating = stod(token);

            // n_ingredients
            if (!getline(ss, token, ',')) continue;
            r.n_ingredients = stoi(token);

            // n_steps
            if (!getline(ss, token, ',')) continue;
            r.n_steps = stoi(token);

            r.calculateScore();
            recipes.push_back(r);
        } catch (...) {
            continue;
        }
    }

    return recipes;
}

void updateScores(vector<Recipe>& recipes, bool weekdayMeal) {
    for (Recipe& recipe : recipes) {
        recipe.calculateScore(weekdayMeal);
    }
}

void printRecipes(const vector<Recipe>& recipes, int count) {
    cout << "\n" << left
              << setw(8)  << "ID"
              << setw(35) << "Name"
              << setw(10) << "Rating"
              << setw(14) << "Ingredients"
              << setw(10) << "Minutes"
              << setw(10) << "Score" << "\n";
    cout << string(87, '-') << "\n";

    int limit = recipes.size();
    if (limit > count) limit = count;
    for (int i = 0; i < limit; i++) {
        const auto& r = recipes[i];
        string displayName = r.name.length() > 32 ? r.name.substr(0, 31) + "..." : r.name;
        cout << left
                  << setw(8)  << r.id
                  << setw(35) << displayName
                  << setw(10) << fixed << setprecision(2) << r.rating
                  << setw(14) << r.n_ingredients
                  << setw(10) << r.minutes
                  << setw(10) << fixed << setprecision(4) << r.score << "\n";
    }
    cout << endl;
}

int main() {
    cout << "Loading dataset..." << endl;
    vector<Recipe> all_recipes = loadDataset("cleaned_recipes.csv");
    cout << "Loaded " << all_recipes.size() << " recipes successfully.\n" << endl;

    int choice = 0;
    int topK = 10;
    int maxIngredients = 100;
    bool weekdayMeal = true;

    while (choice != 5) {
        cout << "=============================\n";
        cout << "    Save & Cook Better!      \n";
        cout << "=============================\n";
        cout << "1. Find Best # of recipes (Current: " << topK << ")\n";
        cout << "2. Choose Max ingredient # (Current: " << maxIngredients << ")\n";
        cout << "3. Choose Meal Type (Current: "
                  << (weekdayMeal ? "Weekday" : "Complex") << ")\n";
        cout << "4. Compare Alg. Performance\n";
        cout << "5. Quit Program\n";
        cout << "Please choose an option: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            string discard;
            cin >> discard;
            continue;
        }

        if (choice == 1) {
            cout << "Enter number of top recipes to retrieve: ";
            int requestedTopK;
            if (!(cin >> requestedTopK) || requestedTopK < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a positive number. Keeping the previous value.\n";
            } else {
                topK = requestedTopK;
            }
        } else if (choice == 2) {
            cout << "Enter maximum ingredient count: ";
            cin >> maxIngredients;
        } else if (choice == 3) {
            int mealChoice;
            cout << "1. Weekday meal (fewer minutes, ingredients, and steps)\n";
            cout << "2. Complex meal (more ingredients and steps)\n";
            cout << "Choose a meal type: ";

            if (cin >> mealChoice && (mealChoice == 1 || mealChoice == 2)) {
                weekdayMeal = mealChoice == 1;
                updateScores(all_recipes, weekdayMeal);
                cout << "Scores updated for "
                          << (weekdayMeal ? "weekday meals.\n" : "complex meals.\n");
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid meal type. Keeping the current choice.\n";
            }
        } else if (choice == 4) {
            // Filter by maxIngredients
            vector<Recipe> filtered;
            for (const auto& r : all_recipes) {
                if (r.n_ingredients <= maxIngredients) {
                    filtered.push_back(r);
                }
            }

            cout << "\nFiltering complete: " << filtered.size() << " eligible recipes.\n";
            vector<Recipe> mergeList = filtered; //copy to run sorting on
            cout << "Running Merge Sort vs Min-Heap...\n";

            // 3. Benchmark Merge Sort
            cout << "Running Merge Sort on " << mergeList.size() << " recipes...\n";
            auto start = chrono::high_resolution_clock::now();

            runMergeSort(mergeList);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> mergeDuration = end - start;

            cout << "Merge Sort completed in: " << mergeDuration.count() << " ms\n";
            printMemory(mergeSortWorkingMemoryBytes(mergeList.size()));

            // 4. Display top-k from the sorted list
            cout << "\nTop " << topK << " Recipes via Merge Sort:";
            printRecipes(mergeList, topK);

            // 5. Benchmark the bounded min-heap. It retains only K recipes
            // instead of allocating a sorting buffer for every eligible recipe.
            cout << "Running Min-Heap on " << filtered.size() << " recipes...\n";
            start = chrono::high_resolution_clock::now();
            vector<Recipe> heapList = findTopKWithMinHeap(filtered, topK);
            end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> heapDuration = end - start;

            cout << "Min-Heap completed in: " << heapDuration.count() << " ms\n";
            printMemory(minHeapWorkingMemoryBytes(filtered.size(), topK));
            cout << "\nTop " << topK << " Recipes via Min-Heap:";
            printRecipes(heapList, topK);
        }
        }

    cout << "Exiting program. Goodbye!\n";
    return 0;
}
