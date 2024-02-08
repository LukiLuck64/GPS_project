
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Lieu Lieu;
struct Lieu{
    unsigned long identifiant;
    char *nom;
    int nombre_de_points;
};


/*
    parametre : void
    retourne : un pointeur de la structure Lieu

    ex:
    getListeLieu[0].identifiant                  retourne l'identifiant du lieu 0
    getListeLieu[3].nom                          retourne le nom du lieu 3
    getListeLieu[6].nombre_de_points             retourne le nombre de points du lieu 6
*/
Lieu* getListeLieu(void);


/*
    parametre : identifiant du lieu
    retourne : un pointeur avec la liste des points du lieux

    ex:
    getPoints(1)[0][3]     retourne la latitude(0) du point 3, du lieu avec l'identifiant 1
    getPoints(3)[1][5]     retourne la longitude(1) du point 5, du lieu avec l'identifiant 3
*/
double** getPoints(int);