class Fichier_Blosum
{
	private:
		ifstream f;
		char* path;
		
		void Open();
		void Close();
		
		void readC(char* C);
		void readS(char* S);

	public:
		Fichier_Blosum(char* file_path);
		int** read();
		void destructor();
};

Fichier_Blosum::Fichier_Blosum(char* file_path){
	path = malloc(sizeof(char)*strlen(file_path));
	strcpy(path,file_path);
}


void Fichier_Blosum::fOpen(){
	f.open(path);
	if(!f.is_open()){
		cout << "Impossible d'ouvrir le fichier, vérifiez que celui ne comporte pas d'espace." << endl;
	}
}

void Fichier_Blosum::fClose(){
	f.close();
}

void Fichier_Blosum::destructor(){
	free(path);
	free(this);
}

void Fichie_Blosum::readC(char* C){
	if(f.is_open()){
		*C = f.get();
	}
}

void Fichier_Blosum::readS(){
	char* s;
	if(f.is_open()){
		getline(f,s);
	}
}

int** Fichier_Blosum::read(){
	int** b = malloc(malloc(sizeof(int)*23)*23);
	char c;
	char* str[3]; //pas besoin d'une taille énorme
	
	fOpen();
	
	if(f.is_open()){
		while(readC(&c) == '#'){
			readS();
		}
	
		readS(); //On saute la ligne des lettres
	
		for(int i=0;i<23;i++){ //Chaque ligne
			f >> str; //On s'enfout des lettres
			for(int j=0;j<23;j++){
				f >> str;
				b[i][j] = atoi(str);
			}
			f >> str; //Dernière colonne inutile
		}
	
		fClose();
	}
	return b;
}






