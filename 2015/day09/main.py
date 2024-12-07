from collections import defaultdict
from functools import reduce

def generateGraph(graph):
    for route in open("input.txt", "r"):
        countries, distance = route.split(" = ")
        distance = int(distance)
        source, dest = countries.split(" to ")
        graph[source].append((dest, distance))
        graph[dest].append((source, distance))
    return graph

def dfs(currCity, currDistance, visited, result, compFunc):
    if len(visited) == len(cities):
        return compFunc(result, currDistance)

    for n in graph[currCity]:
        if n[0] in visited:
            continue

        visited.add(n[0])
        result = compFunc(result, dfs(n[0], currDistance + n[1], visited, result, compFunc))
        visited.remove(n[0])
    return result

def problem(initial, compFunc):
    return reduce(lambda args, city: (args[1](args[0], dfs(city, 0, set([city]), args[0], args[1])), args[1]), cities, (initial, compFunc))[0]

graph = generateGraph(defaultdict(list))
cities = set(graph.keys())

print(problem(float("inf"), min))
print(problem(0, max))