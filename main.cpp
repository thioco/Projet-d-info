#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>
#include <tuple>

#include "Class.cpp"


using namespace std;

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
		
		cout << "Nombre de séquences : "<< pin->getnbreprot() << endl;
		
		for(int i=0;i<pin->getnbreprot(); i++)
		{
			Sequence_Blast* seq = new Sequence_Blast(pin->getseqoffset(i),1210);//pin->getsize(i) un truc du style
			
			cout << "Longueur fasta :" << fasta->getprot_len() << " Longueur blast :" << seq->getprot_len() << endl;
			
			algo->SW_Gotoh_SWIPE(seq);
			cout << "raw score: " << seq->getscore() << " bit score= " << (0.267*(seq->getscore()) + 3.34)/(0.693) << endl;
			delete(seq);
		}
		delete(fasta);
		delete(phr);
		delete(pin);
		delete(psq);
		delete(algo);
	}
	return 0;
}
