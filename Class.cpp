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
	Fichier_head(const char* fichier = 0)
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
	Fichier_index(const char* fichier = 0)
	{
		sprintf(name,"%s.pin",fichier);
		in.open(name,ios::binary |ios::in);
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
			in.seekg(debut+(i+nbreprot)*4);
			in.read((char *) (&x), sizeof(x) );
			in.close();
			return bswap_32((int32_t) x );
		}
	}
	
	int getheadoffset(int i)
	{
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+i*4);
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
		uint32_t x;
		in.seekg(debut+(i+nbreprot)*4);
		int begin = bswap_32((int32_t) x );
		
		in.seekg(debut+(i+nbreprot+1)*4);
		int end = bswap_32((int32_t) x );
		
		return (end - begin);
		
	}
};



class Fichier_sequence: public Fichier
{
public:
	Fichier_sequence(const char* fichier = 0)
	{
		sprintf(name,"%s.psq",fichier);
	}
	void Read(int byte, uint8_t *var)
	{
		if( in.is_open() )
		{
			in.read((char *) (var), sizeof(byte));
		}
	}
	
};



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

class Algorithme{
	//Les classes qui nous seront utiles et qui ne changeront jamais
	class Sequence_Fasta* fasta;
	class Fichier_sequence* psq;
	class Sequence_Blast* blast;
	
	//Matrice Blosum et gap
	int Q;
	int R;
	int D[20][20];
	
	int max(int a,int b,int c=0,int d=0){
	if(a<=b && a<=c && a<=d){ //On priviligie un cas
		return a;}
	if (b<a && b<c && b<d){
		return b;}
	if (c<a && c<b && c<d){
		return c;}
	if (d<a && d<b && d<c){
		return d;
	}
	return 0; //Si erreur; return 0;
	}
	
	public:
	
	/* transcription du pseudocode SW-Gotoh-SWIPE
	* Où D est la matrice BLOSUM
	* la structure (ou classe) local_max a comme données int Best_Score, int x, int y;
	* Structure sequence (ou classe) pour toutes les informations concernant les séquences
	*/
	void SW_Gotoh_SWIPE(){
		//Matrice de score et de gap
		vector<int> H;
		vector<int> E;
		int F;
		
		for(int x=0;x<(*blast).getprot_len();x++){
			H.push_back(0);
			E.push_back(0);
		}
		
		//Variable temporaire pour celles supprimées par l'itération précédente
		int temp_var;
		int H_prec;
		
		//Variable de score local et de meilleur score global aisni que ses coordonnées
		int best_score;
		
		uint8_t prot;
		psq->Open(blast->getpsqoff());

		for (int i=0;i<fasta->getprot_len();i++){
			for(int j=0;j<blast->getprot_len();j++){
				
				psq->Read(sizeof(uint8_t),&prot);
				
				/* {{{ ---- Les matrices de gap ----- */
				if (j == 0)
					E[j] = 0;
				else
					E[j] = max(H[j-1] - Q,E[j-1] - R);
			
				if (i == 0)
					F = 0;
				else
					F = max(H[j] - Q,E[j] - R);
				/* }}}}}}}} */
				
				temp_var = H[j];
				
				/* {{{{{---- Matrice de score ---- */
				if(i == 0 || j == 0) //Si les conditions ne sont pas respectées
					H[j] = 0;
				else
					H[j] = max(H_prec + D[(int) (fasta->getsequence())[i]][(int) prot],F,E[j],0);
				/* }}}}}} */
				
				H_prec = temp_var;
				
				if (best_score < H[j]){
					best_score = H[j];
				}
				
			}
		}
		psq->Close();
		blast->update_score(best_score);
	}
	
};
