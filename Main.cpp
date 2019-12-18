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
		Fichier fich (argv[2]);
		Sequence_Fasta fasta (argv[1]); 
		
		Sequence bidon;
		Fichier_head phr (argv[2]);
		Fichier_index pin (argv[2]);
		Fichier_sequence psq (argv[2]);
		Algorithme algo(&fasta, &psq);
		
		for(int i=0;pin.getnbreprot(); i++)
		{
			Sequence_Blast seq (pin.getseqoffset(i),pin.getsize(i));
			algo.SW_Gotoh_SWIPE(&seq);
			cout<<"we good"<<endl;
			
		}
	}
	return 0;
}
