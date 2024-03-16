#include "fonction.h"
//vous trouverez dans ce fichier toutes les fonctions liées a la création et manipulation des textes.


//récupére le .txt contenant le fichier encodé pour le réécrire dans un fichier .bin
void codage(FILE *bin)
{
	FILE *txt = fopen("txt.txt","r");
	char bit = fgetc(txt);
	char *p = &bit;
	file *fOctet = creerFile();
	int octetInt;
	
	while(*p != EOF)
    {
		creationOctet(fOctet,txt,p); 
		octetInt = convertionBin(fOctet);
		fputc(octetInt,bin);
		supprElemFile(fOctet);
		
	}
	fclose(bin);
	fclose(txt);
	bin = NULL;
	txt = NULL;
	remove("txt.txt");
}
	
//converti une liste de 8bit (un octet) en entier
int convertionBin(file *f)
{
	elemfile *p = f->premier;
	int sum = 0;
	for(int i = 7;0<=i;i--)
    {
		if(p->chemin == '1')
        {
			sum = sum + pow(2,i);
		}
		p=p->suivant;
	}
	return sum;
}

//converti une liste de 16bit (un octet) en entier
int convertionBin2(file *f)
{ 
	elemfile *p = f->premier;
	int sum = 0;
	for(int i = 15;0<=i;i--)
    {
		if(p->chemin == '1')
        {
			sum = sum + pow(2,i);
		}
		p=p->suivant;
	}
	return sum;
}

//converti un entier en une liste de 8bit 
file *convertionDeci(int x,file *octet)
{
	for(int i=7;i>=0;i--)
    {
		if(x < (pow(2,i)))
        {
			enfiler(octet,'0');
			
		}
		else
        {
			enfiler(octet,'1');
			x = x - pow(2,i);
		}
	}
	return octet;
}
	
//regroupe les bits du fichier encodé en txt pour en faire des octet pour après les mettres dans le .bin
file *creationOctet(file *octet,FILE *txt,char *bit)
{
	for(int i=0;i<8;i++)
    {
		if(*bit == EOF && verifTailleFile(octet)<8)
        {
			while(verifTailleFile(octet) < 8)
            {
				enfiler(octet,'0');
			}
			return octet;
		}
		enfiler(octet,*bit);
		*bit = fgetc(txt);
	}
	return octet;
}

//ajout d'un octet au debut etant égal aux nombre de zero ajouté a la fin 
void inscriptionOctet1(FILE *bin)
{
	FILE *txt = fopen("txt.txt","r");
	if(txt == NULL || bin == NULL)
    {
		printf("\nerror\n");
		exit(EXIT_FAILURE);
	}
	int nbZero = tailleTexte(txt) % 8;
	if(nbZero != 0)
    {
		nbZero = 8 - nbZero;
		
	}
	fputc(nbZero,bin);
	fclose(txt);
}

//inscris le 2eme octet dans le bin c'est a dire le nombre de case du tableau
void inscriptionOctet2(FILE *bin,element *tab)
{
	int i = 0;
	while(tab[i].occ == 0)
    {
		i=i+1;
	}
	fputc((256-i),bin);
}

//écris l'arbre (clé de décodage) dans un fichier texte (cle.txt)
void inscriptionTab(FILE *bin,element *tab)
{
	int i = 0;
	int veriftaille = 0;
	while(tab[i].occ == 0)
    {
		i = i+1;
	}
	if(tab[255].occ >255)   //verifier si une occurence depasse 256
    {
		veriftaille = 1;
	}
	putc(veriftaille,bin);
	if(veriftaille == 0)    //dans ce cas la case occurence du tablea sera encoder sur 1 octet (char)
    {
		while(i<256)
        {
		    fwrite(&(tab[i].ascii),sizeof(char),1,bin);
		    fwrite(&(tab[i].occ),sizeof(char),1,bin);
		    i = i+1;
		}
	}
	else    //dans ce cas (occurence depassant 256) la case occurence du tableau sera encoder sur 2 octet (short)
    {
		while(i<256)
        {
			fwrite(&(tab[i].ascii),sizeof(char),1,bin);
			fwrite(&(tab[i].occ),sizeof(short),1,bin);
			i = i+1;
		}
	}
}

//réalise le codage huffman dans un .txt
void inscriptionTxt(arbre *a,char *name)
{ 
	remove("txt.txt");
	FILE *fichier = fopen(name,"r+");
	FILE *txt = fopen("txt.txt","w");
	if(txt == NULL)
    {
		printf("erreur");
	}
	if(fichier == NULL)
    {
		printf("erreur 2");
	}
	file *file = creerFile();
	unsigned char lettre = getc(fichier);
	elemfile *repere = malloc(sizeof(*repere));
	int lettreascii;
	while(!feof(fichier))
    {
		lettreascii = (int)lettre;
		recherche2(lettreascii,a,file);
		repere =file->premier;
		while(repere != NULL)
        {
			lettre = repere->chemin;
			fputc(lettre,txt);
			repere = repere->suivant;
		}
		supprElemFile(file);
		lettre = getc(fichier);
	}
	fclose(fichier);
	fclose(txt);
}

int max(int a,int b)
{
	if(a<b)
    {
		return b;
	}
	return a;
}

//calcul le nombre de caractere que possede une texte
int tailleTexte(FILE *texte)
{
	int taille = 0;
	char caractere;
	while(caractere != EOF)
    {
		caractere = fgetc(texte);
		taille = taille +1;
	}
	taille = taille-1;
	return taille;
} 