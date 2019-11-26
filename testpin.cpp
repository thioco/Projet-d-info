#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <byteswap.h>
#include <iterator>
using namespace std;

	
int main(int argc, char *argv[])
{
	typedef vector<tuple<int, int> > my_tuple;
	my_tuple index;//faire deux vectors des offsets
	ifstream in ("P00533.fasta.pin", ios::binary);
	ofstream out ("out_pin.txt");
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
		debut+= 12;
		in.ignore(20);
		in.read((char *) (&x), sizeof(x) );
		
		
		for (i=1;i<lengthdata+1;i++){
			
			in.seekg(debut+((i+lengthdata+1)*4)); //trouve offset de séquence
			in.read((char *) (&x), sizeof(x) );
			begin = bswap_32((int32_t) x );
			
			in.seekg(debut+((i+lengthdata+2)*4)); //trouve offset de séquence suivante
			in.read((char *) (&x), sizeof(x) );
			end = bswap_32((int32_t) x );
			
			cout<< "end"<< end<<endl; // print pour vérifier si offset correct
			cout<<"begin"<< begin<<endl;
			
			if (end - begin == lengthprotein) //condition pour mettre dans tuple
			{
				in.seekg(debut+(i*4));
				in.read((char *) (&x), sizeof(x) );
				headeroff = bswap_32((int32_t) x ); //trouve offset header équivalent
				index.push_back(tuple<int, int>(headeroff,begin) ); 
				
				
			}
			
		}
		 cout << get<0>(index[0]) << endl;
		 cout << get<1>(index[0]) << endl;
    
		
		
		
		/*while( in.read((char *) (&x), sizeof(x) )){ //lecture byte par byte (sizeof(x) = 1 )
			i++;
			cout << hex << bswap_32((int32_t) x )<< endl;
			if (i == 3){
				p = bswap_32((int32_t)x)/4;
			}
			if (i == 3+p){
				d = bswap_32((int32_t)x)/4;
			}
			if (i == 4+p+d){
				c = bswap_32((int32_t)x)/4;
			}
			if (7+p+d < i =< 7+p+d+c){
				
			}
		}*/
	}
	else
		cout << "Impossible d'ouvrir le fichier" << endl;
		
	in.close();
	out.close();
	cout << endl;
	
	return 0;
	
}
