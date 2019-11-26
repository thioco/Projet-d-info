#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include "list.h"
#include <vector>
#include <map>
//copier protein dans liste(code tp3)
//traduire grâce à dico
//backtracking dans database

using namespace std;
map<char, int> initiate(map<char, int> dico){
	dico.insert(pair<char, int>('-', 0));
	dico['A'] = 1;
	dico['B'] = 2;
	dico['C'] = 3;
	dico['D'] = 4;
	dico['E'] = 5;
	dico['F'] = 6;
	dico['G'] = 7;
	dico['H'] = 8;
	dico['I'] = 9;
	dico['J'] = 27;
	dico['K'] = 10;
	dico['L'] = 11;
	dico['M'] = 12;
	dico['N'] = 13;
	dico['O'] = 26;
	dico['P'] = 14;
	dico['Q'] = 15;
	dico['R'] = 16;
	dico['S'] = 17;
	dico['T'] = 18;
	dico['U'] = 24;
	dico['V'] = 19;
	dico['W'] = 20;
	dico['X'] = 21;
	dico['Y'] = 22;
	dico['Z'] = 23;
	dico['*'] = 25;
	return dico;
}

int main(){
	map<char, int> traduction;
	vector<char> protein;
	int i;
	string line;
	initiate(traduction);
	
	
	ifstream myfile("P00533.fasta");
	ofstream out ("outfasta.txt");
	// 
	if(myfile.is_open())
	{
		char x;
		while( myfile.read((char *) (&x), sizeof(x) ))
		{
			if(x == '>'  )
			{
				getline(myfile,line);
			}
			else if (x == '\n') {
				continue;
			}
			else
			{
				//getline(myfile, line);
				cout << x;
				out <<  x << endl;
				protein.push_back(x);
				
			}
			
		
		/*while(getline(myfile, line))
		{
			protein.push_back(line);
		}
		myfile.close();
		protein.erase(protein.begin());
		for (int i = 0; i < protein.size(); i++) 
        cout << protein[i]  ;*/
		
		}
	cout << protein.size() << endl;
	myfile.close();
	}
}
