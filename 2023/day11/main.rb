class Solution
  attr_reader :grid, :row_indexes, :col_indexes, :row_offsets, :col_offsets

  def initialize
    @grid = File.read("#{Dir.pwd}/2023/day11/input.txt", chomp: true).split("\n").map {_1.split("")}
    @row_offsets = [-1, 1, 0, 0]
    @col_offsets = [0, 0, -1, 1]
  end

  def problem(offset)
    @row_indexes = grid.each_with_index.map {[_1, _2]}.filter{!_1[0].include?("#")}.map{_2}
    @col_indexes = grid.transpose.each_with_index.map {[_1, _2]}.filter{!_1[0].include?("#")}.map{_2}

    count = 1
    galaxies = []
    grid.each_with_index do |line, i|
      line.each_with_index do |c, j|
        if c == '#'
          galaxies << [count, i, j, 0, 0]
          count += 1
        end
      end
    end

    p galaxies.reduce(0) { |res, g|  res += bfs(g, grid, galaxies, offset).sum{|_, v| v} / 2 }
  end

  private

  def bfs(source, grid, galaxies, offset)
    queue = [ source ]
    grid_cpy = grid.map { _1.dup }
    distances = { source[0] => 0 }

    until queue.empty?
      galaxy_id, i, j, dist_x, dist_y = queue.shift

      (0..3).each do |x|
        new_i, new_j = col_offsets[x] + i, row_offsets[x] + j
        next if new_i < 0 || new_i >= grid_cpy.size || new_j < 0 || new_j >= grid_cpy[0].size || grid_cpy[new_i][new_j] == 'x'

        new_dist_x,new_dist_y = dist_x + col_offsets[x].abs, dist_y + row_offsets[x].abs
        new_dist_y += offset if (row_indexes.include?(new_i))
        new_dist_x += offset if (col_indexes.include?(new_j))
        if grid_cpy[new_i][new_j] == '#'
          g_id2 = galaxies.select {|g2| g2[1] == new_i && g2[2] == new_j}.first[0]
          distances[g_id2] = (new_dist_x + new_dist_y) unless  distances.key?(g_id2)
        end

        queue << [galaxy_id, new_i, new_j, new_dist_x, new_dist_y]
        grid_cpy[new_i][new_j] = "x"
      end
    end

    distances
  end
end

s = Solution.new
s.problem(1)
s.problem(999_999)