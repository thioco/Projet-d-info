/*<>
 * Auteur : Losfeld Armand, Courboin Samuel, Hioco Thomasso
 * Date : 28/11/19
 * Description : 
 * Déclaration des fonctions permettant la manipulation du fasta
 */
 

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

//Switch selon le char c et renvoie le vector de protéine traduit en byte(psq)
vector<int8_t> fct_case_vector(vector<int8_t> prot,char c);

//Switch selon le char c et écrit en binaire dans un fichier
void fct_case(const char* filename,char c);

//Ouvre le fichier fasta, le lis et appelle la fct_case_vector 
vector<int8_t> translate(const char* fasta,const char* outpout);

