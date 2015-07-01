g++ tester.cp -o tester
for i in `seq 1 $2`; do
	echo "corriendo" $i
	./tester $i 1 5
	./tp test.txt pop 1
done