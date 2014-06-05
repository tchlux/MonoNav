import invader
import defender
import missile
import turtle

FRAME_RATE = 30
FONT_SIZE = 40
ROWS_OF_INVADERS = 3
COLS_OF_INVADERS = 5
INVADER_VERTICAL_SEPARATION = 100
INVADER_HORIZONTAL_SEPARATION = 150
INVADER_INIT_Y = 0
WINDOW_WIDTH = 640
WINDOW_HEIGHT = 480
DEFENDER_INIT_X = 0
DEFENDER_INIT_Y = -200

class SpaceInvaders:
    def __init__(self):
        self.init_turtle()
        self.init_sprites()

    def init_turtle(self):
        turtle.addshape("invader.gif")
        turtle.addshape("defender.gif")
        turtle.addshape("missile.gif")
        turtle.tracer(0)
        turtle.listen()
        turtle.onkey(self.handle_left_arrow, "Left")
        turtle.onkey(self.handle_right_arrow, "Right")
        turtle.onkey(self.handle_up_arrow, "space")
        turtle.setup(width=WINDOW_WIDTH, height=WINDOW_HEIGHT)

    def init_sprites(self):
        self.defender = defender.Defender(DEFENDER_INIT_X, DEFENDER_INIT_Y)
        self.missiles = []
        self.invaders = []
        window_width = turtle.window_width()
        window_height = turtle.window_height()
        half_window_width = window_width / 2
        half_window_height = window_height / 2
        horizontal_separation = window_width / COLS_OF_INVADERS
        vertical_separation = window_height / ROWS_OF_INVADERS
        min_x = INVADER_HORIZONTAL_SEPARATION * (COLS_OF_INVADERS - 1) // -2
        min_y = INVADER_INIT_Y
        for row in range(ROWS_OF_INVADERS):
            y = min_y + row * INVADER_VERTICAL_SEPARATION
            for col in range(COLS_OF_INVADERS):
                x = min_x + col * INVADER_HORIZONTAL_SEPARATION
                self.invaders.append(invader.Invader(x, y))

    def handle_left_arrow(self):
        self.defender.move_left()

    def handle_right_arrow(self):
        self.defender.move_right()

    def handle_up_arrow(self):
        (x, y) = self.defender.turtle.position()
        self.missiles.append(missile.Missile(x, y))

    def update_all_invaders(self):
        for an_invader in self.invaders:
            an_invader.update()

    def update_all_missiles(self):
        half_window_height = turtle.window_height() / 2
        for a_missile in self.missiles:
            a_missile.update()
            (x, y) = a_missile.turtle.position()
            if y > half_window_height:
                self.missiles.remove(a_missile)
                a_missile.turtle.hideturtle()

    def update_invader_missile_collisions(self):
        for an_invader in self.invaders:
            for a_missile in self.missiles:
                if an_invader.is_overlapping(a_missile):
                    self.invaders.remove(an_invader)
                    self.missiles.remove(a_missile)
                    a_missile.turtle.hideturtle()
                    an_invader.turtle.hideturtle()

    def is_game_over(self):
        game_over = False
        for an_invader in self.invaders:
            if an_invader.is_overlapping(self.defender):
                game_over = True
        return game_over

    def run(self):
        self.update_all_invaders()
        self.update_all_missiles()
        self.update_invader_missile_collisions()
        game_over = self.is_game_over()
        if game_over:
            turtle.penup()
            turtle.goto(0, 0)
            font = ("Arial", FONT_SIZE, "normal")
            turtle.write("Game Over", False, "center", font)
        if not game_over:
            turtle.update()
            turtle.ontimer(self.run, FRAME_RATE)

game = SpaceInvaders()
game.run()
turtle.mainloop()
