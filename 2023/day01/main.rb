def is_digit?(c)
  c.match?(/[[:digit:]]/)
end

def problem(is_problem_2)
  result = 0
  digits = { 'one' => 1, 'two' => 2, 'three' => 3, 'four' => 4, 'five' => 5, 'six' => 6, 'seven' => 7, 'eight' => 8, 'nine' => 9 }

  File.readlines("input.txt", chomp: true).each do |line|
    digit_arr = []

    line.split("").each_with_index do |c,i|
      if is_digit?(c)
        digit_arr << c
      end

      next unless is_problem_2
      digits.each do |word, val|
        if line[i..].start_with?(word)
          digit_arr << val.to_s
        end
      end
    end
    result += (digit_arr[0] + digit_arr[-1]).to_i
  end

  puts result
end

problem(false)
problem(true)