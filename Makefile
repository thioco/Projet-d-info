clean: 
	rm *.o
	
main: fichier.o sequence.o algo.o blosum.o main.cpp
	g++ -O3 -Ofast fichier.o sequence.o algo.o blosum.o main.cpp -o main -Wall

fichier.o: fichier.cpp
	g++ -O3 -Ofast fichier.cpp -c -Wall
	
sequence.o: sequence.cpp
	g++ -O3 -Ofast sequence.cpp -c -Wall

algo.o: algo.cpp
	g++ -O3 -Ofast algo.cpp -c -Wall
	
blosum.o: blosum.cpp
	g++ -O3 -Ofast blosum.cpp -c -Wall

