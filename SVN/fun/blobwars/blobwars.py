#!/usr/bin/env python3
import variables
import lists
import blobhero
import enemy1
import enemy2
import bullet
import missile
import enemyspawn
import blobfriend
import blobbomber
import defense
import animation
import blackhole
######################
import turtle
import random
import math

class BlobWars:

#initializes all turtles, lists, blobs, etc everything to start the game, the variables are done seperately and first
    def __init__(self):
        self.variables = variables.Variables()
        self.init_turtle()
        self.init_blobs()

#initializes all images
#initializes listen for all key strokes and sets cases
#initializes window height and width
    def init_turtle(self):
        turtle.addshape("BlobHeroOpen0.gif")
        turtle.addshape("BlobHeroOpen15.gif")
        turtle.addshape("BlobHeroOpen30.gif")
        turtle.addshape("BlobHeroOpen45.gif")
        turtle.addshape("BlobHeroOpen60.gif")
        turtle.addshape("BlobHeroOpen75.gif")
        turtle.addshape("BlobHeroOpen90.gif")
        turtle.addshape("BlobHeroOpen105.gif")
        turtle.addshape("BlobHeroOpen120.gif")
        turtle.addshape("BlobHeroOpen135.gif")
        turtle.addshape("BlobHeroOpen150.gif")
        turtle.addshape("BlobHeroOpen165.gif")
        turtle.addshape("BlobHeroOpen180.gif")
        turtle.addshape("BlobHeroOpen195.gif")
        turtle.addshape("BlobHeroOpen210.gif")
        turtle.addshape("BlobHeroOpen225.gif")
        turtle.addshape("BlobHeroOpen240.gif")
        turtle.addshape("BlobHeroOpen255.gif")
        turtle.addshape("BlobHeroOpen270.gif")
        turtle.addshape("BlobHeroOpen285.gif")
        turtle.addshape("BlobHeroOpen300.gif")
        turtle.addshape("BlobHeroOpen315.gif")
        turtle.addshape("BlobHeroOpen330.gif")
        turtle.addshape("BlobHeroOpen345.gif")
        turtle.addshape("BlobFriend0.gif")
        turtle.addshape("BlobFriend45.gif")
        turtle.addshape("BlobFriend90.gif")
        turtle.addshape("BlobFriend135.gif")
        turtle.addshape("BlobFriend180.gif")
        turtle.addshape("BlobFriend225.gif")
        turtle.addshape("BlobFriend270.gif")
        turtle.addshape("BlobFriend315.gif")
        turtle.addshape("BlobBomber0.gif")
        turtle.addshape("Missile0.gif")
        turtle.addshape("Missile22.gif")
        turtle.addshape("Missile45.gif")
        turtle.addshape("Missile67.gif")
        turtle.addshape("Missile90.gif")
        turtle.addshape("Missile112.gif")
        turtle.addshape("Missile135.gif")
        turtle.addshape("Missile157.gif")
        turtle.addshape("Missile180.gif")
        turtle.addshape("Missile202.gif")
        turtle.addshape("Missile225.gif")
        turtle.addshape("Missile247.gif")
        turtle.addshape("Missile270.gif")
        turtle.addshape("Missile292.gif")
        turtle.addshape("Missile315.gif")
        turtle.addshape("Missile337.gif")
        turtle.addshape("FireDeath0.gif")
        turtle.addshape("FireDeath1.gif")
        turtle.addshape("FireDeath2.gif")
        turtle.addshape("FireDeath3.gif")
        turtle.addshape("FireDeath4.gif")
        turtle.addshape("FireDeath5.gif")
        turtle.addshape("FireDeath6.gif")
        turtle.addshape("FireDeath7.gif")
        turtle.addshape("FireDeath8.gif")
        turtle.addshape("FireDeath9.gif")
        turtle.addshape("Enemy1.gif")
        turtle.addshape("Bullet.gif")
        turtle.addshape("EnemySpawn.gif")
        turtle.addshape("Ice.gif")
        turtle.addshape("Mothership.gif")
        turtle.addshape("Shield.gif")
        turtle.addshape("PortableShield.gif")
        turtle.addshape("Blackhole1.gif")
        turtle.addshape("Blackhole2.gif")
        turtle.addshape("Blackhole3.gif")
        turtle.addshape("Blackhole4.gif")
        turtle.addshape("Blackhole5.gif")
        turtle.tracer(0)
        turtle.listen()
        turtle.onkeypress(self.handle_left_arrow, "Left")
        turtle.onkeyrelease(self.handle_turn_release, "Left")
        turtle.onkeypress(self.handle_right_arrow, "Right")
        turtle.onkeyrelease(self.handle_turn_release, "Right")
        turtle.onkeypress(self.handle_up_arrow, "Up")
        turtle.onkeypress(self.handle_down_arrow, "Down")
        turtle.onkeypress(self.handle_space_bar, "space")
        turtle.onkeypress(self.handle_b_key, "b")
        turtle.onkeypress(self.handle_z_key, "z")
        turtle.onkeypress(self.handle_x_key, "x")
        turtle.onkeypress(self.handle_c_key, "c")
        turtle.onkeypress(self.handle_v_key, "v")
        turtle.onkeypress(self.handle_f_key, "f")
        turtle.onkeypress(self.handle_p_key, "p")
        turtle.onkeypress(self.handle_g_key, "g")
        turtle.onkeypress(self.help, "h")
        turtle.setup(width=self.variables.INIT_WINDOW_WIDTH, height=self.variables.INIT_WINDOW_HEIGHT)

#initializes the hero, all the reset timers, and all the lists of objects
    def init_blobs(self):
        self.blobhero = blobhero.BlobHero()
        self.stat_pen = turtle.Turtle()
        self.stat_pen.penup()
        self.stat_pen.hideturtle()
        self.pause_pen = turtle.Turtle()
        self.pause_pen.hideturtle()
        self.game_over_bool = False
        self.game_timer = 0
        self.score = 0
        self.kill_count = 0
        self.bullet_timer = 0
        self.ice_timer = 0
        self.shotgun_timer = 0
        self.missile_timer = 0
        self.mothership_spawn_timer = 0
        self.enemy1_spawn_timer = 0
        self.portable_shield_reset_timer = 0
        self.shield_reset_timer = 0
        self.stationary_shield_powerout_timer = 0
        self.stationary_shield_reset_timer = 0
        self.blackhole_reset_timer = 0
        self.pause_timer = 0
        self.lists = lists.Lists()

#takse an input variable and sets it to false
    def variable_to_false(self):
        self.press = False

#calls move_forward in the BlobHero class (blobhero.py)
    def handle_up_arrow(self):
        self.blobhero.move_forward()

#calls move_backward in the BlobHero class (blobhero.py)
    def handle_down_arrow(self):
        self.blobhero.move_backward()

#calls turn_left in BlobHero class (blobhero.py)
    def handle_left_arrow(self):
        self.blobhero.turn_left()

#calls turn_right in BlobHero class (blobhero.py)
    def handle_right_arrow(self):
        self.blobhero.turn_right()

    def handle_turn_release(self):
        self.blobhero.stop_turn()

#reverses the heading of the blobhero
    def handle_f_key(self):
        heading = self.blobhero.turtle.heading()
        heading = heading - 180
        self.blobhero.turtle.setheading(heading)

#pauses the game, turtle is still running so machine speed may be slowed
    def handle_p_key(self):
        if self.pause_timer == 0:
            self.pause_timer = 1
        elif self.pause_timer == 1:
            self.pause_timer = 0
        self.write_pause()

#stationary bubble shield deploy
#checks if another bubbleshield can be deployed based on the number of defenses currently being tracked
#adds a stationary bubble shield to the list of defenses
#starts the reset timer for stationary shields
    def handle_b_key(self):
        if len(self.lists.defenses) < self.variables.MAX_DEFENSES:
            (hero_x, hero_y) = self.blobhero.turtle.pos()
            self.lists.defenses.append(defense.Shield(self.variables.STATIONARY_SHIELD_RADIUS, self.variables.STATIONARY_SHIELD_STRENGTH, self.variables.STATIONARY_SHIELD_IMAGE, hero_x, hero_y, self.variables.STATIONARY_SHIELD_POWEROUT_TIMER))
            self.stationary_shield_reset_timer += 1

#blobfriend turret deploy
#if the user can have 3 or more friends, the last is a missiles, the second to last is a shotgun, the rest are bullets
#if the user can only deploy fewer than 3 friends, they are all bullet friends
    def handle_z_key(self):
        (hero_x, hero_y) = self.blobhero.turtle.pos()
        if (len(self.lists.blobfriends) + len(self.lists.blobbombers)) < self.variables.MAX_BLOBFRIENDS:
            if len(self.lists.blobfriends) == (self.variables.MAX_BLOBFRIENDS-1):
                self.lists.blobbombers.append(blobbomber.BlobBomber(self.variables.BLOBBOMBER_HEALTH,self.variables.BLOBBOMBER_RADIUS, self.variables.BLOBBOMBER_SPEED ,hero_x,hero_y, self.variables.BLOBBOMBER_FIRE_RATE))
            else:
                self.lists.blobfriends.append(blobfriend.BlobFriend(self.variables.BLOBFRIEND_HEALTH,self.variables.BLOBFRIEND_RADIUS, self.variables.BLOBFRIEND_SPEED ,hero_x,hero_y,'bullet', self.variables.BLOBFRIEND_FIRE_RATE_BULLET))

#shoots bullet
#checks to see if bullet_timer has reset
#appends a bullet object to the bullets list
#re-begins the bullet timer
    def handle_space_bar(self):
        if self.bullet_timer == 0:
            (hero_x, hero_y) = self.blobhero.turtle.pos()
            heading = self.blobhero.turtle.heading()
            self.lists.bullets.append(bullet.Bullet(self.variables.BULLET_SPEED, self.variables.BULLET_RADIUS, self.variables.BULLET_IMAGE, self.variables.BULLET_DAMAGE, hero_x, hero_y, heading))
            self.bullet_timer += 1

#shoots iceball
#checks to see if ice_timer has reset
#appends ice object to bullets list
#re-begins the ice timer
    def handle_c_key(self):
        if self.ice_timer == 0:
            (hero_x, hero_y) = self.blobhero.turtle.pos()
            heading = self.blobhero.turtle.heading()
            self.lists.bullets.append(bullet.Bullet(self.variables.ICE_SPEED, self.variables.ICE_RADIUS, self.variables.ICE_IMAGE, self.variables.ICE_DAMAGE, hero_x, hero_y, heading, self.variables.FREEZE))
            self.ice_timer += 1

#shoots shotgun
#checks if shotgun timer has reset
#appends 7 bullets to bullets list in random headings of range (-15,15)
#re-begins shotgun timer
    def handle_v_key(self):
        if self.shotgun_timer == 0:
            self.shotgun_timer += 1
            (hero_x, hero_y) = self.blobhero.turtle.pos()
            min_heading = int(self.blobhero.turtle.heading() - (self.variables.SHOTGUN_SPREAD//2))
            for i in range(7):
                random_heading = random.randint(min_heading, min_heading+self.variables.SHOTGUN_SPREAD)
                self.lists.bullets.append(bullet.Bullet(self.variables.BULLET_SPEED, self.variables.BULLET_RADIUS, self.variables.BULLET_IMAGE, self.variables.SHOTGUN_DAMAGE, hero_x, hero_y, random_heading))

#shoots homing missile
#checks if missile timer has reset
#appends one missile to missiles list
#resets missile timer
    def handle_x_key(self):
        if self.missile_timer == 0:
            (hero_x, hero_y) = self.blobhero.turtle.pos()
            heading = self.blobhero.turtle.heading()
            self.lists.missiles.append(missile.Missile(self.variables.MISSILE_SPEED, self.variables.MISSILE_RADIUS, self.variables.MISSILE_DAMAGE, hero_x, hero_y, heading))
            self.missile_timer += 1

#spawns blackhole
#checks if blackhole timer has reset
#appends one blackhole to the blackholes list
#resets blackhole timer
    def handle_g_key(self):
        if (self.blackhole_reset_timer == 0) and (len(self.lists.blackholes) < self.variables.BLACKHOLE_MAX_COUNT):
            (hero_x, hero_y) = self.blobhero.turtle.pos()
            self.lists.blackholes.append(blackhole.Blackhole(hero_x, hero_y, self.variables.BLACKHOLE_RADIUS, self.variables.BLACKHOLE_DAMAGE, self.variables.BLACKHOLE_DURATION, self.variables.BLACKHOLE_NUMBER_OF_FRAMES))
            self.blackhole_reset_timer += 1

#finds the turn with the lowest absolute value and returns it
    def get_closest_turn(self, turn):
        while turn > 180:
            turn = turn - 360
        while turn < -180:
            turn = turn + 360
        return turn

#calculates an approximate inetercept heading based off distance from shooter and the most recent change in the target's position
    def find_intercept_heading(self, shooter, enemy, distance):
        ratio = math.sqrt(distance) / 25
        if shooter.last_heading < shooter.turtle.towards(enemy.turtle.pos()):
            advance = random.randint(0,10)*ratio
        else:
            advance = -(random.randint(0,15))*ratio
        heading = shooter.turtle.towards(enemy.turtle.pos()) + advance
        shooter.last_heading = shooter.turtle.towards(enemy.turtle.pos())
        return heading

#tests if a given object is overlapping blobher
#if true, self.game_over_bool is set to True
    def game_over(self, enemy):
            if (enemy.is_overlapping(self.blobhero)):
                self.blobhero.turtle.hideturtle()
                font = ("Arial", self.variables.FONT_SIZE, "normal")
                turtle.write("Game Over", False, "center", font)
                turtle.hideturtle()
                self.game_over_bool = True

#this goes through an object's qualities and checks to see if they should be declared dead
#if they should be declared dead(health<=0 or strength<=0) they are removed from the corresponding update list and removed from the screen
#after they are removed, the death animation is initialized in their last locatin with their last heading and speed
    def grim_reaper(self, objct):
        if (objct in self.lists.defenses):
            if objct.strength <= 0:
                objct.turtle.hideturtle()
                if objct.type == "stationary":
                    self.lists.defenses.remove(objct)
        elif (objct.health <= 0) or (objct.health > 200):
            if (objct in self.lists.enemies):
                self.kill_count += 1
                self.lists.enemies.remove(objct)
            if (objct in self.lists.spawners):
                self.kill_count += 1
                self.lists.spawners.remove(objct)
            if (objct in self.lists.blobfriends):
                self.lists.blobfriends.remove(objct)
            objct.turtle.hideturtle()
            (x,y) = objct.turtle.position()
            shape = objct.turtle.shape()
            self.lists.animations.append(animation.FireDeath(x,y,shape,objct.turtle.heading(), objct.speed))

#handles the interaction between projectile objects and target objects
#if the two are overlapping the corresponding damage is taken from the target and or the corresponding effects (ex. enemy.speed = bullet.slow)(enemy.speed = 0)
    def handle_projectiles(self, victim, shot, shot_list):
        if (victim.is_overlapping(shot)):
            if shot in self.lists.defenses:
                damage = shot.strength
                shot.strength -= victim.health
                victim.health -= damage
            else:
                victim.health -= shot.damage
                shot_list.remove(shot)
                shot.turtle.clear()
                shot.turtle.hideturtle()
                if shot.slow != None:
                    victim.speed = shot.slow

#this method cycles through every possible overlap that the enemy object could encounter
    def check_all_possible_overlaps(self, enemy):
            self.game_over(enemy)
            for bullet in self.lists.bullets:
                self.handle_projectiles(enemy, bullet, self.lists.bullets)
            for missile in self.lists.missiles:
                self.handle_projectiles(enemy, missile, self.lists.missiles)
            for blobfriend in self.lists.blobfriends:
                if (enemy.is_overlapping(blobfriend)):
                    damage = blobfriend.health
                    blobfriend.health -= enemy.health
                    enemy.health -= damage
                    self.grim_reaper(blobfriend)
            for defense in self.lists.defenses:
                if (enemy.is_overlapping(defense)):
                    damage = defense.strength
                    defense.strength -= enemy.health
                    if defense.turtle.isvisible():
                        enemy.turtle.setheading(enemy.turtle.heading()-180)
                    enemy.health -= damage
                    self.grim_reaper(defense)
            for blackhole in self.lists.blackholes:
                if (enemy.is_overlapping(blackhole)):
                    enemy.health -= blackhole.damage
            self.grim_reaper(enemy)

#this method goes through all of the enemies and sends them to be cross checked with all possible overlaps
    def update_all_intercepts(self):
        for enemy in self.lists.enemies:
            self.check_all_possible_overlaps(enemy)
        for spawner in self.lists.spawners:
             self.check_all_possible_overlaps(spawner)

#this method checks the timers on the spawn timers on the objects, if they have been reset the correlating enemy is spawned, this is a level based spawn, not from a current enemy
    def spawn_enemies(self):
        if self.mothership_spawn_timer == 0:
            self.mothership_spawn_timer += 1
            self.lists.spawners.append(enemyspawn.EnemySpawn(self.variables.MOTHERSHIP_HEALTH, self.variables.MOTHERSHIP_RADIUS, self.variables.MOTHERSHIP_SPEED, self.variables.MOTHERSHIP_IMAGE, 0,0, self.variables.FRAME_RATE*7, "both"))
        if self.enemy1_spawn_timer == 0:
            self.enemy1_spawn_timer += 1
            for i in range (3):
                zerone = random.randint(0,1)
                y = random.randint((-turtle.window_height()//2), (turtle.window_height()//2))
                x = -((turtle.window_width()/2)*((-1)**(zerone)))
                self.lists.enemies.append(enemy1.Enemy1(self.variables.ENEMY1_HEALTH, self.variables.ENEMY1_RADIUS, self.variables.ENEMY1_SPEED, self.variables.ENEMY1_IMAGE, x,y,(180**zerone)))

#this method checks a few set distances to determine the state of the enemy
#it also finds the closest bullet everytime it runs
    def handle_state(self, objct):
        temp = 10000
        (closest_bullet, temp) = self.find_closest(objct, self.lists.bullets, temp, temp)
        if objct.state == "passive":
            if objct.turtle.distance(self.blobhero.turtle.pos()) > self.variables.AGGRESSIVE_STATE_ACTIVATION_DISTANCE_FROM_HERO:
                objct.state = 'aggressive'
            if closest_bullet < self.variables.EVASIVE_STATE_ACTIVATION_BULLET_DISTANCE:
                objct.state = 'evasive'
        elif objct.state == 'evasive':
            if (len(self.lists.enemies)+len(self.lists.spawners)) > self.variables.PASSIVE_STATE_ACTIVATION_NUMBERS_COUNT:
                objct.state == 'passive'

#this method moves enemies within a blackhole gravity field closer to the blackhole
    def gravity_to_blackhole(self, enemy):
        closest_blackhole = 10000
        heading = enemy.turtle.heading()
        for blackhole in self.lists.blackholes:
            (closest_blackhole, heading) = self.find_closest(enemy, self.lists.blackholes, closest_blackhole, heading)
        if closest_blackhole < self.variables.BLACKHOLE_GRAVITY_FIELD:
            previous_heading = enemy.turtle.heading()
            enemy.turtle.setheading(heading)
            enemy.turtle.forward(self.variables.BLACKHOLE_GRAVITY_STRENGTH)
            enemy.turtle.setheading(previous_heading)
            

#this method updates all enemies, for spawners, it spawns the corresponding enemy based off timers
    def update_all_enemies(self):
        self.spawn_enemies()
        for enemy in self.lists.enemies:
            self.handle_state(enemy)
            enemy.update(self.lists.enemies, self.lists.spawners, self.blobhero, self.lists.blobfriends, self.lists.bullets)
            self.gravity_to_blackhole(enemy)
        for spawner in self.lists.spawners:
            random_heading = random.randint(0,360)
            spawner.update(self.lists.enemies, self.lists.spawners, self.blobhero, self.lists.blobfriends, self.lists.bullets)
            if spawner.i == spawner.spawn_rate:
                (x,y) = spawner.turtle.pos()
                if spawner.child == "enemy1":
                    self.lists.enemies.append(enemy1.Enemy1(self.variables.ENEMY1_HEALTH, self.variables.ENEMY1_RADIUS, self.variables.ENEMY1_SPEED, self.variables.ENEMY1_IMAGE, x,y,random_heading))
                if spawner.child == "spawner":
                    self.lists.spawners.append(enemyspawn.EnemySpawn(self.variables.SPAWNER_HEALTH, self.variables.SPAWNER_RADIUS, self.variables.SPAWNER_SPEED, self.variables.SPAWNER_IMAGE, x,y, self.variables.FRAME_RATE*5))
                if spawner.child == "both":
                    self.lists.spawners.append(enemyspawn.EnemySpawn(self.variables.SPAWNER_HEALTH, self.variables.SPAWNER_RADIUS, self.variables.SPAWNER_SPEED, self.variables.SPAWNER_IMAGE, x,y, self.variables.FRAME_RATE*5))
                    self.lists.enemies.append(enemy1.Enemy1(self.variables.ENEMY1_HEALTH, self.variables.ENEMY1_RADIUS, self.variables.ENEMY1_SPEED, self.variables.ENEMY1_IMAGE, x,y,random_heading))
                    self.lists.enemies.append(enemy1.Enemy1(self.variables.ENEMY1_HEALTH, self.variables.ENEMY1_RADIUS, self.variables.ENEMY1_SPEED, self.variables.ENEMY1_IMAGE, x,y,random_heading))

#this method finds the closest object in a list compared to a shooter object
#it returns an intercept heading to the object and the distance to the closest object
    def find_closest(self, shooter, lst, shortest_distance, intercept_heading):
        for victim in lst:
            distance = shooter.turtle.distance(victim.turtle)
            if distance < shortest_distance:
                shortest_distance = distance
                intercept_heading = self.find_intercept_heading(shooter, victim, distance)
        return (shortest_distance, intercept_heading)

#this method is for making a blobfriend turret type object shoot the corresponding shot
    def blobfriend_shoots(self, blobfriend, intercept_heading):
        (x,y) = blobfriend.turtle.pos()
        blobfriend.turtle.setheading(intercept_heading)
        blobfriend.update()
        blobfriend.timer += 1
        if blobfriend.ammo_type == 'bullet':
            self.lists.bullets.append(bullet.Bullet(self.variables.BULLET_SPEED, self.variables.BULLET_RADIUS, self.variables.BULLET_IMAGE, self.variables.BULLET_DAMAGE, x, y, intercept_heading))
        if blobfriend.ammo_type == 'shotgun':
            min_heading = int(blobfriend.turtle.heading() - (self.variables.SHOTGUN_SPREAD//2))
            for i in range(self.variables.SHOTGUN_SHOTS):
                random_heading = random.randint(min_heading, min_heading+self.variables.SHOTGUN_SPREAD)
                self.lists.bullets.append(bullet.Bullet(self.variables.BULLET_SPEED, self.variables.BULLET_RADIUS, self.variables.BULLET_IMAGE, self.variables.SHOTGUN_DAMAGE, x, y, random_heading))
        if blobfriend.ammo_type == 'missile':
            min_heading = int(blobfriend.turtle.heading() - (self.variables.MISSILE_SPREAD//2))
            for i in range(self.variables.MISSILE_SHOTS):
                random_heading = random.randint(min_heading, min_heading+self.variables.MISSILE_SPREAD)
                self.lists.missiles.append(missile.Missile(self.variables.MISSILE_SPEED, self.variables.MISSILE_RADIUS, self.variables.MISSILE_DAMAGE, x, y, random_heading))

#calculates the movement of the blobfriend according to set distance parameters to be met(with hero)&(with other blobfriends) given a blobfriend movement speed
    def blobfriend_moves(self, blobfriend):
        if blobfriend.turtle.distance(self.blobhero.turtle) > self.variables.PERSONAL_BUBBLE:
            blobfriend.turtle.setheading(blobfriend.turtle.towards(self.blobhero.turtle.pos()))
            blobfriend.turtle.forward(blobfriend.speed)
        else:
            for otherfriend in self.lists.blobfriends:
                if blobfriend.turtle.distance(otherfriend.turtle) > 0:
                    if blobfriend.turtle.distance(otherfriend.turtle) < self.variables.PERSONAL_BUBBLE:
                        blobfriend.turtle.setheading(blobfriend.turtle.towards(otherfriend.turtle)-180)
                        blobfriend.turtle.forward(blobfriend.speed)
            for otherfriend in self.lists.blobbombers:
                if blobfriend.turtle.distance(otherfriend.turtle) > 0:
                    if blobfriend.turtle.distance(otherfriend.turtle) < self.variables.PERSONAL_BUBBLE:
                        blobfriend.turtle.setheading(blobfriend.turtle.towards(otherfriend.turtle)-180)
                        blobfriend.turtle.forward(blobfriend.speed)

#this is the main method for updating all blobfriends in the list of blobfriends
    def update_all_blobfriends(self):
        intercept_heading = 400
        for blobfriend in self.lists.blobfriends:
            self.blobfriend_moves(blobfriend)
            (x,y) = blobfriend.turtle.pos()
            shortest_distance = 10000
            (shortest_distance, intercept_heading) =  self.find_closest(blobfriend, self.lists.spawners, shortest_distance, intercept_heading)
            (shortest_distance, intercept_heading) =  self.find_closest(blobfriend, self.lists.enemies, shortest_distance, intercept_heading)
            if (intercept_heading != 400) and (shortest_distance < self.variables.BLOBFRIEND_RANGE):
                if blobfriend.ammo_type == 'bullet':
                    if blobfriend.timer == 0:
                        self.blobfriend_shoots(blobfriend, intercept_heading)
                    elif blobfriend.timer == self.variables.BLOBFRIEND_FIRE_RATE_BULLET:
                        blobfriend.timer = 0
                    else:
                        blobfriend.timer += 1
                if blobfriend.ammo_type == 'shotgun':
                    if blobfriend.timer == 0:
                        self.blobfriend_shoots(blobfriend, intercept_heading)
                    elif blobfriend.timer == self.variables.BLOBFRIEND_FIRE_RATE_SHOTGUN:
                        blobfriend.timer = 0
                    else:
                        blobfriend.timer += 1
                if blobfriend.ammo_type == 'missile':
                    if blobfriend.timer == 0:
                        self.blobfriend_shoots(blobfriend, intercept_heading)
                    elif blobfriend.timer == self.variables.BLOBFRIEND_FIRE_RATE_MISSILE:
                        blobfriend.timer = 0
                    else:
                        blobfriend.timer += 1
        for blobbomber in self.lists.blobbombers:
            self.blobfriend_moves(blobbomber)
            (x,y) = blobbomber.turtle.pos()
            shortest_distance = 10000
            (shortest_distance, intercept_heading) =  self.find_closest(blobbomber, self.lists.spawners, shortest_distance, intercept_heading)
            (shortest_distance, intercept_heading) =  self.find_closest(blobbomber, self.lists.enemies, shortest_distance, intercept_heading)
            if (intercept_heading != 400) and (shortest_distance < self.variables.BLOBBOMBER_RANGE):
                if blobbomber.timer == 0:
                    self.blobfriend_shoots(blobbomber, intercept_heading)
                elif blobbomber.timer == self.variables.BLOBBOMBER_FIRE_RATE:
                    blobbomber.timer = 0
                else:
                    blobbomber.timer += 1


#this method is primarily for projectiles, it tests if they are on the screen, if not they're removed
    def check_on_screen(self, objct, lst):
        if objct in lst:
            (x,y) = objct.turtle.pos()
            height = turtle.window_height() / 2
            width = turtle.window_width() / 2
            if (math.fabs(x) > width) or (math.fabs(y) > height):
                lst.remove(objct)
                objct.turtle.hideturtle()
                objct.turtle.clear()

#this updates all projectiles on the screen, for missiles it calculates intercept heading based on their seeker bubbler and turn ratio
    def update_all_shots(self):
        height = turtle.window_height() / 2
        width = turtle.window_width() / 2
        for bullet in self.lists.bullets:
            bullet.update()
            self.check_on_screen(bullet, self.lists.bullets)
        for missile in self.lists.missiles:
            shortest_distance = 10000
            intercept_heading = missile.turtle.heading()
            (shortest_distance, intercept_heading) = self.find_closest(missile, self.lists.spawners, shortest_distance, intercept_heading)
            (shortest_distance, intercept_heading) = self.find_closest(missile, self.lists.enemies, shortest_distance, intercept_heading)
            if shortest_distance < self.variables.MISSILE_SEEKER_BUBBLE:
                turn = self.get_closest_turn(intercept_heading - missile.turtle.heading())
                intercept_heading = (missile.turtle.heading() + (self.variables.MISSILE_TURN_RATIO * (turn)))
                missile.turtle.setheading(intercept_heading)
            else:
                turn = (random.randint(-500,500))/100
                turn = missile.turtle.setheading(missile.turtle.heading() + turn)
            missile.update()
            self.check_on_screen(missile, self.lists.missiles)

#this method updates defenses on the screen
#for the portable shield, it just makes it visible if it has been taken down and the reset timer is up
#for the stationary shield it checks if it is visible then it removes it from memory if it isn't
    def update_all_defenses(self):
        if len(self.lists.defenses) == 0:
            (x,y) = self.blobhero.turtle.pos()
            self.lists.defenses.append(defense.PortableShield(self.variables.PORTABLE_SHIELD_RADIUS, self.variables.PORTABLE_SHIELD_STRENGTH, self.variables.PORTABLE_SHIELD_IMAGE, x,y))
        for defence in self.lists.defenses:
            if defence.type == "portable":
                defence.turtle.goto(self.blobhero.turtle.pos())
                if defence.strength <= 0:
                    self.portable_shield_reset_timer += 1
                if self.portable_shield_reset_timer >= self.variables.PORTABLE_SHIELD_RESET_TIMER:
                    self.portable_shield_reset_timer = 0
                    defence.turtle.showturtle()
                    defence.strength = self.variables.PORTABLE_SHIELD_STRENGTH
            if defence.type == "stationary":
                if defence.turtle.isvisible():
                    defence.update()
                else:
                    if defence in self.lists.defenses:
                        self.lists.defenses.remove(defence)

#this method updates blackhole timers and removes them from memory if they are "dead"
    def update_all_blackholes(self):
        for blackhole in self.lists.blackholes:
            if blackhole.turtle.isvisible():
                blackhole.update()
            else:
                if blackhole in self.lists.blackholes:
                    self.lists.blackholes.remove(blackhole)

#this method updates the majority of the game timers
#the few timers that are exluded are ones that don't apply to all objects in the class, such as the duration of a stationary shield or of a blackhole
    def update_timers(self):
        if self.bullet_timer != 0:
            self.bullet_timer += 1
        if self.bullet_timer >= self.variables.BULLET_RESET_TIMER:
            self.bullet_timer = 0
        if self.shotgun_timer != 0:
            self.shotgun_timer += 1
        if self.shotgun_timer >= self.variables.SHOTGUN_RESET_TIMER:
            self.shotgun_timer = 0
        if self.ice_timer != 0:
            self.ice_timer += 1
        if self.ice_timer >= self.variables.ICE_RESET_TIMER:
            self.ice_timer = 0
        if self.missile_timer != 0:
            self.missile_timer += 1
        if self.missile_timer >= self.variables.MISSILE_RESET_TIMER:
            self.missile_timer = 0
        if self.mothership_spawn_timer != 0:
            self.mothership_spawn_timer += 1
        if self.mothership_spawn_timer >= self.variables.MOTHERSHIP_SPAWN_TIMER:
            self.mothership_spawn_timer = 0
        if self.enemy1_spawn_timer != 0:
            self.enemy1_spawn_timer += 1
        if self.enemy1_spawn_timer >= self.variables.ENEMY1_SPAWN_TIMER:
            self.enemy1_spawn_timer = 0
        if self.stationary_shield_reset_timer != 0:
            self.stationary_shield_reset_timer += 1
        if self.stationary_shield_reset_timer >= self.variables.STATIONARY_SHIELD_RESET_TIMER:
            self.stationary_shield_reset_timer = 0
        if self.stationary_shield_powerout_timer != 0:
            self.stationary_shield_powerout_timer += 1
        if self.stationary_shield_powerout_timer >= self.variables.STATIONARY_SHIELD_POWEROUT_TIMER:
            self.stationary_shield_powerout_timer = 0
        if self.blackhole_reset_timer != 0:
            self.blackhole_reset_timer += 1
        if self.blackhole_reset_timer >= self.variables.BLACKHOLE_RESET_TIMER:
            self.blackhole_reset_timer = 0

#this method produces the 'stats' bar at the bottom
    def update_stats(self):
        self.game_timer += 1
        self.score = ((self.game_timer // (self.variables.FRAME_RATE*10))*50 + (100*self.kill_count))
        half_height = turtle.window_height() / 2
        half_width = turtle.window_width() / 2
        self.stat_pen.goto(-half_width+10, -half_height+10)
        self.stat_pen.clear()
        (x,y) = self.blobhero.turtle.pos()
        string0 = "Survival Time: "+str(self.game_timer//self.variables.FRAME_RATE)
        string1 = "   Speed: "+str(self.blobhero.speed)
        string2 = "   Position: ("+str(int(x))+","+str(int(y))+")"
        string3 = "   Number of Allies: "+str(len(self.lists.blobfriends))
        string4 = "   Number of Enemies: "+str(len(self.lists.spawners)+len(self.lists.enemies))
        string5 = "   SCORE: "+str(self.score)
        string = string0+string1+string2+string3+string4+string5
        font = ("Arial", 10, "normal")
        self.stat_pen.write(string, False, 'left', font)

#this method updates all animatoins put up after object demise
    def update_all_animations(self):
        for animation in self.lists.animations:
            if animation.turtle.isvisible():
                animation.update()
            else:
                self.lists.animations.remove(animation)

#this pauses the game, turtle will keep looping but all game updates stop, memory on the machine is still taken up
    def write_pause(self):
        font = ("Arial", self.variables.FONT_SIZE, "normal")
        self.pause_pen.write("Pause", False, "center", font)
        if self.pause_timer == 0:
            self.pause_pen.clear()

#this is a main that runs the loop for apparent animation
    def run(self):
        if self.pause_timer == 0:
            if not self.game_over_bool:
                self.blobhero.update()
                self.update_all_defenses()
                self.update_stats()
            self.update_all_blobfriends()
            self.update_all_blackholes()
            self.update_all_shots()
            self.update_all_intercepts()
            self.update_all_enemies()
            self.update_all_animations()
            self.update_timers()
        else:
            self.write_pause()
        turtle.update()
        turtle.ontimer(self.run, self.variables.FRAME_RATE)

    def help(self):
        self.pause_timer = 1
        print('')
        print('')
        print("-------------------------ENEMYLIST----------------------------------")
        print('length:', str(len(self.lists.enemies)))
        i = 0
        for enemy in self.lists.enemies:
            i += 1
            print('                    Enemy Number',i)
            print('health:',enemy.health)
            (x,y) = enemy.turtle.pos()
            print('speed, (x,y): ', enemy.speed, "("+str(int(x))+','+str(int(y))+')')
            print('is visible: ', str(enemy.turtle.isvisible()))
        print('')
        print('')
        print("--------------------------SPAWNERLIST----------------------------------")
        print('length:', str(len(self.lists.spawners)))
        i = 0
        for spawner in self.lists.spawners:
            i += 1
            print('                    Spawner Number',i)
            print('health:',spawner.health)
            (x,y) = spawner.turtle.pos()
            print('speed, (x,y): ', spawner.speed, "("+str(int(x))+','+str(int(y))+')')
            print('is visible: ', str(spawner.turtle.isvisible()))
        print('')
        print('')
        print("--------------------------BLOBFRIENDLIST----------------------------------")
        print('length:', str(len(self.lists.blobfriends)))
        i = 0
        for blobfriend in self.lists.blobfriends:
            i += 1
            print('                    Blobfriend Number',i)
            print('health:',blobfriend.health)
            (x,y) = blobfriend.turtle.pos()
            print('speed, (x,y): ', blobfriend.speed, "("+str(int(x))+','+str(int(y))+')')
            print('is visible: ', str(blobfriend.turtle.isvisible()))
        print('')
        print('')
        print("---------------------------BULLETLIST----------------------------------")
        print('length:', str(len(self.lists.bullets)))
        i = 0
        for bullet in self.lists.bullets:
            i += 1
            print('                    Bullet Number',i)
            (x,y) = bullet.turtle.pos()
            print('damage: ', bullet.damage)
            print('speed, (x,y): ', bullet.speed, "("+str(int(x))+','+str(int(y))+')')
            print('is visible: ', str(bullet.turtle.isvisible()))
        print('')
        print('')
        print("---------------------------DEFENSELIST----------------------------------")
        print('length:', str(len(self.lists.defenses)))
        i = 0
        for defense in self.lists.defenses:
            i += 1
            print('                    Defense Number',i)
            (x,y) = defense.turtle.pos()
            print('strength: ', defense.strength)
            print('is visible: ', str(defense.turtle.isvisible()))
        print('')
        print('')
        print("---------------------------BLACKHOLELIST----------------------------------")
        print('length:', str(len(self.lists.blackholes)))
        i = 0
        for blackhole in self.lists.blackholes:
            i += 1
            print('                    Blackhole Number',i)
            (x,y) = blackhole.turtle.pos()
            print('position: ',str(int(x)),str(int(y)))


game = BlobWars()
game.run()
turtle.mainloop()
