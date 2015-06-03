python metnum.py clean
python metnum.py
rm -r TESTEADOR/*.txt
g++ TESTEADOR/generadorEntrada.cp -o generadorEntrada
for i in {5..20}
do 
	echo "Corriendo instancia para " $(($i*10)) "Sanguijuelas"
	./generadorEntrada $(($i*10)) 50 10 
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output0 0
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output1 1
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output2 2
	./tp TESTEADOR/instancia.txt TESTEADOR/out/output3 3
done
