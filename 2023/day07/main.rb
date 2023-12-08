class Solution
  attr_reader :data, :card_strength

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day07/input.txt", chomp: true)
    @card_strength = %w[2 3 4 5 6 7 8 9 T J Q K A]
  end

  def problem1
    perform(&method(:get_score1))
  end

  def problem2
    card_strength.insert(0, card_strength.delete('J'))
    perform(&method(:get_score2))
  end

  private

  def perform(&score_func)
    p data
      .split("\n")
      .map { [_1.scan(/([A-Z0-9]+) (\d+)/).first] }
      .map { [_1[0][0], _1[0][1].to_i] }
      .sort_by { |x| [score_func.call(x[0]), 5.times.map { |i| card_strength.index(x[0][i]) }] }
      .each_with_index
      .map { _1[1] * (_2 + 1) }
      .sum
  end

  def get_score1(hand)
    get_score(get_counts(hand))
  end

  def get_score2(hand)
    count = get_counts(hand)
    joker_count = count['J']
    count.delete('J')
    return 7 if joker_count == 5
    count[count.max_by {_2}[0]] += joker_count
    get_score(count)
  end

  def get_counts(hand)
    count = Hash.new(0)
    hand.split("").each do |c|
      count[c] += 1
    end
    count
  end

  def get_score(count)
    return 7 if count.values.max == 5
    return 6 if count.values.max == 4
    return 5 if (count.values & [2,3]).size == 2
    return 4 if count.values.max == 3
    return 3 if count.values.filter { _1 == 2 }.size == 2
    return 2 if count.values.filter { _1 == 2 }.size == 1
    1
  end
end

solution = Solution.new
solution.problem1
solution.problem2