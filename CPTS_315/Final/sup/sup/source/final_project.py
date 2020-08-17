# Programmer:Jesus Cruz
# Cpts:315


import pandas as pd
import numpy as np
from numpy import linalg as LA

import string

#read data in
open_file = open("../data/common_words.txt", 'r')
common_words = open_file.readlines()

def main_hw2():
    d = dict.fromkeys(string.ascii_lowercase, [])

    for word in common_words:
        if word not in d[word[0].lower()]:
            d[word[0].lower()].append(word.lower())
            # print("dictionary key:", d[word[0]], "character: ", word[0])

    print(d)


if __name__ == '__main__':
    print(main_hw2())
