import re

# global variables
opstack = []  # assuming top of the stack is the end of the list
dictstack = []  # assuming top of the stack is the end of the list


def checkType(value1, value2):
    if not isinstance(value1, (int, float)) or not isinstance(value2, (int, float)):
        print("ERROR: Operators must be same type")
        opPush(value2)
        opPush(value1)
        return False
    if isinstance(value1, str) or isinstance(value2, str):
        print("ERROR: Operators must be of comparable types")
        opPush(value2)
        opPush(value1)
        return False
    return True


def opPop():
    if opstack == []:
        print("ERROR: OpStack is empty")
        return
    value = opstack[-1]
    del opstack[-1]
    return value


def opPush(value):
    opstack.append(value)
    return


def dictPop():
    if dictstack == []:
        print("ERROR: DictStack is empty")
        return
    dictionary = dictstack[-1]
    del dictstack[-1]
    return dictionary


def dictPush():
    dictstack.append({})
    return


def dictPushStatic(index):
    dictstack.append(({}, index))
    return


def define(name, value):
    if dictstack == []:
        dictstack.append(({name: value}, 0))
        return
    dictstack[-1][0][name] = value
    return


def lookup(name):
    name = "/" + name
    for t in reversed(dictstack):
        for entry in t[0]:
            if entry == name:
                return t[0][entry]
    return False


def lookupStaticHelper(name, index):
    t = dictstack[index]
    for x in t[0]:
        if x == name:
            return t[0][x]
    if t[1] == index:
        print("ERROR: variable not found")
        return None
    return lookupStaticHelper(name, t[1])


def lookupStatic(name):
    name = "/" + name
    return lookupStaticHelper(name, -1)


def getIndexHelper(name, index):
    t = dictstack[index]
    for x in t[0]:
        if x == name:
            if index == -1:
                return len(dictstack) - 1
            else:
                return index
    if t[1] == index:
        print("ERROR: variable not found")
        return None
    return getIndexHelper(name, t[1])


def getIndex(name):
    name = "/" + name
    return getIndexHelper(name, -1)


def add():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not checkType(op1, op2):
        return
    opPush(op1+op2)
    return op1 + op2


def sub():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not checkType(op1, op2):
        return
    opPush(op2-op1)
    return op2 - op1


def mul():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not checkType(op1, op2):
        return
    opPush(op1*op2)
    return op1 * op2


def div():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not checkType(op1, op2):
        return
    opPush(op2/op1)
    return op2 / op1


def eq():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not op1 == op2:
        opPush(False)
        return False
    opPush(True)
    return True


def lt():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not op1 > op2:
        opPush(False)
        return False
    opPush(True)
    return True


def gt():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not op1 < op2:
        opPush(False)
        return False
    opPush(True)
    return True


def length():
    array = opPop()
    if not isinstance(array, list):
        print("ERROR: Element not an array")
        opPush(array)
        return
    opPush(len(array))
    return len(array)


def get():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    index = opPop()
    array = opPop()
    if not isinstance(index, int) or not isinstance(array, list):
        print("ERROR: Operators must be of type int and array")
        opPush(array)
        opPush(index)
        return
    if array == []:
        print("ERROR: Array is empty")
        opPush(array)
        opPush(index)
        return
    if index >= len(array) or index < 0:
        print("ERROR: Index out of range")
        opPush(array)
        opPush(index)
        return
    opPush(array[index])
    return array[index]


def psAnd():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not isinstance(op1, bool) or not isinstance(op2, bool):
        print("ERROR: Operators must be boolean type")
        opPush(op2)
        opPush(op1)
        return
    opPush(op1 and op2)
    return (op1 and op2)


def psOr():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    op2 = opPop()
    if not isinstance(op1, bool) or not isinstance(op2, bool):
        print("ERROR: Operators must be boolean type")
        opPush(op2)
        opPush(op1)
        return
    opPush(op1 or op2)
    return op1 or op2


def psNot():
    if len(opstack) < 1:
        print("ERROR: Not enough operands")
        return
    op1 = opPop()
    if not isinstance(op1, bool):
        print("ERROR: Operator must be boolean type")
        opPush(op1)
        return
    opPush(not op1)
    return not op1


def dup():
    if opstack == []:
        print("ERROR: Stack is empty")
        return
    op1 = opPop()
    opPush(op1)
    opPush(op1)
    return


def exch():
    if len(opstack) < 2:
        print("ERROR: Not enough operands")
        return
    if opstack == []:
        print("ERROR: Stack is empty")
        return
    op1 = opPop()
    op2 = opPop()
    opPush(op1)
    opPush(op2)
    return


def pop():
    opPop()
    return


def copy():
    temp = []
    i = 0
    j = 0
    if opstack == []:
        print("ERROR: Stack is empty")
        return
    num = opPop()
    if num > len(opstack) or num < 0:
        print("ERROR: Not enough elements in stack")
        opPush(num)
        return
    while i < num:
        temp.append(opPop())
        i = i + 1
    while j < 2:
        for x in reversed(temp):
            opPush(x)
        j = j + 1
    return


def clear():
    for x in reversed(opstack):
        opPop()
    return


def clearDict():
    for x in reversed(dictstack):
        dictPop()
    return


def clearAll():
    clearDict()
    clear()
    return


def stack(scope):
    index = len(dictstack) - 1
    if scope == 'dynamic':
        print("Dynamic")
    if scope == 'static':
        print("Static")
    print("==============")
    for x in reversed(opstack):
        print(x)
    print("==============")
    for t in reversed(dictstack):
        print("----", index, "----", t[1], "----")
        for entry in t[0]:
            print(entry, t[0][entry])
        index = index - 1
    print("==============", "\n")
    return


def psDict():
    opPop()
    opPush({})
    return


def begin():
    d = opPop()
    if not isinstance(d, dict):
        print("ERROR: Argument is not a dictionary")
        opPush(d)
        return
    dictPush()
    return


def end():
    dictPop()
    return


def psDef():
    v = opPop()
    n = opPop()
    define(n, v)
    return


def psIf(scope):
    op1 = opPop()
    op2 = opPop()
    if isinstance(op1, list) and isinstance(op2, bool):
        if op2:
            interpretSPS(op1, scope)
    else:
        print("ERROR: operands must be a list and a bool")
        opPush(op2)
        opPush(op1)


def psIfelse(scope):
    op1 = opPop()
    op2 = opPop()
    op3 = opPop()
    if isinstance(op1, list) and isinstance(op2, list) and isinstance(op3, bool):
        if op3:
            interpretSPS(op2, scope)
        else:
            interpretSPS(op1, scope)
    else:
        print("ERROR: operands must be a list, list, and bool")
        opPush(op3)
        opPush(op2)
        opPush(op1)


def psFor(scope):
    block = opPop()
    f = opPop()
    i = opPop()
    initial = opPop()
    if isinstance(block, list) and isinstance(f, int) and isinstance(i, int) and isinstance(initial, int):
        while not initial == f:
            opPush(initial)
            interpretSPS(block, scope)
            initial = initial + i
        opPush(initial)
        interpretSPS(block, scope)
        initial = initial + i
    else:
        print("ERROR: operands must be list, int, int, and int")
        opPush(initial)
        opPush(i)
        opPush(f)
        opPush(block)


def forAll(scope):
    op1 = opPop()
    op2 = opPop()
    if isinstance(op1, list) and isinstance(op2, list):
        for v in op2:
            opPush(v)
            interpretSPS(op1, scope)
        return
    else:
        print("ERROR: operands must be a list and a function")
        opPush(op2)
        opPush(op1)


# -------------------------------- PART 2 ------------------------------------------------------


def tokenize(s):
    return re.findall("/?[a-zA-Z][a-zA-Z0-9_]*|[[][a-zA-Z0-9_\s!][a-zA-Z0-9_\s!]*[]]|[-]?[0-9]+|[}{]+|%.*|[^ \t\n]", s)


def groupMatching(it):
    res = []
    for c in it:
        if c == '}':
            return res
        else:
            res.append(groupMatching(it))
    return False


def group(s):
    res = []
    it = iter(s)
    for c in it:
        if c == '}':
            return False
        else:
            res.append(groupMatching(it))
    return res


def groupMatching2(it):
    res = []
    for c in it:
        if c == '}':
            return res
        elif c == '{':
            res.append(groupMatching2(it))
        else:
            if c.isdigit() or c[0] == '-':
                res.append(int(c))
            elif c == 'true' or c == 'True':
                res.append(True)
            elif c == 'false' or c == 'False':
                res.append(False)
            elif c[0] == '[':
                c = c.replace("[", "")
                c = c.replace("]", "")
                temp = c.split(" ")
                temp2 = []
                for x in temp:
                    temp2.append(int(x))
                if not all(isinstance(x, int) for x in temp):
                        print("ERROR: List must contain Integers")
                        return
                res.append(temp)
            else:
                res.append(c)
    return False


def parse(L):
    res = []
    it = iter(L)
    for c in it:
        if c == '}':
            return False
        elif c == '{':
            res.append(groupMatching2(it))
        else:
            if c.isdigit() or c[0] == '-':
                res.append(int(c))
            elif c == 'true' or c == 'True':
                res.append(True)
            elif c == 'false' or c == 'False':
                res.append(False)
            elif c[0] == '[':
                c = c.replace("[", "")
                c = c.replace("]", "")
                temp = c.split(" ")
                temp2 = []
                for x in temp:
                    temp2.append(int(x))
                if not all(isinstance(x, int) for x in temp2):
                        print("ERROR: List must contain Integers")
                        return
                res.append(temp2)
            else:
                res.append(c)
    return res


def interpretSPS(code, scope):
    if not scope == 'dynamic' and not scope == 'static':
        print("ERROR: scope must be either dynamic or static")
        return
    it = iter(code)
    for x in it:
        if isinstance(x, (int, bool, list)):
            opPush(x)
        elif lookup(x):
            if scope == 'dynamic':
                value = lookup(x)
                if isinstance(value, list):
                    dictPushStatic(0)
                    interpretSPS(value, scope)
                    dictPop()
                else:
                    opPush(value)
            elif scope == 'static':
                value = lookupStatic(x)
                if isinstance(value, list):
                    dictPushStatic(getIndex(x))
                    interpretSPS(value, scope)
                    dictPop()
                else:
                    opPush(value)
        elif x == 'add':
            add()
        elif x == 'sub':
            sub()
        elif x == 'mul':
            mul()
        elif x == 'div':
            div()
        elif x == 'eq':
            eq()
        elif x == 'lt':
            lt()
        elif x == 'gt':
            gt()
        elif x == 'length':
            length()
        elif x == 'get':
            get()
        elif x == 'or':
            psOr()
        elif x == 'and':
            psAnd()
        elif x == 'not':
            psNot()
        elif x == 'dup':
            dup()
        elif x == 'exch':
            exch()
        elif x == 'pop':
            pop()
        elif x == 'copy':
            copy()
        elif x == 'clear':
            clear()
        elif x == 'stack':
            stack(scope)
        elif x == 'begin':
            begin()
        elif x == 'end':
            end()
        elif x == 'dict':
            psDict()
        elif x == 'def':
            psDef()
        elif x == 'forall':
            forAll(scope)
        elif x == 'for':
            psFor(scope)
        elif x == 'ifelse':
            psIfelse(scope)
        elif x == 'if':
            psIf(scope)
        else:
            opPush(x)
    return


def interpreter(s, scope):
    interpretSPS(parse(tokenize(s)), scope)


# ----------------------------------- Testing -----------------------------------------------------

input1 = """
/x 4 def
/g { x stack } def
/f { /x 7 def g } def
f
"""


input2 = """ 
/m 50 def
/n 100 def
/egg1 {/m 25 def n} def
/chic {
 /n 1 def
 /egg2 { n } def
 m n
 egg1
 egg2
 stack } def
n
chic   
"""


input3 = """
/x 10 def
/A { x } def
/C { /x 40 def A stack } def
/B { /x 30 def /A { x } def C } def
B
"""


input4 = """
/x 10 def
/D { x } def
/A { /x 50 def D } def
/C { /x 40 def A } def
/B { /x 30 def /A { x } def C } def
B
stack
"""


input5 = """
/x 111 def
/y 333 def
/g { x y stack } def
/f { /x 222 def g } def
f
"""


def main():
    print("------------Interpreter Test 1-------------")
    interpreter(input1, 'static')
    clearAll()
    interpreter(input1, 'dynamic')
    clearAll()
    print("------------Interpreter Test 2-------------")
    interpreter(input2, 'static')
    clearAll()
    interpreter(input2, 'dynamic')
    clearAll()
    print("------------Interpreter Test 3-------------")
    interpreter(input3, 'static')
    clearAll()
    interpreter(input3, 'dynamic')
    clearAll()
    print("------------Interpreter Test 4-------------")
    interpreter(input4, 'static')
    clearAll()
    interpreter(input4, 'dynamic')
    clearAll()
    print("------------Interpreter Test 5-------------")
    interpreter(input5, 'static')
    clearAll()
    interpreter(input5, 'dynamic')
    clearAll()
    return

if __name__ == '__main__':
    main()
