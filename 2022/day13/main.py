import ast
from functools import cmp_to_key, reduce


def array_compare(v1, v2):
    i = 0
    j = 0
    while i < len(v1) and j < len(v2):
        res = compare(v1[i], v2[i])
        i += 1
        j += 1
        if res != 0:
            return res

    if i == len(v1) and j == len(v2):
        return 0
    if i == len(v1):
        return - 1
    if j == len(v2):
        return 1

# 0 - neutral, -1 is left, 1 is right
def compare(v1, v2):
    if isinstance(v1, int) and isinstance(v2, int):
       if v1 == v2:
           return 0
       return -1 if v1 < v2 else 1
   
    if isinstance(v1, list) and isinstance(v2, list):
        return array_compare(v1, v2)
    
    if isinstance(v1, list):
        return array_compare(v1, [v2])
    
    return array_compare([v1], v2)

def sumIndexes(res, args):
    return res + args[0] + 1 if compare(args[1][0], args[1][1]) == -1 else res

def problem1():
    return reduce(sumIndexes, enumerate(pairs), 0)

def problem2():
    flattenedPackets = [packet for pair in pairs for packet in pair]
    sortedPackets = sorted(flattenedPackets + [[6], [2]], key=cmp_to_key(compare))

    return (sortedPackets.index([2]) + 1) * (sortedPackets.index([6]) + 1)

lines = [line.strip() for line in open("input.txt", "r")]
pairs = list([ast.literal_eval(lines[i]), ast.literal_eval(lines[i + 1])] for i in range(0, len(lines), 3))

print(problem1())
print(problem2())
