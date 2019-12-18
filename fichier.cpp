#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>
#include "fichier.h"


using namespace std;


Fichier::Fichier(const char* fichier) //constructeur de la classe mère
	{
		strcpy(name,fichier);
	}
const char* Fichier::getname() const
	{
		return name;
	}
//méthodes pour ouvrir et fermer les fichier, utilisé dans algo.cpp pour éviter de devoir ouvrir et refermer les fichiers dans les boucles for
void Fichier::Open(int offset) 
	{
		in.open(name, ios::binary|ios::out);
		in.seekg(offset);
	}
void Fichier::Close()
	{
		in.close();
	}




Fichier_head::Fichier_head(const char* fichier): Fichier(fichier)
	{
		sprintf(name,"%s.phr",fichier);
	}
	
void Fichier_head::getprotname(int offset) 
	{
		in.open(name,ios::binary |ios::out);
		in.seekg(offset);
		in.ignore(7*sizeof(char)); //On ignore 7 bytes selon le template du phr
		uint8_t n;
		in.read((char*) &n,sizeof(n));
		char a[(uint)n];
		in.read(a,sizeof(a));
		a[(uint)n]=0; //Des caractères s'ajoutent en plus pour aucune raison...
	
		cout << "Le nom du fichier est :" << endl;
		cout <<">"<< a << endl;
		in.close();
	}




Fichier_index::Fichier_index(const char* fichier): Fichier(fichier) 
	{
		sprintf(name,"%s.pin",fichier);
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			
			in.ignore(8); //on saute les infos sur le type et la version de la database
			debut = 8;
			in.read((char *) (&x), sizeof(x) ); //lis taille du titre
			debut += 4+bswap_32((int32_t)x);
			in.ignore(bswap_32((int32_t)x)); //saute le titre
		
			in.read((char *) (&x), sizeof(x) ); //lis taille de la "timestamp string"
			debut += 4+bswap_32((int32_t)x);
			in.ignore(bswap_32((int32_t)x)); //saute "timestamp string"
		
			in.read((char *) (&x), sizeof(x) ); //lis nombre de protéines dans la séquence et le stocke dans une variable
			nbreprot =  bswap_32((int32_t) x );
			
			debut+= 16; //début est un offset qui va permettre d'aller directement dans le header et sequence offset table
			in.close();
		}
	}

int Fichier_index::getseqoffset(int i)
	{
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i+1+nbreprot)*4); //va directement dans les tables et on saute la table des offset des header
			in.read((char *) (&x), sizeof(x) );
			in.close();
			return bswap_32((int32_t) x);
		}
		return 0;
	}
	
int Fichier_index::getheadoffset(int i)
	{
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i)*4);//va directement dans la table header et saute le nombre nécessaire de protéines pour arriver à celle qui nous intéresse
			in.read((char *) (&x), sizeof(x) );
			in.close();
			return bswap_32((int32_t) x );
		}
		return 0;
	}
	
int Fichier_index::getnbreprot() const
	{
		return nbreprot;
	}
	
int Fichier_index::getsize(int i) //fais différence entre offset de la protéine et du offset de la protéine qui suit pour connaitre la taille de celle qui nous intéresse
	{
		int begin, end;
		in.open(name,ios::binary |ios::in);
		if( in.is_open() )
		{
			uint32_t x;
			in.seekg(debut+(i+1+nbreprot)*4);
			in.read((char *) (&x), sizeof(x));
			begin = bswap_32((int32_t) x );
		
			//in.seekg(debut+(i+nbreprot)*4);
			in.read((char *) (&x), sizeof(x));
			end = bswap_32((int32_t) x );
			in.close();
		}
		return (end - begin-1);
		
	}




Fichier_sequence::Fichier_sequence(const char* fichier): Fichier(fichier)
	{
		sprintf(name,"%s.psq",fichier);
	}
void Fichier_sequence::Read(int byte, uint8_t *var) //lis caractère à l'offset qu'on a demandé
	{
		if( in.is_open() )
		{
			in.read((char *) (var), sizeof(char)*byte);
		}
	}
	

