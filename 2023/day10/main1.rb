class Solution
  attr_reader :data, :result, :col_offsets, :row_offsets, :grid

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day10/input.txt", chomp: true)
    @result = 0

    # [W, E, N, S]
    @row_offsets = {
      "|" => [0, 0, 0, 0], "-" => [-1, 1, 0, 0], "L" => [0, 1, 0, 0], "J" => [-1, 0, 0, 0],
      "7" => [-1, 0, 0, 0], "F" => [0, 1, 0, 0], "S" => [-1,1, 0, 0], '.' => [0, 0, 0, 0], '!' => [0, 0, 0, 0]
    }

    # [N, S]
    @col_offsets = {
      "|" => [0, 0, -1, 1], "-" => [0, 0, 0, 0], "L" => [0, 0, -1, 0], "J" => [0, 0, -1, 0],
      "7" => [0, 0,0, 1], "F" => [0, 0, 0,1], "S" => [0, 0, -1, 1], '.' => [0, 0, 0, 0], '!' => [0, 0, 0, 0]
    }
  end

  def problem1
    @grid = []
    data.split("\n").each do |line|
      grid << line
    end

    queue = []
    found = false
    grid.each_with_index do |line, y|
      line.split("").each_with_index do |c, x |
        if c == 'S'
          queue << [y, x, 0]
          found = true
          break
        end
      end
      break if found
    end

    until queue.empty?
      y, x, count = queue.shift

      if grid[y][x] != '.' || grid[y][x] != '!'
        @result = [result, count].max
      end

      curr = grid[y][x]
      grid[y][x] = '!'
      (0..3).each do |i|
        new_x = x + row_offsets[curr][i]
        new_y = y + col_offsets[curr][i]

        next if new_y < 0 || new_y >= grid.size || new_x < 0 || new_x >= grid[0].size || grid[new_y][new_x] == "." || grid[new_y][new_x] == "!"
        if new_x != x
          next if !row_offsets[grid[y][new_x]].include?(1) && new_x < x
          next if !row_offsets[grid[y][new_x]].include?(-1) && new_x > x
        end
        if new_y != y
          next if !col_offsets[grid[new_y][x]].include?(1) && new_y < y
          next if !col_offsets[grid[new_y][x]].include?(-1) && new_y > y
        end

        queue << [new_y, new_x, count + 1]
      end
    end
    p result
  end
end