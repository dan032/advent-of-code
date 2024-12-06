from collections import defaultdict
from itertools import permutations
from functools import reduce


def calculateHappiness(args, i):
    return args[0] + args[2][(args[1][i], args[1][(i + 1) % len(args[1])])] + args[2][(args[1][i], args[1][i - 1])], *args[1:]

def problem(addMe):
    graph = defaultdict(int)
    people = set()
    for line in open("input.txt", "r"):
        words = line.split(" ")
        graph[(words[0], words[-1][:-2])] = (1 if words[2] == "gain" else -1 * int(words[3]))
        people.add(words[0])
        people.add(words[-1][:-2])

    if addMe:
        for person in people:
            graph[("ME", person)] = 0
            graph[(person, "ME")] = 0

        people.add("ME")

    return max(map(lambda perm: reduce(calculateHappiness, range(len(perm)), (0, perm, graph))[0], permutations(people)))

print(problem(False))
print(problem(True))

