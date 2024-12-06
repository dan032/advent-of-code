Node = Struct.new(:location, :direction, :score,)
class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day17/input.txt", chomp: true).split("\n").map {_1.split("").map {|x| x.to_i}}
  end

  def problem1
    queue = [[0, 0, 0, 0, 0, 0, data[0][0]], "right", 0] # y, x, (up, right, down, left), score, last dir, curr_score
    until queue.empty?
      y, x, up, right, down, left, score, last_dir = queue.shift

    end
  end

  def problem2
  end
end

s = Solution.new
s.problem1
s.problem2