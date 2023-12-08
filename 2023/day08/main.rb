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

  def problem2
    instructions = data[0]
    @data = data[2..]
    entries = {}
    a_entries = []
    ins_idx = 0
    data.each do |e|
      x = e.scan(/([0-9A-Z]+) = \(([0-9A-Z]+), ([0-9A-Z]+)\)/).first
      entries[x[0]] = [x[0],x[1], x[2], -1]

      a_entries << entries[x[0]] if x[0][2] == "A"
    end

    res = 0
    finished = []
    until a_entries.empty?
      res += 1
      curr_entries = a_entries
      if instructions[ins_idx % instructions.size] == "L"
        a_entries = curr_entries.map do |entry|
          get_entry(entry[1], entries)
        end
      else
        a_entries = curr_entries.map do |entry|
          get_entry(entry[2], entries)
        end
      end

      a_entries = a_entries.filter do |x|
        if x[0][2] == 'Z'
          finished << res
          false
        else
          true
        end

      end

      ins_idx += 1
    end

    p finished.reduce(1) {|acc, n| acc.lcm(n)}
  end

  private

  def get_entries(a_entries, entries)
    res = []
    a_entries.each do |x|
      res << x
    end
    res
  end

  def complete?(entries)
    entries.all? {|x| x[3] != -1}
  end

  def get_entry(key, entries)
    entries[key]
  end
end

s = Solution.new
s.problem1
s.problem2