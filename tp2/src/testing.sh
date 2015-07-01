g++ TESTING/tester.cp -o ./TESTING/tester
python metnum.py clean
python metnum.py
rm TESTING/*.txt
for i in `seq 1 $1`; do
	echo "corriendo" $i
	./TESTING/tester $i 1 5
	./tp TESTING/test.txt lol 0 2>> tiempos.txt
done