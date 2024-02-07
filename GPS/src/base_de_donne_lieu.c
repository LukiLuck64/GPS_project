#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LONGUEUR_CHAINE_CHARACTERE 50



typedef struct Lieu Lieu;
struct Lieu{
    int identifiant;
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
    retourne : un pointeur avec la liste des lieu

    ex:
    getPoints(1)[0][3]     retourne la latitude du point 3, du lieu avec l'identifiant 1
    getPoints(3)[1][5]     retourne la longitude du point 5, du lieu avec l'identifiant 3
*/
double** getPoints(int);



int main(){
    Lieu* ma_liste_lieu;

    ma_liste_lieu = getListeLieu();

    // Test:
    printf("Lieux 1: \n");
    printf("identifiant : %d\r\n", ma_liste_lieu[1].identifiant);
    printf("nom : %s\r\n", ma_liste_lieu[1].nom);
    printf("nombre_de_points : %d\n\n", ma_liste_lieu[1].nombre_de_points);


    double** mes_points;

    mes_points = getPoints(1);
    // Test:
    printf("Lieux 1: \n");
    printf("latitude point 0: %lf\n\n", mes_points[0][0]);
    printf("longitude point 3: %lf\n\n", mes_points[1][3]);
    
    return 0;
}






Lieu* getListeLieu(void){
    Lieu* liste_lieu = NULL;
    Lieu nouveau_lieu;


    FILE *fichier_liste_lieux = NULL;
    FILE *fichier_lieu = NULL;




    int nombre_de_lieu = 0;
    char *pointeur_premier_ligne = NULL;                           // Pointeur utilisé récupéré à chaque ligne

    char donnees_txt [LONGUEUR_CHAINE_CHARACTERE];          // Tram récupéré
    const char s[2] = ",";                                  // Séparateur



    




    
    // Ouverture du fichier liste des lieux
    fichier_liste_lieux = fopen("liste_lieux.txt", "r");

    if ( fichier_liste_lieux == NULL ) {
        printf("erreur d'ouverture du fichier fichier_liste_lieux");    
        exit(0);
    }

    else{
        
        while(fgets(donnees_txt, LONGUEUR_CHAINE_CHARACTERE, fichier_liste_lieux) != NULL){
            nombre_de_lieu++;
        }
        // On replace le curseur au debut du fichier
        rewind(fichier_liste_lieux);
        liste_lieu = malloc(nombre_de_lieu * sizeof(Lieu));
        nombre_de_lieu = 0;


        // Recupération de la liste des lieux (fichier .txt)
        while(fgets(donnees_txt, LONGUEUR_CHAINE_CHARACTERE, fichier_liste_lieux)){       

            if(donnees_txt != NULL){
                pointeur_premier_ligne = strtok(donnees_txt, s);
                //printf("\ntest :%s\n", donnees_txt);

                // Ajout nom lieu
                nouveau_lieu.nom = malloc(strlen(pointeur_premier_ligne) * sizeof(char));
                strcpy(nouveau_lieu.nom, pointeur_premier_ligne);   // Copie du nom du lieu

                //printf("nomLieu : %s\r\n", nouveau_lieu.nom);



                // Ajout nombre de points
                nouveau_lieu.nombre_de_points = atoi(strtok(NULL, s));
                //printf("nb points : %d\r\n", nouveau_lieu.nombre_de_points);





                // Ajout identifiant
                nouveau_lieu.identifiant = nombre_de_lieu;
                //printf("ID lieu : %d\n\n", nouveau_lieu.identifiant);
                

                // AJout lieu à la liste des lieux
                liste_lieu[nombre_de_lieu] = nouveau_lieu;

                nombre_de_lieu ++;
            }
        }
    }
    fclose(fichier_liste_lieux);


    return liste_lieu;
}







double** getPoints(int id){
    double **pointeur = NULL;


    FILE *fichier_lieu_points = NULL;

    char donnees_txt[LONGUEUR_CHAINE_CHARACTERE] = "";       // Donné récupéré
    const char s[2] = ",";                                  // Séparateur

    double *latitude = NULL;
    double *longitude = NULL;

    int compteur = 0;
    char *path;
    int nombre_de_lignes = 0;

    char *pointeur_premier_ligne = NULL;                           // Pointeur utilisé récupéré à chaque ligne


    

    // Ouverture du fichier liste des lieux
    path = malloc(6*sizeof(char));
    sprintf(path, "lieu/%d.csv", id);
    //printf("%s\n", path);

    fichier_lieu_points = fopen(path, "r");
    
    if (fichier_lieu_points == NULL) {
        printf("erreur d'ouverture du fichie\n");    
    }
    else{
        //printf("ouverture reussite du fichier\n");    
        
        // On compte le nombre de lignes dans le fichier (nb de points)
        while(fgets(donnees_txt, LONGUEUR_CHAINE_CHARACTERE, fichier_lieu_points) != NULL){
            nombre_de_lignes++;
        }
        //printf("nb lignes : %d\r\n", nombre_de_lignes);



        latitude = malloc(nombre_de_lignes * sizeof(double));
        longitude = malloc(nombre_de_lignes * sizeof(double));



        rewind(fichier_lieu_points);                    // On replace le curseur au debut du fichier

        while(fgets(donnees_txt, LONGUEUR_CHAINE_CHARACTERE, fichier_lieu_points)){
            
            pointeur_premier_ligne = strtok(donnees_txt, s);
            
            latitude[compteur] = atof(pointeur_premier_ligne);
            longitude[compteur] = atof(strtok(NULL, s));

            compteur ++;
        }
    }


    fclose(fichier_lieu_points);



    pointeur = malloc(2 * sizeof(double*));



    pointeur[0] = latitude;
    pointeur[1] = longitude;

    return pointeur;
}



