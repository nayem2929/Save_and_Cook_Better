import csv

print("Loading interactions...")
ratings = {}
with open('RAW_interactions.csv', mode='r', encoding='utf-8') as f:
    reader = csv.DictReader(f)
    for row in reader:
        r_id = row['recipe_id']
        rating = float(row['rating'])
        if r_id not in ratings:
            ratings[r_id] = [0.0, 0]
        ratings[r_id][0] += rating
        ratings[r_id][1] += 1

print("Processing recipes with minutes...")
with open('RAW_recipes.csv', mode='r', encoding='utf-8') as fin, \
     open('cleaned_recipes.csv', mode='w', newline='', encoding='utf-8') as fout:
    
    reader = csv.DictReader(fin)
    writer = csv.writer(fout)
    # Added 'minutes' to the header
    writer.writerow(['recipe_id', 'name', 'minutes', 'rating', 'n_ingredients', 'n_steps'])
    
    count = 0
    for row in reader:
        r_id = row['id']
        name = row['name'].replace('"', '')  # strip quotes to keep CSV plain and simple
        minutes = row['minutes']
        n_ingredients = row['n_ingredients']
        n_steps = row['n_steps']
        
        # Calculate average rating
        if r_id in ratings and ratings[r_id][1] > 0:
            avg_rating = round(ratings[r_id][0] / ratings[r_id][1], 2)
        else:
            avg_rating = 0.0
            
        writer.writerow([r_id, name, minutes, avg_rating, n_ingredients, n_steps])
        count += 1

print(f"Finished! Wrote {count} clean rows with minutes to cleaned_recipes.csv")