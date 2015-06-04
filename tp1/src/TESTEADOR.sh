python metnum.py clean
python metnum.py
rm -r TESTEADOR/*.txt
g++ TESTEADOR/generadorEntrada.cp -o generadorEntrada
for i in {0..9}
do 
	echo "Corriendo instancia para " 0.$(($i*10)) "Sanguijuelas"
	./generadorEntrada 100 100 4 0.$i
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output0 0
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output1 1
done
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output2 2
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output3 3
