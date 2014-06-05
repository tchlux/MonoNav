import turtle

def compute_point(p1, p2, t):
    (x1, y1) = p1
    (x2, y2) = p2
    return ( ((1-t)*x2 + t*x1),((1-t)*y2 + t*y1) )

5,3
1,-7
t = .1
-.4,.1 
