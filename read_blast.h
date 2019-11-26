#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

//Ouvre le fichier file_blast, lis soit le tablleau d'header soit séq et n sert à ce qu'on va faire
vector<tuple<int,int>> read_pin_seq(const char* file_blast,int n);

vector<int> read_seq(const char* file_blast,int cursor);
