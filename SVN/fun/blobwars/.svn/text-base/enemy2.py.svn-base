import turtle
import random

RADIUS = 7
SPEED = 3
INIT_X = 0
INIT_Y = 0
HEALTH = 5
IMAGE = "Enemy1.gif"
SPAWNER_RATIO = .0125
HERO_RATIO = .005
AGGRESSIVE_HERO_RATIO = .2
EVADE_DISTANCE = 20
BULLETS_RATIO = .2
PASSIVE_SPEED = 1
AGRESSIVE_SPEED = 3

class Stringer:

    def __init__(self, health, radius, image, x, y, heading, state="aggressive"):
        self.turtle = turtle.Turtle()
        self.turtle.shape(image)
        self.turtle.penup()
        self.health = health
        self.radius = radius
        self.last_heading = 0
        self.speed = AGRESSIVE_SPEED
        self.turtle.goto(x,y)
        self.turtle.setheading(heading)
        self.state = state

    def get_closest_turn(self, turn):
        if turn > 180:
            turn = turn - 360
        if turn < -180:
            turn = turn + 360
        return turn

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance

    def keep_on_screen(self):
        (half_window_width) = turtle.window_width() / 2
        (half_window_height) = turtle.window_height() / 2
        if (math.fabs(self.x) > half_window_width):
            new_heading = 180 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
        elif (math.fabs(self.y) > half_window_height):
            new_heading = 360 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
        else:
            turn = random.randint(-2,2)
        return turn

    def track_spawners(self, spawners):
        turn = 0
        shortest_distance = 10000
        for spawner in spawners:
            dist = self.turtle.distance(spawner.turtle)
            if dist < shortest_distance:
                shortest_distance = dist
                new = self.turtle.towards(spawner.turtle)
                turn = new - self.turtle.heading()
        return turn

    def track_bullets(self, bullets):
        turn = 0
        shortest_distance = 10000
        for bullet in bullets:
            dist = self.turtle.distance(bullet.turtle)
            if dist < shortest_distance:
                shortest_distance = dist
                new = self.turtle.towards(bullet.turtle)
                turn = new - self.turtle.heading()
        if turn > 180:
            turn -= 180
        else:
            turn += 180
        return turn

    def track_blob_hero(self, hero):
        turn = 0
        new_heading = self.turtle.towards(hero.turtle.pos())
        turn = (new_heading - self.turtle.heading())
        self.closest_hero = self.turtle.distance(hero.turtle)
        return turn

    def factor_final_turn(self, enemies_list, spawners_list, hero, blobs, bullet_list):
        turn = 0
        wall = self.get_closest_turn(self.keep_on_screen())
        spawner = self.get_closest_turn(self.track_spawners(spawners_list))
        hero = self.get_closest_turn(self.track_blob_hero(hero))
        bullets = self.get_closest_turn(self.track_bullets(bullet_list))
        if self.state == 'passive':
            turn += (spawner)*SPAWNER_RATIO
            self.speed = PASSIVE_SPEED
        elif self.state == 'aggressive':
            turn += (hero) * AGGRESSIVE_HERO_RATIO
            self.speed = AGGRESSIVE_SPEED
        elif self.state == 'evasive':
            if len(bullet_list) > 0:
                turn += bullets * BULLETS_RATIO
            else:
                turn += (spawner)*SPAWNER_RATIO
        if self.shortest_distance_to_nearest_friend < EVADE_DISTANCE:
            temp = self.get_closest_turn(self.heading_to_nearest_friend)
            turn = (temp - self.turtle.heading())*COLLISION_RATIO
        if (wall > 2) or (wall < -2):
            turn = wall
        return turn

    def update(self, spawners_list, hero, bullets):
        (self.x, self.y) = self.turtle.pos()
        self.last_heading = self.turtle.heading()
        self.heading = self.turtle.heading()
        turn = self.factor_final_turn(spawners_list, hero, bullets)
        self.turtle.left(turn)
        self.turtle.forward(self.speed)
        (half_window_width) = turtle.window_width() / 2
        (half_window_height) = turtle.window_height() / 2
        if (math.fabs(self.x) > (half_window_width+5)) or (math.fabs(self.y) > (half_window_height+5)):
            self.health = 0

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
