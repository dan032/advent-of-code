class Solution
  attr_reader :data, :cities, :reverse_cities

  def initialize
    @data = File.read("#{Dir.pwd}/2015/day09/input.txt", chomp: true).split("\n")
    @cities = Hash.new { |h, k| h[k] = [] }
    @reverse_cities = Hash.new { |h, k| h[k] = [] }

    data
     .map {_1.scan(/([A-Za-z]+) to ([A-Za-z]+) = (\d+)/).first}
     .each do |row|
      cities[row[0]] << [row[1], row[2].to_i, false]
      reverse_cities[row[1]] << [row[0], row[2].to_i, false]
    end
  end

  def problem1
    res = Float::INFINITY
    cities.keys.each do |city|
      distances, previous_vertices = dijkstra(city, cities)
      res = [res, distances.sum{|k, v| v}].min
    end

    reverse_cities.keys.each do |city|
      distances, previous_vertices = dijkstra(city, reverse_cities)
      res = [res, distances.sum{|k, v| v}].min
    end
    p res
  end

  def problem2
  end

  private

  def dijkstra(source, graph)
    queue = []
    distances = {}
    previous_vertices = {}
    graph.keys.each do |city|
      distances[city] = Float::INFINITY
      previous_vertices[city] = nil
      queue << city
    end
    distances[source] = 0

    until queue.empty?
      u = distances.filter {|k, v| queue.include?(k)}.min_by {|k, v| v}
      queue.delete(u[0])

      graph[u[0]].filter{|city| queue.include?(city[0])}.each do |neighbor|
        alt = u[1] + graph[u[0]].select {|city| city[0] == neighbor[0]}.first[1]
        if alt < distances[neighbor[0]]
          distances[neighbor[0]] = alt
          previous_vertices[neighbor[0]] = u[0]
        end
      end
    end
    [distances, previous_vertices]
  end
end

s = Solution.new
s.problem1
s.problem2