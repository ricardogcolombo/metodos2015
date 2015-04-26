#!/bin/bash

python metnum.py clean
python metnum.py build

python tests/generador.py	
for x in 0 1 2 3 4 5 6 7 8 9 10
do
  ./tp "tests/test"$x".in" "tests/sherman/testSherma"$x".out" 3
  ./tp "tests/test/test"$x".in" "tests/sherman/testShermb"$x".out" 3
  ./tp "tests/test/test2/test"$x".in" "tests/sherman/testShermc"$x".out" 3
done



