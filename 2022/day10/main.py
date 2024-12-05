from math import prod
from functools import reduce


def problem(result, updateFunc, generateResult):
    return generateResult(reduce(performInstruction, instructions, (0, 1, result, updateFunc))[2])

def generateInstruction(ins):
    return (ins[0], 0, 1) if ins[0] == "noop" else (ins[0], int(ins[1]), 2)

def performInstruction(args, ins):
    return reduce(update, range(ins[2]), (args))[0], args[1] + ins[1] if ins[0] == "addx" else args[1], *args[2:]

def update(args, _):
    args[-1](args[0] + 1, *args[1:3])
    return args[0] + 1, *args[1:4]

def update1(cycles, register, result):
    if cycles in range(20, 221, 40):
        result.append((register, cycles))

def update2(cycles, register, result):
    if cycles % 40 in range(register, register + 3):
        result[(cycles - 1) // 40][(cycles - 1) % 40] = "#"


instructions = list(generateInstruction(line.strip().split(" ")) for line in open("input.txt"))
print(problem([], update1, lambda result: sum(prod(x) for x in result)))
print(problem([["."] * 40 for _ in range(6)], update2, lambda result: "\n".join(map(str, map("".join, result)))))
