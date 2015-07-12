g++ TESTING/tester.cp -o ./TESTING/tester
python metnum.py clean
python metnum.py
rm TESTING/*.txt
for i in `seq 1 30`; do
	echo "corriendo" $i
	VAR=". $i 14 10"
	sed -i "1s/.*/$VAR/" ./TESTING/test.in
	./tp TESTING/test.in lol 1 2>> TESTING/tiempos.txt
done
