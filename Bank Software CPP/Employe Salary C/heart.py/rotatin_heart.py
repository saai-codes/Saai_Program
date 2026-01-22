import turtle
import math

screen = turtle.Screen()
screen.bgcolor("black")

pen = turtle.Turtle()
pen.color("red")
import time
pen.speed(0)
pen.hideturtle()

angle = 0

def draw_heart(pen, angle):
    pen.clear()
    pen.penup()

    points = []
    for t in range(0, 360, 1):
        x = 16 * math.sin(math.radians(t)) ** 3
        y = 13 * math.cos(math.radians(t)) - 5 * math.cos(math.radians(2 * t)) - 2 * math.cos(math.radians(3 * t)) - math.cos(math.radians(4 * t))

        # Apply rotation
        rad = math.radians(angle)
        rx = x * math.cos(rad) - y * math.sin(rad)
        ry = x * math.sin(rad) + y * math.cos(rad)
        points.append((rx * 10, ry * 10))  # scale up

    pen.goto(points[0])
    pen.pendown()
    pen.begin_fill()
    pen.fillcolor("red")
    for pt in points:
        pen.goto(pt)
    pen.end_fill()

    # Draw the text
    pen.penup()
    pen.color("white")
    pen.goto(0, -20)
    pen.write("SAAI", align="center", font=("Arial", 18, "bold"))
    pen.color("red")

import time  # <-- Add this at the top of your code if not already there

# Animation loop
while True:
    draw_heart(pen, angle)
    angle += 2  # Rotation speed
    time.sleep(0.05)  # <-- This slows down the redraw so "Shive" is visible
