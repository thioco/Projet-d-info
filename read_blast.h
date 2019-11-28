/*<>
 * Auteur : Losfeld Armand, Courboin Samuel, Hioco Thomasso
 * Date : 28/11/19
 * Description : 
 * Déclaration des fonctions permettant la manipulation du blast
 */

#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

//Ouvre le fichier file_blast, lis soit le tableau d'header soit séq et n est la taille de la séquence
vector<tuple<int,int>> read_pin_seq(const char* file_blast,int n);

