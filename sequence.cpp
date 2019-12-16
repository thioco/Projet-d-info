#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>


using namespace std;


class Sequence
{
	protected:
		int prot_len;
	public:
		int getprot_len()
		{
			return prot_len;
		}
};

class Sequence_Blast: public Sequence
{
		int psqoff;
		int hdroff;
		int score;
		
	public:
		Sequence_Blast(int offset, int size)
		{
			psqoff = offset;
			prot_len = size;
		}
		void update_score(int points)
		{
			score = points;
		}
		int getpsqoff()
		{
			return psqoff;
		}
		int gethdroff()
		{
			return hdroff;
		}
		int getscore()
		{
			return score;
		}
		
};


class Sequence_Fasta: public Sequence
{
	vector<int8_t> sequence;
public:
	Sequence_Fasta(const char* fasta)
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
			prot_len = sequence.size();
		}
		else
			cout << "Rentrez un nom de fichier correct" << endl;
		sequence.push_back(0);
	}
	
	vector<int8_t> fct_case_vector(vector<int8_t> prot,char c)
	{
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
	//par principe on s'assure d'avoir un const
	const vector<int8_t> getsequence()
	{
		return sequence;
	}
};
