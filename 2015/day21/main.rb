class Player
  attr_reader :hit_points, :damage, :armor_stat, :gold_spent, :armor,
              :weapon, :rings, :og_armor_stat, :og_damage, :og_hit_points

  def initialize(hit_points, damage, armour)
    @og_hit_points = hit_points
    @og_damage = damage
    @og_armor_stat = armour
    @hit_points = hit_points
    @damage = damage
    @armor_stat = armour
    @gold_spent = 0
    @armor = nil
    @weapon = nil
    @rings = []
  end

  def takes_damage(damage)
    amount = damage - armor_stat
    amount = 1 if amount < 1
    @hit_points -= amount
  end

  def alive?
    @hit_points > 0
  end

  def buy_armor_item(gold, armor_stat, armor_name)
    return unless armor.nil?
    @gold_spent += gold
    @armor_stat += armor_stat
    @armor = armor_name
  end

  def buy_weapon_item(gold, damage_stat, weapon_name)
    return unless weapon.nil?
    @gold_spent += gold
    @damage += damage_stat
    @weapon = weapon_name
  end

  def buy_ring(gold, damage_stat, armor_stat, ring_name)
    return if rings.size >= 2
    @gold_spent += gold
    @damage += damage_stat
    @armor_stat += armor_stat
    @rings << ring_name
  end

  def reset
    @hit_points = og_hit_points
    @damage = og_damage
    @armor_stat = og_armor_stat
    @gold_spent = 0
    @armor = nil
    @weapon = nil
    @rings = []
  end
end

class Game
  attr_reader :player, :computer, :weapons, :armours, :rings
  def initialize
    @player = Player.new(100, 0, 0)
    @computer = Player.new(100, 8, 2)
    items = File.read("#{Dir.pwd}/2015/day21/input.txt", chomp: true).split("\n\n")
    @weapons = parse_items(items[0], "weapon")
    @armours = parse_items(items[1], "armour")
    @rings = parse_items(items[2], "ring")
  end

  def perform(mode)
    result = mode == 1 ? Float::INFINITY : 0
    result_method = mode == 1 ? "min" : "max"

    combs = (weapons + armours + rings).combination(5)
    combs.each do |c|
      c.each do |item|
        player.buy_weapon_item(item[1], item[2], item[0]) if item[4] == "weapon"
        player.buy_armor_item(item[1], item[3], item[0]) if item[4] == "armour"
        player.buy_ring(item[1], item[2], item[3], item[0]) if item[4] == "ring"
      end
      next if player.weapon == nil

      won, curr = play
      player.reset
      computer.reset
      result = [result, curr].public_send(result_method) if won && mode == 1 || !won && mode == 2
    end
    p result
  end

  def play
    while player.alive? && computer.alive?
      computer.takes_damage(player.damage)
      break unless computer.alive?
      player.takes_damage(computer.damage)
    end

    if player.alive?
      [true, player.gold_spent]
    else
      [false, player.gold_spent]
    end
  end

  private

  def parse_items(items, type)
    items
      .split("\n")
      .map {_1.scan(/([A-Za-z0-9+]+)\s+(\d+)\s+(\d+)\s+(\d+)/).first}
      .map {[_1[0], _1[1].to_i, _1[2].to_i, _1[3].to_i, type]}
  end
end

game = Game.new
game.perform(1)
game.perform(2)