## README

This program compares the result of merge sort and min-heap on a recipe dataset to find the top K recipes based on ratings, specific meal type (either simple or complex), and prearation time.

## Dataset Setup
1. After cloning the repository, download RAW_interactions.csv and RAW_recipes.csv from https://www.kaggle.com/datasets/shuyangli94/food-com-recipes-and-user-interactions?resource=download
and place them in the root project folder.
2. Run preprocessor.py to create the cleaned_recipes.csv

## Build and run
bash:
g++ -std=c++17 -O2 main.cpp -o save_and_cook
./save_and_cook

powershell:
g++ -std=c++17 -O2 main.cpp -o save_and_cook.exe
.\save_and_cook.exe


## Menu
Menu Explained:
1. Option 1 sets the number of top (best) recipes (k value)
2. Option 2 sets the maximum ingredient count
3. Option 3 chooses the meal type, either simple (high-rated recipes with fewer steps and ingredients) or complex meal (high-rated recipes with more steps and ingredients)
4. Option 4 finds and compares the algorithm performance between merge sort and min heap using a selected amount of recipes.
5. Option 5 quits the program.

## Meal Scoring
- Higher scores are ranked first. Maximum ingredient count is applied to both meal types.
- For simple meals, high ratings with shorter preparation times and less ingredients are favored more:

score = rating × 10
      − minutes × 0.10
      − ingredients × 1.50
      − steps × 0.75

- For complex meals, high ratings with greater preparation steps and more ingredients are favored more:

score = rating × 10
      + ingredients × 1.50
      + steps × 0.75

## Merge Sort
- The algorithm sorts all the eligible recipes in descending ranked order, then displays the first K. It uses insertion sort for partitions of 16 recipes or less.

## Min Heap
- The algorithm scans the given input while it retains at most K recipes. The root has the lowest-ranked recipes, allowing better recipes to place it as the input gets scanned. Then, the recipes get displayed in highest to lowest ranked order.

## Comparing Algorithm Performance
- Option 4 fliters recipes by given maxmimum ingredient count, then allows the user to pick the number of eligible recipes to utilize.
  - This is different from comparing maximum ingredient count, which is in option 2. 
- Pick a number to request a specific number of recipes, otherwise use '0' to utilize all eligible recipes
- Examples of suggested dataset sizes: 1000, 10000, 100000, all eligible recipes (0).

- The comparison displays:
  - Algorithm runtime (ms)
  - Estimated additional working memory
  - Top-k recipe lists from both algorithms and confirms both lists display the recipes in the same order.
  - The speedup amount of the faster algorithm

  ## Memory Based on Algorithms
  - Memory values are estimated from recipe storage.
  - The estimates do not include the input or other dynamically allocated overhead.
  - Merge sort utilizes 1 tempporary recipe slot per input recipe
  - Min heap employs 1 recipe slot per retained candidate, up to K

