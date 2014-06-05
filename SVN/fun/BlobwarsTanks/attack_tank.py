import turtle
import variables as v
import ai as ai
import projectiles
from projectiles import TankShell
from projectiles import Bullet
from projectiles import SniperShell
from projectiles import GunnerShell

class Aimer(turtle.Turtle):
    def __init__(self, parent, color1, color2, distance):
        super().__init__()
        self.parent = parent
        self.fire = color1
        self.wait = color2
        self.distance = distance
        self.step = 0
        self.shape("Aimer")
        self.pu()
        self.pencolor(color1)

    def ready(self):
        self.pencolor(self.fire)

    def reloading(self):
        self.pencolor(self.wait)

    def aim(self):
        pos = ai.get_aimer_position(self)
        self.goto(pos)

    def run(self):
        self.aim()
        self.step += v.AIMER_STEP_SIZE
        if self.step > self.distance:
            self.step = 0

class Tank(turtle.Turtle):
    def __init__(self, start=v.TANK_START, heading=v.TANK_HEADING, pencolor="black", hidden=False):
        super().__init__()
        if hidden:
            self.ht()
        self.pu()
        self.goto(start)
        self.pencolor(pencolor)
        self.setheading(heading)
        self.shape("Tank")
        self.turn_speed = 0
        self.forward_speed = 0
        self.timer = 0
        self.hp = v.TANK_HP
        self.collision_range = v.TANK_COLLISION
        self.projectile = TankShell
        self.projectiles = v.enemy_projectile_list

    def think(self):
        pass

    def turn(self):
        self.lt(self.turn_speed)

    def move(self):
        self.fd(self.forward_speed)

    def fire(self):
        if self.timer <= 0:
            shot = self.projectile(self.pos(), self.heading())
            self.timer = shot.fire_rate
            self.projectiles.append(shot)

    def live(self):
        if self.hp <= 0:
            v.TANK_DEATH(self)

    def check_walls(self):
        dist_list = [wall.distance_to_wall(self.pos())[0] for wall in v.wall_list]
        if min(dist_list) < self.collision_range:
            wall = v.wall_list[dist_list.index(min(dist_list))]
            self.collision(wall)
            wall.live()

    def check_collision(self, obj):
        if self.distance(obj) < self.collision_range:
            self.collision(obj)

    def collision(self, obj):
        if obj.hp > self.hp:
            obj.hp -= self.hp
            self.hp = 0
        else:
            self.hp -= obj.hp
            obj.hp = 0
        obj.live()
        self.live()

    def run(self):
        if self.timer > 0:
            self.timer -= 1
        self.think()
        self.turn()
        self.move()
        self.check_walls()
        self.live()

class UserTank(Tank):
    def __init__(self, controls, start=v.TANK_START,
                 heading=v.TANK_HEADING, aimer=v.USER_HAS_AIMER):
        super().__init__(start, heading)
        self.prepare_listeners(controls)
        self.pencolor(v.USER_TANK_COLOR)
        self.hp = v.USER_TANK_HP
        self.reset_hp = v.USER_TANK_HP
        self.primary = TankShell
        self.secondary = Bullet
        self.projectiles = v.friendly_projectile_list
        self.clas = "Tank"
        self.mv_turn = v.USER_TANK_TURN_SPEED
        self.mv_fd = v.USER_TANK_FORWARD_SPEED
        if aimer:
            self.aimer = Aimer(self, v.USER_AIMER_COLOR1,
                               v.USER_AIMER_COLOR2, v.USER_AIMER_LENGTH)
        else:
            self.aimer = aimer


    def prepare_listeners(self, controls):
        turtle.onkeypress(self.left, controls[0])
        turtle.onkeypress(self.right, controls[1])
        turtle.onkeypress(self.forward, controls[2])
        turtle.onkeypress(self.backward, controls[3])
        turtle.onkeypress(self.fire_primary, controls[4])
        turtle.onkeypress(self.fire_secondary, controls[5])
        turtle.onkeypress(self.change_class, controls[6])

        turtle.onkeyrelease(self.stop_turn, controls[0])
        turtle.onkeyrelease(self.stop_turn, controls[1])
        turtle.onkeyrelease(self.stop_move, controls[2])
        turtle.onkeyrelease(self.stop_move, controls[3])

    def change_class(self):
        index = v.CLASS_LIST.index(self.clas)
        self.clas = v.CLASS_LIST[index-1]
        projectiles.set_user_weapons(self)
        set_user_atts(self)
        v.user_class_copy = self
        self.hp = 0

    def left(self):
        self.turn_speed = self.mv_turn

    def right(self):
        self.turn_speed = -self.mv_turn

    def forward(self):
        self.forward_speed = self.mv_fd

    def backward(self):
        self.forward_speed = -self.mv_fd

    def stop_turn(self):
        self.turn_speed = 0

    def stop_move(self):
        self.forward_speed = 0

    def fire_primary(self):
        if self.timer == 0:
            shot = self.primary(self.pos(), self.heading())
            self.timer = shot.fire_rate
            v.friendly_projectile_list.append(shot)

    def fire_secondary(self):
        if self.timer == 0:
            shot = self.secondary(self.pos(), self.heading())
            self.timer = shot.fire_rate
            v.friendly_projectile_list.append(shot)

    def check_walls(self):
        dist_list = [wall.distance_to_wall(self.pos())[0] for wall in v.wall_list]
        if min(dist_list) < self.collision_range:
            self.hp = 0

    def aim(self):
        if self. aimer:
            self.aimer.run()
            if self. timer > 0:
                self.aimer.reloading()
            else:
                self.aimer.ready()

    def time(self):
        if not self.isvisible():
            self.write(self.timer//v.TURTLE_UPDATE_RATE)

    def respawn(self):
        self.goto(v.TANK_START)
        self.hp = v.USER_TANK_HP
        self.setheading(v.TANK_HEADING)
        self.st()

    def run(self):
        super().run()
        self.check_walls()
        self.aim()

class AITank(Tank):
    def __init__(self, start, heading, pencolor, hp, think_method,
                 projectile_list, projectile):
        super().__init__(start, heading, pencolor)
        self.hp = hp
        self.ai = think_method
        self.projectiles = projectile_list
        self.projectile = projectile

    def think(self):
        self.turn_speed, self.forward_speed, fire = self.ai(self)
        if fire and self.timer == 0:
            self.timer -= 1

    def fire(self):
        shot = self.projectile(self.pos(), self.heading())
        self.timer = shot.fire_rate
        self.projectiles.append(shot)

    def run(self):
        super().run()
        if self.timer < 0:
            self.fire()

class FriendlyTank(AITank):
    def __init__(self, start=v.FRIENDLY_START,
                 h=v.FRIENDLY_TANK_HEADING, pc=v.FRIENDLY_COLOR):
        hp = v.FRIENDLY_TANK_HP
        think_method = ai.friendly_tank_think
        projectile_list = v.friendly_projectile_list
        choice = [TankShell, Bullet]
        chance = [v.TANK_SHELL_CHANCE, v.BULLET_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)

class EnemyTank(AITank):
    def __init__(self, start=v.ENEMY_START,
                 h=v.ENEMY_TANK_HEADING, pc=v.ENEMY_COLOR):
        hp = v.ENEMY_TANK_HP
        think_method = ai.enemy_tank_think
        projectile_list = v.enemy_projectile_list
        choice = [TankShell, Bullet]
        chance = [v.TANK_SHELL_CHANCE, v.BULLET_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)

class EnemySniper(AITank):
    def __init__(self, start=v.ENEMY_START,
                 h=v.ENEMY_TANK_HEADING, pc=v.ENEMY_COLOR):
        hp = v.SNIPER_TANK_HP
        think_method = ai.enemy_sniper_think
        projectile_list = v.enemy_projectile_list
        choice = [TankShell, SniperShell]
        chance = [v.TANK_SHELL_CHANCE, v.SNIPER_SHELL_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)
        self.collision_range = v.SNIPER_COLLISION
        self.shape("Sniper")

class FriendlySniper(AITank):
    def __init__(self, start=v.FRIENDLY_START,
                 h=v.FRIENDLY_TANK_HEADING, pc=v.FRIENDLY_COLOR):
        hp = v.SNIPER_TANK_HP
        think_method = ai.friendly_sniper_think
        projectile_list = v.friendly_projectile_list
        choice = [TankShell, SniperShell]
        chance = [v.TANK_SHELL_CHANCE, v.SNIPER_SHELL_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)
        self.collision_range = v.SNIPER_COLLISION
        self.shape("Sniper")

class EnemyScout(AITank):
    def __init__(self, start=v.ENEMY_START,
                 h=v.ENEMY_TANK_HEADING, pc=v.ENEMY_COLOR):
        hp = v.SCOUT_TANK_HP
        think_method = ai.enemy_scout_think
        projectile_list = v.enemy_projectile_list
        choice = [Bullet]
        chance = [v.BULLET_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)
        self.collision_range = v.SCOUT_COLLISION
        self.shape("Scout")

class FriendlyScout(AITank):
    def __init__(self, start=v.FRIENDLY_START,
                 h=v.FRIENDLY_TANK_HEADING, pc=v.FRIENDLY_COLOR):
        hp = v.SCOUT_TANK_HP
        think_method = ai.friendly_scout_think
        projectile_list = v.friendly_projectile_list
        choice = [Bullet]
        chance = [v.BULLET_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)
        self.collision_range = v.SCOUT_COLLISION
        self.shape("Scout")

class EnemyGunner(AITank):
    def __init__(self, start=v.ENEMY_START,
                 h=v.ENEMY_TANK_HEADING, pc=v.ENEMY_COLOR):
        hp = v.GUNNER_TANK_HP
        think_method = ai.enemy_gunner_think
        projectile_list = v.enemy_projectile_list
        choice = [TankShell, GunnerShell]
        chance = [v.TANK_SHELL_CHANCE, v.GUNNER_SHELL_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)
        self.collision_range = v.GUNNER_COLLISION
        self.shape("Gunner")

class FriendlyGunner(AITank):
    def __init__(self, start=v.FRIENDLY_START,
                 h=v.FRIENDLY_TANK_HEADING, pc=v.FRIENDLY_COLOR):
        hp = v.GUNNER_TANK_HP
        think_method = ai.friendly_gunner_think
        projectile_list = v.friendly_projectile_list
        choice = [TankShell, GunnerShell]
        chance = [v.TANK_SHELL_CHANCE, v.GUNNER_SHELL_CHANCE]
        projectile = ai.random_choice(choice, chance)
        super().__init__(start, h, pc, hp, think_method, projectile_list, projectile)
        self.collision_range = v.GUNNER_COLLISION
        self.shape("Gunner")

class EnemySpawn(EnemyTank):
    def __init__(self, start=v.ENEMY_START, h=v.ENEMY_SPAWN_HEADING, pc=v.ENEMY_COLOR):
        super().__init__(start, h, pc)
        self.collision_range = v.SPAWN_COLLISION
        self.shape("Spawn")
        self.hp = v.ENEMY_SPAWN_HP

    def think(self):
        self.turn_speed, self.forward_speed = ai.enemy_spawn_think(self)

    def fire(self):
        if self.timer <= 0:
            if len(v.enemy_tank_list) <= v.ENEMY_SPAWN_TRIGGER:
                while len(v.enemy_tank_list) <= v.TEAM_SIZE:
                    choice_list = [EnemyTank,EnemySniper,EnemyScout,EnemyGunner]
                    chance_list = [v.TANK_CHANCE,v.SNIPER_CHANCE,v.SCOUT_CHANCE,v.GUNNER_CHANCE]
                    choice = ai.random_choice(choice_list, chance_list)
                    v.enemy_tank_list.append(choice(self.pos(), self.heading()+180))
            self.timer = v.RESPAWN_TIME

    def run(self):
        super().run()
        if self.timer == 0:
            self.fire()
 
class FriendlySpawn(FriendlyTank):
    def __init__(self, start=v.FRIENDLY_START, h=v.FRIENDLY_SPAWN_HEADING, pc=v.FRIENDLY_COLOR):
        super().__init__(start, h, pc)
        self.collision_range = v.SPAWN_COLLISION
        self.shape("Spawn")
        self.hp = v.FRIENDLY_SPAWN_HP

    def think(self):
        self.turn_speed, self.forward_speed = ai.friendly_spawn_think(self)

    def new_user(self):
        new = v.user_class_copy
        new.st()
        new.hp = new.reset_hp
        new.goto(self.pos())
        new.setheading(self.heading()+180)
        return new

    def fire(self):
        if self.timer <= 0:
            if len(v.user_tank_list) <= v.FRIENDLY_SPAWN_TRIGGER:
                type_list = [type(tank) for tank in v.user_tank_list]
                if UserTank not in type_list:
                    v.user_tank_list.append(self.new_user())
                while len(v.user_tank_list) <= v.TEAM_SIZE:
                    choice_list = [FriendlyTank,FriendlySniper,FriendlyScout,FriendlyGunner]
                    chance_list = [v.TANK_CHANCE,v.SNIPER_CHANCE,v.SCOUT_CHANCE,v.GUNNER_CHANCE]
                    choice = ai.random_choice(choice_list, chance_list)
                    v.user_tank_list.append(choice(self.pos(), self.heading()+180))
            self.timer = v.RESPAWN_TIME

    def run(self):
        super().run()
        if self.timer == 0:
            self.fire()

def set_user_atts(user):
    if user.clas == "Tank":
        user.hp = v.TANK_HP
        user.reset_hp = v.TANK_HP
        user.mv_turn = v.TANK_TURN_RATE
        user.mv_fd = v.TANK_SPEED
        user.shape("Tank")
        user.collision_range = v.TANK_COLLISION
    elif user.clas == "Scout":
        user.hp = v.SCOUT_TANK_HP
        user.reset_hp = v.SCOUT_TANK_HP
        user.mv_turn = v.SCOUT_MAX_TURN_SPEED
        user.mv_fd = v.SCOUT_TANK_SPEED
        user.shape("Scout")
        user.collision_range = v.SCOUT_COLLISION
    elif user.clas == "Sniper":
        user.hp = v.SNIPER_TANK_HP
        user.reset_hp = v.SNIPER_TANK_HP
        user.mv_turn = v.SNIPER_MAX_TURN_SPEED
        user.mv_fd = v.SNIPER_TANK_SPEED
        user.shape("Sniper")
        user.collision_range = v.SNIPER_COLLISION
    elif user.clas == "Spawn":
        user.hp = v.SPAWN_HP
        user.reset_hp = v.SPAWN_HP
        user.mv_turn = v.SPAWN_TURN_RATE
        user.mv_fd = v.SPAWN_SPEED
        user.shape("Spawn")
        user.collision_range = v.SPAWN_COLLISION

def initialize_user_copy():
    v.user_class_copy = UserTank(v.USER_TANK_CONTROLS)
