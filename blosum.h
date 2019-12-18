#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>
#include <iostream>

using namespace std;

class Fichier_Blosum
{
	private:
		ifstream f;
		char path[50];
		
		int fOpen();
		void fClose();
		
		void readS();

	public:
		Fichier_Blosum(char* file_path);
		int** read();
};
