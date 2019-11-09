#!python
#!usr/bin/python
# -*- coding: utf-8 -*-
from turtle import *
from random import choice

def jumpto(x,y) :
    up(); goto(x,y); down()

def draw(x,y,angle,len) : #先跳转至目标坐标，再调整角度，画len的直线
    pencolor(choice(color))
    jumpto(x,y)
    left(angle)
    forward(len)

def drawL(x,y) :
    seth(0) #新技能：设置绝对角度：水平向左为0°
    draw(x,y,270,100)
    draw(x,y-100,90,50)

color = ["red","green","blue","brown","orange","pink","black","purple"]

reset()
speed("slow")

#Line
jumpto(-300,200)
res=choice(color)
pencolor(res)
width(10)
forward(420)
width(3)

#H
draw(-300,50,90,100)
draw(-300,100,270,50)
draw(-250,150,270,100)

#E
draw(-220,150,0,100)
draw(-220,50,90,50)
jumpto(-220,100)
forward(50)
jumpto(-220,150)
forward(50)

#L
drawL(-150,150)
drawL(-80,150)

#O
jumpto(20,50)
fillcolor(choice(color))
begin_fill()
circle(50)
end_fill()

#W
pencolor(choice(color))
jumpto(-220,-20)
goto(-195,-120)
goto(-170,-20)
goto(-145,-120)
goto(-120,-20)

#O
pencolor(choice(color))
jumpto(-50,-120)
circle(50)

#R
draw(20,-20,270,100)
draw(20,-20,90,40)
left(270)
forward(40)
left(270)
forward(40)
goto(70,-120)

#L
drawL(90,-20)

#D
draw(160,-20,270,100)
left(90)
fillcolor(choice(color))
begin_fill()
circle(50,180)
end_fill()

#Line
width(10)
jumpto(-220,-160)
seth(0)
pencolor(res)
forward(420)

pencolor(choice(color))
jumpto(-300,-190)
left(180)
write("Hello MSC!")
jumpto(120,-190)
write("by Zhang Chong.")

hideturtle()
s=Screen()
s.exitonclick()
