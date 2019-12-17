#ifndef SEQUENCE_H
#define SEQUENCE_H
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
	int getprot_len();		
};
class Sequence_Blast: public Sequence
{
public:
//constructeur
Sequence_Blast();
Sequence_Blast(int offH,int offP, int size);
void update_score(int points);
//accesseurs
int getpsqoff() const;
int gethdroff() const;
int getscore() const;
private:
int psqoff;
int hdroff;
int score;
};
class Sequence_Fasta: public Sequence
{
public:
//constructeur
Sequence_Fasta(const char* fasta);
//traducteur
vector<int8_t> fct_case_vector(vector<int8_t> prot,char c);
//accesseur
vector<int8_t> getsequence() const;

private:
vector<int8_t> sequence;
};
#endif
