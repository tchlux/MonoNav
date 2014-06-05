
##############################################################
        for spawner in self.spawners:
            self.game_over(spawner)
            for bullet in self.bullets:
                if (spawner.is_overlapping(bullet)):
                    if bullet.slow != None:
                        spawner.speed = bullet.slow
                    spawner.health -= bullet.damage
                    self.bullets.remove(bullet)
                    bullet.turtle.hideturtle()
                if (spawner.health <= 0):
                    if spawner in self.spawners:
                        self.kill_count += 1
                        self.spawners.remove(spawner)
                        spawner.turtle.hideturtle()
            for missile in self.missiles:
                if (spawner.is_overlapping(missile)):
                    spawner.health -= missile.damage
                    self.missiles.remove(missile)
                    missile.turtle.hideturtle()
                    missile.turtle.clear()
                if (spawner.health <= 0):
                    if spawner in self.spawners:
                        self.kill_count += 1
                        self.spawners.remove(spawner)
                        spawner.turtle.hideturtle()
            for blobfriend in self.blobfriends:
                if (spawner.is_overlapping(blobfriend)):
                    if spawner in self.spawners:
                        self.spawners.remove(spawner)
                        self.blobfriends.remove(blobfriend)
                        spawner.turtle.hideturtle()
                        blobfriend.turtle.hideturtle()
            for defense in self.defenses:
                if (spawner.is_overlapping(defense)):
                    damage = defense.strength
                    defense.strength -= spawner.health
                    spawner.health -= damage
                if spawner.health <= 0:
                    if spawner in self.spawners:
                        self.kill_count += 1
                        self.spawners.remove(spawner)
                        spawner.turtle.hideturtle()
                if defense.strength <= 0:
                    if defense in self.defenses:
                        defense.turtle.hideturtle()
                        if defense.type == "stationary":
                            self.defenses.remove(defense)


#### extra ####


    # def find_intercept_heading(self, blobfriend, distance, enemy):
    #     heading = math.radians(enemy.turtle.heading())
    #     x_percent = math.sin(heading)
    #     y_percent = 1 - x_percent
    #     x_speed = x_percent * enemy.speed
    #     y_speed = y_percent * enemy.speed
    #     advance = (distance*(INT_DISTANCE_RATIO) + x_speed*(INT_SPEEDX_RATIO) + y_speed*(INT_SPEEDY_RATIO) + BULLET_SPEED*(INT_SHOTSPEED_RATIO))
    #     blob_heading = blobfriend.turtle.heading()
    #     blob_heading_plus = blob_heading
    #     en_heading = enemy.turtle.heading()
    #     heading = advance + (blobfriend.turtle.towards(enemy.turtle.pos()))
    #     return heading


        # direction = 0
        # if (blob_heading+180) > 360:
        #     blob_heading_plus = ((blob_heading+180) - 360)
        # else:
        #     blob_heading_plus = (blob_heading+180)
        # if (blob_heading < blob_heading_plus):
        #     if (blob_heading < en_heading < blob_heading_plus):
        #         direction = 1
        #     if (blob_heading > en_heading > blob_heading_plus):
        #         direction = -1
        # else:
        #     if (blob_heading_plus < en_heading < blob_heading):
        #         direction = 1
        #     if (blob_heading_plus > en_heading > blob_heading):
        #         direction = -1

        # heading = advance + (math.fabs(blobfriend.turtle.towards(enemy.turtle.pos()))*direction)


    # ## INTERCEPTION RATIOS ##
    # INT_DISTANCE_RATIO = .005
    # INT_SPEEDX_RATIO = 2
    # INT_SPEEDY_RATIO = 3
    # INT_SHOTSPEED_RATIO = 0




def is_overlapping(circle, other_circle):
    distance = circle.turtle.distance(other_circle.turtle)
    return (circle.radius + other_circle.radius) > distance



    def object_projectile_interaction(self, objct, prjctile):
        if is_overlapping(objct, prjctile):
            objct.health -= prjctile.damage
            if prjctile.slow != None:
                objct.speed = prjctile.slow
            if objct.health <= 0:
                if (objct in self.enemies):
                    self.kill_count += 1
                    self.enemies.remove(objct)
                    self.bullets.remove
                if (objct in self.spawners):
                    

    def update_all_intercepts(self):
        for enemy in self.enemies:
            for bullet in self.bullets:
                if is_overlapping(enemy, bullet):
                    
                # turn += (blobs)*BLOBS_RATIO
                # turn += (hero)*HERO_RATIO

        # self.turtle.pendown()
        # self.turtle.pensize(2)
        # self.turtle.pencolor('grey')
