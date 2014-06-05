import random
import math
import listmath
import variables as v

def get_aimer_position(aimer):
    (x,y) = aimer.parent.pos()
    heading = aimer.parent.heading()
    x_change = math.cos(math.radians(heading))*aimer.step
    y_change = math.sin(math.radians(heading))*aimer.step
    return (x+x_change, y+y_change)

def random_choice(choice, chance):
    total = sum(chance)
    chance = [one/total for one in chance]
    sort = chance[:]
    sort.sort()
    rand = random.random()
    for percent in sort:
        if percent >= rand:
            return choice[chance.index(percent)]
    return choice[chance.index(sort[-1])]

def enemy_spawn_think(tank):
    turn_speed = False
    forward_speed = v.ENEMY_SPAWN_SPEED
    if len(v.enemy_tank_list) > 1:
        dist_list = [tank.distance(friend) for friend in v.enemy_tank_list]
        dist_list.remove(0)
        if min(dist_list) < v.SPAWN_STOP_TRIGGER:
            forward_speed = v.SPAWN_SLOW_SPEED
    if len(v.user_tank_list) >= 0:
        turn_speed = flee(tank, v.user_tank_list,
                          v.ENEMY_SPAWN_ATTACK_RANGE)
    if not turn_speed:
        turn_speed = random.uniform(-v.SPAWN_TURN_RATE, v.SPAWN_TURN_RATE)
        turn_speed = check_walls(tank, turn_speed)
    else:
        max_tspeed = v.SPAWN_TURN_RATE
        if turn_speed >= 0:
            turn_speed = min([turn_speed, max_tspeed])
        else:
            turn_speed = max([turn_speed, -max_tspeed])
    return turn_speed, forward_speed

#note: the friendly spawn is running a slightly modified AI that does
#not properly handle when flee() returns false as the turn speed.
#Instead of doing a random turn it merely avoids walls but I'm leaving
#this because it seems to work well
def friendly_spawn_think(tank):
    turn_speed = False
    forward_speed = v.FRIENDLY_SPAWN_SPEED
    if len(v.user_tank_list) > 1:
        dist_list = [tank.distance(friend) for friend in v.user_tank_list]
        dist_list.remove(0)
        if min(dist_list) < v.SPAWN_STOP_TRIGGER:
            forward_speed = v.SPAWN_SLOW_SPEED
    if len(v.enemy_tank_list) > 0:
        turn_speed = flee(tank, v.enemy_tank_list,
                          v.FRIENDLY_SPAWN_ATTACK_RANGE)
        max_tspeed = v.SPAWN_TURN_RATE
        if turn_speed >= 0:
            turn_speed = min([turn_speed, max_tspeed])
        else:
            turn_speed = max([turn_speed, -max_tspeed])
    else:
        turn_speed = random.uniform(-v.SPAWN_TURN_RATE, v.SPAWN_TURN_RATE)
    turn_speed = check_walls(tank, turn_speed)
    return turn_speed, forward_speed

def enemy_gunner_think(tank):
    fd_speed = v.GUNNER_TANK_SPEED
    enemy_lst = v.user_tank_list
    t_speed = v.GUNNER_TANK_TURN
    max_tspeed = v.GUNNER_MAX_TURN_SPEED
    atk_range = v.GUNNER_ATTACK_RANGE
    min_range = v.GUNNER_MINIMUM_RANGE
    shell_speed = v.GUNNER_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def friendly_gunner_think(tank):
    fd_speed = v.GUNNER_TANK_SPEED
    enemy_lst = v.enemy_tank_list
    t_speed = v.GUNNER_TANK_TURN
    max_tspeed = v.GUNNER_MAX_TURN_SPEED
    atk_range = v.GUNNER_ATTACK_RANGE
    min_range = v.GUNNER_MINIMUM_RANGE
    shell_speed = v.GUNNER_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def enemy_scout_think(tank):
    fd_speed = v.SCOUT_TANK_SPEED
    enemy_lst = v.user_tank_list
    t_speed = v.SCOUT_TANK_TURN
    max_tspeed = v.SCOUT_MAX_TURN_SPEED
    atk_range = v.SCOUT_ATTACK_RANGE
    min_range = v.SCOUT_MINIMUM_RANGE
    shell_speed = v.TANK_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def friendly_scout_think(tank):
    fd_speed = v.SCOUT_TANK_SPEED
    enemy_lst = v.enemy_tank_list
    t_speed = v.SCOUT_TANK_TURN
    max_tspeed = v.SCOUT_MAX_TURN_SPEED
    atk_range = v.SCOUT_ATTACK_RANGE
    min_range = v.SCOUT_MINIMUM_RANGE
    shell_speed = v.TANK_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def enemy_sniper_think(tank):
    fd_speed = v.SNIPER_TANK_SPEED
    enemy_lst = v.user_tank_list
    t_speed = v.SNIPER_TANK_TURN
    max_tspeed = v.SNIPER_MAX_TURN_SPEED
    atk_range = v.SNIPER_ATTACK_RANGE
    min_range = v.SNIPER_MINIMUM_RANGE
    shell_speed = v.TANK_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def friendly_sniper_think(tank):
    fd_speed = v.SNIPER_TANK_SPEED
    enemy_lst = v.enemy_tank_list
    t_speed = v.SNIPER_TANK_TURN
    max_tspeed = v.SNIPER_MAX_TURN_SPEED
    atk_range = v.SNIPER_ATTACK_RANGE
    min_range = v.SNIPER_MINIMUM_RANGE
    shell_speed = v.TANK_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def enemy_tank_think(tank):
    fd_speed = v.ENEMY_TANK_SPEED
    enemy_lst = v.user_tank_list
    t_speed = v.ENEMY_TANK_TURN
    max_tspeed = v.ENEMY_MAX_TURN_SPEED
    atk_range = v.ENEMY_ATTACK_RANGE
    min_range = v.ENEMY_MINIMUM_RANGE
    shell_speed = v.TANK_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def friendly_tank_think(tank):
    fd_speed = v.FRIENDLY_TANK_SPEED
    enemy_lst = v.enemy_tank_list
    t_speed = v.FRIENDLY_TANK_TURN
    max_tspeed = v.FRIENDLY_MAX_TURN_SPEED
    atk_range = v.FRIENDLY_ATTACK_RANGE
    min_range = v.FRIENDLY_MINIMUM_RANGE
    shell_speed = v.TANK_SHELL_SPEED
    return think(tank, fd_speed, enemy_lst, t_speed, max_tspeed, atk_range, min_range, shell_speed)

def think(tank, foward_speed, enemy_lst, t_speed, max_tspeed,
          atk_range, min_range, shell_speed):
    fd_speed = v.TANK_SPEED
    turn_speed = 0
    fire = False
#    tank.clear() ##DEV MODE
    if len(enemy_lst) > 0:
        turn_speed, fire = attack(tank, enemy_lst, atk_range, shell_speed, t_speed)
        check_walls(tank, turn_speed)
        fd_speed = move(tank, enemy_lst, foward_speed, atk_range, min_range)
    if not fire:
        turn_speed = check_walls(tank, turn_speed)
    if abs(turn_speed) > v.TANK_FIRE_TOLORANCE:
        fire = False
    if turn_speed >= 0:
        turn_speed = min([turn_speed, max_tspeed])
    else:
        turn_speed = max([turn_speed, -max_tspeed])
    return turn_speed, fd_speed, fire

def flee(tank, enemies, a_range, turn_speed=False):
    tank2 = enemies[find_closest_in_list(tank, enemies)]
    if tank.distance(tank2) < a_range:
        turn = (tank.towards(tank2)+180)%360
        if turn > 180:
            turn = -(360-turn)
        turn_speed = turn
    return turn_speed

def attack(tank, lst, a_range, shell_speed, turn_rate):
    index = find_closest_in_list(tank, lst)
    tank2 = lst[index]
    if tank.distance(tank2) < a_range and line_of_sight(tank, tank2):
        new_heading = find_intercept_heading(tank, tank2, shell_speed)
        turn = (new_heading - tank.heading())%360
        if turn > 180:
            turn = -(360-turn)
        turn_speed = turn
        fire = True
    else:
        turn_speed = random.uniform(-turn_rate, turn_rate)
        fire = False
    return turn_speed, fire

def find_intercept_heading(origin_tank, tank, shot_speed):
    if tank.forward_speed == 0 or origin_tank.distance(tank) < v.TANK_MINIMUM_RANGE:
        return origin_tank.towards(tank)
    heading = math.radians(tank.heading())
    tank_speed = tank.forward_speed
    x_change = math.cos(heading) * tank_speed
    y_change = math.sin(heading) * tank_speed
    (x2, y2) = tank.pos()
    origin = origin_tank.pos()
    p1x, p1y = (x2-origin[0]), (y2-origin[1])
    p2x, p2y = (p1x+x_change), (p1y+y_change)
    t1x, t1y = (0, origin_tank.distance(p1x, p1y))
    t2x, t2y = (1, origin_tank.distance(p2x, p2y))
    (slope, b) = generate_line((t1x,t1y),(t2x,t2y))
    time = b / (shot_speed-slope)
    (x,y) = (x2+x_change*time), (y2+y_change*time)
    heading = origin_tank.towards((x,y))
    return heading

def generate_line(p1, p2):
    xchange = p2[0]-p1[0]
    ychange = p2[1]-p1[1]
    try:
        slope = ychange/xchange
    except ZeroDivisionError:
        print("Tried to divide by zero! Didn't work out :/")
        slope = 1000000
    b = p1[1] - p1[0]*slope
    return (slope, b)

def find_closest_in_list(tank, lst):
    dist_list = [distance(tank.pos(), tnk.pos()) for tnk in lst]
    return dist_list.index(min(dist_list))

def distance(p1, p2):
    return ((p1[0]-p2[0])**2+(p1[1]-p2[1])**2)**.5

def check_walls(tank, turn):
    dist_list = [wall.distance_to_wall(tank.pos())[0] for wall in v.wall_list]
    index = dist_list.index(min(dist_list))
    if dist_list[index] < v.TANK_COLLISION:
        tank.hp = 0
    close_wall = v.wall_list[index]
    point = close_wall.distance_to_wall(tank.pos())[1]
####THE FOLLOWING CODE IS FOR DEV MODE###
    original = tank.pos() 
    tank.clear()
    tank.goto(point)
    tank.dot()
    tank.goto(original)
###end
    away = (tank.towards(point)-180)%360
    away_turn = (away-tank.heading())%360
    if away_turn > 180:
        away_turn = -(360-turn)
    return factor_distance_to_wall(dist_list[index], away_turn, turn)

def factor_distance_to_wall(dist, away, turn):
    total = [v.WALL_BOUND/dist, dist/v.WALL_BOUND]
    weights = [total[0]/sum(total), total[1]/sum(total)]
    final = away*weights[0] + turn*weights[1]
    return final

def move(tank, enemy_lst, speed, atk_range, min_range):
    index = find_closest_in_list(tank, enemy_lst)
    tank2 = enemy_lst[index]
    dist = tank.distance(tank2)
    if tank.distance(tank2) < atk_range:
        max_range = atk_range
        factor = cosine_interpolation_factor(dist, max_range, min_range)
        speed = speed*factor - (min_range/max_range)*speed
    return speed

def cosine_interpolation_factor(dist, max_dist, min_dist):
    rad = (math.pi/2.0)/(max_dist) * dist
    factor = math.sin(rad)
#    translation = (max_dist*factor-min_dist)/max_dist
    return factor#translation

def line_of_sight(tank1, tank2):
    for wall in v.wall_list:
        if wall.wall_path_intersect(tank1.pos(), tank2.pos()):
            return False
    return True
