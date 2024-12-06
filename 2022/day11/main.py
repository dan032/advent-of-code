import re
from collections import defaultdict
from math import prod


inputs = [line.strip() for line in open("input.txt", "r")]
monkey_inputs = []
monkeys = []

def element_in_list(inputs, el):
    try:
        return inputs.index(el)
    except:
        return -1

while element_in_list(inputs, "") != -1:
    idx = inputs.index("")
    monkey_inputs.append(inputs[:idx])
    del inputs[:idx+1]

# (idx, items, op, test, true res, false res)
i = 0
for mi in monkey_inputs:
    items = list(map(int, re.findall(r"\d+", mi[1])))
    op = mi[2][17:].split(" ")
    test = int(re.findall(r"\d+", mi[3])[0])
    true_result = int(re.findall(r"\d+", mi[4])[0])
    false_result = int(re.findall(r"\d+", mi[5])[0])
    monkeys.append([i, items, op, test, true_result, false_result])
    i += 1


modulo = prod(map(lambda m: m[3], monkeys))
    
def problem(problem1):
    results = defaultdict(int)
    for _ in range(20 if problem1 else 10000):
        for monkey in monkeys:
            count = 0
            for item in monkey[1]:
                count += 1
                right = item if monkey[2][2] == "old" else int(monkey[2][2])
                current = item + right if monkey[2][1] == "+" else item * right
                current = current // 3 if problem1 else current % modulo
                
                if current % monkey[3] == 0:
                    monkeys[monkey[4]][1].append(current)
                else:
                    monkeys[monkey[5]][1].append(current)
            monkey[1] = []
            results[monkey[0]] += count

    return prod(sorted(results.values(), reverse=True)[:2])

print(problem(True))
print(problem(False))
