#!/bin/bash

rm tests/test*
python metnum.py clean
python metnum.py build
python tests/generador.py	
for x in 0 1 2 3 4 5 6 7 8 9 10
do
  ./tp "tests/test"$x".in" "tests/testGauss"$x".in" 0
  ./tp "tests/test"$x".in" "tests/testLU"$x".in" 1
  ./tp "tests/test"$x".in" "tests/testSalvacion"$x".in" 2
  ./tp "tests/test"$x".in" "tests/testSherm"$x".in" 3
done



