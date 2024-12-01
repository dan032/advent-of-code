class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2021/day01/input.txt", chomp: true).split("\n").map { _1.to_i }
  end

  def problem1
    p data
        .each_cons(2)
        .select { _1[1] > _1[0] }
        .count
  end

  def problem2
    p data
        .each_cons(3)
        .map { _1.sum }
        .each_cons(2)
        .select { _1[1] > _1[0] }
        .count
  end
end

s = Solution.new
s.problem1
s.problem2