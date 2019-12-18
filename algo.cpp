#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>


#include "algo.h"

using namespace std;

//Constructeur : 
Algorithme::Algorithme(Sequence_Fasta* f, Fichier_sequence* p,int g_o, int g_e,int** B)
		{
			fasta = f;
			psq = p;
			Q = g_o + g_e;
			R = g_e;
			blosum = B;
			
		} 
	
/*	L'algorithme Smith-Waterman 
 * 	Amélioré par Gotoh : récurrence démontré dans son article pour obtenir un cout en O(n.m); Seulement 2 matrices de taille 1xm (m nombre de lignes/colonnes) et une variable 
 * 	Amélioré par SWIPE : dans l'article, la récurrence de Smith-Waterman avec les améliorations de Gotoh y étaient présentées
 */
void Algorithme::SW_Gotoh_SWIPE(Sequence_Blast* blast){
		//Matrice de score et de gap
		int* H;
		int* E;
		int F = 0;
		H = new int[blast->getprot_len()];
		E = new int[blast->getprot_len()];
		
		for(int x=0;x<blast->getprot_len();x++){
			H[x]=0;
			E[x]=0;
		}
		
		//Variable temporaire pour celles supprimées par l'itération précédente
		int temp_var=0;
		int H_prec=0;
		
		//Variable du meilleur score local
		int best_score=0;
		
		//Variable permettant de lire dans le fichier blast
		uint8_t prot;
		
		for (int i=0;i<fasta->getprot_len();i++){
			//On ouvre le fichier pour chaque nouvelle prot du fasta car on veut se repositionner au début.
			//psq->Open(blast->getpsqoff());
			
			//Repositionnement dans le psq pour chaque nouvelle protéine du fasta
			psq->pos(blast->getpsqoff());
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
				
				//On sauvegarde la valeur qui va être supprimée
				temp_var = H[j];

				/* {{{{{---- Matrice de score ---- */
				if(i == 0 || j == 0) //Si les conditions ne sont pas respectées
					H[j] = 0;
				else
					H[j] = max(H_prec + blosum[indices_blosum((int) prot)][indices_blosum((fasta->getsequence())[i])],F,E[j],0);
				/* }}}}}} */
				
				//On stocke l'ancienne valeur pour ne pas la perdre
				H_prec = temp_var;
				
				//Si on a un meilleur score 
				if (best_score < H[j]){
					best_score = H[j];
				}	
			}
			//On ferme le fichier pour se repositionner
			//psq->Close();
		}
		//On ferme le fichier
		psq->Close();
		//On update le score maximal local de la séquence blast
		blast->update_score(best_score);
	}
	

	
//Une fonction permettant de choisir un maximum parmis 4 cas
int Algorithme::max(int a,int b,int c,int d){
		if(a>=b && a>=c && a>=d){ //On priviligie un cas 
			return a;}
		if (b>a && b>c && b>d){
			return b;}
		if (c>a && c>b && c>d){
			return c;}
		if (d>a && d>b && d>c){ 
			return d;
		}
		return 0; //Si erreur; return 0;
	}

//Traduction des entiers du .psq dans l'ordre des indices de la BLOSUM
int Algorithme::indices_blosum(uint8_t a){
		int res;
		switch(a){
			case 1:
				res = 0;
				break;
			case 2:
				res = 20;
				break;
			case 3:
				res = 4;
				break;
			case 4:
				res = 3;
				break;
			case 5:
				res = 6;
				break;
			case 6:
				res = 13;
				break;
			case 7:
				res = 7;
				break;
			case 8:
				res = 8;
				break;
			case 9:
				res = 9;
				break;
			case 10:
				res = 11;
				break;
			case 11:
				res = 10;
				break;
			case 12:
				res = 12;
				break;
			case 13:
				res = 2;
				break;
			case 14:
				res = 14;
				break;
			case 15:
				res = 5;
				break;
			case 16:
				res = 1;
				break;
			case 17:
				res = 15;
				break;
			case 18:
				res = 16;
				break;
			case 19:
				res = 19;
				break;
			case 20:
				res = 17;
				break;
			case 21:
				res = 22;
				break;
			case 22:
				res = 18;
				break;
			case 23:
				res = 21;
				break;
		}
		return res;
	}

