#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "algo.cpp"

using namespace std;

//<>

int gap_open = 11;
int gap_extension = 1;

void recur_list_seq(vector<Sequence_Blast*> list_seq,Sequence_Blast* seq);

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		cout << "2 arguments requis : query_sequence.fasta database.fasta" << endl;
		cout << "Des options supplémentaires peuvent être ajoutées, consultez README pour plus d'informations." << endl;
		return 1;
	}
	else if (argc > 3){
		for(int arg=3;arg<argc;arg++){
			if(!strcmp(argv[arg],"-gap_open")){
				if(argc > arg+1){
					gap_open = atoi(argv[arg+1]);
					arg++;}
				else{
					cout << "Valeur pour gap_open manquante." << endl;
					return 2;
				}
			}
			else if(!strcmp(argv[arg],"-gap_ext")){
				if(argc > arg+1){
					gap_extension = atoi(argv[arg+1]);
					arg++;}
				else{
					cout << "Valeur pour gap_extension manquante." << endl;
					return 2;
				}
			}
			else if(!strcmp(argv[arg],"-blosum")){
				if(argc > arg+1){
					//read blosum
					cout <<" ";
					arg++;}
				else{
					cout << "Chemin de la BLOSUM manquante." << endl;
					return 2;}
			}
			else{
				cout << "Veuillez consulter le README pour ajouter des options." << endl;
				return -2;
			}
		}
	}
	
	clock_t tStart = clock();
		
	Sequence_Fasta* fasta = new Sequence_Fasta(argv[1]); 
		
	Fichier_head* phr = new Fichier_head(argv[2]);
	Fichier_index* pin = new Fichier_index(argv[2]);
	Fichier_sequence* psq = new Fichier_sequence(argv[2]);
	Algorithme* algo = new Algorithme(fasta, psq,gap_open,gap_extension);
		
	int init_map = 0;
	vector<Sequence_Blast*> list_seq;
		
	cout << "Nombre de séquences : "<< pin->getnbreprot() << endl;
		
	for(int i=0;i<pin->getnbreprot(); i++)
	{
		Sequence_Blast* seq = new Sequence_Blast(pin->getheadoffset(i),pin->getseqoffset(i),pin->getsize(i));//pin->getsize(i) un truc du style
			
		algo->SW_Gotoh_SWIPE(seq);
			
		if(init_map < 5){
			list_seq.push_back(seq);
			init_map++;
		}
		else
			recur_list_seq(list_seq,seq);
	}
	
	cout << endl;
	cout << "Le temps pris par l'algorithme : " << (double)(clock()-tStart)/(CLOCKS_PER_SEC)  << " secondes."<< endl << endl;
	for(uint j=0;j<list_seq.size();j++){
		phr->getprotname((list_seq[j])->gethdroff());
		cout << "raw score: " << (list_seq[j])->getscore() << ", bit score= " << (0.267*((list_seq[j])->getscore()) + 3.34)/(0.693) << endl << endl;
		delete list_seq[j];}
		
	delete(fasta);
	delete(phr);
	delete(pin);
	delete(psq);
	delete(algo);

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









