#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>
#include <string>


#include "blosum.h"

using namespace std;

Fichier_Blosum::Fichier_Blosum(char* file_path){
	//path = (char*) malloc(sizeof(char)*strlen(file_path));
	strcpy(path,file_path);
}


int Fichier_Blosum::fOpen(){
	f.open(path);
	if(!f.is_open()){
		cout << "Impossible d'ouvrir le fichier, vérifiez que celui ne comporte pas d'espace." << endl;
		return 1;
	}
	return 0;
}

void Fichier_Blosum::fClose(){
	f.close();
}

void Fichier_Blosum::readS(){
	string s;
	if(f.is_open()){
		getline(f,s);
	}
}

int** Fichier_Blosum::read(){
	int** b = (int**) malloc(sizeof(int)*23);
	for(int x=0;x<23;x++)
		b[x] = (int*) malloc(sizeof(int)*23);
	
	
	
	string c = "";
	string str = ""; //pas besoin d'une taille énorme
	
	if(fOpen() == 1){
		return NULL;
	}
	
	if(f.is_open()){
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






