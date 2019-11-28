/*<>
 * Auteur : Losfeld Armand, Courboin Samuel, Hioco Thomasso
 * Date : 28/11/19
 * Description : 
 * Fichier principale du code possèdant 3 fonctions
 */
 
#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>
#include <tuple>

#include "read_fasta.h"
#include "read_blast.h"

#define LONG_MAX 50
using namespace std;
vector<int8_t> sequence; //Séquence de la protéine

vector<tuple<int,int>> find_exact_match_pin(const char* file_fasta,const char* file_blast_pin){
	char outpout[LONG_MAX];
	sprintf(outpout,"%s.psq",file_fasta);
	
	sequence = translate(file_fasta,outpout);
	cout << "Taille de la séquence :"<< sequence.size() << endl;
	
	vector <tuple<int,int>> res;
	
	res=read_pin_seq(file_blast_pin,sequence.size());
		
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
				compteur++;
			}
		}
		blast.close();
		
	}
	else
		cout<< "Impossible d'ouvrir le fichier" <<endl;
	return -1;
}

void find_exact_match_phr(const char* filename,int header_offset){
	ifstream f(filename,ios::binary |ios::out);

	f.seekg(header_offset);
	
	f.ignore(7*sizeof(char)); //On ignore 8bytes selon le template du phr
	uint8_t n;
	
	f.read((char*) &n,sizeof(n));
	
	char a[(uint)n];
	f.read(a,sizeof(a));
	a[(uint)n]=0; //Des caractères s'ajoutent en plus pour aucune raison...
	
	cout << "Le nom du fichier est :" << endl;
	cout << a << endl;

	f.close();
}


int main(int argc, char **argv)
{
	if (argc != 3){
		cout << "2 arguments requis : proteine.fasta et database.fasta" << endl;
		return -1;}
	else{
		vector<tuple<int,int>> res_size;
		int sequence_match;
		char blast[LONG_MAX];
	
		sprintf(blast,"%s.pin",argv[2]);
		
		res_size=find_exact_match_pin(argv[1],blast);
		
		if (res_size.size() == 0)
			return -2;
		
		sprintf(blast,"%s.psq",argv[2]);
		
		sequence_match = find_exact_match_psq(sequence, blast, res_size);
		if ( sequence_match == -1) {
			cout << "Aucun match n'a été trouvé, vérifiez votre protéine" << endl;
			return -2;
		}
		
		sprintf(blast,"%s.phr",argv[2]);
		
		find_exact_match_phr(blast,sequence_match);
	}	
	
	return 0;
}

