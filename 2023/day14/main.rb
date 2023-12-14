class Solution
  attr_reader :data, :directions
  ITERATIONS = 1_000_000_000

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day14/input.txt", chomp: true).split("\n").map{_1.split("")}
  end

  def problem1
    grid = roll(data, "north")
    p grid.transpose.each.reduce(0) { |result, line| result + get_line_result(line) }
  end

  def problem2
    known_states = {}
    count = 0
    grid = data.dup

    while count < ITERATIONS
      %w[north west south east].each { grid = roll(grid, _1) }
      if known_states.key?(grid.hash)
        length = count - known_states[grid.hash]
        skips = (ITERATIONS - count) / length
        count += skips * length
      else
        known_states[grid.hash] = count
      end
      count += 1
    end

    p grid.transpose.each.reduce(0) { |result, line| result + get_line_result(line) }
  end

  private

  def roll(grid, dir)
    case dir
    when "north"
      grid.reverse.transpose.map { new_line(_1, &method(:fill)) }.transpose.reverse
    when "west"
      grid.map { new_line(_1, &method(:fill_west)) }
    when "south"
      grid.transpose.map { new_line(_1, &method(:fill)) }.transpose
    when "east"
      grid.reverse.map { new_line(_1, &method(:fill)) }.reverse
    else
      raise StandardError.new("Unsupported Direction")
    end
  end

  def get_line_result(line)
    line.each_with_index.reduce(0) { |res, char_with_idx| char_with_idx[0] == "O" ? res + 1 * (line.size - char_with_idx[1]) : res }
  end

  def new_line(line, &fill_func)
    count = 0
    last_index = 0
    line.each_with_index do |c, i|
      next count += 1 if c == 'O'
      next unless c == '#'
      next last_index = i if count == 0

      line = fill_func.call(last_index, i, line, count)
      count = 0
      last_index = i
    end
    fill_func.call(last_index, line.size, line, count)
  end

  def fill(start_index, last_index, line, count)
    (start_index..last_index - 1).each do |idx|
      next if line[idx] == '#'
      next line[idx] = 'O' unless (last_index - idx) > count
      line[idx] = '.'
    end
    line
  end

  def fill_west(start_index, last_index, line, count)
    (start_index..last_index - 1).each do |idx|
      next if line[idx] == '#'
      next line[idx] = '.' unless count > 0
      line[idx] = 'O'
      count -= 1
    end
    line
  end
end

s = Solution.new
s.problem1
s.problem2