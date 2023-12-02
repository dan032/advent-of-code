def problem1
  result = 0
  idx = 0

  File.readlines("input.txt", chomp: true).each do |line|
    valid = true
    colors = {"red" => 12, "green" => 13, "blue" => 14}
    line = line[line.index(":") + 2..]
    idx += 1
    sets = line.split("; ")
    sets.each_with_index do |s, i|
      vals = s.split(", ")

      vals.each do |e|
        n = e.scan(/\d/).join('')
        col = e.scan(/(green|red|blue)/).join('')

        next if n.nil? || col.nil?

        valid = false if colors[col] < n.to_i
      end

      next unless valid
    end

    result += idx if valid
  end

  puts result
end

def problem2
  result = 0
  idx = 0

  File.readlines("input.txt", chomp: true).each do |line|
    valid = true
    colors = {"red" => -1, "green" => -1, "blue" => -1}
    line = line[line.index(":") + 2..]
    idx += 1
    sets = line.split("; ")
    sets.each_with_index do |s, i|
      vals = s.split(", ")
      vals.each do |e|
        n = e.scan(/\d/).join('')
        col = e.scan(/(green|red|blue)/).join('')

        next if n.nil? || col.nil?
        colors[col] = [colors[col], n.to_i].max
      end

    end

    result += (colors["red"] * colors["green"] * colors["blue"])
  end

  puts result
end

problem1
problem2