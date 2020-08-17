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


def define(name, value):
    if dictstack == []:
        dictstack.append({name: value})
        return
    dictstack[-1][name] = value
    return


def lookup(name):
    name = "/" + name
    for dictionary in reversed(dictstack):
        for entry in dictionary:
            if entry == name:
                return dictionary[entry]
    return False


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


def stack():
    for x in reversed(opstack):
        print(x)
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


def psIf():
    op1 = opPop()
    op2 = opPop()
    if isinstance(op1, list) and isinstance(op2, bool):
        if op2:
            interpretSPS(op1)
    else:
        print("ERROR: operands must be a list and a bool")
        opPush(op2)
        opPush(op1)


def psIfelse():
    op1 = opPop()
    op2 = opPop()
    op3 = opPop()
    if isinstance(op1, list) and isinstance(op2, list) and isinstance(op3, bool):
        if op3:
            interpretSPS(op2)
        else:
            interpretSPS(op1)
    else:
        print("ERROR: operands must be a list, list, and bool")
        opPush(op3)
        opPush(op2)
        opPush(op1)


def psFor():
    block = opPop()
    f = opPop()
    i = opPop()
    initial = opPop()
    if isinstance(block, list) and isinstance(f, int) and isinstance(i, int) and isinstance(initial, int):
        while not initial == f:
            opPush(initial)
            interpretSPS(block)
            initial = initial + i
        opPush(initial)
        interpretSPS(block)
        initial = initial + i
    else:
        print("ERROR: operands must be list, int, int, and int")
        opPush(initial)
        opPush(i)
        opPush(f)
        opPush(block)

def forAll():
    op1 = opPop()
    op2 = opPop()
    if isinstance(op1, list) and isinstance(op2, list):
        for v in op2:
            opPush(v)
            interpretSPS(op1)
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


def interpretSPS(code):
    it = iter(code)
    for x in it:
        if isinstance(x, (int, bool, list)):
            opPush(x)
        elif lookup(x):
            value = lookup(x)
            if isinstance(value, list):
                interpretSPS(value)
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
            stack()
        elif x == 'begin':
            begin()
        elif x == 'end':
            end()
        elif x == 'dict':
            psDict()
        elif x == 'def':
            psDef()
        elif x == 'forall':
            forAll()
        elif x == 'for':
            psFor()
        elif x == 'ifelse':
            psIfelse()
        elif x == 'if':
            psIf()
        else:
            opPush(x)
    return

def interpreter(s):
    interpretSPS(parse(tokenize(s)))


# ----------------------------------- Testing -----------------------------------------------------

input1 = """
  /square {dup mul} def  
  [1 2 3 4] {square} forall 
  add add add 30 eq true 
  stack
"""


input2 = """ 
  [1 2 3 4 5] dup length /n exch def
  /fact {
      0 dict begin
         /n exch def
         n 2 lt
         { 1}
         {n 1 sub fact n mul }
         ifelse
      end 
  } def
  n fact stack    
"""


input3 = """
  [9 9 8 4 10] {dup 5 lt {pop} if} forall 
  stack 
"""

input4 = """
  [1 2 3 4 5] dup length exch {dup mul}  forall
  add add add add
  exch 0 exch -1 1 {dup mul add} for
  eq stack 
"""

input5 = """
  /y 3 def
  /f { /z y def 1 dict
        begin
        /z 4 def
        /y 5 def
        z y mul
        end
      } def
  f y mul
  stack
"""

input6 = """
  /x 4 def
  x 3 eq
    {x 1 add /result exch def}
    {x 4 eq
    {x 2 add /result exch def}
    {x 3 add /result exch def}
    ifelse }
  ifelse
result
stack
"""


def interpreterTest1():
    clear()
    dictstack = []
    ans = [True, True]
    interpreter(input1)
    print("\n")
    if opstack == ans:
        return True
    else:
        return False


def interpreterTest2():
    clear()
    dictstack = []
    ans = [[1, 2, 3, 4, 5], 120]
    interpreter(input2)
    print("\n")
    if opstack == ans:
        return True
    else:
        return False


def interpreterTest3():
    clear()
    dictstack = []
    ans = [9, 9, 8, 10]
    interpreter(input3)
    print("\n")
    if opstack == ans:
        return True
    else:
        return False


def interpreterTest4():
    clear()
    dictstack = []
    ans = [True]
    interpreter(input4)
    print("\n")
    if opstack == ans:
        return True
    else:
        return False


def interpreterTest5():
    clear()
    dictstack = []
    ans = [60]
    interpreter(input5)
    print("\n")
    if opstack == ans:
        return True
    else:
        return False


def interpreterTest6():
    clear()
    dictstack = []
    ans = [6]
    interpreter(input6)
    print("\n")
    if opstack == ans:
        return True
    else:
        return False


def main_part2():

    testCases = [('Test1', interpreterTest1), ('Test2', interpreterTest2), ('Test3', interpreterTest3),
                 ('Test4', interpreterTest4), ('Test5', interpreterTest5), ('Test6', interpreterTest6)]

    failedTests = [testName for (testName, testProc) in testCases if not testProc()]

    if failedTests:
        return ('Some tests failed', failedTests)
    else:
        return ('All Tests Passed')


if __name__ == '__main__':
    print(main_part2())
