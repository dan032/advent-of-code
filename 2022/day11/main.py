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

results = defaultdict(int)
modulo = prod(map(lambda m: m[3], monkeys))
    
for _ in range(10000):
    for monkey in monkeys:
        count = 0
        for item in monkey[1]:
            count += 1
            op = monkey[2][1]
            rightOp = monkey[2][2]
            right = item
            left = item
            if rightOp != "old":
                right = int(rightOp)
            res = 0

            if op == "+":
                res = left + right
            else:
                res = left * right
            res %= modulo

            if res % monkey[3] == 0:
                monkeys[monkey[4]][1].append(res)
            else:
                monkeys[monkey[5]][1].append(res)
        monkey[1] = []
        results[monkey[0]] += count

print(prod(sorted(results.values(), reverse=True)[:2]))
