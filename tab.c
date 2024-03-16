#include "fonction.h"
//vous trouverez dans ce fichier toutes les fonctions liées a la création et manipulation des tableaux.


void initialisationTab(element *tab)
{
    for(int i=0; i<256;i++)
    {
        tab[i].ascii = i;
        tab[i].occ = 0;
    }

}

//mesure la frequence d'un caractere
void occurence(element *tab, FILE *fichier)
{ 
    int deci;
	unsigned char c = getc(fichier);
    while(!feof(fichier))
    {
        deci = (int)c;
        tab[deci].occ = 1 + tab[deci].occ ;
        c = getc(fichier);
    }
}

void recreationTab(FILE *bin,element *restTab,int tailleTab,int size)
{
	int i = 0;
	if(size == 0)   //si aucun caractere ne depasse 256 occurence c'est a dire qu'aucun caractere n'est codé sur 2 octet
    {
		for(i;i<tailleTab;i++)
        {
			restTab[i].ascii = getc(bin);
			restTab[i].occ = getc(bin); 
		}
	}
	else    //les occurence sont codé sur 2 octet
    {
		int occ,occ1,occ2;
		file *tmp1 = creerFile();
		file *tmp2 = creerFile();
		i=0;
		for(i;i<(tailleTab+1);i++)
        {
			restTab[i].ascii = getc(bin);
			occ2 = getc(bin);
			occ1 = getc(bin);
			tmp1 = convertionDeci(occ1,tmp1);
			tmp2 = convertionDeci(occ2,tmp2);
			tmp1 = ajoutFile(tmp1,tmp2);
			supprElemFile(tmp2);
			occ = convertionBin2(tmp1);
			restTab[i].occ = occ;
			supprElemFile(tmp1);
		}
	}
}

//tri d'un tableau de structure 
void triTab(element *tab)
{ 
    element tmp;
    for(int i = 0; i<256;i++)
    {
        for(int j = 0; j<i;j++)
        {
            if(tab[j].occ>tab[i].occ)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}