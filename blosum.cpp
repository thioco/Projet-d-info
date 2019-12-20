#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>
#include <string>
#include <string>


#include "blosum.h"

using namespace std;

//Constructeur
Fichier_Blosum::Fichier_Blosum(char* file_path){
	strcpy(path,file_path);
}

//Ouvre le fichier avec comme chemin path et retourne un code d'erreur
int Fichier_Blosum::fOpen(){
	f.open(path);
	if(!f.is_open()){
		cout << "Impossible d'ouvrir le fichier, vérifiez que celui ne comporte pas d'espace." << endl;
		return 1;
	}
	return 0;
}

//ferme le fichier
void Fichier_Blosum::fClose(){
	f.close();
}

//Lis une ligne entière
void Fichier_Blosum::readS(){
	string s;
	if(f.is_open()){
		getline(f,s);
	}
}

//Lis le fichier Blosum en entier
int** Fichier_Blosum::read(){
	//Les BLOSUM sont des matrices de taille 23x23, on alloue dynamiquement cette matrice 
	//int** b = (int**) malloc(sizeof(int)*23);
	int**b;
	b = new int*[23];
	for(int x=0;x<23;x++)
		b[x] = new int[23];
		//b[x] = (int*) malloc(sizeof(int)*23);
	
	
	//Variable qui vont nous servir à lire
	string c = "";
	string str = ""; 
	
	if(fOpen() == 1){
		return NULL;
	}
	
	if(f.is_open()){
		//Si le premier charactère de la ligne est un commentaire, on passe à la ligne suivante
		f >> c;
		while(c.compare("#") == 0){
			readS();
			f >> c;
		}
	
		readS(); //On saute la ligne des lettres
	
		for(int i=0;i<23;i++){ //Chaque ligne
			f >> str; //On s'enfout des lettres
			for(int j=0;j<23;j++){
				f >> str;
				b[i][j] = atoi(str.c_str());
			}
			f >> str; //Dernière colonne inutile
		}
	
		fClose();
	}
	return b;
}






