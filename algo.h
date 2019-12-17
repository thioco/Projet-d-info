#ifndef ALGO_H
#define ALGO_H
#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>
#include "fichier.h"
#include "sequence.h"

using namespace std;

class Algorithme
{
public:
//Constructeur
Algorithme(Sequence_Fasta* f , Fichier_sequence* p ,int g_o , int g_e,int** B);

//fonction smith watermann
void SW_Gotoh_SWIPE(Sequence_Blast* blast);
private:
//Les classes qui nous seront utiles et qui ne changeront jamais
class Sequence_Fasta* fasta;
class Fichier_sequence* psq;
	
//Matrice Blosum et gap
int Q;
int R;
int blosum62[23][23];

//méthodes privés
int max(int a,int b,int c=0,int d=0);
int indices_blosum(uint8_t a);
};


#endif
