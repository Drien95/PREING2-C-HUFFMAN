#include "fonction.h"


int main(int argc, char** argv){
	
	printf("1.Encoder un texte\n2.Decoder un texte\nSelectionnez votre choix : ");
	int choix;
	scanf("%d",&choix);
	while(choix != 1 && choix != 2)
	{
		printf("Ce choix est impossible, veuillez entrer 1 pour compresser un fichier, 2 pour en décompresser ou bien CTRL+C pour arreter l'execution du programme : ");	
		scanf("%d",&choix);
	}
	
	//encodage
	if(choix == 1)
	{
		//récuperation du fichier texte et création d'un tableau de structure (structure contenant un caractere et son nombre d'occurence)
		char name[100];
		element tab[256];
		initialisationTab(tab);
		printf("Entrez le nom du fichier .txt a décoder( et son chemin s'il n'est pas dans le même répertoire que le programme ) :\n");
		scanf("%s", &name);
		FILE *fichier = fopen(name,"r+");
		if(fichier == NULL)
		{
			printf("\nerreur\n");
			exit(EXIT_FAILURE);
		}
		printf("\nEncodage en cours...\n");

		
		//parcours du fichier texte caractere par caractere et ajoute +1 occurence dans la case du tableau correspondant au caractere parcouru puis tri le tableau par rapport au nombre d'occurence
		occurence(tab,fichier);
		triTab(tab);
		fclose(fichier);
		arbre *arb = creerArbre();

		//creation de l'arbre huffman
		arb = creationArbreTab(tab,arb,255);
	
		//encodage du texte grace a l'arbre
		FILE *bin = fopen("Huffman.bin","wba");
		if(bin == NULL){
			printf("\nerreur ouverture bin\n");
		}
		inscriptionTxt(arb,name);//creer un fichier texte pour y mettre chaque caractere mais par rapport a leur chemin dans l'arbre
		inscriptionOctet1(bin);//implementation du premier octet dans le .bin correspondant au nombre de 0 a supprimer si il faut remplir un octet a la fin pour le rentrer dans le .bin
		inscriptionOctet2(bin,tab);//implementation du deuxieme octet dans le .bin correspondant a la taille du tableau afin de savoir combien d'octet faut-il lire
		inscriptionTab(bin,tab);//inscription du tableau dans le .bin
		codage(bin);//inscription du fichier texte contenant le texte chiffré dans le .bin puis supprime le fichier texte
		printf("Compression réussie! Recuperez votre texte encodé sous le nom Huffman.bin dans le dossier où se trouve le programme.\n");
		//afficher les resultats du chiffrement
		struct stat st;
		struct stat st2;
		stat(name, &st);
		stat("Huffman.bin",&st2);
		int size = st.st_size;
		int size2 = st2.st_size;
		printf("\n%s : %d Octets\nHuffman.bin : %d Octets\nRatio de compression : %d %%\n",name,size,size2,(100 - (size2*100)/ size));
		printf("\nSouhaitez arreter l'execution du programme ou decompresser un texte?\n1.Arreter le programme\n2.Decompresser un texte\nSelectionnez votre choix : ");
		scanf("%d",&choix);
		while(choix != 1 && choix != 2)
		{
			printf("Ce choix est impossible, veuillez entrer 1 pour arrêter le programme ou bien 2 pour décompresser un fichier : ");	
			scanf("%d",&choix);
		}
	}
	// decodage
	if(choix == 2)
	{ 
		
		//recuperation du fichier encodé
		printf("\nEntrez le nom du fichier encodé en .bin ( et son chemin s'il n'est pas dans le même répertoire que le programme ) : ");
		char name[30];
		scanf("%s", &name);
		FILE *restBin = fopen(name,"r");
		if(name == NULL)
		{
			printf("erreur");
		}

		//recupération des valeur inscrites sur les 3 premiere octet
		int nbz = fgetc(restBin);
		int tailleTab = fgetc(restBin);
		int size = fgetc(restBin);

		//recuperation de l'arbre
		element restTab[tailleTab];
		arbre *arbTmp = creerArbre();
		recreationTab( restBin , restTab , tailleTab , size);
		creationArbreTab( restTab,  arbTmp , (tailleTab-1) );
		arbre *restArb = arbTmp->fg;

		//recuperation du texte encodé
		unsigned char repere = getc(restBin);
		
		file *tmp = creerFile();
		elemfile *d  = NULL;//file contenant le texte codé
		FILE *txtTmp = fopen("txt.txt","w");
		if(txtTmp == NULL)
		{
			printf("erreur");
		}
		while(!feof(restBin))
		{
			tmp = convertionDeci(repere,tmp);
			d = tmp->premier;
			while(d != NULL)
			{
				fputc(d->chemin, txtTmp);
				d = d->suivant;
			}
			d = NULL;
			tmp = supprElemFile(tmp);
			repere = getc(restBin);
		}
		fclose(txtTmp);

		//decodage a l'aide du fichier texte contenant le texte codé et l'arbre huffman
		FILE *decode = fopen("MonTexte.txt","w");
		if(decode== NULL)
		{
			printf("erreur");
		}
		txtTmp = fopen("txt.txt","r");
		arbre *p = restArb;
		unsigned char tt;
		unsigned char restLettre = getc(txtTmp);
		while(!feof(txtTmp)){
			if((restLettre == '0') && (estFeuille(p) == 0))
			{
				p =p->fg;
			}
			else if((restLettre == '1') && (estFeuille(p) == 0))
			{
				p = p->fd;
			}
			if(estFeuille(p) == 1)
			{
				tt = p->val.ascii;
				fputc(tt,decode);
				p = restArb;
			}
			restLettre = (unsigned char)getc(txtTmp);
		}
		
		fclose(decode);
		fclose(txtTmp);
		remove("txt.txt");
		printf("Décompression réussie! Retrouvez votre texte sous le nom MonTexte.txt\n");
	}
	

	return 0;
}
