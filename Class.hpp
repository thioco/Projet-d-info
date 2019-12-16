#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>


using namespace std;

class Fichier
{
protected:
	char name[50];
	ifstream in;
public:
	Fichier(const char* fichier = 0);
	const char* getname();
	void Open(int offset);
	void Close();
};

class Fichier_head: public Fichier
{

public:
	Fichier_head(const char* fichier = 0);
	char getprotname(int offset);
};

class Fichier_index: public Fichier
{
	int debut;
	int nbreprot;
public:
	Fichier_index(const char* fichier = 0);
	int getseqoffset(int i);
	int getheadoffset(int i);
	int getnbreprot();
	int getsize(int i);
};

class Fichier_sequence: public Fichier
{
public:
	Fichier_sequence(const char* fichier = 0);
	void Read(int byte, int8_t *var);
};

class Sequence
{
protected:
	int prot_len;
public:
	int getprot_len();
};

class Sequence_Fasta: public Sequence
{
	vector<int8_t> sequence;
public:
	Sequence_Fasta(const char* fasta);
	vector<int8_t> fct_case_vector(vector<int8_t> prot,char c);
	const vector<int8_t> getsequence();
};

class Sequence_Blast: public Sequence
{
	int psqoff;
	int hdroff;
	int score;
public:
	Sequence_Blast(int offset, int size);
	void update_score(int points);
	int getpsqoff();
	int gethdroff();
	int getscore();
};

class Algorithme
{
	class Sequence_Fasta* fasta;
	class Fichier_sequence* psq;
	class Sequence_Blast* blast;
	int max(int a,int b,int c=0,int d=0);
	int indices_blosum(uint8_t a);
public:
	Algorithme(Sequence_Fasta* fasta,Fichier_sequence* psq);
	void SW_Gotoh_SWIPE(Sequence_Blast* blast);
};

