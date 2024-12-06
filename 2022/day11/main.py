import re
from collections import defaultdict
from math import prod


def element_in_list(inputs, el):
    try:
        return inputs.index(el)
    except:
        return -1

def parse_num(x):
    return int(re.findall(r"\d+", x)[0])

def generate_monkeys():
    return list(map(lambda x: [x[0], list(map(int, re.findall(r"\d+", x[1][1]))), x[1][2][17:].split(" "), *list(map(parse_num, x[1][3:]))], enumerate(monkey_inputs)))

def problem(problem1):
    monkeys = generate_monkeys()
    modulo = prod(map(lambda m: m[3], monkeys))
    results = defaultdict(int)
    for _ in range(20 if problem1 else 10000):
        for monkey in monkeys:
            for item in monkey[1]:
                right = item if monkey[2][2] == "old" else int(monkey[2][2])
                res = item + right if monkey[2][1] == "+" else item * right
                res = res // 3 if problem1 else res % modulo

                if res % monkey[3] == 0:
                    monkeys[monkey[4]][1].append(res)
                else:
                    monkeys[monkey[5]][1].append(res)

            results[monkey[0]] += len(monkey[1])
            monkey[1] = []

    return prod(sorted(results.values(), reverse=True)[:2])

inputs = [line.strip() for line in open("input.txt", "r")]
monkey_inputs = []

while element_in_list(inputs, "") != -1:
    idx = inputs.index("")
    monkey_inputs.append(inputs[:idx])
    del inputs[:idx+1]

print(problem(True))
print(problem(False))