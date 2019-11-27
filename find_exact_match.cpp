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
vector<int8_t> sequence; //taille de la séquence

vector<tuple<int,int>> find_exact_match_pin(const char* file_fasta,const char* file_blast_pin){
	char outpout[LONG_MAX];
	sprintf(outpout,"%s.psq",file_fasta);
	
	sequence = translate(file_fasta,outpout);
	cout << sequence.size() << endl;
	
	vector <tuple<int,int>> res;
	
	res=read_pin_seq(file_blast_pin,sequence.size());
	for (int j=0;j<res.size();j++)
		cout << get<0>(res[j]) << " " << get<1>(res[j]) << endl;
		
	return res;
}

int find_exact_match_psq(vector<int8_t> sequence,const char* file_blast_psq,vector<tuple<int,int>> same_size){
	int compteur;
	int8_t protein;
	int8_t protein_blast;
	ifstream blast(file_blast_psq,ios::binary);
	if( blast.is_open() )
	{
		for(int i=0;i<same_size.size();i++)
		{
			protein = 0;
			protein_blast = 0;
			compteur = 0;
			blast.seekg(get<1>(same_size[i]));
			
			while(protein == protein_blast)
			{
				if(compteur==sequence.size())
				{
					return get<0>(same_size[i]);
				}
				blast.read((char *) (&protein_blast), sizeof(protein_blast));
				protein = sequence[compteur];
				cout<<"protein = "<<(int) protein << " blast " << (int) protein_blast<< endl;
				compteur++;
			}
		}
		blast.close();
		
	}
	else
		cout<< "fichier ne s'ouvre pas" <<endl;
	return -1;
}

void find_exact_match_phr(const char* filename,int header_offset){
	ifstream f(filename,ios::binary |ios::out);

	f.seekg(header_offset);
	
	f.ignore(7*sizeof(char));
	uint8_t n;
	
	f.read((char*) &n,sizeof(n));
	
	char a[(uint)n];
	f.read(a,sizeof(a));
	a[(uint)n]=0;
	
	cout << a << endl;

	f.close();
}


int main(int argc, char **argv)
{
	int test;
	if (argc != 3){
		cout << "Il faut 2 arguments" << endl;
		return 1;}
	else{
		
		vector<tuple<int,int>> res_size;
		res_size=find_exact_match_pin(argv[1],argv[2]);
		test = find_exact_match_psq(sequence, "uniprot_sprot.fasta.psq", res_size);
		if ( test == -1)
			cout << "Aucun match n'a été trouvé, vérifiez votre protéine" << endl;
		cout<< test<<endl;
		find_exact_match_phr("uniprot_sprot.fasta.phr",test);
	}	
	
	return 0;
}

