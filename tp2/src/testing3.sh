rm TESTING3/*.txt
for i in `seq 1 50`; do
	echo "corriendo" $i
	VAR=". 3 $i 10"
	sed -i "1s/.*/$VAR/" ./TESTING3/test.in
	./tp TESTING3/test.in lol3 1 2>> TESTING3/tiempos.txt
done