g++ TESTING/tester.cp -o ./TESTING/tester
python metnum.py clean
python metnum.py
rm TESTING/*.txt
for i in `seq 1 $1`; do
	echo "corriendo" $i
	./TESTING/tester 3 $i 5
	./tp TESTING/test.txt lol 1 2>> TESTING/tiempos.txt
done