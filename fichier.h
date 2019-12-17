#ifndef FICHIER_H
#define FICHIER_H
#include <iostream>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <vector>
#include <tuple>
#include <string.h>

using namespace std;

class Fichier
{
public:
//constructeur
Fichier(const char* fichier = 0); 
//accesseurs
const char* getname() const;
//autres méthodes
void Open(int offset);
void Close();

protected:
char name[50];
ifstream in;
};

class Fichier_head: public Fichier
{
public:
//constructeur
Fichier_head(const char* fichier = 0);//:Fichier(fichier);
//autres méthodes
void getprotname(int offset);
};

class Fichier_index: public Fichier
{
public:
//constructeur
Fichier_index(const char* fichier = 0); //:Fichier(fichier);
//autres méthodes
int getseqoffset(int i);
int getheadoffset(int i);
int getsize(int i);
//accesseurs
int getnbreprot() const;

private:
int debut;
int nbreprot;
};

class Fichier_sequence: public Fichier
{
public:
//constructeur
Fichier_sequence(const char* fichier = 0);//: Fichier(fichier);
//autres méthodes
void Read(int byte, uint8_t *var);
};

#endif
