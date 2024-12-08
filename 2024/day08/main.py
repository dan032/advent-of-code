from collections import defaultdict
from itertools import permutations, chain

def outOfBounds(i, j):
    return i < 0 or i >= len(matrix) or j < 0 or j >= len(matrix[0])

def populateAntiNodes1(i, j, *_):
    return [] if outOfBounds(i, j) else [(i, j)]
    
def populateAntiNodes2(i, j, start, current):
    return [] if outOfBounds(i, j) else populateAntiNodes2(i + start[0] - current[0], j + start[1] - current[1], start, current) + [(i, j)]

def problem(populateAntiNodes, indexMapping):
    antinodes = (populateAntiNodes(*indexMapping(pair[0], current), pair[0], current) for indexes in antennas.values() for pair in list(permutations(indexes)) for current in pair[1:])
    return len(set(chain.from_iterable(antinodes)))

matrix = [list(line.strip()) for line in open("input.txt", "r")]
antennas = defaultdict(list)

for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        if matrix[i][j] != ".":
            antennas[matrix[i][j]].append((i, j))

print(problem(populateAntiNodes1, lambda start, current: (2 * start[0] - current[0], 2 * start[1] - current[1])))
print(problem(populateAntiNodes2, lambda start, _: (start[0], start[1])))
