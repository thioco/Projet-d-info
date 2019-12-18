#ifndef FICHIER_H
#define FICHIER_H
#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>

using namespace std;

/* Classe Fichier
 * Classe parent pour les 3 types de fichier (.psq,.pin,.phd)
 * La fonction open a été redéfini pour qu'on ouvre le fichier à un certain offset(on se positionne dans le fichier)
 */
class Fichier
{
	public:
		//constructeur
		Fichier(const char* fichier = 0); 
		//accesseurs
		const char* getname() const;
		//Redéfinition des fcts open et close
		void Open(int offset);
		void Close();

	protected:
		char name[50];
		ifstream in;
};

class Fichier_head: public Fichier
{
	public:
	//constructeur
	Fichier_head(const char* fichier = 0);
	
	// Fonction permettant d'aller rechercher le nom d'une protéine dans le .phd en fonction d'un offset
	void getprotname(int offset);
};

class Fichier_index: public Fichier
{
	public:
		//constructeur
		Fichier_index(const char* fichier = 0);
		//autres méthodes
		
		// la i-ème séquence de protéines
		//On va chercher l'offset .psq de la séquence i
		int getseqoffset(int i);
		//On va chercher l'offset .phd de la séquence i
		int getheadoffset(int i);
		//On va chercher la taille de la séquence i
		int getsize(int i);
		//accesseurs
		int getnbreprot() const;

	private:
		int debut; //Entier pour ignorer toutes les choses dont on n'a pas besoin
		int nbreprot;
};

class Fichier_sequence: public Fichier
{
	public:
		//constructeur
		Fichier_sequence(const char* fichier = 0);//: Fichier(fichier);
		//Permet tout simplement de lire les bytes dans le fichier .psq
		void Read(int byte, uint8_t *var);
};

#endif
