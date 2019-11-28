/*<>
 * Auteur : Losfeld Armand, Courboin Samuel, Hioco Thomasso
 * Date : 28/11/19
 * Description : 
 * Définition des fonctions permettant la manipulation du fasta
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include "read_fasta.h"
#include <vector>

#define MAX_COMM 500
using namespace std;

vector<int8_t> fct_case_vector(vector<int8_t> prot,char c){
	
	int8_t a;
	switch(c) {
		case 'A':
			a = 1;
			prot.push_back(a);
			break;
		case 'B':
			a = 2;
			prot.push_back(a);
			break;
		case 'C':
			a = 3;
			prot.push_back(a);
			break;
		case 'D':
			a = 4;
			prot.push_back(a);
			break;
		case 'E':
			a = 5;
			prot.push_back(a);
			break;
		case 'F':
			a = 6;
			prot.push_back(a);
			break;
		case 'G':
			a = 7;
			prot.push_back(a);
			break;
		case 'H':
			a = 8;
			prot.push_back(a);
			break;
		case 'I':
			a = 9;
			prot.push_back(a);
			break;
		case 'J':
			a = 27;
			prot.push_back(a);
			break;
		case 'K':
			a = 10;
			prot.push_back(a);
			break;
		case 'L':
			a = 11;
			prot.push_back(a);
			break;
		case 'M':
			a = 12;
			prot.push_back(a);
			break;
		case 'N':
			a = 13;
			prot.push_back(a);
			break;
		case 'O':
			a = 26;
			prot.push_back(a);
			break;
		case 'P':
			a = 14;
			prot.push_back(a);
			break;
		case 'Q':
			a = 15;
			prot.push_back(a);
			break;
		case 'R':
			a = 16;
			prot.push_back(a);
			break;
		case 'S':
			a = 17;
			prot.push_back(a);
			break;
		case 'T':
			a = 18;
			prot.push_back(a);
			break;
		case 'U':
			a = 24;
			prot.push_back(a);
			break;
		case 'V':
			a = 19;
			prot.push_back(a);
			break;
		case 'W':
			a = 20;
			prot.push_back(a);
			break;
		case 'X':
			a = 21;
			prot.push_back(a);
			break;
		case 'Y':
			a = 22;
			prot.push_back(a);
			break;
		case 'Z':
			a = 23;
			prot.push_back(a);
			break;
	}
	return prot;
	
}


// !!! PAS ENCORE FONCTIONEL !!!
void fct_case(const char* filename,char c){
	ofstream fo(filename,ios::out | ios::binary);
	int8_t a;
	if(fo.is_open())
	{
		
	}
	switch(c) {
		case 'A':
			a = 1;
			fo.write(reinterpret_cast<const char*>(&a), sizeof(int));
			
			break;
		case 'B':
			a = 2;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'C':
			a = 3;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'D':
			a = 4;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'E':
			a = 5;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'F':
			a = 6;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'G':
			a = 7;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'H':
			a = 8;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'I':
			a = 9;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'J':
			a = 27;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'K':
			a = 10;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'L':
			a = 11;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'M':
			a = 12;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'N':
			a = 13;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'O':
			a = 26;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'P':
			a = 14;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'Q':
			a = 15;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'R':
			a = 16;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'S':
			a = 17;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'T':
			a = 18;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'U':
			a = 24;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'V':
			a = 19;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'W':
			a = 20;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'X':
			a = 21;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'Y':
			a = 22;
			fo.write((char *)&a, sizeof(int8_t));
			break;
		case 'Z':
			a = 23;
			fo.write((char *)&a, sizeof(int8_t));
			break;
	}
	fo.close();
}

vector<int8_t> translate(const char* fasta,const char* outpout){
	FILE* f=fopen(fasta,"r");

	vector<int8_t> protein;
	
	if (f != NULL) {
	
		char c; /*Un seul caractère = un seul acide aminé*/
		char poubelle[MAX_COMM]="";
		fgets(poubelle,MAX_COMM,f);

		for (c=getc(f);c!=EOF;c=getc(f)){
			protein = fct_case_vector(protein,c);
		}
		fclose(f);
	}
	else
		cout << "Rentrez un nom de fichier correct" << endl;
	protein.push_back(0);//Pour le byte NULL qui permet de terminer la séquence
	return protein;
}
	
	
	
