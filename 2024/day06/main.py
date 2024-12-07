from functools import reduce


def inBounds(i, j):
    return all(0 <= x < n for x in [i, j])

def openSpot(i, j):
    return not inBounds(i, j) or matrix[i][j] != "#"

def getStart():
    return [(i, j) for i, row in enumerate(matrix) for j, val in enumerate(row) if val == "^"][0]

def update(i, j, currDir, iDiff, jDiff, newDir):
    return (i + iDiff, j + jDiff, currDir, True) if openSpot(i + iDiff, j + jDiff) else (i, j, newDir, False)

def traverse(i, j):
    visited = [[False] * n for _ in range(n)]
    direction = "U"
    seen = set()
    while inBounds(i, j):
        if (i, j, direction) in seen:
            return visited, True

        seen.add((i, j, direction))
        visited[i][j] = True
        halt = False
        while not halt:
            i, j, direction, halt = update(i, j, direction, *updateParams[direction])
 
    return visited, False

def checkForLoop(args, coords):
    x, y, i, j = *coords, *args[1:]

    if x == i and y == j:
        return args

    old = matrix[x][y]
    matrix[x][y] = "#"
    found = traverse(i, j)[1]
    matrix[x][y] = old

    return (args[0] + 1, *args[1:]) if found else args

def problem1(i, j):
    return traverse(i, j)[0]

def problem2(visitedLocations, i, j):
    return reduce(checkForLoop, visitedLocations, (0, i, j))[0]

matrix = [list(line) for line in open("input.txt")]
n = len(matrix)
i, j = getStart()
updateParams = {"U": (-1, 0, "R"), "R": (0, 1, "D"), "D": (1, 0, "L"), "L": (0, -1, "U")}

visited = problem1(i, j)
print(sum(sum(line) for line in visited))
print(problem2([(x, y) for x, row in enumerate(visited) for y, val in enumerate(row) if val], i, j))