import pandas as pd
import numpy as np
import re

ratings_df = pd.read_csv("ratings.csv")
movies_df = pd.read_csv("movies.csv")

user_array = ratings_df['userId'].values
movie_array = ratings_df['movieId'].values
rating_array = ratings_df['rating'].values

item_profiles = {}

i = 0
while i < user_array.size:
    if not item_profiles.__contains__(movie_array[i]):
        item_profiles[movie_array[i]] = {}
        item_profiles[movie_array[i]][user_array[i]] = rating_array[i]
    else:
        if not item_profiles[movie_array[i]].__contains__(user_array[i]):
            item_profiles[movie_array[i]][user_array[i]] = rating_array[i]
    i = i+1

itemsDataFrame = pd.DataFrame(item_profiles)

itemsDataFrame = itemsDataFrame.fillna(0)

print(itemsDataFrame)


