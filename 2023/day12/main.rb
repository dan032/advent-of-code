class Solution
  attr_reader :data, :memo

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day12/input.txt", chomp: true).split("\n")
    @memo = {}
  end

  def problem1
    lines, groups =  data
                       .map {_1.scan(/([?.#]+) ([\d+,]+)/).first}
                       .map {[_1[0], _1[1].split(",").map {|x| x.to_i}]}

    result = 0

    # end

    p result
  end
end

s = Solution.new
s.problem1
s.problem2