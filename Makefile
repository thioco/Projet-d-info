find_exact: read_fasta.o read_blast.o
	g++ read_fasta.o read_blast.o find_exact_match.cpp -o main
	
read_fasta.o: read_fasta.cpp
	g++ read_fasta.cpp -c

read_blast.o: read_blast.cpp
	g++ read_blast.cpp -c

clean: 
	rm *.o
