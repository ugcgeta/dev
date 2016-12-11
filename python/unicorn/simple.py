#!/usr/bin/env python

import time

import unicornhat as unicorn

unicorn.set_layout(unicorn.AUTO)
unicorn.rotation(0)
unicorn.brightness(0.3)
width,height=unicorn.get_shape()

print(unicorn.get_shape(),unicorn.AUTO)

for y in range(height):
  for x in range(width):
    unicorn.set_pixel(x,y,255,0,255)
    unicorn.show()
    print(x,y)
    time.sleep(0.1)
#unicorn.set_pixel(6,0,255,0,255)
#unicorn.show()
#time.sleep(0.5)
unicorn.off()
time.sleep(1)
