#include "fonction.h"
//vous trouverez dans ce fichier toutes les fonctions liées a la création et manipulation des files.


//ajoute une liste f2 a la suite d'une liste f1
file *ajoutFile(file *f1,file *f2)
{
	elemfile *l2 = f2->premier;	
	while(l2 != NULL)
    {
		enfiler(f1,l2->chemin);
		l2 = l2->suivant;
	}
	return f1;
}

file *creerFile()
{
	file *f = malloc(sizeof(*f));
	if(f==NULL)
    {
		exit(EXIT_FAILURE);
	}
	f->premier = NULL;
	return f;
}

file *empiler(file *f,char x)
{
	elemfile *new = malloc(sizeof(*new));
	new->suivant = f->premier;
	new->chemin = x;
	f->premier = new;
	return f;
}

file *enfiler(file *f, char x)
{
	elemfile *new = malloc(sizeof(*new));
    elemfile *repere = f->premier;
	new->suivant = NULL;
	new->chemin = x;
	if(f->premier ==NULL)
    {
		f->premier = new;
		return f;
	}
	while(repere->suivant != NULL)
    {
		repere = repere->suivant;
	}
	repere->suivant = new;
	return f;
}

file *supprDernierElem(file *f)
{
	elemfile *repere = f->premier;
	while(repere->suivant->suivant != NULL)
    {
		repere = repere->suivant;
	}
	free(repere->suivant);
	repere->suivant = NULL;
	return f;
}

//supprime tout les noeud d'une liste et renvoi la tete de la liste
file *supprElemFile(file *f)
{
	if(f->premier!=NULL)
    {
		elemfile *repere = f->premier;
		elemfile *repere2 = f->premier;
		f->premier = NULL;
		while(repere !=NULL)
        {
			repere =repere->suivant;
			free(repere2);
			repere2=repere;
		}
	}
	return f;
}

file *supprZero(file *f, int nbZero)
{
	
	int place = (verifTailleFile(f) - nbZero);
	elemfile *repere = f->premier;
	int m=0;

	while(m!=place)
    {
		repere = repere->suivant;
		m = m+1;
	}
	for(int i =0; i<nbZero;i++)
    {
		supprDernierElem(f);
	}	
	return f;
}

//fonction qui renvoie le nombre d'lement d'une liste
int verifTailleFile(file *f)
{
	elemfile *repere = f->premier;
	int i = 0;
	while(repere!=NULL)
    {
		i = i+1;
		repere = repere->suivant;
	}
	return i;
}