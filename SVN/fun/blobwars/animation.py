import turtle
import random

class FireDeath:

    def __init__(self, x, y, enemy_image='Enemy1', heading=0, enemy_speed=0, image_base_name='FireDeath', fps=30, aps=10, number_of_animations=10):
        self.turtle = turtle.Turtle()
        image = image_base_name + '0.gif'
        self.turtle.shape(image)
        self.turtle.penup()
        self.turtle.goto(x,y)
        self.turtle.setheading(heading)
        self.enemy_turtle = turtle.Turtle()
        self.enemy_turtle.penup()
        self.enemy_turtle.shape(enemy_image)
        self.enemy_turtle.goto(x,y)
        self.enemy_turtle.setheading(heading)
        self.image_base_name = image_base_name
        self.animation_timer = 0
        self.speed = enemy_speed
        self.fps = fps
        self.aps = aps
        self.number_of_animations = number_of_animations
        self.turn = random.randint(-17,17)

    def update(self):
        frame = int(self.animation_timer // (self.fps/self.aps))
        self.turtle.forward(self.speed)
        self.enemy_turtle.forward(self.speed)
        self.turtle.left(self.turn)
        self.enemy_turtle.left(self.turn)
        self.speed = (self.speed / 1.07)
        if frame < self.number_of_animations:
            string = self.image_base_name + str(frame) + '.gif'
            self.turtle.shape(string)
            self.animation_timer += 1
        else:
            self.turtle.hideturtle()
            self.enemy_turtle.hideturtle()
