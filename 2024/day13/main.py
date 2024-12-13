import re

def problem(offset):
    machines = [[int(d) for d in re.findall(r"(\d+)", "".join(entry))] for entry in open("input.txt", "r").read().split("\n\n")]
    tokens = 0
    for machine in machines:
        a_x, a_y, b_x, b_y, p_x, p_y = machine
        p_x += offset
        p_y += offset

        a = (p_x * b_y - p_y * b_x) / (a_x * b_y - a_y * b_x)
        b = (p_y * a_x - p_x * a_y) / (a_x * b_y - a_y * b_x)

        if all(x == int(x) for x in [a, b]):
            tokens += int(3 * a + b)
    return tokens

print(problem(0))
print(problem(10000000000000))
