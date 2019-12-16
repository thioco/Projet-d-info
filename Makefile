clean: 
	rm *.o
	
main: fichier.o sequence.o algo.o main.cpp
	g++ Class.o main.cpp -o main

fichier.o: fichier.cpp
	g++ fichier.cpp -c
	
sequence.o: sequence.cpp
	g++ sequence.cpp -c

algo.o: algo.cpp
	g++ algo.cpp -c

