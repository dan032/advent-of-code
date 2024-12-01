class Solution
  attr_reader :data

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day06/input.txt", chomp: true)
  end

  def problem1
    times = data.split("\n")[0].scan(/Time:\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/).first.map(&:to_i)
    distances = data.split("\n")[1].scan(/Distance:\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/).first.map(&:to_i)
    result = 1

    4.times do |idx|
      result *= calculate_wins(distances[idx], times[idx])
    end
    p result
  end

  def problem2
    time = data.split("\n")[0].scan(/Time:\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/).first.join("").to_i
    distance = data.split("\n")[1].scan(/Distance:\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/).first.join("").to_i
    p calculate_wins(distance, time)
  end

  private

  def calculate_wins(distance, time)
    wins = 0
    time_held = 1
    while time_held <= time
      curr_time = distance / time_held
      wins += 1 if curr_time + time_held < time
      time_held += 1
    end
    wins
  end
end

solution = Solution.new
solution.problem1
solution.problem2