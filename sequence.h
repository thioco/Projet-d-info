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

/* Classe Sequence
 * protected prot_len (les classes filles y ont accès) : longueur de la séquence
 * public getprotlen() : accesseurs pour prot_len
*/
class Sequence
{
	protected:
		int prot_len;
	public:
		int getprot_len();		
};


class Sequence_Blast: public Sequence //Hérite de Sequence
{
	public:
		//constructeur
		Sequence_Blast(int offH,int offP, int size);
		//Commutateur de score
		void update_score(int points);
		//accesseurs
		int getpsqoff() const;
		int gethdroff() const;
		int getscore() const;
		private:
		//Les offset du psq et phd de la séquence, le score provenant de l'algorithme Smith-Waterman
		int psqoff;
		int hdroff;
		int score;
};

class Sequence_Fasta: public Sequence
{
	public:
		//constructeur et traduction du fasta en tableau dynamique et statique
		Sequence_Fasta(const char* fasta);
		//traduction des charactères en entier selon le template du psq
		vector<int8_t> fct_case_vector(vector<int8_t> prot,char c);
		//accesseur
		uint8_t* getsequence() const;

	private:
		//Tableau statique (pointeur) alloué sur le tas, tableau dynamique (vector)
		uint8_t* seq;
		vector<int8_t> sequence;
};
#endif
