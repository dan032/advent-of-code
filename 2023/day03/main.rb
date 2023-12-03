class Solution
  attr_reader :data, :row_offsets, :col_offsets

  def initialize
    @data = []
    @row_offsets = [0, 0, 0, -1, -1,-1, 1, 1, 1]
    @col_offsets = [-1, 0, 1, -1, 0, 1, -1, 0, 1]

    File.readlines("input.txt", chomp: true).each do |line|
      @data << line.split("")
    end
  end

  def problem1
    result = 0
    data.each_with_index do |row, i|
      curr_num = ""
      next_to_symbol = false

      row.each_with_index do |col, j|
        if is_digit?(col)
          curr_num += col
          next if next_to_symbol
          next_to_symbol = next_to_symbol?(i,j)
        else
          if next_to_symbol && !curr_num.empty?
            result += curr_num.to_i
            next_to_symbol = false
          end
          curr_num = ""
        end
      end

      result += curr_num.to_i if next_to_symbol && !curr_num.empty?
    end

    puts result
  end

  def problem2
    gear_visits = Hash.new {|h, k| h[k] = []}
    data.each_with_index do |row, i|
      curr_num = ""
      found = false
      row.each_with_index do |col, j|
        next unless col == "*"

        (0..8).each do |e|
          new_i, new_j = i + row_offsets[e], j + col_offsets[e]
          next if out_of_range?(new_i, new_j)

          num = find_number(new_i, new_j)
          found = false if !is_digit?(data[new_i][new_j]) || new_row?(e)
          next if num == 0 || found

          found = true
          gear_visits[index(i, j)] << num
        end
      end
    end

    p gear_visits.values.filter{ |v| v.size == 2 }.map{ |v| v.inject(:*) }.sum
  end

  private

  def next_to_symbol?(i, j)
    (0..8).each do |e|
      new_i, new_j = i + row_offsets[e], j + col_offsets[e]
      return true if !out_of_range?(new_i, new_j) && !is_digit?(data[new_i][new_j]) && data[new_i][new_j] != '.'
    end
    false
  end

  def find_number(i, j)
    left = j
    right = j
    curr = ""

    left -= 1 while left >= 0 && is_digit?(data[i][left])
    right += 1 while right < data[0].size && is_digit?(data[i][right])

    left += 1 if left < 0 || !is_digit?(data[i][left])
    right -= 1 if right >= data[0].size || !is_digit?(data[i][right])

    while left <= right
      curr += data[i][left]
      left += 1
    end

    curr.to_i
  end

  def is_digit?(c)
    c.match?(/[[:digit:]]/)
  end

  def out_of_range?(i, j)
    i < 0 || i >= data.size || j < 0 || j >= data[0].size
  end

  def index(i, j)
    (i) * (data.size) + j
  end

  def new_row?(i)
    i % 3 == 0
  end
end

s = Solution.new
s.problem1
s.problem2