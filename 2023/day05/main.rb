class Solution
  attr_reader :data, :number_start, :number_end, :range_start, :range_end, :problem

  def initialize
    @data = File.read("#{Dir.pwd}/2023/day05/input.txt", chomp: true)
  end

  def perform(problem)
    @problem = problem
    maps = generate_maps(data)
    numbers = generate_seeds(data.split("\n").first.scan(/\d+/).map {_1.to_i })
    source_key = "seed"

    until source_key == "location"
      new_numbers = []
      curr_map = maps[source_key]

      until numbers.empty?
        old_numbers_len = new_numbers.size
        @number_start, @number_end = numbers.shift

        curr_map["mappings"].each do |range_start, range_end, offset|
          @range_start = range_start
          @range_end = range_end

          if total_overlap?
            new_numbers << [(number_start + offset), (number_start + offset)]
          elsif partial_center_overlap?
            numbers << [number_start, range_start - 1] + [range_end + 1, number_end]
            new_numbers << [(range_start + offset), (range_end + offset)]
          elsif left_overlap?
            numbers << [range_end + 1, number_end]
            new_numbers << [(number_start + offset), (range_end + offset)]
          elsif right_overlap?
            numbers << [number_start, range_start - 1]
            new_numbers << [(range_start + offset), (number_end + offset)]
          end
          break unless old_numbers_len == new_numbers.size
        end

        new_numbers << [number_start, number_end] if old_numbers_len == new_numbers.size
      end

      source_key = curr_map["destination"]
      numbers = new_numbers
    end
    p numbers.map { _1[0] }.min
  end

  private

  def generate_maps(data)
    data
      .split("\n\n")
      .map { _1.scan(/([a-z\-]+) map:\n((?:\d+ \d+ \d+\n?)+)/).first }
      .filter { _1 }
      .map { [_1[0].scan(/([a-z]+)-to-([a-z]+)/).first, _1[1].split("\n")] }
      .map { [_1[0], _1[1].map { |x| x.scan(/(\d+) (\d+) (\d+)/).first.map(&:to_i) }] }
      .map { [_1[0], _1[1].map { |x| [x[1], x[2] + x[1] - 1, x[0] - x[1]] }] }
      .map { [_1[0][0], [["destination", _1[0][1]], ["mappings", _1[1]]].to_h] }.to_h
  end

  def generate_seeds(seeds)
    seeds
      .each_with_index
      .map { problem == 1 ? [seeds[_2], seeds[_2]] : generate_seed(seeds, _2) }
      .filter { _1.any? }
  end

  def generate_seed(seeds, i)
    return [] if i % 2 == 1
    [ seeds[i], seeds[i] + seeds[i + 1] - 1 ]
  end

  def total_overlap?
    left_overlap? && right_overlap?
  end

  def left_overlap?
    range_start <= number_start && number_start <= range_end
  end

  def right_overlap?
    range_start <= number_end && number_end <= range_end
  end

  def partial_center_overlap?
    number_start < range_start && number_end > range_end
  end
end

solution = Solution.new
solution.perform(1)
solution.perform(2)