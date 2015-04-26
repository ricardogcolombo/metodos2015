#! /usr/bin/env python

from random import randint
print("GENERANDO CASOS DE TEST...")
for j in range(1,10):
	fo = open("tests/test"+str(j)+".in", "wb")
	n = 100
	m = 100
	h = randint(1,30)
	cantsang = 10
        fo.write(str(n) + " " + str(m) + " " + str(h) + " " + str(cantsang))
	fo.write("\n")
	for x in range(1, cantsang):
	    sx = randint(1,n)
	    sy = randint(1,m)
            stemp = randint(1,999)
	    sradio = randint(1,10)
	    fo.write(str(sx) + " " + str(sy) + " " + str(sradio) + " " + str(stemp))
	    fo.write("\n")
	fo.close()
