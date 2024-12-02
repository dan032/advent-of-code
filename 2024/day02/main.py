from itertools import combinations


def isSafeCombination(copy):
    allowedDifferences =  [(1 if copy[0] < copy[1] else -1) * x for x in [1, 2, 3]]
    return all(copy[i] - copy[i - 1] in allowedDifferences for i in range(1, len(copy)))

def isSafeReport(report, generateCombinations):
    return any(isSafeCombination(combination) for combination in combinations(report, len(report) - 1)) if generateCombinations else isSafeCombination(report)

def numberOfSafeReports(generateCombinations):
    return sum(isSafeReport(list(map(int, line.split(" "))), generateCombinations) for line in open("input.txt", "r"))

print(numberOfSafeReports(False))
print(numberOfSafeReports(True))