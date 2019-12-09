#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>

using namespace std;

class Fichier
{
private:
const char* name;
public:
Fichier(const char* fichier = 0)
{
	name = fichier;
}
const char* getname()
{
	return name;
}
};

class Fichier_head: public Fichier
{
private:
	char name[50];
public:
	Fichier_head(const char* fichier = 0)
	{
		sprintf(name,"%s.phr",fichier);
	}
	const char* getname()
	{
		return name;
}
	
};

class Fichier_index: public Fichier
{
private:
	char name[50];
	int debut;
	int lengthdata;
public:
	Fichier_index(const char* fichier = 0)
	{
		sprintf(name,"%s.pin",fichier);
		ifstream in(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			debut = 8;
			in.read((char *) (&x), sizeof(x) );
			debut += 4+bswap_32((int32_t)x);
			in.ignore(bswap_32((int32_t)x));
		
			in.read((char *) (&x), sizeof(x) );
			debut += 4+bswap_32((int32_t)x);
			in.ignore(bswap_32((int32_t)x));
		
			in.read((char *) (&x), sizeof(x) );
			lengthdata =  bswap_32((int32_t) x );

			debut+= 16;
		}
	}
	
	const char* getname()
	{
		return name;
	}
	
	int getseqoffset(int i)
	{
		ifstream in(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i+lengthdata)*4);
			in.read((char *) (&x), sizeof(x) );
			return bswap_32((int32_t) x );
		}
	}
	int getheadoffset(int i)
	{
		ifstream in(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+i*4);
			in.read((char *) (&x), sizeof(x) );
			return bswap_32((int32_t) x );
		}
	}
};

class Fichier_sequence: public Fichier
{
private:
char name[50];
public:
Fichier_sequence(char fichier = 0)
{
	sprintf(name,"%s.psq",fichier);
}

const char* getname()
{
	return name;
}
	
};

class Sequence
{
private:
	vector<int8_t> sequence;
public:
	Sequence(const char* fasta)
	{
		FILE* f=fopen(fasta,"r");

	
	
	if (f != NULL) {
	
		char c; /*Un seul caractère = un seul acide aminé*/
		char poubelle[500]="";
		fgets(poubelle,500,f);

		for (c=getc(f);c!=EOF;c=getc(f)){
			sequence = fct_case_vector(sequence,c);
		}
		fclose(f);
	}
	else
		cout << "Rentrez un nom de fichier correct" << endl;
	sequence.push_back(0);
	}
	
	vector<int8_t> fct_case_vector(vector<int8_t> prot,char c){
	
	int8_t a;
	switch(c) {
		case 'A':
			a = 1;
			prot.push_back(a);
			break;
		case 'B':
			a = 2;
			prot.push_back(a);
			break;
		case 'C':
			a = 3;
			prot.push_back(a);
			break;
		case 'D':
			a = 4;
			prot.push_back(a);
			break;
		case 'E':
			a = 5;
			prot.push_back(a);
			break;
		case 'F':
			a = 6;
			prot.push_back(a);
			break;
		case 'G':
			a = 7;
			prot.push_back(a);
			break;
		case 'H':
			a = 8;
			prot.push_back(a);
			break;
		case 'I':
			a = 9;
			prot.push_back(a);
			break;
		case 'J':
			a = 27;
			prot.push_back(a);
			break;
		case 'K':
			a = 10;
			prot.push_back(a);
			break;
		case 'L':
			a = 11;
			prot.push_back(a);
			break;
		case 'M':
			a = 12;
			prot.push_back(a);
			break;
		case 'N':
			a = 13;
			prot.push_back(a);
			break;
		case 'O':
			a = 26;
			prot.push_back(a);
			break;
		case 'P':
			a = 14;
			prot.push_back(a);
			break;
		case 'Q':
			a = 15;
			prot.push_back(a);
			break;
		case 'R':
			a = 16;
			prot.push_back(a);
			break;
		case 'S':
			a = 17;
			prot.push_back(a);
			break;
		case 'T':
			a = 18;
			prot.push_back(a);
			break;
		case 'U':
			a = 24;
			prot.push_back(a);
			break;
		case 'V':
			a = 19;
			prot.push_back(a);
			break;
		case 'W':
			a = 20;
			prot.push_back(a);
			break;
		case 'X':
			a = 21;
			prot.push_back(a);
			break;
		case 'Y':
			a = 22;
			prot.push_back(a);
			break;
		case 'Z':
			a = 23;
			prot.push_back(a);
			break;
	}
	return prot;
	
}
	vector<int8_t> getsequence()
	{
		return sequence;
	}
};

int main(){
	return 0;
}
