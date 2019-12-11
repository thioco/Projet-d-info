/*
 * Test d'un code avec Smith-Waterman et Gotoh
 */


#include <iostream>


/*fonction de max*/
int max(int a,int b,int c=0){
	if(a<=b && a<=c) //On priviligie un cas
		return a;
	if (b<a && b<c)
		return b;
	if (c<a && c<b)
		return c;
	return 0; //Si erreur; return 0;
}


/* transcription du pseudocode SW-Gotoh-SWIPE
 * Où D est la matrice BLOSUM
 * la structure (ou classe) local_max a comme données int Best_Score, int x, int y;
 * Structure sequence (ou classe) pour toutes les informations concernant les séquences
*/
int** SW-Gotoh-SWIPE(int** D,struct* local_max,struct sequence fasta,struct sequence blast){
	int H[fasa.taille][blast.taille]; //Matrice de n lignes et m colonnes
	int E[fasa.taille][blast.taille];//Matrice de gap
	int F[fasa.taille][blast.taille];
	
	local_max.Best_score = 0; //D'ailleurs on dervait pas mettre ça dans la strcut sequence blast ???
	
	for (int i=0;i<fasa.taille;i++){
		for(int j=0;j<blast.taille;i++){
			/* {{{ ---- Les matrices de gap ----- */
			if (j == 0)
				E[i][j] = 0;
			else
				E[i][j] = max(H[i][j-1] - Q,E[i,j-1] - R);
			
			if (i == 0)
				F[i][j] = 0;
			else
				F[i[][j] = max(H[i-1][j] - Q,E[i-1][j] - R);
			/* }}}}}}}} */
			
			/* {{{{{---- Matrice de score ---- */
			if((i == 0 && j == 0) || (i <0) || (j<0)) //Si les conditions ne sont pas respectées
				H[i][j] = 0;
			else
				H[i][j] = max(H[i-1][j-1] + D[fasta[i]][blast[j]],F[i][j],E[i][j])
			/* }}}}}} */
			
			if (local_max.Best_score < H[i][j]){
				local_max.Best_score = H[i][j];
				x=i;
				y=j;
			}
		}
	}
	return H;
}










