class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day13/input.txt", chomp: true).split("\n\n")
  end

  def problem(changes)
    result = 0
    data
      .each
      .map{_1.split("\n").map {|x| x.split("")}}
      .each do |block|
        horizontal = get_value(block, changes)
        vertical = get_value(block.transpose, changes)
        result += horizontal > vertical ? horizontal * 100 : vertical
      end

    p result
  end

  private

  def get_value(block, changes)
    res = 0
    block.each_with_index do |line, idx|
      next if idx == 0

      left = idx - 1
      right = idx
      diff = count_diff(block[left], block[right])

      loop do
        left -= 1
        right += 1
        break if left < 0 || right > block.size - 1
        diff += count_diff(block[left], block[right])
      end

      next unless diff == changes
      next unless left < 0 || right > block.size - 1
      res = idx
      break
    end
    res
  end

  def count_diff(line1, line2)
    line1.each_with_index.reduce(0) do |count, args|
      count += 1 if line1[args[1]] != line2[args[1]]
      count
    end
  end
end

s = Solution.new
s.problem(0)
s.problem(1)