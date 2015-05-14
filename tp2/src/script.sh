 #!/bin/bash
for vecinos in 1 .. 10
do
	sed -i -e "1d" tests/test1.in
	echo '/data/ ' $vecinos ' 10 5' | cat - tests/test1.in > temp && mv temp tests/test1.in
    ./tp tests/test1.in output 1 >> log
done