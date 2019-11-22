find_exact: fasta_to_txt.o read_blast.o
	g++ fasta_to_txt.o read_blast.o find_exact_match.cpp -o main
	
fasta_to_txt.o: fasta_to_txt.cpp
	g++ fasta_to_txt.cpp -c

read_blast.o: read_blast.cpp
	g++ read_blast.cpp -c

clean: 
	rm *.o
	rm *.txt
