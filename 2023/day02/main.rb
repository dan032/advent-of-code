class Solution
  attr_reader :data, :colors

  def initialize
    @colors = {"red" => 12, "green" => 13, "blue" => 14}
    @data = File.readlines("input.txt", chomp: true)
  end

  def problem1
    p data.map { game(_1) }.filter { valid_game?(_1[1]) }.map { _1[0].to_i }.sum
  end

  def problem2
    p data.map { game(_1) }.map { get_max_values(_1[1]) }.map { _1.inject(:*) }.sum
  end

  private

  def game(line)
    line.scan(/Game (?<id>\d+): (?<game>.*)/).first
  end

  def get_max_values(game)
    %w[red green blue].map{ game.scan(/(?<count>\d+) (?<color>(#{_1}))/).map{|r| r[0].to_i}.max }
  end

  def valid_game?(game)
    colors.all? { |color, max_val| max_val >= game.scan(/(?<count>\d+) (?<color>(#{color}))/).map{_1[0].to_i}.max }
  end
end

s = Solution.new
s.problem1
s.problem2