#ifndef BLOSUM_H
#define BLOSUM_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>
#include <iostream>

using namespace std;

/* Classe Fichier_Blosum
 * Permet de lire les fichiers Blosum
 * Redéfinition des fcts d'ouverture et fermeture de fichier
 * void readS() : Une fct pour lire des lignes
 * int** read() : fct pour lire le Blosum en entier, renvoie un double pointeur alloué sur le tas
 */
class Fichier_Blosum
{
	private:
		ifstream f;
		
		//String statique car les noms des blosums sont du type : BLOSUMXX
		char path[50];
		
		int fOpen();
		void fClose();
		
		void readS();

	public:
		Fichier_Blosum(char* file_path);
		int** read();
};
#endif
