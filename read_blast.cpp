#include <iostream>
#include <fstream>
#include <vector>
#include <byteswap.h>
#include <tuple>

#include "read_blast.h"


using namespace std;
/*<>*/

vector<tuple<int,int>> read_pin_seq(const char* file_blast, int n){
	ifstream in(file_blast,ios::binary |ios::in);
	typedef vector<tuple<int, int> > my_tuple;
	my_tuple index;//faire deux vectors des offsets
	int lengthdata ;
	int debut = 8;
	int lengthprotein = 1211;
	int begin;
	int end;
	int i;
	int headeroff;
	if( in.is_open() )
	{
		uint32_t x;
		in.ignore(8);
		in.read((char *) (&x), sizeof(x) );
		debut += 4+bswap_32((int32_t)x);
		in.ignore(bswap_32((int32_t)x));
		
		in.read((char *) (&x), sizeof(x) );
		debut += 4+bswap_32((int32_t)x);
		in.ignore(bswap_32((int32_t)x));
		
		in.read((char *) (&x), sizeof(x) );
		lengthdata =  bswap_32((int32_t) x );
		cout<< debut<<endl;
		debut+= 16;
		in.ignore(20);
		in.read((char *) (&x), sizeof(x) );
		
		
		for (i=0;i<lengthdata+1;i++){
			
			in.seekg(debut+((i+lengthdata+1)*4)); //trouve offset de séquence
			in.read((char *) (&x), sizeof(x) );
			begin = bswap_32((int32_t) x );
			
			//in.seekg(debut+((i+lengthdata+2)*4)); //trouve offset de séquence suivante
			in.read((char *) (&x), sizeof(x) );
			end = bswap_32((int32_t) x );
			
			
			
			if (end - begin == n) //condition pour mettre dans tuple
			{
				//cout<< "end"<< end<<endl; // print pour vérifier si offset correct
				//cout<<"begin"<< begin<<endl;
				in.seekg(debut+(i*4));
				in.read((char *) (&x), sizeof(x) );
				headeroff = bswap_32((int32_t) x ); //trouve offset header équivalent
				index.push_back(tuple<int, int>(headeroff,begin) ); 
				
				
			}
			
		}
		 
    
		
		

	}
	else
		cout << "Impossible d'ouvrir le fichier" << endl;
	
	in.close();
	return index;
	
}
