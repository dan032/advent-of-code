class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day08/input.txt", chomp: true).split("\n")
  end

  def problem1
    instructions = data[0]
    entries = data[2..]
      .map {_1.scan(/([A-Z]+) = \(([A-Z]+), ([A-Z]+)\)/).first}
      .map {[_1[0], [_1[1], _1[2]]]}.to_h

    ins_idx = 0
    result = 0
    curr_key = "AAA"
    until curr_key == "ZZZ"
      curr_entry = entries[curr_key]
      curr_key = instructions[ins_idx % instructions.size] == "L" ? curr_entry[0] : curr_entry[1]
      ins_idx += 1
      result += 1
    end

    p result
  end
end

s = Solution.new
s.problem1