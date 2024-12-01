require 'json'

class Solution
  attr_reader :data, :val

  def initialize
    @data = JSON.parse(File.read("#{Dir.pwd}/2015/day12/input.txt", chomp: true))
    @val = 0
  end

  def problem2
    calculate(data)
    p val
  end

  private

  def calculate(obj)
    return if obj.nil?
    if obj.kind_of?(Hash)
      return if obj.values.any? {|v| v == "red"}
      add_numbers(obj.values)
      traverse(obj.values)
    elsif obj.kind_of?(Array)
      add_numbers(obj)
      traverse(obj)
    end
  end

  def add_numbers(enum)
    @val += enum.reduce(0) do |acc, k|
      next acc unless literal?(k) && k.is_a?(Numeric)
      acc + k
    end
  end

  def traverse(enum)
    enum.each { |k| calculate(k) unless literal?(k) }
  end

  def literal?(obj)
    !obj.kind_of?(Hash) && !obj.kind_of?(Array)
  end
end

s = Solution.new
s.problem2