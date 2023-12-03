def game(line)
  m = line.match(/Game (?<id>\d+): (?<game>.*)/)
  [ m['id'].to_i, m['game'].split("; ") ]
end

def dies(round)
  round.split(", ")
end

def die_data(die)
  m = die.match(/(?<die_count>\d+) (?<die_color>.*)/)
  [ m['die_count'].to_i, m['die_color'] ]
end

def problem1
  result = 0
  colors = {"red" => 12, "green" => 13, "blue" => 14}

  File.readlines("input.txt", chomp: true).each do |line|
    valid = true
    id, rounds = game(line)

    rounds.each do |round|
      dies(round).each do |die|
        die_count, die_color = die_data(die)
        valid = false if colors[die_color] < die_count
      end
    end
    result += id if valid
  end
  puts result
end

def problem2
  result = 0
  File.readlines("input.txt", chomp: true).each do |line|
    colors = {"red" => 1, "green" => 1, "blue" => 1}

    game(line)[1].each do |round|
      dies(round).each do |die|
        die_count, die_color = die_data(die)
        colors[die_color] = [colors[die_color], die_count].max
      end
    end

    result += (colors["red"] * colors["green"] * colors["blue"])
  end
  puts result
end

problem1
problem2