#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "algo.cpp"
//commentaire useless
using namespace std;

//<>

/*{{{{{-----Définition des variables globales-----*/
int gap_open = 11;
int gap_extension = 1;
int** BLOSUM = NULL;
/*}}}}}}}*/

//Voir plus bas
void recur_list_seq(Sequence_Blast* list_seq[],Sequence_Blast* seq ,int i);

int main(int argc, char **argv)
{
	/* {{{{{----- Gestion des paramètres----- */
	if (argc < 3)
	{
		cout << "2 arguments requis : query_sequence.fasta database.fasta" << endl;
		cout << "Des options supplémentaires peuvent être ajoutées, consultez README pour plus d'informations." << endl;
		return 1;
	}
	//On gère les options
	else if (argc > 3){
		for(int arg=3;arg<argc;arg++){
			if(!strcmp(argv[arg],"-gap_open")){
				if(argc > arg+1){
					gap_open = atoi(argv[arg+1]);
					arg++;}
				else{
					cout << "Valeur pour gap_open manquante." << endl;
					return 2;
				}
			}
			else if(!strcmp(argv[arg],"-gap_ext")){
				if(argc > arg+1){
					gap_extension = atoi(argv[arg+1]);
					arg++;}
				else{
					cout << "Valeur pour gap_extension manquante." << endl;
					return 2;
				}
			}
			else if(!strcmp(argv[arg],"-blosum")){
				if(argc > arg+1){
					/* PAS ENCORE OPERATIONNEL ATTENDRE LA MISE EN FORME SOUS .h
					 * Fichier_Blosum* f_b = new(argv[arg+1]);
					 * BLOSUM = f_b->read();
					 * f_b->destrcutor();
					 */
					cout <<" ";
					arg++;}
				else{
					cout << "Chemin de la BLOSUM manquante." << endl;
					return 2;}
			}
			else{
				cout << "Veuillez consulter le README pour ajouter des options." << endl;
				return -2;
			}
		}
	}
	/* }}}}}}} */
	
	/* {{{---- Chronomètre---*/
	clock_t tStart = clock();
	/* }}}}}*/
	
	/*{{{{-----Création des classes-----*/	
	//Voir fichier.h,sequence.h,algo.h pour plus d'informations ou README
	Sequence_Fasta* fasta = new Sequence_Fasta(argv[1]); 
	Fichier_head* phr = new Fichier_head(argv[2]);
	Fichier_index* pin = new Fichier_index(argv[2]);
	Fichier_sequence* psq = new Fichier_sequence(argv[2]);
	Algorithme* algo = new Algorithme(fasta, psq,gap_open,gap_extension,BLOSUM);
	/* }}}}}}*/
	 	
	/*{{{{----- Variables pour le classement des séquences----- */ 	
	int init_list = 0;
	Sequence_Blast* list_seq [5];
	/*}}}}}}*/
	
	cout << "Nombre de séquences : "<< pin->getnbreprot() << endl;
	
	/*{{{{{----- Lancement de l'algorithme pour les N prot------*/	
	for(int i=0;i<pin->getnbreprot(); i++)
	{
		//On crée une classe pour chaque nouvelle protéine, voir sequence.h
		Sequence_Blast* seq = new Sequence_Blast(pin->getheadoffset(i),pin->getseqoffset(i),pin->getsize(i));
		
		algo->SW_Gotoh_SWIPE(seq);
			
		//si la liste n'a pas encore été initialisée complètement, on insère chaque nouvelle protéine
		if(init_list < 5){
			list_seq[init_list] = seq;
			init_list++;
		}
		else
			recur_list_seq(list_seq,seq,0);
	}
	/* }}}}}} */
	
	/*{{{{{------ Affichage de nos résultats -------*/
	cout << endl;
	cout << "Le temps pris par l'algorithme : " << (double)(clock()-tStart)/(CLOCKS_PER_SEC)  << " secondes."<< endl << endl;
	//Affichage des scores dans l'ordre croissant
	for(int j=init_map-1;j>=0;j--){
		phr->getprotname((list_seq[j])->gethdroff());
		cout << "raw score: " << (list_seq[j])->getscore() << ", bit score= " << (0.267*((list_seq[j])->getscore()) + 3.34)/(0.693) << endl << endl;
		delete list_seq[j];}
	/*}}}}}}*/
		
	/*{{{{----Libération de la mémoire allouée ---- */
	delete(fasta);
	delete(phr);
	delete(pin);
	delete(psq);
	delete(algo);
	/* }}}}}} */
	
	return 0;
}

// Fonction pour insérer une séquence dans la liste et trier la liste de séquence
// Si la database a un nombre assez grand de protéine (N>>5), la liste a de grandes chances d'être triée
// 3 paramètres : la liste des séquences; la séquence à insérer; la place à partir de laquelle on voudrait se placer (nouvelle protéine : i=0, protéine existante dans la liste (position n) : i=n+1)
void recur_list_seq(Sequence_Blast* list_seq [], Sequence_Blast* seq, int i){
	int n;
	for(n=i;n<5;n++){
		if((list_seq[n])->getscore() < seq->getscore()){
			Sequence_Blast* temp = list_seq[n];
			list_seq[n] = seq;
			recur_list_seq(list_seq,temp,n+1);
			break;
		}
	}
	//Si la séquence est plus petite que toutes les autres, on libére sa mémoire
	if(n==5){
		delete seq;
	}
	
}	










