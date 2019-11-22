#include <iostream>
#include <fstream>
#include <vector>
#include <byteswap.h>

#include "read_blast.h"


using namespace std;
/*<>*/

vector<int> read_pin_seq(const char* file_blast, int n){
	ifstream f(file_blast,ios::binary |ios::in);
	
	vector<int> res;
	int previous = 0;
	int next;
	int N; //nombre de séquences
	
	if(f.is_open()){
		//On ignore toutes les informations qu'on a pas besoin
		f.ignore(8);
		f.read((char*) (&next),sizeof(next));
		f.ignore(bswap_32((int)next));
		f.read((char*) (&next),sizeof(next));
		f.ignore(bswap_32((int)next));
		
		f.read((char*) (&N),sizeof(N));
		
		f.ignore(12);
		f.ignore(bswap_32((int) N)*4);
		
		for(int i=0;i<N+2;i++){
			f.read((char*) (&next),sizeof(next));
			next = bswap_32((int) next);
			
			if ((next-previous) == n)
				res.push_back(previous);
			previous = next;
		}
		f.close();
	}
	else
		cout << "Rentrez un nom de fichier correct" << endl;
	return res;
}
