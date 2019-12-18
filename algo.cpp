#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>


#include "algo.h"
//commentaire useless

using namespace std;


Algorithme::Algorithme(Sequence_Fasta* f, Fichier_sequence* p,int g_o, int g_e,int** B)
		{
			fasta = f;
			psq = p;
			Q = g_o + g_e;
			R = g_e;
			blosum = B;
			
		} 
	
	
void Algorithme::SW_Gotoh_SWIPE(Sequence_Blast* blast){
		//Matrice de score et de gap
		//vector<int> H;
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
		
		//Variable de score local et de meilleur score global aisni que ses coordonnées
		int best_score=0;
		
		uint8_t prot;
		//cout << "Offset psq=" << blast->getpsqoff() << endl;
		
		for (int i=0;i<fasta->getprot_len();i++){
			psq->Open(blast->getpsqoff());
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
					H[j] = max(H_prec + blosum[indices_blosum((int) prot)][indices_blosum((fasta->getsequence())[i])],F,E[j],0);
				/* }}}}}} */
				
				H_prec = temp_var;
				
				if (best_score < H[j]){
					best_score = H[j];
				}	
			}
			psq->Close();
		}
		psq->Close();
		blast->update_score(best_score);
	}
	

	
	
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

