class Solution
  attr_reader :data

  def initialize
    @data = File.readlines("input.txt", chomp: true)
  end

  def problem1
    p data
      .map { game(_1) }
      .map { winning_numbers(_1[1]) & player_numbers(_1[1]) }
      .sum { |x| x.size - 1 >= 0 ? 2 ** (x.size - 1) : 0 }
  end

  def problem2
    cards = Array.new(data.size, 1)

    data
      .map { game(_1) }
      .map { [ winning_numbers(_1[1]) & player_numbers(_1[1]), _1[0].to_i] }
      .filter { !_1[0].empty? }
      .each { |matching| matching[0].size.times {|y| cards[matching[1] + y] += cards[matching[1] - 1] } }

    p cards.sum
  end

  private

  def winning_numbers(game)
    game[..game.index("|") - 2].split(" ")
  end

  def player_numbers(game)
    game[game.index("|") + 2..].split(" ")
  end

  def game(line)
    line.scan(/Card\s+(?<id>\d+): (?<game>.*)/).first
  end
end

s = Solution.new
s.problem1
s.problem2