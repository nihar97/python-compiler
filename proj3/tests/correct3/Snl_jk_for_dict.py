myDict:: dict of [str, int] = {
    "apple": 1,
    "orange": 2,
    "banana": 3
}

myList:: list of str = [
    "apple",
    "apple",
    "orange",
    "banana",
    "orange"
]

c = 0
sum = 0

for fruit in myList:
    c = c + 1
    sum = sum + myDict[fruit] * c

print sum #expect (1*1) + (1*2) + (2*3) + (3*4) + (2*5) = 31
