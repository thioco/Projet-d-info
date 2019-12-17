#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>
#include <algorithm>

#include "algo.cpp"

using namespace std;

void recur_list_seq(vector<Sequence_Blast*> list_seq,Sequence_Blast* seq);

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Il faut 2 arguments" << endl;
		return 1;
	}
	else
	{
		Sequence_Fasta* fasta = new Sequence_Fasta(argv[1]); 
		
		Fichier_head* phr = new Fichier_head(argv[2]);
		Fichier_index* pin = new Fichier_index(argv[2]);
		Fichier_sequence* psq = new Fichier_sequence(argv[2]);
		Algorithme* algo = new Algorithme(fasta, psq);
		
		int init_map = 0;
		vector<Sequence_Blast*> list_seq;
		
		cout << "Nombre de séquences : "<< pin->getnbreprot() << endl;
		
		for(int i=0;i<pin->getnbreprot(); i++)
		{
			Sequence_Blast* seq = new Sequence_Blast(pin->getheadoffset(i),pin->getseqoffset(i),pin->getsize(i));//pin->getsize(i) un truc du style
			
			//cout << "Longueur fasta :" << fasta->getprot_len() << " Longueur blast :" << seq->getprot_len() << endl;
			
			algo->SW_Gotoh_SWIPE(seq);
			//cout << "raw score: " << seq->getscore() << " bit score= " << (0.267*(seq->getscore()) + 3.34)/(0.693) << endl;
			
			//phr->getprotname(seq->gethdroff());
			
			if(init_map < 5){
				list_seq.push_back(seq);
				init_map++;
			}
			else
				recur_list_seq(list_seq,seq);
		}
		/////
		
		
		/////
		for(uint j=0;j<list_seq.size();j++){
			phr->getprotname((list_seq[j])->gethdroff());
			cout << "raw score: " << (list_seq[j])->getscore() << " bit score= " << (0.267*((list_seq[j])->getscore()) + 3.34)/(0.693) << endl;
			delete list_seq[j];}
		
		delete(fasta);
		delete(phr);
		delete(pin);
		delete(psq);
		delete(algo);
	}
	return 0;
}

void recur_list_seq(vector<Sequence_Blast*> list_seq, Sequence_Blast* seq){
	int size = list_seq.size();
	int n;
	for(n=0;n<size;n++){
		if((list_seq[n])->getscore() < seq->getscore()){
			Sequence_Blast* temp = list_seq[n];
			list_seq[n] = seq;
			recur_list_seq(list_seq,temp);
			break;
		}
	}
	if(n==5){
		delete seq;
	}
	
}









