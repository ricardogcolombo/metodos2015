rm *.txt
g++ corrector.cpp -o corrector -O2 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
for i in `seq 1 $2`; do
	echo $i
    ./tp k$1/$i.res.png 1 2
    ./corrector k$1/$i.png res.jpg >> metodo1.txt

    ./tp k$1/$i.res.png 2 2
    ./corrector k$1/$i.png res.jpg >> metodo2.txt

    ./tp k$1/$i.res.png 3 2
    ./corrector k$1/$i.png res.jpg >> metodo3.txt
done