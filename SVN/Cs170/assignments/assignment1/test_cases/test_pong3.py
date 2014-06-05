

#pong
import bouncing_ball
import bricks
import paddle
import window

w = window.Window()

#set the paddle on the right side of the screen
p = paddle.Paddle(x=300, color="black")

#set the ball heading south at normal speed
b = boucing_ball.Ball(x=0, y=0, heading=SOUTH, speed=SPEED)

#user will move paddle so that it is moving when it hits the ball
#expected behavior - if the paddle hits the ball with an x velocity, it will factor into the new heading of the ball based off of the speed of the paddle
