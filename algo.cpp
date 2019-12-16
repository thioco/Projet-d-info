#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>


using namespace std;


class Algorithme{
	public:
		Algorithme(Sequence_Fasta* f, Fichier_sequence* p)
		{
			fasta = f;
			psq = p;
		} 
	
	
	/* transcription du pseudocode SW-Gotoh-SWIPE
	* Où D est la matrice BLOSUM
	* la structure (ou classe) local_max a comme données int Best_Score, int x, int y;
	* Structure sequence (ou classe) pour toutes les informations concernant les séquences
	*/
	void SW_Gotoh_SWIPE(Sequence_Blast* blast){
		//Matrice de score et de gap
		vector<int> H;
		vector<int> E;
		int F = 0;
		
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
				
				cout << "Matrice E :" << E[j] << " pour j :" << j <<endl;
				
				if (i == 0)
					F = 0;
				else
					F = max(H[j] - Q,E[j] - R);
				/* }}}}}}}} */
				
				cout << "Matrice F :" << F << " pour j :" << j <<endl;
				
				temp_var = H[j];
				cout << "temp_var:" << temp_var << " H_prec :" << H_prec <<endl;
				
				/* {{{{{---- Matrice de score ---- */
				if(i == 0 || j == 0) //Si les conditions ne sont pas respectées
					H[j] = 0;
				else
					H[j] = max(H_prec + blosum62[indices_blosum((int) prot)][indices_blosum((fasta->getsequence())[i])],F,E[j],0);
				/* }}}}}} */
				
				cout << "Voici la valeur du max:" << max(H_prec + blosum62[indices_blosum((int) prot)][indices_blosum((fasta->getsequence())[i])],F,E[j],0) << endl;
				cout << "Voici la valeur de la blosum :" << blosum62[indices_blosum((int) prot)][indices_blosum((fasta->getsequence())[i])] << endl;
				
				cout << "Matrice H :" << H[j] << " pour j :" << j <<endl;
				
				H_prec = temp_var;
				
				if (best_score < H[j]){
					best_score = H[j];
					//cout << "Meilleur score :" << best_score << endl;
				}
				
				if (j == 24)
					break;
				
			}
			
			//cout << "Voici la valeur de la blosum :" << blosum62[indices_blosum((int) prot)][indices_blosum((fasta->getsequence())[i])] << endl;
			if(i==0)
				break;
		}
		psq->Close();
		blast->update_score(best_score);
	}
	
	
	private:
	//Les classes qui nous seront utiles et qui ne changeront jamais
	class Sequence_Fasta* fasta;
	class Fichier_sequence* psq;
	
	//Matrice Blosum et gap
	int Q = 1 + 11;;
	int R = 1;
	
	int blosum62[23][23] = {{4, -1,-2, -2, 0, -1, -1, 0, -2, -1, -1, -1, -1, -2, -1,  1,  0, -3, -2,  0, -2, -1,  0},
            {-1, 5,  0, -2, -3,  1,  0, -2,  0, -3, -2,  2, -1, -3, -2, -1, -1, -3, -2, -3, -1,  0, -1},
            {-2,  0,  6,  1, -3,  0,  0,  0,  1, -3, -3,  0, -2, -3, -2,  1,  0, -4, -2, -3,  3,  0, -1},
            {-2, -2,  1,  6, -3,  0,  2, -1, -1, -3, -4, -1, -3, -3, -1,  0, -1, -4, -3, -3,  4,  1, -1},
            {0, -3, -3, -3,  9, -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1, -3, -3,-2},
            {-1,  1,  0,  0, -3,  5,  2, -2,  0, -3, -2,  1,  0, -3, -1,  0, -1, -2, -1, -2,  0,  3, -1},
            {-1,  0,  0,  2, -4,  2,  5, -2,  0, -3, -3,  1, -2, -3, -1,  0, -1, -3, -2, -2,  1,  4, -1},
            {0, -2,  0, -1, -3, -2, -2,  6, -2, -4, -4, -2, -3, -3, -2,  0, -2, -2, -3, -3, -1, -2, -1},
            {-2,  0,  1, -1, -3,  0,  0, -2,  8, -3, -3, -1, -2, -1, -2, -1, -2, -2,  2, -3,  0,  0, -1},
            {-1, -3, -3, -3, -1, -3, -3, -4, -3,  4,  2, -3,  1,  0, -3, -2, -1, -3, -1,  3, -3, -3, -1},
            {-1, -2,-3, -4, -1, -2, -3, -4, -3,  2,  4, -2,  2,  0, -3, -2, -1, -2, -1,  1, -4, -3, -1},
            {-1,  2,  0, -1, -3,  1,  1, -2, -1, -3, -2,  5, -1, -3, -1,  0, -1, -3, -2, -2,  0,  1, -1},
            {-1, -1, -2, -3, -1,  0, -2, -3, -2,  1,  2, -1,  5,  0, -2, -1, -1, -1, -1,  1, -3, -1, -1},
            {-2, -3, -3, -3, -2, -3, -3, -3, -1,  0,  0, -3,  0,  6, -4, -2, -2,  1,  3, -1, -3, -3, -1},
            {-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4,  7, -1, -1, -4, -3, -2, -2, -1, -2},
            {1, -1,  1,  0, -1,  0,  0,  0, -1, -2, -2,  0, -1, -2, -1,  4,  1, -3, -2, -2,  0,  0,  0},
            {0, -1,  0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1,  1,  5, -2, -2,  0,-1, -1,  0},
            {-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1,  1, -4, -3, -2, 11,  2, -3, -4, -3, -2},
            {-2, -2, -2, -3, -2, -1, -2, -3,  2, -1, -1, -2, -1,  3, -3, -2, -2,  2,  7, -1, -3, -2, -1},
            {0, -3, -3, -3, -1, -2, -2, -3, -3,  3,  1, -2,  1, -1, -2, -2,  0, -3, -1,  4, -3, -2, -1},
            {-2, -1,  3,  4, -3,  0, 1, -1,  0, -3, -4,  0, -3, -3, -2,  0, -1, -4, -3, -3,  4,  1, -1},
            {-1,  0,  0,  1, -3,  3,  4, -2,  0, -3, -3,  1, -1, -3, -1,  0, -1, -3, -2, -2,  1,  4, -1},
            {0, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1,-1, -1, -1, -2,  0,  0, -2, -1, -1, -1, -1, -1}};
	
	int max(int a,int b,int c=0,int d=0){
		if(a>=b && a>=c && a>=d){ //On priviligie un cas
			cout << "a =" << a << endl; 
			return a;}
		if (b>a && b>c && b>d){
			cout << "b =" << b << endl; 
			return b;}
		if (c>a && c>b && c>d){
			cout << "c =" << c << endl; 
			return c;}
		if (d>a && d>b && d>c){
			cout << "d =" << d << endl; 
			return d;
		}
		return 0; //Si erreur; return 0;
	}
	
	int indices_blosum(uint8_t a){
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
	
};
