import re
from itertools import product
from functools import reduce


def add(line, curr, i):
    return curr + line[1][i]

def mult(line, curr, i):
    return curr * line[1][i]

def concat(line, curr, i):
    return int(f"{curr}{line[1][i]}")

def calculate(args, i):
    curr, operations, line = args
    return operations[i - 1](line, curr, i), operations, line

def calculations(line, functions):
    return map(lambda ops: reduce(calculate, range(1, len(line[1])), (line[1][0], ops, line))[0], product(functions, repeat=len(line[1]) - 1))

def validCalibration(line, functions):
    return any(result == line[0] for result in calculations(line, functions))

def calibrationResult(*functions):
    return sum(line[0] for line in filter(lambda line: validCalibration(line, functions), lines))


lines = list((nums[0], nums[1:]) for nums in (list(map(int, re.findall(r"\d+", line))) for line in open("input.txt", "r")))
print(calibrationResult(add, mult))
print(calibrationResult(add, mult, concat))