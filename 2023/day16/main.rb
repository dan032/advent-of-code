class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day16/input.txt", chomp: true).split("\n").map{_1.chomp.chars}
  end

  def problem1
    beams = [[0, 0, "right"]] # y, x, dir
    p perform(beams)
  end

  def problem2
    result = 0

    # Top
    (0..data[0].size - 1).each do |i|
      result = [result, perform([[0, i, "down"]])].max
    end

    # Left Side
    (0..data.size - 1).each do |i|
      result = [result, perform([[i, 0, "right"]])].max
    end

    # Bottom
    (0..data[0].size - 1).each do |i|
      result = [result, perform([[data.size - 1, i, "up"]])].max
    end

    # Bottom
    (0..data.size - 1).each do |i|
      result = [result, perform([[i, data[0].size - 1, "left"]])].max
    end

    p result
  end

  private

  def perform(beams)
    tiles = data.map {|line| line.map {{}}}

    until beams.empty?
      new_beams = []

      beams.each do |y, x, dir|
        next if tiles[y][x][dir]
        tiles[y][x][dir] = true
        field = data[y][x]

        case dir
        when "right"
          case field
          when "/"
            new_beams << [y - 1, x, "up"]
          when "\\"
            new_beams << [y + 1, x, "down"]
          when "|"
            new_beams << [y - 1, x, "up"]
            new_beams << [y + 1, x, "down"]
          when
          new_beams << [y, x + 1, "right"]
          end
        when "left"
          case field
          when "/"
            new_beams << [y + 1, x, "down"]
          when "\\"
            new_beams << [y - 1, x, "up"]
          when "|"
            new_beams << [y - 1, x, "up"]
            new_beams << [y + 1, x, "down"]
          else
            new_beams << [y, x - 1, "left"]
          end
        when "up"
          case field
          when "/"
            new_beams << [y, x + 1, "right"]
          when "\\"
            new_beams << [y, x - 1, "left"]
          when "-"
            new_beams << [y, x - 1, "left"]
            new_beams << [y, x + 1, "right"]
          else
            new_beams << [y - 1, x, "up"]
          end
        when "down"
          case field
          when "/"
            new_beams << [y, x - 1, "left"]
          when "\\"
            new_beams << [y, x + 1, "right"]
          when "-"
            new_beams << [y, x - 1, "left"]
            new_beams << [y, x + 1, "right"]
          else
            new_beams << [y + 1, x, "down"]
          end
        end
      end
      beams = new_beams.select do |y, x, _|
        x >= 0 && x < data[0].size && y >= 0 && y < data.size
      end
    end

    res = tiles.map {|row| row.map {_1.values.count(true)}.join}
    res.join.size - res.join.count("0")
  end
end

s = Solution.new
s.problem1
s.problem2