#!/usr/bin/python
import sys

size = int(sys.argv[1])
n = 0
tmp = size
while tmp > 0:
	n += 1
	tmp -= 512

print(n * 512 - size)
