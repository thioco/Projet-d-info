/*<>*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>

#include "fasta_to_txt.h"
#include "read_blast.h"

#define LONG_MAX 50
using namespace std;

vector<int> find_exact_match_pin(const char* file_fasta,const char* file_blast){
	char outpout[LONG_MAX];
	sprintf(outpout,"%s.txt",file_fasta);
	
	int size_S;//taille de la séquence
	size_S = translate(file_fasta,outpout);
	cout << size_S << endl;
	
	vector <int> i;
	
	i=read_pin_seq(file_blast,size_S);
	for (int j=0;j<i.size();j++)
		cout << i[j] << endl;
	return i;
}

int main(int argc, char **argv)
{
	if (argc != 3)
		cout << "Il faut 2 arguments" << endl;
	else 
		find_exact_match_pin(argv[1],argv[2]);
	
	return 0;
}

