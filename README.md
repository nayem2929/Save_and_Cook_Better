## README ##
Welcome to the project!
Getting Started & Setup: 
- After cloning the repository, download RAW_interactions.csv and RAW_recipes.csv and place them in the root project folder.
- Run preprocessor.py
Note: This script generates cleaned_recipes.csv so the C++ program doesn't have to re-parse all 230k lines on every run.
- Scoring Logic & Proposed Features
    Current Implementation: The formula is kept simple—it rewards recipes with low ingredient counts and high ratings.
    Proposed Enhancement: Add an option for users to choose between two meal types: Weekday Meal: Low preparation time (minutes), low ingredient count, few steps, high rating. Weeknight / Complex Meal: High rating, higher number of ingredients, and more steps (reflecting the complexity of the dish)
Feel free to adjust the scoring calculations and assign specific weights to these attributes.
Note: Code comments are minimal for now—please reach out if you have any questions!
Heap Implementation Recommendation: For the heap implementation, I recommend a Min-Heap of the topK elements (default: K = 10). This should save a significant amount of memory compared to building a heap over the entire dataset.
Benchmarks & Performance Baseline:
Current test results on the full dataset:
`Running Merge Sort vs Min-Heap...`
`Running Merge Sort on 231637 recipes...`
`Merge Sort completed in: 397.34 ms`
Merge Sort currently runs in approximately 400 ms.

Todo / Help Needed: 
Memory Counter: A memory counter still needs to be implemented. If one of you can add tracking for memory usage, that would be greatly appreciated!


Sorry for the delay getting this set up, and again, please let me know if anything is unclear!