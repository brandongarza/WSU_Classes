from sklearn.linear_model import Perceptron
import pandas as pd
import numpy as np
import enchant
import string
from string import digits
import os.path
from os import path
import re

def main():
    TrainingDict = {}
    TestingDict = {}
    TrainingRatings = None
    TestingRatings = None
    vocabulary = []
    alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    headers = ['Rating', 'Title', 'Comment']
    english = enchant.Dict("en_US")

    if not path.exists("./saved/TrainingDataFrame.csv") and not path.exists("./saved/TestingDataFrame.csv"):

        train = pd.read_csv("TrainingData.csv", names=headers)
        trainDF = pd.DataFrame(train)
        test = pd.read_csv("TestingData.csv", names=headers)
        testDF = pd.DataFrame(test)

        EnglishWords = open("common_words.txt")
        SpanishWords = open("common_spanish.txt")

        StopListDict = dict.fromkeys(alphabet, [' '])

        for entry in EnglishWords:
            entry = entry.lower()
            entry = entry.rstrip()
            key = entry[0]
            if StopListDict[key] == [' ']:
                StopListDict[key] = [entry]
            else:
                StopListDict[key].append(entry)

        for entry in SpanishWords:
            entry = entry.lower()
            entry = entry.rstrip()
            key = entry[0]
            if StopListDict[key] == [' ']:
                StopListDict[key] = [entry]
            else:
                StopListDict[key].append(entry)

        #print(StopListDict)

        x = 0
        while x < len(trainDF.index):
            trainDF.loc[x, 'Comment'] = trainDF.loc[x, 'Comment'].translate(str.maketrans('', '', string.punctuation))
            trainDF.loc[x, 'Comment'] = trainDF.loc[x, 'Comment'].translate(str.maketrans('', '', digits))
            trainDF.loc[x, 'Comment'] = trainDF.loc[x, 'Comment'].lower()

            TrainingDict[x] = {}
            line = trainDF.loc[x, 'Comment'].split()
            for word in line:
                if word[0] in alphabet:
                    if not StopListDict[word[0]].__contains__(word) and english.check(word):
                        if not vocabulary.__contains__(word):
                            vocabulary.append(word)
                        TrainingDict[x][word] = 1
            print(x)
            x = x + 1

        x = 0
        while x < len(testDF.index):
            testDF.loc[x, 'Comment'] = testDF.loc[x, 'Comment'].translate(str.maketrans('', '', string.punctuation))
            testDF.loc[x, 'Comment'] = testDF.loc[x, 'Comment'].translate(str.maketrans('', '', digits))
            testDF.loc[x, 'Comment'] = testDF.loc[x, 'Comment'].lower()

            TestingDict[x] = {}
            line = testDF.loc[x, 'Comment'].split()
            for word in line:
                if word[0] in alphabet:
                    if not StopListDict[word[0]].__contains__(word) and vocabulary.__contains__(word) and english.check(word):
                        TestingDict[x][word] = 1
            print(x)
            x = x + 1

        TrainingDF = pd.DataFrame(TrainingDict, index=vocabulary)
        TrainingDF = TrainingDF.fillna(0)

        TestingDF = pd.DataFrame(TestingDict, index=vocabulary)
        TestingDF = TestingDF.fillna(0)

        TrainingRatings = trainDF['Rating'].values
        TestingRatings = testDF['Rating'].values

        TrainingDF.to_csv("./saved/TrainingDataFrame.csv")
        np.savetxt("./saved/TrainingLabels.txt", TrainingRatings, delimiter=',')
        TestingDF.to_csv("./saved/TestingDataFrame.csv")
        np.savetxt("./saved/TestingLabels.txt", TestingRatings, delimiter=',')

    else:
        TrainingDF = pd.read_csv("./saved/TrainingDataFrame.csv", index_col=0)
        TestingDF = pd.read_csv("./saved/TestingDataFrame.csv", index_col=0)
        if not path.exists("./saved/TrainingLabels.txt"):
            print("ERROR: Training labels not found")
            return -1
        if not path.exists("./saved/TestingLabels.txt"):
            print("ERROR: Testing labels not found")
            return -1
        TrainingRatings = np.loadtxt("./saved/TrainingLabels.txt", delimiter=',').astype(int)
        TestingRatings = np.loadtxt("./saved/TestingLabels.txt", delimiter=',').astype(int)

    per = Perceptron()
    per.fit(TrainingDF.transpose(), TrainingRatings)
    print(per.score(TestingDF.transpose(), TestingRatings))

if __name__ == "__main__":
    main()