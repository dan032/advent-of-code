from collections import Counter

def populateLists():
    list1 = []
    list2 = []

    with open("input.txt", "r") as f:
        for line in f:
            nums = line.strip().split(" ")
            list1.append(int(nums[0]))
            list2.append(int(nums[-1]))
    return list1, list2

def problem1():
    return sum(abs(x[0] - x[1]) for x in zip(*list(map(sorted, populateLists()))))

def problem2():
    list1, list2 = populateLists()
    count = Counter(list2)

    return sum(y[0] * y[1] for y in list(map(lambda x: [x, count[x]], list1)))

print(problem1())
print(problem2())
