#include <iostream>
#include <fstream>
#include <vector>
#include <byteswap.h>
#include <tuple>

#include "read_blast.h"


using namespace std;
/*<>*/

vector<tuple<int,int>> read_pin_seq(const char* file_blast, int n){
	ifstream f(file_blast,ios::binary |ios::in);
	
	vector<tuple<int,int>> res;//Premier int = N de séq et second Position dans séq
	int previous = 0;
	int next=0;
	int N; //nombre de séquences
	int begin_header;
	int offset_h;
	
	if(f.is_open()){
		//On ignore toutes les informations qu'on a pas besoin
		f.ignore(8);
		f.read((char*) (&next),sizeof(next));
		f.ignore(bswap_32((int)next));
		begin_header += 4+bswap_32((int32_t)next);
		
		f.read((char*) (&next),sizeof(next));
		f.ignore(bswap_32((int)next));
		begin_header += 4+bswap_32((int32_t)next);
		
		f.read((char*) (&N),sizeof(N));
		
		f.ignore(12);
		begin_header += 16;
		
		//f.ignore(bswap_32((int) N)*4);
		
		for(int i=0;i<N+2;i++){
			f.seekg(begin_header+((i+N+1)*4));
			f.read((char*) (&next),sizeof(next));
			next = bswap_32((int) next);
			
			cout << f.tellg() << endl;
			if ((next-previous) == n){
				cout << "ffsfse" << endl;
				f.seekg(begin_header+i*4);
				f.read((char*) (&offset_h),sizeof(offset_h));
				offset_h = bswap_32((int) offset_h);
				res.push_back({offset_h,previous});
			}
			previous = next;
		}
		f.close();
	}
	else
		cout << "Rentrez un nom de fichier correct" << endl;
	return res;
}
