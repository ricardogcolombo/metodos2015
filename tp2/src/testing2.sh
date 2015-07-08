rm TESTING2/*.txt
for i in `seq 1 50`; do
	echo "corriendo" $i
	VAR=". 1 $i 10"
	sed -i "1s/.*/$VAR/" ./TESTING2/test.in
	./tp TESTING2/test.in lol 1 2>> TESTING2/tiempos.txt
done