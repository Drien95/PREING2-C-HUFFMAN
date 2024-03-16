#include "fonction.h"
//vous trouverez dans ce fichier toutes les fonctions liées a la création et manipulation des arbres.


//creer un arbre huffman depuis un tableau contenant caractere et leurs occurence
arbre *creationArbreTab(element *tab,arbre *arb,int tailletab)
{
    int i = 0;
    if(tab[i].occ == 0)
    {
        while(tab[i].occ<1)
        {
            i = i+1;
        }
    }
    arb->fg = sousArbre(tab,(i+1),(i));
    i=i+2;
    while(i<=(tailletab))
    {
        if(i != (tailletab))
        {
            if((arb->fg->val.occ + tab[i].occ) <= (tab[i].occ +tab[i+1].occ))//cherche l'addition la moins grande pour trouver la meilleur option (option 1)
            {
                arb = option1(tab,i,arb);
                i=i+1;
            }
            else    //option 2
            {
            arb = option2(tab,i,arb);
            i=i+2;
            }
        }
        else    //option ou c'est le dernier caractere
        {
            arb = option1(tab,i,arb);
            i = i+1;
        }	
    }
    return arb;
}

arbre *creerArbre() //créé l'element d'un arbre vide
{
	arbre *a = malloc(sizeof(*a));
	if(a == NULL)
    {
		exit(EXIT_FAILURE);
	}
	a->val.ascii = -1;
	a->val.occ = -1;
	a->fg = NULL;
	a->fd = NULL;
	return a;
}

arbre *creerElemArbre(element x)   //créé l'element d'un arbre prenant juste un element en entré
{ 
	arbre *a = malloc(sizeof(*a));
	if(a == NULL)
    {
		exit(EXIT_FAILURE);
	}
	a->val = x;
	a->fg = NULL;
	a->fd = NULL;
	return a;
}

//booleen verifiant qu'un noeud d'un arbre est une feuille (1 si oui  0 si non)
int estFeuille(arbre *a)
{
	if((a->fg == NULL) && (a->fd == NULL))
    {
		return 1;
	}
	return 0;
}

int hauteur(arbre *a)
{
	if(a == NULL)
    {
		return 0;
	}
	return 1 +max(hauteur(a->fg),hauteur(a->fd));
}

//fonction recursive qui renvoie le chemin d'un caractere de l'arbre dans une liste exemple : 0110a (0 = fg 1 =fd et a la fin le caractere) 
int recherche(int c,arbre *a,file *f)
{
	if(estFeuille(a) == 1)
    {
		if(a->val.ascii == c)
        {
			empiler(f,(char)c);
			return 1;
		}
		else
        {
			return 0;
		}
	}
	if(recherche(c,a->fg,f) == 1)
    {
		if(a->fg !=NULL && a->fd != NULL)
		{
			empiler(f,'0');	
		}
		return 1;	

	}
	if(recherche(c,a->fd,f) == 1)
    {
		empiler(f,'1');
		return 1;
	}
	return -1;
}

//creer un arbre avec en fg une addition de deux noeud et en fils droit un nouveau caractere avec son nombre d'occurence
arbre *option1(element *tab,int i,arbre *a)
{ 
	arbre *tmp = creerArbre();
	tmp->val.occ = (tab[i].occ) + (a->fg->val.occ);
	tmp->fg = a->fg;
	a->fg = tmp;
	tmp->fd = creerArbre();
	tmp->fd->val = tab[i];
	return a;
}

// creer un arbre avec en fils des caractere et leur occurrence,creer ensuite son pere qui va etre une addition des fils
arbre *option2(element *tab,int i,arbre *a)
{ 
	arbre *tmp = creerArbre();					
	tmp->fd = creerArbre();
	tmp->fd->val = tab[i+1];
	tmp->fg =creerArbre();
	tmp->fg->val = tab[i];
	tmp->val.occ = (tmp->fg->val.occ) + (tmp->fd->val.occ);
	arbre *tmp2 = creerArbre();
	tmp2->fd = tmp;
	tmp2->fg = a->fg;
	a->fg = tmp2;
	tmp2->val.occ = (tmp2->fg->val.occ) + (tmp2->fd->val.occ);
	return a;
}

//meme fonction que recherche mais qui renvoie un chemin sans le caractere a la fin
int recherche2(int c,arbre *a,file *f)
{
	if(estFeuille(a) == 1)
    {
		if(a->val.ascii == c)
        {
			return 1;
		}
		else{
			return 0;
		}
	}
	if(recherche2(c,a->fg,f) == 1)
    {
		if(a->fg !=NULL && a->fd != NULL)
		{
			empiler(f,'0');	
		}
		return 1;	

	}
	if(recherche2(c,a->fd,f) == 1)
    {
		empiler(f,'1');
		return 1;
	}
	return -1;
}

arbre *recreationArbre(FILE *cle)
{
	char car = fgetc(cle);
	arbre *arb = creerArbre();
	arbre *repere = arb;
	while(car != EOF)
    {
		if(car == '0')
        {
			if(repere->fg == NULL)
            {
				repere->fg = creerArbre();
			}
			repere = arb->fg;	
		}
		else if(car == '1')
        {
			if(repere->fd == NULL)
            {
				repere->fd = creerArbre();
			}
			repere = arb->fd;	
		}
		else
        {
			repere->val.ascii = (int)car;
		}
		car = fgetc(cle);
	}
	return arb;
}

//créé un sousArbre prenant 2 case du tableau pour en faire les 2 fils du sousArbre
arbre *sousArbre(element *tab,int x,int y)
{ 
	arbre *a = creerElemArbre(tab[x]);
	arbre *b = creerElemArbre(tab[y]);
	arbre *c = creerArbre();
	c->val.occ = (a->val.occ + b->val.occ);
	c->fg = b;
	c->fd = a;
	return c;
	
}

int taille(arbre *a)
{
	if(a == NULL)
    {
		return 0;
	}
	return ( 1 + taille(a->fg) + taille(a->fd));
}