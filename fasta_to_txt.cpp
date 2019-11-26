#include <iostream>
#include <cstdio>
#include <cstring>

#include "fasta_to_txt.h"

#define MAX_COMM 500
using namespace std;

/*<>*/

void fct_case(const char* filename,char c){
	FILE* fo;
	switch(c) {
		case 'A':
			fo=fopen(filename,"a");
			fputs("1 \n",fo);
			fclose(fo);
			break;
		case 'B':
			fo=fopen(filename,"a");
			fputs("2 \n",fo);
			fclose(fo);
			break;
		case 'C':
			fo=fopen(filename,"a");
			fputs("3 \n",fo);
			fclose(fo);
			break;
		case 'D':
			fo=fopen(filename,"a");
			fputs("4 \n",fo);
			fclose(fo);
			break;
		case 'E':
			fo=fopen(filename,"a");
			fputs("5 \n",fo);
			fclose(fo);
			break;
		case 'F':
			fo=fopen(filename,"a");
			fputs("6 \n",fo);
			fclose(fo);
			break;
		case 'G':
			fo=fopen(filename,"a");
			fputs("7 \n",fo);
			fclose(fo);
			break;
		case 'H':
			fo=fopen(filename,"a");
			fputs("8 \n",fo);
			fclose(fo);
			break;
		case 'I':
			fo=fopen(filename,"a");
			fputs("9 \n",fo);
			fclose(fo);
			break;
		case 'J':
			fo=fopen(filename,"a");
			fputs("27 \n",fo);
			fclose(fo);
			break;
		case 'K':
			fo=fopen(filename,"a");
			fputs("10 \n",fo);
			fclose(fo);
			break;
		case 'L':
			fo=fopen(filename,"a");
			fputs("11 \n",fo);
			fclose(fo);
			break;
		case 'M':
			fo=fopen(filename,"a");
			fputs("12 \n",fo);
			fclose(fo);
			break;
		case 'N':
			fo=fopen(filename,"a");
			fputs("13 \n",fo);
			fclose(fo);
			break;
		case 'O':
			fo=fopen(filename,"a");
			fputs("26 \n",fo);
			fclose(fo);
			break;
		case 'P':
			fo=fopen(filename,"a");
			fputs("14 \n",fo);
			fclose(fo);
			break;
		case 'Q':
			fo=fopen(filename,"a");
			fputs("15 \n",fo);
			fclose(fo);
			break;
		case 'R':
			fo=fopen(filename,"a");
			fputs("16 \n",fo);
			fclose(fo);
			break;
		case 'S':
			fo=fopen(filename,"a");
			fputs("17 \n",fo);
			fclose(fo);
			break;
		case 'T':
			fo=fopen(filename,"a");
			fputs("18 \n",fo);
			fclose(fo);
			break;
		case 'U':
			fo=fopen(filename,"a");
			fputs("24 \n",fo);
			fclose(fo);
			break;
		case 'V':
			fo=fopen(filename,"a");
			fputs("19 \n",fo);
			fclose(fo);
			break;
		case 'W':
			fo=fopen(filename,"a");
			fputs("20 \n",fo);
			fclose(fo);
			break;
		case 'X':
			fo=fopen(filename,"a");
			fputs("21 \n",fo);
			fclose(fo);
			break;
		case 'Y':
			fo=fopen(filename,"a");
			fputs("22 \n",fo);
			fclose(fo);
			break;
		case 'Z':
			fo=fopen(filename,"a");
			fputs("23 \n",fo);
			fclose(fo);
			break;
	}
}

int translate(const char* fasta,const char* outpout){
	FILE* f=fopen(fasta,"r");
	FILE* fo=fopen(outpout,"w+"); /*pour réinitialiser le fichier si celui-ci existe déjà*/
	fclose(fo);
	
	int N=0; //Taille de la séquence
	
	if (f != NULL) {
	
		char c; /*Un seul caractère = un seul acide aminé*/
		char poubelle[MAX_COMM]="";
		fgets(poubelle,MAX_COMM,f);

		for (c=getc(f);c!=EOF;c=getc(f)){
			fct_case(outpout,c);
			if ( c != '\n')
				N++;
		}
		fclose(f);
	}
	else
		cout << "Rentrez un nom de fichier correct" << endl;
	N++;
	return N;
}
	
	
	
