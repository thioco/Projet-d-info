// .h 
// ; pour les fct ????


class Fichier
{
private:
	const char* name;
public:
	Fichier(const char* fichier = 0);
	const char* getname();
};

class Fichier_head
{
private:
	const char* name; //Pas besoin de ça vu qu'on hérite de la classe parent 
public:
	Fichier_head(const char* fichier = 0);
	const char* getname(); //Pas besoin de ça vu qu'on hérite de la classe parent
};

class Fichier_index
{
private:
	const char* name; //Pas besoin de ça vu qu'on hérite de la classe parent
	int debut;
	int lengthdata;
public:
	Fichier_index(const char* fichier = 0);
	const char* getname() //Pas besoin de ça vu qu'on hérite de la classe parent
	int getseqoffset(int i);
	int getheadoffset(int i);
};

class Fichier_sequence
{
private:
	const char* name; //Pas besoin de ça vu qu'on hérite de la classe parent
public:
	Fichier_sequence(const char* fichier = 0);
	const char* getname(); //Pas besoin de ça vu qu'on hérite de la classe parent
	
};

class Sequence
{
private:
	vector<int8_t> sequence;
public:
	Sequence(const char* fasta = 0);
	vector<int8_t> fct_case_vector(vector<int8_t> prot,char c);
	const vector<int8_t> getsequence(); //changement here
};
