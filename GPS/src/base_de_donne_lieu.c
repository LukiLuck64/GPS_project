#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NOMBRE_DE_LIEU 1


typedef struct Lieu Lieu;
struct Lieu{
    int identifiant;
    char *nom;
    int nombre_de_points;
};


double** getPoints(int);



int main(){
    Lieu* liste_lieu = NULL;
    Lieu nouveau_lieu;


    FILE *fichier_liste_lieux = NULL;
    FILE *fichier_lieu = NULL;




    int taille;
    char *nomLieu;

    char donnees_txt [30];       // Tram récupéré
    const char s[2] = ",";  // Séparateur



    liste_lieu = malloc(NOMBRE_DE_LIEU * sizeof(Lieu));




    
    // Ouverture du fichier liste des lieux
    fichier_liste_lieux = fopen("liste_lieux.txt", "r");

    if ( fichier_liste_lieux == NULL ) {
        printf("erreur d'ouverture du fichier fichier_liste_lieux");    
    }


    

    for(int i=0; i<NOMBRE_DE_LIEU; i++){
        // Recupération donne liste lieux (.txt)
        if(fichier_liste_lieux != NULL){
            fgets(donnees_txt, 30, fichier_liste_lieux);
        }
        

        // Ajout identifiant
        nouveau_lieu.identifiant = i;


        // Ajout nom lieu
        //strcpy(nomLieu, "chateau");
        nomLieu = strtok(donnees_txt, s);
        nouveau_lieu.nom = malloc(strlen(nomLieu) * sizeof(char));
        printf("nomLieu : %s\r\n", nomLieu);

        strcpy(nouveau_lieu.nom, nomLieu);


        // Ajout nombre de points
        //nouveau_lieu.nombre_de_points = 16;
        nouveau_lieu.nombre_de_points = atoi(strtok(NULL, s));


        // AJout lieu à la liste des lieux
        liste_lieu[i] = nouveau_lieu;


        /*         fichier_lieu = fopen(strcat(nouveau_lieu.nom, ".txt"), "r");
        if ( fichier_lieu == NULL ) {
            printf("erreur d'ouverture du fichier");    
        }    */
    }


    fclose(fichier_liste_lieux);

    //printf("%s\r\n", liste_lieu[1].nom);



    // l'erreur est du au nombre de donnée à 2


    

    getPoints(0);
    


    return 0;
}





double** getPoints(int id){
    double **pointeur;
    FILE *fichier_lieu_points = NULL;

    char donnees_txt[40] = "";       // Donné récupéré
    const char s[2] = ",";  // Séparateur

    double *latitude = NULL;
    double *longitude = NULL;

    int compteur = 0;
    char path[6];
    int nombre_de_points = 0;




    

    // Ouverture du fichier liste des lieux
    sprintf(path, "%d.csv", id);

    fichier_lieu_points = fopen("lieu/0.csv", "r");
    if ( fichier_lieu_points == NULL ) {
        printf("erreur d'ouverture du fichier fichier_liste_lieux");    
    }


    if(fichier_lieu_points != NULL){
        // On compte le nombre delignes dans le fichier (nb de points)

        while(fgets(donnees_txt, 40, fichier_lieu_points) != NULL){
            nombre_de_points++;
        }

        printf("nb lignes : %d\r\n", nombre_de_points);



        latitude = malloc(nombre_de_points * sizeof(double));
        longitude = malloc(nombre_de_points * sizeof(double));



        rewind(fichier_lieu_points);                    // On replace le curseur au debut du fichier

        while(fgets(donnees_txt, 40, fichier_lieu_points)){
            
            latitude[compteur] = atof(strtok(donnees_txt, s));
            longitude[compteur] = atol(strtok(NULL, s));

            compteur ++;
        }
    }


    //printf("latitude 2 : %f\r\n", latitude[2]);



    pointeur = malloc(2 * sizeof(double*));



    pointeur[0] = latitude;
    pointeur[0] = latitude;
    return pointeur;
}



