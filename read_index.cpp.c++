/*<>*/
#include <iostream>
#include <cstdio>
#include <fstream>


using namespace std;

//Pour transformer les int en big ou little endian
inline void endian_swap(int& x){
	x = (x>>24) |
		((x<<8) & 0x00FF0000)|
		((x>>8) & 0x0000FF00)|
		(x<<24);
}

int main(int argc, char* argv[]){
	int32_t i;
	int it=0;//Pour savoir ce qu'on est entrain de lire voir tableau .pin
	ifstream f1(argv[1],ios::binary|ios::in);
	if (f1.is_open()) {
		while(true){//voir break;
			if(it==3 || it==5) //Voir tableau: char[T] et char[S]
				f1.seekg(i,ios::cur);//On déplace les curseurs de i*char = i*8octets
			else if (it==7)//Voir tableau: int64
				f1.seekg(8,ios::cur);
			else{
				if (!f1.read((char*) (&i),sizeof(i)))
					break; //se ferme quand on a plus rien à lire
				endian_swap(i);
				cout << (int) i << endl;
			}
			it++;
		}
	}
	f1.close();
}
