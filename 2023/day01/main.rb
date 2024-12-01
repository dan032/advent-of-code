class Solution
  attr_reader :data, :digits
  def initialize
    @data = File.readlines("input.txt", chomp: true)
    @digits = { 'one' => 'o1e', 'two' => 't2o', 'three' => 't3e',
                'four' => 'f4r', 'five' => 'f5e', 'six' => 'x6x',
                'seven' => 's7n', 'eight' => 'e8t', 'nine' => 'n9e'
              }
  end

  def problem(is_problem_2)
    p data
      .map{ is_problem_2 ? _1.gsub(/#{digits.keys.join('|')}/, digits) : _1 }
      .map{ is_problem_2 ? _1.gsub(/#{digits.keys.join('|')}/, digits) : _1 }
      .map{ _1.match?(/[\d+]/) }
      .map{ _1.filter { |c| is_digit?(c) } }
      .map{ _1.first + _1.last }
      .map{ _1.to_i }
      .sum
  end
end

s = Solution.new
s.problem(false)
s.problem(true)