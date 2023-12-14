class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day14/input.txt", chomp: true)
  end

  def problem1
    result = 0
    data.split("\n").map{_1.split("")}.transpose.each_with_index do |line, l_idx|
      line = line.reverse
      curr = 0
      last_idx = 0
      line.each_with_index do |c, i|
        if c == "#"
          if curr == 0
            last_idx = i
            next
          end

          (last_idx..i - 1).each do |new_idx|
            next if line[new_idx] == '#'
            if (i - new_idx) > curr
              line[new_idx] = "."
            else
              line[new_idx] = 'O'
            end
          end
          curr = 0
          last_idx = i
        elsif c == "O"
          curr += 1
        end
      end
      (last_idx..line.size - 1).each do |new_idx|
        next if line[new_idx] == '#'
        if line.size - new_idx > curr
          line[new_idx] = "."
        else
          line[new_idx] = 'O'
        end
      end

      result += get_result(line)
    end
    p result
  end

  def problem2
    # p data
  end

  private

  def get_result(line)
    res = 0
    line.each_with_index do |c, i|
      res += 1 * (i + 1) if c == "O"
    end
    res
  end
end

s = Solution.new
s.problem1
s.problem2