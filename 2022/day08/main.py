import math
import itertools


def problem1():
    visible = [[False] * n for _ in range(n)]

    def dfs(i, j, currMax, offset):
        if i < 0 or i >= n or j < 0 or j >= n:
            return
        
        if arr[i][j] > currMax:
            visible[i][j] = True
        
        dfs(i + offset[0], j + offset[1], max(arr[i][j], currMax), offset)       

    for i in range(n):
        dfs(n - 1, i, -1, offsets[0])
        dfs(0, i, -1, offsets[1])
        dfs(i, n - 1, -1, offsets[2])
        dfs(i, 0, -1, offsets[3])

    return sum([sum(x) for x in visible])

def problem2():
    def dfs(i, j, val, offset, curr):
        if i < 0 or i >= n or j < 0 or j >= n:
            return curr
        
        return curr + 1 if arr[i][j] >= val else dfs(i + offset[0], j + offset[1], val, offset, curr + 1)
    
    return max(math.prod(dfs(i + offset[0], j + offset[1], arr[i][j], offset, 0) for offset in offsets) for i, j in itertools.product(range(n), range(n)))

arr = [list(map(int, list(line.strip()))) for line in open("input.txt", "r")]
n = len(arr)
offsets = [(-1, 0), (1, 0), (0, -1), (0, 1)]

print(problem1())
print(problem2())