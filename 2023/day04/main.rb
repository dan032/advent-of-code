class Solution
  attr_reader :data

  def initialize
    @data = []

    File.readlines("input.txt", chomp: true).each do |line|
      @data << line
    end
  end

  def problem1
    p data
      .map{game(_1)}
      .map{|game| winning_numbers(game) & player_numbers(game) }
      .sum{|x| x.size - 1 >= 0 ? 2 ** (x.size - 1) : 0}
  end

  def problem2
    cards = Array.new(data.size, 1)

    data
      .map{game(_1)}
      .each_with_index.map{|game, idx|[winning_numbers(game) & player_numbers(game), idx]}
      .filter{!_1[0].empty?}
      .each {|matching| matching[0].size.times {|y| cards[matching[1] + y + 1] += cards[matching[1]] }}

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
    line.match(/Card\s+\d+: (?<game>.*)/)["game"]
  end
end

s = Solution.new
s.problem1
s.problem2