#!/usr/bin/python
# -*- coding: utf-8 -*-

import bint 
import sys
import random


def xgcd(a, b):
	
	if a == bint.bint(0):
		return 0, 1, b

	if b == bint.bint(0):
		return 1, 0, a

	px = bint.bint(0)
	ppx = bint.bint(1)
	py = bint.bint(1)
	ppy = bint.bint(0)

	while b > bint.bint(0):
		q = a / b
		a, b = b, a % b
		x = ppx - q * px
		y = ppy - q * py
		ppx, px = px, x
		ppy, py = py, y

	return ppx, ppy, a


def inverse(a, p):
	x, y, g = xgcd(a, p)

	return (x % p + p) % p


def gen_keys():
	
	f = open("p.txt")

	p = int(f.read())

	f.close()

	

	while True:
		g = random.randint(2, p - 1)

		if ((p - 1) % g) != 1:
			break

	x = random.randint(2, p - 1)

	p = bint.bint(str(p))

	g = bint.bint(str(g))

	x = bint.bint(str(x))

	y = p.powmod(g, x, p)

	return p, g, y, x


def elgamal(msg, p, g, y, x):

	msg = bint.bint(str(msg))

	if msg > p:
		raise ValueError("Неверная длина сообщения")

	pp = p.st()

	pp = int(pp)

	k = random.randint(2, pp - 1)

	k = bint.bint(str(k))

	a = p.powmod(g, k, p)                                               # Кодирование

	b = p.powmod(y, k, p)                                               # Кодирование
	b = (msg * b) % p

	print "code ( "+ str(a) + "," + str(b) + ")"

	decode_msg = p.powmod(a, x, p)                                      # Декодирование
	decode_msg = inverse(decode_msg, p)
	decode_msg = (decode_msg * b) % p

	return decode_msg


def usage():
	print "\nИспользование: python ElGamal.py msg.txt\n"

	sys.exit(-1)


def main():
	if len(sys.argv) != 2:
		usage()
	try:
		f = open(sys.argv[1])

		msg = int(f.read())
		
		f.close()
	except Exception:
		print "File not found!"
		sys.exit(-1)
	
	print "text " + str(msg)

	p, g, y, x = gen_keys()

	decode_msg = elgamal(msg, p, g, y, x)

	print "text " + str(decode_msg)


main()