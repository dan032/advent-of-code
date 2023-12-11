class Solution
  attr_reader :grid, :row_indexes, :col_indexes, :offset

  def initialize
    @grid = File.read("#{Dir.pwd}/2023/day11/input.txt", chomp: true).split("\n").map {_1.split("")}
  end

  def problem(offset)
    @row_indexes = grid.each_with_index.map {[_1, _2]}.filter{!_1[0].include?("#")}.map{_2}
    @col_indexes = grid.transpose.each_with_index.map {[_1, _2]}.filter{!_1[0].include?("#")}.map{_2}
    @offset = offset

    galaxies = extract_galaxies
    p galaxies.reduce(0) { |res, g|  res += calculate(g, galaxies).sum{|_, v| v}} / 2
  end

  private

  def extract_galaxies
    count = 0
    grid.each_with_index.map { [_1, _2] }.map do|line_with_idx|
      line_with_idx[0].each_with_index.map do |c, j|
        if c == "#"
          count += 1
          [count, line_with_idx[1], j]
        end
      end.filter { _1 }
    end.filter { !_1.empty? }.flatten(1)
  end

  def calculate(source, galaxies)
    galaxies.map do |g|
      x, y = [g[1] - source[1], g[2] - source[2]].map {_1.abs}
      x_offset = calculate_offset(row_indexes, source[1], g[1])
      y_offset = calculate_offset(col_indexes, source[2], g[2])

      [g[0], (x + y + x_offset + y_offset)]
    end.to_h
  end

  def calculate_offset(indexes, g1, g2)
    start_point, end_point = [g1, g2].min, [g1, g2].max

    indexes.reduce(0) do |curr_offset, idx|
      if (start_point..end_point).include?(idx)
        curr_offset += offset
      end
      curr_offset
    end
  end
end

s = Solution.new
s.problem(1)
s.problem(999_999)