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
    for dictionary in reversed(dictstack):
        for entry in dictionary:
            if entry == name:
                return dictionary[entry]
    print("ERROR: No ", name, "in dictStack")
    return


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


# ----------------------------- Part 1 TEST CASES -----------------------------------
def testDefine():
    define("/n1", 4)
    if lookup("/n1") != 4:
        return False
    return True


def testLookup():
    opPush("/n1")
    opPush(3)
    psDef()
    if lookup("/n1") != 3:
        return False
    return True


# Arithmatic operator tests
def testAdd():
    opPush(1)
    opPush(2)
    add()
    if opPop() != 3:
        return False
    return True


def testSub():
    opPush(10)
    opPush(4.5)
    sub()
    if opPop() != 5.5:
        return False
    return True


def testMul():
    opPush(2)
    opPush(4.5)
    mul()
    if opPop() != 9:
        return False
    return True


def testDiv():
    opPush(10)
    opPush(4)
    div()
    if opPop() != 2.5:
        return False
    return True


# Comparison operators tests
def testEq():
    opPush(6)
    opPush(6)
    eq()
    if opPop() != True:
        return False
    return True


def testLt():
    opPush(3)
    opPush(6)
    lt()
    if opPop() != True:
        return False
    return True


def testGt():
    opPush(3)
    opPush(6)
    gt()
    if opPop() != False:
        return False
    return True


# boolean operator tests
def testPsAnd():
    opPush(True)
    opPush(False)
    psAnd()
    if opPop() != False:
        return False
    return True


def testPsOr():
    opPush(True)
    opPush(False)
    psOr()
    if opPop() != True:
        return False
    return True


def testPsNot():
    opPush(True)
    psNot()
    if opPop() != False:
        return False
    return True


# Array operator tests
def testLength():
    opPush([1, 2, 3, 4, 5])
    length()
    if opPop() != 5:
        return False
    return True


def testGet():
    opPush([1, 2, 3, 4, 5])
    opPush(4)
    get()
    if opPop() != 5:
        return False
    return True


# stack manipulation functions
def testDup():
    opPush(10)
    dup()
    if opPop() != opPop():
        return False
    return True


def testExch():
    opPush(10)
    opPush("/x")
    exch()
    if opPop() != 10 and opPop() != "/x":
        return False
    return True


def testPop():
    l1 = len(opstack)
    opPush(10)
    pop()
    l2 = len(opstack)
    if l1 != l2:
        return False
    return True


def testCopy():
    opPush(1)
    opPush(2)
    opPush(3)
    opPush(4)
    opPush(5)
    opPush(2)
    copy()
    if opPop() != 5 and opPop() != 4 and opPop() != 5 and opPop() != 4 and opPop() != 3 and opPop() != 2:
        return False
    return True


def testClear():
    opPush(10)
    opPush("/x")
    clear()
    if len(opstack) != 0:
        return False
    return True


# dictionary stack operators
def testDict():
    opPush(1)
    psDict()
    if opPop() != {}:
        return False
    return True


def testBeginEnd():
    opPush("/x")
    opPush(3)
    psDef()
    opPush({})
    begin()
    opPush("/x")
    opPush(4)
    psDef()
    end()
    if lookup("/x") != 3:
        return False
    return True


def testpsDef():
    opPush("/x")
    opPush(10)
    psDef()
    if lookup("/x") != 10:
        return False
    return True


def testpsDef2():
    opPush("/x")
    opPush(10)
    psDef()
    opPush(1)
    psDict()
    begin()
    if lookup("/x") != 10:
        end()
        return False
    end()
    return True


def main_part1():
    testCases = [('define', testDefine), ('lookup', testLookup), ('add', testAdd), ('sub', testSub), ('mul', testMul),
                 ('div', testDiv), \
                 ('eq', testEq), ('lt', testLt), ('gt', testGt), ('psAnd', testPsAnd), ('psOr', testPsOr),
                 ('psNot', testPsNot), \
                 ('length', testLength), ('get', testGet), ('dup', testDup), ('exch', testExch), ('pop', testPop),
                 ('copy', testCopy), \
                 ('clear', testClear), ('dict', testDict), ('begin', testBeginEnd), ('psDef', testpsDef),
                 ('psDef2', testpsDef2)]
    # add you test functions to this list along with suitable names
    failedTests = [testName for (testName, testProc) in testCases if not testProc()]
    if failedTests:
        return ('Some tests failed', failedTests)
    else:
        return ('All part-1 tests OK')


if __name__ == '__main__':
    print(main_part1())