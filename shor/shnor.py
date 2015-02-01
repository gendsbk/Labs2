#!/usr/bin/python
# -*- coding: utf-8 -*-

import bint
import sys
import random





def evklid(a, b):
	
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
	x, y, g = evklid(a, p)

	return (x % p + p) % p


def keys():
	
	f = open("p.txt")

	p = int(f.read())

	f.close()

	f = open("q.txt")

	q = int(f.read())

	f.close()

	f = open("g.txt")

	g = int(f.read())

	f.close()

	
	w = random.randint(2, q - 1)

	r = random.randint(2, q - 1)

	p = bint.bint(str(p))
	q = bint.bint(str(q))
	g = bint.bint(str(g))
	w = bint.bint(str(w))
	r = bint.bint(str(r))

	inv_g = inverse(g, p)

	y = p.powmod(inv_g, w, p)

	x = p.powmod(g, r, p)

	print "\nKeys is ready:"

	print "x = ", x, "to Bob"

	return p, q, g, w, r, y, x


def shnor(p, q, g, w, r, y, x):
	e = random.randint(0, pow(2, 20) - 1)

	e = bint.bint(str(e))

	print "e = ", e, "to Alice"

	s = (r + w * e) % q

	print "s = ", s, "to Bob"

	m1 = p.powmod(g, s, p)
	m2 = p.powmod(y, e, p)

	m = (m1 * m2) % p

	if m == x:
		print "Alice is  Alise x = ", m, ""
	else:
		print "Wrong"


def main():
	p, q, g, w, r, y, x = keys()

	shnor(p, q, g, w, r, y, x)
main()