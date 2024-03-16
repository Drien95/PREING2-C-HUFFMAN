#ifndef __main__
#define __main__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>


/*en vérité c'est une liste pas une file*/
typedef struct elemfile elemfile;
struct elemfile{
	char chemin;
	elemfile *suivant;
};

typedef struct file file;
struct file{
	elemfile *premier;
};

typedef struct element element;
struct element{
    int ascii;
    int occ;
};


typedef struct arbre arbre;
struct arbre{
	element val;
	arbre *fg;
	arbre *fd;
};

file *ajoutFile(file *f1,file *f2);
void codage();
int convertionBin(file *f);
int convertionBin2(file *f);
file *convertionDeci(int x,file *octet);
arbre *creationArbreTab(element *tab,arbre *arb,int tailletab);
file *creationOctet(file *octet,FILE *txt,char *bit);
arbre *creerArbre();
arbre *creerElemArbre(element x);
file *creerFile();
file *empiler(file *f,char x);
file *enfiler(file *f, char x);
int estFeuille(arbre *a);
int hauteur(arbre *a);
void initialisationTab(element *tab);
void inscriptionOctet1(FILE *bin);
void inscriptionOctet2(FILE *bin,element *tab);
void inscriptionTab(FILE *bin,element *tab);
void inscriptionTxt(arbre *a,char *fich);
int max(int a,int b);
void occurence(element *tab, FILE *fichier);
arbre *option1(element *tab,int i,arbre *a);
arbre *option2(element *tab,int i,arbre *a);
int recherche(int c,arbre *a,file *f);
int recherche2(int c,arbre *a,file *f);
void recreationTab(FILE *bin,element *restTab,int tailleTab,int size);
arbre *sousArbre(element *tab,int x,int y);
file *supprDernierElem(file *f);
file *supprElemFile(file *f);
file *supprZeros(file *file, int nbZero);
int taille(arbre *a);
int tailleTexte(FILE *txt);
void triTab(element *tab);
int verifTailleFile(file *f);

#endif


