from itertools import product


def xmasCount(baseLetter, calculateResult):
    return sum(calculateResult(i, j) if arr[i][j] == baseLetter else 0 for i, j in product(range(n), range(n)))

def outOfBounds(i, j, iLimit, jLimit):
    return any(x in [iLimit, jLimit] for x in [i, j])

def search(i, j, currWord, offset):
    if outOfBounds(i, j, -1, n) or len(currWord) == 4:
        return 0
    
    currWord += arr[i][j]
    return 1 if currWord == "XMAS" else search(i + offset[0], j + offset[1], currWord, offset)

def notGoodDiag(i1, j1, i2, j2):
    return any(c not in [arr[i1][j1], arr[i2][j2]] for c in ["M", "S"])

arr = [line for line in open("input.txt", "r")]
n = len(arr)

print(xmasCount("X", lambda i, j: sum(search(i, j, "", [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)][direction]) for direction in range(8))))
print(xmasCount("A", lambda i, j: 0 if outOfBounds(i, j, 0, n - 1) or notGoodDiag(i - 1, j - 1, i + 1, j + 1) or notGoodDiag(i + 1, j - 1, i - 1, j + 1) else 1))
