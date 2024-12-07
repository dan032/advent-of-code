import re
from itertools import product

def problem(includeCalories):
    ingredients = []

    for line in open("input.txt", "r"):
        ingredients.append(list(map(int, re.findall("-?\d+", line))))

    if not includeCalories:
        for ingredient in ingredients:
            del ingredient[-1]

    result = 0
    for c in [combo for combo in product(range(100 + 1), repeat=len(ingredients)) if sum(combo) == 100]:
        curr = 1
        for a in range(4):
            s = 0
            for i in range(len(ingredients)):
                s += (c[i] * ingredients[i][a])
            if s < 0:
                s = 0
            curr *= s
        if not includeCalories:
            result = max(result, curr)
            continue
        else:
            cals = 0
            for i in range(len(ingredients)):
                cals += (c[i] * ingredients[i][-1])
            
            if cals == 500:
                result = max(result, curr)
            
    return result

print(problem(False))
print(problem(True))