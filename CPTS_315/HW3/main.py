import pandas as pd
import numpy as np
import re


def part1():
    StopListDict = {}
    TrainingDict = {}
    TestingDict = {}
    TrainingAccuracy = {}
    TestingAccuracy = {}
    TrainingMistakes = {}
    TestingMistakes = {}
    TrainingAccuracy_avg = {}
    TestingAccuracy_avg = {}
    TrainingMistakes_avg = {}
    TestingMistakes_avg = {}
    vocabulary = []

    key = 0

    TrainData = pd.Series(open("traindata.txt"))
    TrainData = TrainData.replace('\n', '', regex=True)
    TrainLabels = pd.Series(open("trainlabels.txt"))
    TrainLabels = TrainLabels.replace('\n', '', regex=True)
    StopList = pd.Series(open("stoplist.txt"))
    StopList = StopList.replace('\n', '', regex=True)
    TestData = pd.Series(open("testdata.txt"))
    TestData = TestData.replace('\n', '', regex=True)
    TestLabels = pd.Series(open("testlabels.txt"))
    TestLabels = TestLabels.replace('\n', '', regex=True)
    Output = open("output.txt", "a")

    for entry in StopList:
        if entry.isalpha() and len(entry) == 1:
            StopListDict[entry] = []
            key = entry
            StopListDict[key].append(entry)
        else:
            StopListDict[key].append(entry)

    i = 1
    for line in TrainData:
        TrainingDict[i] = {}
        line = line.split()
        for word in line:
            if not StopListDict[word[0]].__contains__(word):
                if not vocabulary.__contains__(word):
                    vocabulary.append(word)
                TrainingDict[i][word] = 1
        i = i + 1

    vocabulary.sort()

    i = 1
    for line in TestData:
        TestingDict[i] = {}
        line = line.split()
        for word in line:
            if not StopListDict[word[0]].__contains__(word) and vocabulary.__contains__(word):
                TestingDict[i][word] = 1
        i = i + 1

    TrainingDF = pd.DataFrame(TrainingDict, index=vocabulary)
    TrainingDF = TrainingDF.fillna(0)

    TestingDF = pd.DataFrame(TestingDict, index=vocabulary)
    TestingDF = TestingDF.fillna(0)

    T = 20
    x = 1
    y = 1
    z = 1
    n = 1
    w = (pd.Series(index=vocabulary)).fillna(0)
    w2 = (pd.Series(index=vocabulary)).fillna(0)
    w_avg = (pd.Series(index=vocabulary)).fillna(0)
    w_total = (pd.Series(index=vocabulary)).fillna(0)


    while x <= T:
        while y <= 322:
            guess = np.sign(np.inner(TrainingDF[y], w))
            guess_avg = np.sign(np.inner(TrainingDF[y], w_avg))
            if (int(TrainLabels[y-1])*2 - 1) != guess:
                w = w + n * (int(TrainLabels[y-1]) * 2 - 1) * TrainingDF[y]
                if TrainingMistakes.__contains__(x):
                    TrainingMistakes[x] = TrainingMistakes[x] + 1
                else:
                    TrainingMistakes[x] = 1
            if (int(TrainLabels[y-1])*2 - 1) != guess_avg:
                w2 = w2 + n * (int(TrainLabels[y-1]) * 2 - 1) * TrainingDF[y]
                w_total = w_total + w2
                if TrainingMistakes_avg.__contains__(x):
                    TrainingMistakes_avg[x] = TrainingMistakes_avg[x] + 1
                    w_avg = w_total.divide(TrainingMistakes_avg[x])
                else:
                    TrainingMistakes_avg[x] = 1
            y = y + 1
        while z <= 101:
            guess = np.sign(np.inner(TestingDF[z], w))
            guess_avg = np.sign(np.inner(TrainingDF[z], w_avg))
            if (int(TestLabels[z-1])*2 - 1) != guess:
                if TestingMistakes.__contains__(x):
                    TestingMistakes[x] = TestingMistakes[x] + 1
                else:
                    TestingMistakes[x] = 1
            if (int(TestLabels[z-1])*2 - 1) != guess_avg:
                if TestingMistakes_avg.__contains__(x):
                    TestingMistakes_avg[x] = TestingMistakes_avg[x] + 1
                else:
                    TestingMistakes_avg[x] = 1
            z = z + 1
        TrainingAccuracy[x] = (322 - TrainingMistakes[x]) / 322
        TestingAccuracy[x] = (101 - TestingMistakes[x]) / 101
        TrainingAccuracy_avg[x] = (322 - TrainingMistakes_avg[x]) / 322
        TestingAccuracy_avg[x] = (101 - TestingMistakes_avg[x]) / 101
        y = 1
        z = 1
        x = x + 1

    x = 1
    Output.write("ALGORITHM 1\n")
    Output.write("A)\n")
    Output.write("Iteration, Mistakes\n")
    while x <= T:
        Output.write("%d : %d\n" % (x, TrainingMistakes[x]))
        x = x+1

    Output.write("B)\n")
    Output.write("Iteration, Training Accuracy, Testing Accuracy\n")
    x = 1
    while x <= T:
        Output.write("%d : %f , %f\n" % (x, TrainingAccuracy[x], TestingAccuracy[x]))
        x = x+1

    Output.write("C)\n")
    Output.write("Standard Perceptron\n")
    Output.write("Iteration, Training Accuracy, Testing Accuracy\n")
    Output.write("%d : %f , %f\n" % (20, TrainingAccuracy[20], TestingAccuracy[20]))
    Output.write("\nAverage Perceptron\n")
    Output.write("Iteration, Training Accuracy, Testing Accuracy\n")
    Output.write("%d : %f , %f\n" % (20, TrainingAccuracy_avg[20], TestingAccuracy_avg[20]))


def part2():
    headers = ['number', 'data', 'label', '-']
    weights = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    TrainingMistakes = {}
    TestingMistakes = {}
    TrainingAccuracy = {}
    TestingAccuracy = {}
    TrainingMistakes_avg = {}
    TestingMistakes_avg = {}
    TrainingAccuracy_avg = {}
    TestingAccuracy_avg = {}
    T = 20
    n = 1
    i = 1

    Output = open("output.txt", "a")
    train = pd.read_csv("ocr_train.txt", sep="\t", names=headers).dropna()
    OcrTrainDF = pd.DataFrame(train).replace('im', '', regex=True)
    OcrTrainDF['data'] = OcrTrainDF['data'].apply(lambda x: list(map(int, x)))

    test = pd.read_csv("ocr_test.txt", sep="\t", names=headers).dropna()
    OcrTestDF = pd.DataFrame(test).replace('im', '', regex=True)
    OcrTestDF['data'] = OcrTestDF['data'].apply(lambda x: list(map(int, x)))

    WeightsDF = pd.DataFrame(index=range(0, 128), columns=weights).fillna(0)
    WeightsDF2 = pd.DataFrame(index=range(0, 128), columns=weights).fillna(0)
    WeightsDF_avg = pd.DataFrame(index=range(0, 128), columns=weights).fillna(0)
    WeightsDF_total = pd.DataFrame(index=range(0, 128), columns=weights).fillna(0)

    while i <= T:
        for index, row in OcrTrainDF.iterrows():
            GuessDF = np.inner(WeightsDF.transpose(), row['data'])
            GuessDF_avg = np.inner(WeightsDF_avg.transpose(), row['data'])
            guess = weights[int(np.argmax(GuessDF))]
            guess_avg = weights[int(np.argmax(GuessDF_avg))]
            if guess != row['label']:
                WeightsDF[row['label']] = WeightsDF[row['label']] + n * row['data']
                WeightsDF[guess] = WeightsDF[guess] - n * row['data']
                if TrainingMistakes.__contains__(i):
                    TrainingMistakes[i] = TrainingMistakes[i] + 1
                else:
                    TrainingMistakes[i] = 1
            if guess_avg != row['label']:
                WeightsDF2[row['label']] = WeightsDF2[row['label']] + n * row['data']
                WeightsDF2[guess_avg] = WeightsDF2[guess_avg] - n * row['data']
                WeightsDF_total[row['label']] = WeightsDF_total[row['label']] + WeightsDF2[row['label']]
                WeightsDF_total[guess_avg] = WeightsDF_total[guess_avg] + WeightsDF2[guess_avg]
                if TrainingMistakes_avg.__contains__(i):
                    TrainingMistakes_avg[i] = TrainingMistakes_avg[i] + 1
                    WeightsDF_avg = WeightsDF_total.divide(TrainingMistakes_avg[i])
                else:
                    TrainingMistakes_avg[i] = 1

        for index, row in OcrTestDF.iterrows():
            GuessDF = np.inner(WeightsDF.transpose(), row['data'])
            GuessDF_avg = np.inner(WeightsDF_avg.transpose(), row['data'])
            guess = weights[int(np.argmax(GuessDF))]
            guess_avg = weights[int(np.argmax(GuessDF_avg))]
            if guess != row['label']:
                if TestingMistakes.__contains__(i):
                    TestingMistakes[i] = TestingMistakes[i] + 1
                else:
                    TestingMistakes[i] = 1
            if guess_avg != row['label']:
                if TestingMistakes_avg.__contains__(i):
                    TestingMistakes_avg[i] = TestingMistakes_avg[i] + 1
                else:
                    TestingMistakes_avg[i] = 1
        TrainingAccuracy[i] = (len(OcrTrainDF.index) - TrainingMistakes[i]) / len(OcrTrainDF.index)
        TestingAccuracy[i] = (len(OcrTestDF.index) - TestingMistakes[i]) / len(OcrTestDF.index)
        TrainingAccuracy_avg[i] = (len(OcrTrainDF.index) - TrainingMistakes_avg[i]) / len(OcrTrainDF.index)
        TestingAccuracy_avg[i] = (len(OcrTestDF.index) - TestingMistakes_avg[i]) / len(OcrTestDF.index)
        print(i)
        i = i + 1

    print(TrainingAccuracy)
    print(TestingAccuracy)

    i = 1
    Output.write("\n\nALGORITHM 2\n")
    Output.write("A)\n")
    Output.write("Iteration, Mistakes\n")
    while i <= T:
        Output.write("%d : %d\n" % (i, TrainingMistakes[i]))
        i = i+1

    Output.write("B)\n")
    Output.write("Iteration, Training Accuracy, Testing Accuracy\n")
    i = 1
    while i <= T:
        Output.write("%d : %f , %f\n" % (i, TrainingAccuracy[i], TestingAccuracy[i]))
        i = i+1

    Output.write("C)\n")
    Output.write("Standard Perceptron\n")
    Output.write("Iteration, Training Accuracy, Testing Accuracy\n")
    Output.write("%d : %f , %f\n" % (20, TrainingAccuracy[20], TestingAccuracy[20]))
    Output.write("\nAverage Perceptron\n")
    Output.write("Iteration, Training Accuracy, Testing Accuracy\n")
    Output.write("%d : %f , %f\n" % (20, TrainingAccuracy_avg[20], TestingAccuracy_avg[20]))


def main():
    part1()
    part2()


if __name__ == "__main__":
    main()
