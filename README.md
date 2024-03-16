
# Project Huffman

Ce projet consiste à reconstituer l'algorithme de compression de Huffman en language C. 

Pour cela nous avons eu recours à la création d'arbres binaire de recherche, de listes chainées et à la manipulations de fichiers.

**Utilisation du programme:**

Lorsque vous compilez le code un fichier executable sera généré dans le répertoire où se trouve le main.

En lançant le programme deux options vous seront proposées via un menu : 
- En entrant 1 vous pourrez compresser un fichier texte*
- En entrant 2 vous pour décompresser un fichier binaire.

**En selectionnant la premiere option, on vous demandera de séléctionner le fichier texte à encoder. Si celui-ci se trouve dans le même répertoire que l'éxécutable, entrez simplement son nom et son extention, s'il est situé dans un autre répertoire entrez le chemin vers le texte puis son nom.*

 En compressant un texte,
un fichier binaire sera généré dans le répertoire de l'éxécutable et sera toujours nommé "Huffman.bin". Il s'agit d'un choix arbitraire le nom n'a pas d'importance lors de la décompression.

Une fois le texte compressé il vous sera demandé si vous voulez arrêter l'éxécution du programme ou si vous voulez passer à l'étape de la décompression encore une fois séléctionnez votre choix en entrant 1 ou 2. 

En séléctionnant la deuxieme option, on vous demandera de choisir un fichier binaire à décompresser. Il vous sera encore demandé d'entrer le nom du fichier à décompresser, avec son chemin s'il ne se trouve pas dans le répertoire de l'écéxutable.

Il est possible de décompresser un fichier nommé différemment que "Huffman.bin" tant qu'il a été compressé via notre programme. Ainsi sera généré le fichier nommé MonTexte.txt
étant la version décompressée du fichier binaire.



## Authors

- [@Drien95](https://github.com/Drien95) 

