#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>


using namespace std;

class Fichier
{
protected:
	char name[50];
	ifstream in;
public:
	Fichier(const char* fichier = 0)
	{
		strcpy(name,fichier);
	}
	const char* getname()
	{
		return name;
	}
	void Open(int offset)
	{
		in.open(name, ios::binary|ios::out);
		in.seekg(offset);
	}
	void Close()
	{
		in.close();
	}
};



class Fichier_head: public Fichier
{
public:
	Fichier_head(const char* fichier = 0) : Fichier(fichier)
	{
		sprintf(name,"%s.phr",fichier);
	}
	
	char getprotname(int offset)
	{
		in.open(name,ios::binary |ios::out);
		in.seekg(offset);
		in.ignore(7*sizeof(char)); //On ignore 8bytes selon le template du phr
		uint8_t n;
		in.read((char*) &n,sizeof(n));
		char a[(uint)n];
		in.read(a,sizeof(a));
		a[(uint)n]=0; //Des caractères s'ajoutent en plus pour aucune raison...
	
		cout << "Le nom du fichier est :" << endl;
		cout << a << endl;
		in.close();
	}
};



class Fichier_index: public Fichier
{
	int debut;
	int nbreprot;
public:
	Fichier_index(const char* fichier = 0): Fichier(fichier)
	{
		sprintf(name,"%s.pin",fichier);
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			
			in.ignore(8);
			debut = 8;
			in.read((char *) (&x), sizeof(x) );
			debut += 4+bswap_32((int32_t)x);
			in.ignore(bswap_32((int32_t)x));
		
			in.read((char *) (&x), sizeof(x) );
			debut += 4+bswap_32((int32_t)x);
			in.ignore(bswap_32((int32_t)x));
		
			in.read((char *) (&x), sizeof(x) );
			nbreprot =  bswap_32((int32_t) x );
			
			debut+= 16;
			in.close();
		}
	}

	int getseqoffset(int i)
	{
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i+1+nbreprot)*4);
			in.read((char *) (&x), sizeof(x) );
			in.close();
			return bswap_32((int32_t) x);
		}
	}
	
	int getheadoffset(int i)
	{
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i-1)*4);//Si pas bon titre regardez ici
			in.read((char *) (&x), sizeof(x) );
			in.close();
			return bswap_32((int32_t) x );
		}
	}
	
	int getnbreprot()
	{
		return nbreprot;
	}
	
	int getsize(int i)
	{
		int begin, end;
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i+1+nbreprot)*4);
			in.read((char *) (&x), sizeof(x));
			begin = bswap_32((int32_t) x );
		
			//in.seekg(debut+(i+nbreprot)*4);
			in.read((char *) (&x), sizeof(x));
			end = bswap_32((int32_t) x );
			in.close();
		}
		return (end - begin-1);
		
	}
};



class Fichier_sequence: public Fichier
{
public:
	Fichier_sequence(const char* fichier = 0): Fichier(fichier)
	{
		sprintf(name,"%s.psq",fichier);
	}
	void Read(int byte, uint8_t *var)
	{
		if( in.is_open() )
		{
			in.read((char *) (var), sizeof(char)*byte);
		}
	}
	
};
