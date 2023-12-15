class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day15/input.txt", chomp: true)
  end

  def problem1
    p data.split(",").reduce(0) { |res, group| res + get_hash(group) }
  end

  def problem2
    indexes = { }
    256.times do |t|
      indexes[t] = []
    end

    data.split(",").each do |group|
      label, action, value = group.scan(/([a-z]+)([=-])(\d+)?/).first
      h = get_hash(label)
      if action == "="
        found = false
        indexes[h].each_with_index do |_, i|
          if indexes[h][i][0] == label
            indexes[h][i] = [label, value]
            found = true
            break
          end
        end
        indexes[h] << [label, value] unless found
      else
        indexes[h].each_with_index do |_, i|
          if indexes[h][i][0] == label
            indexes[h].delete_at(i)
            break
          end
        end
      end
    end

    p indexes.reduce(0) { |result, args|
      k, v = args
      result + v.each_with_index.reduce(0) do |curr, args2|
        curr + (k + 1) * args2[0][1].to_i * (args2[1] + 1)
      end
    }
  end

  private

  def get_hash(group)
    group.split("").each.reduce(0) { |acc, c| ((acc + c.ord) * 17) % 256 }
  end
end

s = Solution.new
s.problem1
s.problem2