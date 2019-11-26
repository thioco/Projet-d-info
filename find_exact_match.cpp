/*<>*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>
#include <tuple>

#include "fasta_to_txt.h"
#include "read_blast.h"

#define LONG_MAX 50
using namespace std;
int* size_S; //taille de la séquence

vector<tuple<int,int>> find_exact_match_pin(const char* file_fasta,const char* file_blast_pin){
	char outpout[LONG_MAX];
	sprintf(outpout,"%s.txt",file_fasta);
	
	*size_S = translate(file_fasta,outpout);
	cout << *size_S << endl;
	
	vector <tuple<int,int>> res;
	
	res=read_pin_seq(file_blast_pin,*size_S);
	for (int j=0;j<res.size();j++)
		cout << get<0>(res[j]) << " " << get<1>(res[j]) << endl;
		
	return res;
}

int find_exact_match_psq(const char* file_fasta_txt,const char* file_blast_psq,vector<tuple<int,int>> same_size){
	
}

int main(int argc, char **argv)
{
	if (argc != 3){
		cout << "Il faut 2 arguments" << endl;
		return 1;}
	else{
		size_S=new int;
		vector<tuple<int,int>> res_size;
		res_size=find_exact_match_pin(argv[1],argv[2]);
	}
	
	return 0;
}

