from itertools import combinations

IN_FILE = "../data/browsingdata.txt"
OUT_FILE = "../output.txt"


def count_singles(file):
    item_count = {}
    for basket in file:
        item_list = basket.split(' ')
        for item in item_list:
            if not item == '' and not item =='\n':
                if item_count.__contains__(item):
                    item_count[item] = item_count[item] + 1
                else:
                    item_count[item] = 1
    return item_count


def count_pairs(possiblePairs, file):
    pairs_count = {}
    for basket in file:
        item_list = basket.split(' ')
        pairs = combinations(item_list, 2)
        for i in list(pairs):
            if possiblePairs.__contains__(i):
                if pairs_count.__contains__(i):
                    pairs_count[i] = pairs_count[i] + 1
                else:
                    pairs_count[i] = 1
    return pairs_count


def count_triples(possibleTriples, file):
    triples_count = {}
    for basket in file:
        item_list = basket.split(' ')
        triples = combinations(item_list, 3)
        for i in list(triples):
            if possibleTriples.__contains__(i):
                if triples_count.__contains__(i):
                    triples_count[i] = triples_count[i] + 1
                else:
                    triples_count[i] = 1
    return triples_count


def possible_pairs(frequent_singles):
    pairs = {}
    c = combinations(frequent_singles, 2)
    for entry in list(c):
        if not pairs.__contains__(entry):
            pairs[entry] = 1
    return pairs


def possible_triples(frequent_doubles):
    single_items = {}
    triples = {}
    for double in frequent_doubles:
        for item in double:
            if not single_items.__contains__(item):
                single_items[item] = 1
    t = combinations(single_items, 3)
    for entry in list(t):
        if not triples.__contains__(entry):
            triples[entry] = 1
    return triples


def confidence_doubles(singlesCount, pairsCount):
    all_confidence_doubles = {}
    for item in pairsCount:
        all_confidence_doubles[item[0], item[1]] = pairsCount[item] / singlesCount[item[0]]
        all_confidence_doubles[item[1], item[0]] = pairsCount[item] / singlesCount[item[1]]
    return all_confidence_doubles


def confidence_triples(doublesCount, triplesCount):
    all_confidence_triples = {}
    for item in triplesCount:
        if doublesCount.__contains__((item[1], item[2])) and doublesCount.__contains__((item[0], item[1]))\
                and doublesCount.__contains__((item[0], item[2])):
            all_confidence_triples[(item[0], item[1]), item[2]] = triplesCount[item] / doublesCount[item[0], item[1]]
            all_confidence_triples[(item[0], item[2]), item[1]] = triplesCount[item] / doublesCount[item[0], item[2]]
            all_confidence_triples[(item[1], item[2]), item[0]] = triplesCount[item] / doublesCount[item[1], item[2]]
    return all_confidence_triples


def get_max_doubles(all_confidence_doubles):
    i = 1
    top5 = {}
    while i < 6:
        key_max = max(all_confidence_doubles.keys(), key=(lambda k: all_confidence_doubles[k]))
        top5[key_max] = all_confidence_doubles[key_max]
        all_confidence_doubles.pop(key_max)
        i = i + 1
    return top5


def get_max_triples(all_confidence_triples):
    i = 1
    top5 = {}
    while i < 6:
        key_max = max(all_confidence_triples.keys(), key=(lambda k: all_confidence_triples[k]))
        top5[key_max] = all_confidence_triples[key_max]
        all_confidence_triples.pop(key_max)
        i = i + 1
    return top5


def threshold_check(items):
    frequent_items = {}
    for item in items:
        if items[item] >= 100:
            frequent_items[item] = items[item]
    return frequent_items


def print_items(dictionary, label):
    i = 1
    print(label)
    for item in dictionary:
        print(i, "  ", item, "  ", dictionary[item])
        i = i + 1
    print("\n")


def dump_output(outfile, topDoubles, topTriples):
    outfile.write("OUTPUT A\n")
    for i in topDoubles:
        outfile.write(i[0])
        outfile.write(" ")
        outfile.write(i[1])
        outfile.write(" ")
        outfile.write(str(topDoubles[i]))
        outfile.write("\n")
    outfile.write("\nOUTPUT B\n")
    for i in topTriples:
        outfile.write(i[0][0])
        outfile.write(" ")
        outfile.write(i[0][1])
        outfile.write(" ")
        outfile.write(i[1])
        outfile.write(" ")
        outfile.write(str(topTriples[i]))
        outfile.write("\n")



def main():
    # find frequent single items
    file = open(IN_FILE, "r")
    itemCount = count_singles(file)
    frequentSingleItems = threshold_check(itemCount)

    # find frequent pairs
    file = open(IN_FILE, "r")
    possiblePairs = possible_pairs(frequentSingleItems)
    pairsCount = count_pairs(possiblePairs, file)
    frequentPairs = threshold_check(pairsCount)

    # find frequent triples
    file = open(IN_FILE, "r")
    possibleTriples = possible_triples(frequentPairs)
    triplesCount = count_triples(possibleTriples, file)
    frequentTriples = threshold_check(triplesCount)

    # top 5 confidence for doubles
    topDoubles = get_max_doubles(confidence_doubles(itemCount, pairsCount))
    # top 5 confidence for triples
    topTriples = get_max_triples(confidence_triples(pairsCount, triplesCount))

    # open/write to outfile
    outfile = open(OUT_FILE, "w")
    dump_output(outfile, topDoubles, topTriples)


if __name__ == '__main__':
    main()
