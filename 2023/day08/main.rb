class Solution
  attr_reader :data, :instructions, :entries

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day08/input.txt", chomp: true).split("\n")
    @instructions = data[0].split("").cycle
    @entries = data[2..].map { _1.scan(/(.+) = \((.+), (.+)\)/).first }.map { [_1[0], [_1[0], _1[1], _1[2]]] }.to_h
  end

  def problem1
    curr_key = "AAA"

    p instructions.reduce(0) { |sum, ins|
        curr_key = ins == "L" ? entries[curr_key][1] : entries[curr_key][2]
        sum += 1
        break sum if curr_key == "ZZZ"
        sum
    }
  end

  def problem2
    curr_entries = entries.filter { _1[2] == "A"}
    res = instructions.each_with_index.reduce([]) do |finished, args|
      break finished if curr_entries.empty?
      instruction, idx = args
      curr_entries = curr_entries.map { next_entry(instruction, _1) }
      found = curr_entries.filter! { |x| x[0][2] != 'Z' }
      finished << idx + 1 if found
      finished
    end

    p res.reduce(1) { _1.lcm(_2) }
  end

  private

  def next_entry(ins, curr_entry)
    ins == "L" ? entry(curr_entry[1][1]) : entry(curr_entry[1][2])
  end

  def entry(id)
    [id, entries[id]]
  end
end

s = Solution.new
s.problem1
s.problem2