clean: 
	rm *.o
	
main: fichier.o sequence.o algo.o main.cpp
	g++ fichier.o sequence.o algo.o main.cpp -o main -Wall

fichier.o: fichier.cpp
	g++ fichier.cpp -c -Wall
	
sequence.o: sequence.cpp
	g++ sequence.cpp -c -Wall

algo.o: algo.cpp
	g++ algo.cpp -c -Wall

