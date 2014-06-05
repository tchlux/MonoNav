import turtle
import variables as v


class Projectile(turtle.Turtle):
    def __init__(self, pos, heading):
        super().__init__()
        self.pu()
        self.goto(pos)
        self.seth(heading)
        self.speed = 0
        self.hp = 1
        self.range = 100
        self.distance = 0

    def move(self):
        self.fd(self.speed)
        self.distance += self.speed

    def hit(self):
        v.REMOVE_PROJECTILE(self, True)

    def check_collision(self, enemies):
        for tank in enemies:
            tank.check_collision(self)

    def live(self):
        if self.hp <= 0:
            v.REMOVE_PROJECTILE(self, True)
            return None
        x, y = self.pos()
        dist_list = [wall.distance_to_wall(self.pos())[0] for wall in v.wall_list]
        case1 = abs(x)>v.INIT_WINDOW_WIDTH/2.0
        case2 = abs(y)>v.INIT_WINDOW_HEIGHT/2.0
        case3 = self.distance > self.range
        case4 = min(dist_list) < v.PROJECTILE_WALL_COLLISION
        if case1 or case2 or case3:
            v.REMOVE_PROJECTILE(self, False)
        if case4:
            v.REMOVE_PROJECTILE(self, True)
            wall = v.wall_list[dist_list.index(min(dist_list))]
            wall.hp -= self.hp
            wall.live()

    def run(self):
        self.move()
        self.live()

class FakeProjectile(Projectile):
    def __init__(self, pos, head):
        super().__init__(pos, head)
        self.fire_rate = 0
        self.hp = 0

class TankShell(Projectile):
    def __init__(self, pos, heading):
        super().__init__(pos, heading)
        self.speed = v.TANK_SHELL_SPEED
        self.hp = v.TANK_SHELL_HP
        self.shape("TankShell")
        self.pencolor(v.TANK_SHELL_COLOR)
        self.range = v.TANK_SHELL_RANGE
        self.fire_rate = v.TANK_SHELL_FIRE_RATE

class Bullet(Projectile):
    def __init__(self, pos, heading):
        super().__init__(pos, heading)
        self.speed = v.BULLET_SPEED
        self.hp = v.BULLET_HP
        self.shape("Bullet")
        self.pencolor(v.BULLET_COLOR)
        self.range = v.BULLET_RANGE
        self.fire_rate = v.BULLET_FIRE_RATE

class SniperShell(Projectile):
    def __init__(self, pos, heading):
        super().__init__(pos, heading)
        self.speed = v.SNIPER_SHELL_SPEED
        self.hp = v.SNIPER_SHELL_HP
        self.shape("SniperShell")
        self.pencolor(v.SNIPER_SHELL_COLOR)
        self.range = v.SNIPER_SHELL_RANGE
        self.fire_rate = v.SNIPER_SHELL_FIRE_RATE

class GunnerShell(Projectile):
    def __init__(self, pos, heading):
        super().__init__(pos, heading)
        self.speed = v.GUNNER_SHELL_SPEED
        self.hp = v.GUNNER_SHELL_HP
        self.shape("GunnerShell")
        self.pencolor(v.GUNNER_SHELL_COLOR)
        self.range = v.GUNNER_SHELL_RANGE
        self.fire_rate = v.GUNNER_SHELL_FIRE_RATE

def set_user_weapons(user):
    if user.clas == "Tank":
        user.primary = TankShell
        user.secondary = Bullet
    elif user.clas == "Scout":
        user.primary = Bullet
        user.secondary = Bullet
    elif user.clas == "Sniper":
        user.primary = SniperShell
        user.secondary = Bullet
    elif user.clas == "Spawn":
        user.primary = FakeProjectile
        user.secondary = FakeProjectile
