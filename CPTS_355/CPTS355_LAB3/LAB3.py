# CPTS 355 LAB 3
# Brandon Garza

import random


# Problem 1-A

def addDict(d):
    ans = {}
    for c, w in d.items():
        for day, time in w.items():
            ans[day] = ans.get(day, 0) + time
    return ans


# Problem 1-B

def addDictN(L):
    d = {}
    for w in L:
        hours = addDict(w)
        for x, y in hours.items():
            d[x] = d.get(x, 0) + y
    return d


# Problem 2-A

def lookupVal (L, k):
    for x in reversed(L):
        for y in x:
            if y == k:
                return x[y]


# Problem 2-B

def lookupHelper (tL, k, index):
    x = tL[index]
    for y in x[1]:
        if y == k:
            return x[1][y]
    if x[0] == index:
        return None
    return lookupHelper(tL, k, x[0])


def lookupVal2 (tL, k):
    return lookupHelper(tL, k, -1)


# Problem 3

def numPathsHelper (tL, t):
    for x in tL:
        if x == t:
            return True
    return False


def numPaths(m, n, blocks):
    path1 = 0
    path2 = 0
    if m == 1 and n == 1:
        return 1
    if not (numPathsHelper(blocks, (m-1, n))) and m-1 > 0 and n > 0:
        path1 = numPaths(m-1, n, blocks)
    if not (numPathsHelper(blocks, (m, n-1))) and m > 0 and n-1 > 0:
        path2 = numPaths(m, n-1, blocks)
    return path1 + path2


# Problem 4

def palindromes(key):

    table = set()
    length = len(key)
    for index, char in enumerate(key):

        start = (index - 1)
        end = (index + 1)

        while start >= 0 and end < length and key[start] == key[end]:
            table.add(key[start:end+1])
            start = (start - 1)
            end = (end + 1)

        start = index
        end = (index + 1)

        while start >= 0 and end < length and key[start] == key[end]:
            table.add(key[start:end+1])
            start = (start - 1)
            end = (end + 1)

    ans = list(table)
    ans.sort()
    return ans


# Problem 5-A

class iterApply():
    def __init__(self, n, F):
        self.number = n
        self.function = F

    def __next__(self):
        ans = self.function(self.number)
        self.number = (self.number + 1)
        return ans

    def __prev__(self):
        self.number = (self.number - 1)
        ans = self.function(self.number)
        return ans


# Problem 5-B

def iMerge(iNumbers1, iNumbers2, N):
    i = N
    ans = []
    while i > 0:
        if iNumbers1.__next__() <= iNumbers2.__next__():
            iNumbers1.__prev__()
            ans.append(iNumbers1.__next__())
            iNumbers2.__prev__()
        else:
            iNumbers2.__prev__()
            ans.append(iNumbers2.__next__())
            iNumbers1.__prev__()
        i = (i-1)
    ans.sort()
    print(ans)


# Problem 6-A

class Stream(object):
    def __init__(self, first, compute_rest, empty= False):
        self.first = first
        self._compute_rest = compute_rest
        self.empty = empty
        self._rest = None
        self._computed = False
    @property
    def rest(self):
        assert not self.empty, 'Empty streams have no rest.'
        if not self._computed:
            self._rest = self._compute_rest()
            self._computed = True
        return self._rest


empty_stream = Stream(None, None, True)


def streamRandoms (k, min, max):
    def compute_rest():
        return streamRandoms(random.randint(min, max), min, max)
    return Stream(k, compute_rest)


rStream = streamRandoms(1, 1, 100)
myList = []
for i in range(0, 10):
    myList.append(rStream.first)
    rStream = rStream.rest


# Problem 6-B

def oddStream(stream):
    while stream.first % 2 == 0:
        stream = stream.rest

    def compute_rest():
        return oddStream(stream.rest)
    return Stream(stream.first, compute_rest)


oddS = oddStream(streamRandoms(1, 1, 100))
myList = []
for i in range(0, 100):
    myList.append(oddS.first)
    oddS = oddS.rest


# --------------------- TEST CODE --------------------------


def testaddDict():
    d = {'355': {'Mon': 3, 'Wed': 2, 'Sat': 2}, '360': {'Mon': 3, 'Tue': 2, 'Wed': 2, 'Fri': 10},
         '321': {'Tue': 2, 'Wed': 2, 'Thu': 3}, '322': {'Tue': 1, 'Thu': 5, 'Sat': 2}}
    if addDict({}) != {}:
        print("Case 1 function addDict")
        return False
    if dict(sorted(list(addDict(d).items()))) != {'Fri': 10, 'Mon': 6, 'Sat': 4,
                                                  'Thu': 8, 'Tue': 5, 'Wed': 6}:
        print("Case 2 function addDict")
        return False
    return True


def testaddDictN():
    d = [{'355': {'Mon': 3, 'Wed': 2, 'Sat': 2}, '360': {'Mon': 3, 'Tue': 2, 'Wed': 2, 'Fri':
        10}, '321': {'Tue': 2, 'Wed': 2, 'Thu': 3}, '322': {'Tue': 1, 'Thu': 5, 'Sat': 2}},
         {'322': {'Mon': 2}, '360': {'Thu': 2, 'Fri': 5}, '321': {'Mon': 1, 'Sat': 3}},
         {'355': {'Sun': 8}, '360': {'Fri': 5}, '321': {'Mon': 4}, '322': {'Sat': 3}}]

    if addDictN([]) != {}:
        print("Case 1 function addDictN")
        return False
    if (addDictN(d)) != {'Fri': 20, 'Mon': 13, 'Sat': 10, 'Sun': 8, 'Thu': 10, 'Tue': 5, 'Wed': 6}:
        print("Case 2 function addDictN")
        return False
    return True


def testlookupVal():
    L1 = [{"x": 1, "y": True, "z": "found"}, {"x": 2}, {"y": False}]

    if lookupVal(L1,"x") != 2:
        return False
    if lookupVal(L1,"y") != False:
        return False
    if lookupVal(L1, "z") != "found":
        return False
    if lookupVal(L1, "t") != None:
        return False
    return True


def testlookupval2():
    L2 = [(0, {"x": 0, "y": True, "z": "zero"}),
          (0, {"x": 1}),
          (1, {"y": False}),
          (1, {"x": 3, "z": "three"}),
          (2, {})]
    if lookupVal2(L2, "x") != 1:
        return False
    if lookupVal2(L2,"y") != False:
        return False
    if lookupVal2(L2, "z") != "zero":
        return False
    if lookupVal2(L2, "t") != None:
        return False
    return True


def testnumpaths():
    if numPaths(2, 2, [(2, 1)]) != 1:
        return False
    if numPaths(3, 3, [(2, 3)]) != 3:
        return False
    if numPaths(4, 3, [(2, 2)]) != 4:
        return False
    if numPaths(10, 3, [(2, 2), (7, 1)]) != 27:
        return False
    return True


def testpalindromes():
    if palindromes('cabbbaccab') != ['abbba', 'acca', 'baccab', 'bb', 'bbb', 'cabbbac', 'cc']:
        return False
    if palindromes(' bacdcabdbacdc') != ['abdba', 'acdca', 'bacdcab', 'bdb', 'cabdbac', 'cdc', 'cdcabdbacdc',
                                          'dcabdbacd']:
        return False
    if palindromes(' myracecars') != ['aceca', 'cec', 'racecar']:
        return False
    return True


# ################################################## Main program execution ###########################################
if __name__ == '__main__':
    passedMsg = "%s passed"
    failedMsg = "%s failed"

    varaddDict = testaddDict()
    varaddDictN = testaddDictN()
    varlookupVal = testlookupVal()
    varlookupva2 = testlookupval2()
    varnumpaths = testnumpaths()
    varpalindromes = testpalindromes()

    test = {'addDict': varaddDict, 'addDictN': varaddDictN, 'lookupVal': varlookupVal,
            'lookupVal2': varlookupva2, 'numPaths': varnumpaths, 'palindromes': varpalindromes}

    for w in test:
        if test[w]:
            print(passedMsg % w)
        else:
            print(failedMsg % w)


