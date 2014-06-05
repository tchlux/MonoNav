#!/usr/bin/env python3

import turtle
import variables as v
import attack_tank
from wall import Wall
import random as r
from multiprocessing import Process

class Game:
    def __init__(self):
        self.prepare_turtle()
        self.prepare_map()
        self.prepare_tanks()
        self.time = 0

    def prepare_tanks(self):
        attack_tank.initialize_user_copy()
        v.enemy_tank_list.append(attack_tank.EnemySpawn())
        v.user_tank_list.append(attack_tank.FriendlySpawn())

    def prepare_turtle(self):
        turtle.register_shape("Bullet", v.BULLET)
        turtle.register_shape("TankShell", v.TANK_SHELL)
        turtle.register_shape("SniperShell", v.SNIPER_SHELL)
        turtle.register_shape("GunnerShell", v.GUNNER_SHELL)
        turtle.register_shape("Tank", v.TANK)
        turtle.register_shape("Spawn", v.SPAWN)
        turtle.register_shape("Sniper", v.SNIPER)
        turtle.register_shape("Scout", v.SCOUT)
        turtle.register_shape("Gunner", v.GUNNER)
        turtle.register_shape("Aimer", v.AIMER)
        turtle.bgcolor(v.BACKGROUND_COLOR)
        turtle.tracer(0)
        turtle.listen()
        turtle.setup(width=v.INIT_WINDOW_WIDTH, height=v.INIT_WINDOW_HEIGHT)

    def prepare_map(self):
        #   This uses globals from rooms_for_simulator.py to build the
        #   rooms, some options are listed below
        #  TRIANGLE  #  BOX  #  TRAPEZOID  #  OCTAGON  #  CAVE  #  FOX 
        self.turn_points_into_walls(v.MAP)
        self.make_random_obstacles()

    def make_random_obstacles(self):
        for i in range(r.randint(0,v.NUMBER_OF_ROCKS)):
            x = r.uniform(-v.X_ROCK_AREA, v.X_ROCK_AREA)
            y = r.uniform(-v.Y_ROCK_AREA, v.Y_ROCK_AREA)
            rock = []
            self.turn_points_into_walls(v.ROCK, x, y, v.ROCK_HP, rock)
            

    #Method:This method uses a variable number of (x,y) points sent to
    #       it to rebuild a room
    def turn_points_into_walls(self, points, ox=0, oy=0,
                               hp=float("inf"), lst=[]):
        unit = v.BATTLEFIELD_LENGTH // 10
        for item in points:
            x = item[0]*unit + ox
            y = item[1]*unit + oy
            lst.append((x,y))
        for i in range(len(lst)):
            p1 = (lst[i-1][0], lst[i-1][1])
            p2 = (lst[i][0], lst[i][1])
            v.wall_list.append(Wall(p1,p2,hp))


    def dev_print(self):
        if self.time == 0:
            num = (len(v.user_tank_list) + len(v.enemy_tank_list) +
                   len(v.friendly_projectile_list) +
                   len(v.enemy_projectile_list))
            print("Number of turtles: %f"%num)
            self.time = v.DEV_PRINT_TIMER
        else:
            self.time -= 1

    def mainloop(self):
#        self.dev_print()
        for tank in v.user_tank_list:
            tank.run()
        for tank in v.enemy_tank_list:
            tank.run()
        for projectile in v.friendly_projectile_list:
#            projectile.pencolor(v.FRIENDLY_COLOR)
            projectile.run()
            projectile.check_collision(v.enemy_tank_list)
        for projectile in v.enemy_projectile_list:
#            projectile.pencolor(v.ENEMY_COLOR)
            projectile.run()
            projectile.check_collision(v.user_tank_list)
        turtle.update()
        turtle.ontimer(self.mainloop, v.TURTLE_UPDATE_RATE)

if __name__ == "__main__":
    game = Game()
    game.mainloop()
    turtle.mainloop()
