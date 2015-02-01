#!/usr/bin/python
# -*- coding: utf-8 -*-

import bint 
import sys
import random




def xgcd(a, b):
	"""Расширенный алгоритм Евклида

	"""
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


def generate_d(a, b):
	"""Генерирует число d

	"""
	while True:
		x, y, g = xgcd(a, b)

		if g != bint.bint(1):
			raise ValueError("Невозможно подобрать такое d, чтобы выполнялось условие d * e mod fi = 1.")
		else:
			z = x % b
			break
	return z


def rsa(q,p,e,m,n):

	fi = (p - bint.bint(1)) * (q - bint.bint(1))

	d = generate_d(e, fi)


	s = bint.bint()

	s = d.powmod(m,d,n)

	return m,s
	

def usage():
	print "\nИспользование: python RSA.py msg.txt\n"

	sys.exit(-1)


def main():
	if len(sys.argv) != 2:
		usage()

	f = open(sys.argv[1])

	msg = f.read()

	f.close()
	
	tmp = bint.bint()

	p = bint.bint(tmp.read("p.txt"))
	q = bint.bint(tmp.read("q.txt"))
	e = bint.bint(tmp.read("e.txt"))

	n = p * q


	m = bint.bint(str(bint.Hash(sys.argv[1])))
	
	m, sign = rsa(q,p,e,m,n)

	checksign = p.powmod(sign,e,n)


	print "sign: ("+str(m)+","+ str(sign)+ ")"


	if m == checksign:
		print "m==m' : "+str(m)+"=="+str(checksign)
		print "Sign is true!"
	else:
		print "m!=m' : "+str(m)+"!="+str(checksign)
		print "Sign is false!"

main()