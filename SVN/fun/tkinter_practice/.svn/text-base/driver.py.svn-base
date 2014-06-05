import nxt.locator
from nxt.motor import *
import turtle

INITIAL_POWER = 20
CHANGE_AMOUNT = 5

#motor.run(power_level, True)
#power levels can be negative
#Stop movement:
#motor.idle()

class MockMotor:
    def __init__(self, name):
        self.name = name

    def run(self, power, bol):
        print self.name, "Power:", power
    def idle(self):
        pass

left_motor = MockMotor("Left")
right_motor = MockMotor("Right")

# brick = nxt.locator.find_one_brick()
# left_motor = Motor(brick, PORT_A)
# right_motor = Motor(brick, PORT_C)
# print("Brick status check")
# print("Motors check")


class Fun:
    def __init__(self):
        self.left = 0
        self.right = 0
        self.prepare_listeners()

    def prepare_listeners(self):
        turtle.onkey(self.forward, "Up")
        turtle.onkey(self.turn_left, "Left")
        turtle.onkey(self.turn_right, "Right")
        turtle.onkey(self.backward, "Down")
        turtle.onkey(self.stop, "s")
        turtle.listen()

    def forward(self):
        print("Forwards")
        self.right = INITIAL_POWER
        self.left = INITIAL_POWER

    def backward(self):
        print("Backwards")
        self.right = -INITIAL_POWER
        self.left = -INITIAL_POWER

    def turn_left(self):
        print("Left turn")
        print("Left motor idle")
        self.right = INITIAL_POWER
        self.left = 0

    def turn_right(self):
        print("Right turn")
        print("Right motor idle")
        self.right = 0
        self.left = INITIAL_POWER

    def stop(self):
        print("Stop")
        self.left = 0
        print("Left motor idle.")
        self.right = 0
        print("Right motor idle.")

    def operate(self):
        if self.left != 0:
            left_motor.run(self.left, True)
        else:
            left_motor.idle()
        if self.right != 0:
            right_motor.run(self.right, True)
        else:
            right_motor.idle()

    def accelerate(self):
        if self.right > 0:
            if self.right < 100:
                self.right += CHANGE_AMOUNT
        elif self.right < 0:
            if self.right > -100:
                self.right -= CHANGE_AMOUNT
        if self.left > 0:
            if self.left < 100:
                self.left += CHANGE_AMOUNT
        elif self.left < 0:
            if self.left > -100:
                self.left -= CHANGE_AMOUNT

    def mainloop(self):
        self.operate()
        self.accelerate()
        turtle.ontimer(self.mainloop, 200)

if __name__ == "__main__":
    a = Fun()
    a.mainloop()
    turtle.mainloop()
