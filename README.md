## README ##

This program compares the result of merge sort and min-heap on a recipe dataset to find recipes based on the ingredient count.

Dataset Setup: 
1. After cloning the repository, download RAW_interactions.csv and RAW_recipes.csv from https://www.kaggle.com/datasets/shuyangli94/food-com-recipes-and-user-interactions?resource=download
and place them in the root project folder.
2. Run preprocessor.py to create the cleaned_recipes.csv

### Build and run

```bash
g++ -std=c++17 -O2 main.cpp -o save_and_cook
./save_and_cook
```

## Menu
Menu Explained:
1: Option 1 sets the number of top (best) recipes (k value)
2: Option 2 sets the maximum ingredient count
3: Option 3 chooses the meal tyoe
4: Option 4 compares the algorithm performance
5: Quits the program

- Scoring Logic & Proposed Features
  - Current Implementation: The formula is kept simple for now, it rewards recipes with low ingredient counts and high ratings.
- Proposed Enhancement: Add an option for users to choose between two meal types: Weekday Meal: Low preparation time (minutes), low ingredient count, few steps, high rating. Weeknight / Complex Meal: High rating, higher number of ingredients, and more steps (reflecting the complexity of the dish)
- Meal-type scoring is implemented. Weekday score = `rating * 10 - minutes * 0.10 - ingredients * 1.50 - steps * 0.75`. Complex score = `rating * 10 + ingredients * 1.50 + steps * 0.75`. Users choose the meal type from the main menu before running the comparison.
- Code comments are minimal for now—please reach out if you have any questions!
- Heap Implementation Recommendation: For the heap implementation, I recommend a Min-Heap of the topK elements (default: K = 10). This should save a significant amount of memory compared to building a heap over the entire dataset.
- Min-Heap implementation: Option 3 benchmarks a bounded min-heap against merge sort. It keeps at most `topK` recipes in memory and presents both top-K result lists in descending score order.
- Benchmarks & Performance Baseline:
  -Current test results on the full dataset:
    `Running Merge Sort vs Min-Heap...`
    `Running Merge Sort on 231637 recipes...`
    `Merge Sort completed in: 397.34 ms`
  Merge Sort currently runs in approximately 400 ms.

- Todo / Help Needed: 
-Memory Counter: A memory counter still needs to be implemented. If one of you can add tracking for memory usage, that would be greatly appreciated!
  - Implemented: Option 3 now prints each algorithm's estimated additional working memory. The number is the vector storage allocated by the algorithm itself: one `Recipe` slot per eligible recipe for merge sort and at most `topK` `Recipe` slots for the min-heap. It intentionally excludes the already-loaded dataset and recipe-name allocations shared with the input data.




