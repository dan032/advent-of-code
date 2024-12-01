class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day09/input.txt", chomp: true).split("\n")
  end

  def problem(mode)
    res = data.reduce([]) do |res, line|
      arrs = []
      line = line.split(" ").map {_1.to_i}
      until line.all? {|x| x == 0}
        arrs << line
        line = line.take(line.size - 1).each_with_index.map {line[_2 + 1].to_i - line[_2].to_i}
      end
      val = arrs.reverse.drop(0).reduce(0) do |val, entry|
        mode == 1 ? val + entry[0] : entry[0] - val
      end
      res << val
    end
    p res.sum
  end
end

s = Solution.new
s.problem(1)
s.problem(2)