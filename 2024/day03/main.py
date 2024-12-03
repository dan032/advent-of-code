import re
import math


def performOperation(op, enable, result):
    if "d" in op:
        enable =  op == "do()"
    if "mul" in op and enable:
        result += math.prod(map(int, re.findall(r"\d+", op)))
    return (result, enable)

def problem(regex):
    answer = 0
    enable = True

    for operation in re.findall(regex, "".join(line for line in open("input.txt", "r"))):
        answer, enable = performOperation(operation, enable, answer)
    return answer

print(problem(r"mul\(\d+,\d+\)"))
print(problem(r"don't\(\)|mul\(\d+,\d+\)|do\(\)"))
