from collections import defaultdict
from functools import cmp_to_key


def createPair(update):
    return update, sorted(update, key=cmp_to_key(lambda i1, i2: 1 if i1 in orderings[i2] else -1))

def keepPair(pair, isProblem1):
    return pair[0] == pair[1] and isProblem1 or pair[0] != pair[1] and not isProblem1

def middleElement(pair):
    return pair[1][len(pair[1]) // 2]
 
def problem(isProblem1):
    return sum(map(middleElement, filter(lambda pair: keepPair(pair, isProblem1), map(createPair, updates))))

inp = [line.strip() for line in open("input.txt", "r")]
updates = [list(map(int, update.split(","))) for update in inp[inp.index("") + 1:]]
orderings = defaultdict(list)

for ordering in inp[:inp.index("")]:
    source, dest = map(int, ordering.split("|"))
    orderings[source].append(dest)

print(problem(True))
print(problem(False))
