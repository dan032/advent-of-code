class Solution
  attr_reader :data, :action

  def initialize
    @data = File.read("#{Dir.pwd}/2021/day02/input.txt", chomp: true).split("\n")
    @action = {"down" => 1, "up" => -1, "forward" => 1}
  end

  def problem1
    p data
      .map { _1.scan(/(forward|up|down) (\d+)/).first }
      .each_with_object({"x" => 0, "y" => 0}) { |line, sums|
        amount = line[1].to_i * action[line[0]]
        sums["x"] += amount if line[0] == "forward"
        sums["y"] += amount unless line[0] == "forward"
      }
      .values
      .inject(:*)
  end

  def problem2
    p data
      .map { _1.scan(/(forward|up|down) (\d+)/).first }
      .each_with_object({"x" => 0, "y" => 0, "aim" => 0}) { |line, sums|
        amount = line[1].to_i * action[line[0]]
        sums["x"] += amount if line[0] == "forward"
        sums["y"] += (amount * sums["aim"]) if line[0] == "forward"
        sums["aim"] += amount unless line[0] == "forward"
      }
      .values
      .take(2)
      .inject(:*)
  end
end

s = Solution.new
s.problem1
s.problem2