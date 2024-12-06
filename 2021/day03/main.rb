class Solution
  attr_reader :data, :action

  def initialize
    @data = File.read("#{Dir.pwd}/2021/day03/input.txt", chomp: true).split("\n")
  end

  def problem1
    gamma = calculate1('max_by', &proc {|_, v| v})
    epsilon = calculate1('min_by', &proc {|_, v| v})
    p epsilon * gamma
  end

  def problem2
    @data = data.map {_1.split("")}
    p oxygen_rating * co2_rating
  end

  private

  def calculate1(compare_method, &proc)
    data
      .map { _1.split("") }
      .transpose
      .map { _1.tally.public_send(compare_method, &proc)[0].to_i }
      .join("")
      .to_i(2)
  end

  def oxygen_rating
    idx = 0
    sz = data[0].size
    curr = @data
    count = curr.transpose.map {_1.tally}
    while curr.length > 1 && idx < sz
      curr = curr.filter { |line| count[idx]["1"] >= count[idx]["0"] ? line[idx] == '1' : line[idx] == '0' }
      count = curr.transpose.map {_1.tally}
      idx += 1
    end
    curr.join("").to_i(2)
  end

  def co2_rating
    idx = 0
    sz = data[0].size
    curr = @data
    count = curr.transpose.map {_1.tally}
    while curr.length > 1 && idx < sz
      curr = curr.filter { |line| count[idx]["1"] < count[idx]["0"] ? line[idx] == '1' : line[idx] == '0' }
      count = curr.transpose.map {_1.tally}
      idx += 1
    end
    curr.join("").to_i(2)
  end
end

s = Solution.new
s.problem1
s.problem2