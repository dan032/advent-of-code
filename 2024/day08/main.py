from collections import defaultdict
from itertools import permutations


def populateAntiNodes1(start, p, antinodes):
    i = 2 * start[0] - p[0]
    j = 2 * start[1] - p[1]

    if i < 0 or i >= len(matrix) or j < 0 or j >= len(matrix[0]):
        return
    
    antinodes.add((i, j))

def populateAntiNodes2(start, p, antinodes):
    i = start[0]
    j = start[1]

    while i >= 0 and i < len(matrix) and j >= 0 and j < len(matrix[0]):
        antinodes.add((i, j))
        i += start[0] - p[0]
        j += start[1] - p[1]

def problem(populateAntiNodes):
    antinodes = set()
    for v in locs.values():
        for pair in list(permutations(v)):
            for p in pair[1:]:
                populateAntiNodes(pair[0], p, antinodes)
    return len(antinodes)

matrix = [list(line.strip()) for line in open("input.txt", "r")]
locs = defaultdict(list)

for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        if matrix[i][j] == ".":
            continue

        locs[matrix[i][j]].append((i, j))

print(problem(populateAntiNodes1))
print(problem(populateAntiNodes2))