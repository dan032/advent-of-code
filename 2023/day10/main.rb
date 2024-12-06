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

  def problem2
    grid = []
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

    # stack = []
    #
    # # Left
    # (0..grid.size - 1).each do |j|
    #   stack << [j, 0] if grid[j][0] != '!'
    # end
    #
    # (0..grid.size - 1).each do |j|
    #   stack << [j, grid[0].size - 1] if grid[j][grid[0].size - 1] != '!'
    # end
    #
    # (0..grid[0].size - 1).each do |i|
    #   stack << [0, i] if grid[0][i] != '!'
    # end
    #
    # (0..grid[0].size - 1).each do |i|
    #   stack << [grid.size - 1, i] if grid[grid.size - 1][i] != '!'
    # end
    #
    # x_offsets = [0, 0, -1, 1]
    # y_offsets = [-1, 1, 0, 0]
    #
    # until stack.empty?
    #   y, x = stack.pop
    #   next if y < 0 || y >= grid.size || x < 0 || x >= grid[0].size || grid[y][x] == "!"
    #
    #   grid[y][x] = '0'
    #   (0..3).each do |i|
    #     new_x = x + x_offsets[i]
    #     new_y = y + y_offsets[i]
    #     next if new_y < 0 || new_y >= grid.size || new_x < 0 || new_x >= grid[0].size || grid[new_y][new_x] == "!" || grid[new_y][new_x] == '0'
    #     stack << [new_y, new_x]
    #   end
    # end

    count = 0

    grid.each do |line|
      intercepts = 0
      line.split("").each do |c|
        if c == '!'
          intercepts += 1
        else
          count += 1 if intercepts % 2 == 1
        end

        # count += 1 if c != '!' && c != '0'
      end
    end

    p count

  end

  # private

  def dfs(x, y)
    return if y < 0 || y >= grid.size || x < 0 || x >= grid[0].size || grid[y][x] == "!"




  end
end

s = Solution.new
# s.problem1
s.problem2