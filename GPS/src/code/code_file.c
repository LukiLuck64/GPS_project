#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction_analyse_gps.h"
#include "base_de_donne_lieu.h"


int main(int , char* argv[])
{
    //Initialisation variable analyse trame
    FILE *trame1_txt;
    FILE *trame2_txt;
    FILE *fichierDonnees = fopen("donnees.nmea", "w");
    FILE *fichierDonneesGPS = fopen("donnees_gps.txt", "w");
    FILE *fichierDonneesGPS2 = fopen("donnees_gps2.txt", "w");

    char str[256];
    char str2[256];
    char ligne[256];
    char ligne2[256];

    int  nb_trame1=0, nb_ligne1=0;
    int  nb_trame2=0, nb_ligne2=0;

    double trame_1_lat_lon[2][NB_TRAME];
    double trame_2_lat_lon[2][NB_TRAME];

    double dist_km=0, dist_tot=0, dist_km_min=0, dist_avant=0;

    double temps_1[NB_TRAME][3];
    double temps_total_1[3];

    double temps_2[NB_TRAME][3];

    int index_trame_1=0;

    //Initialisation base donnée
    Lieu* List_lieu;
    unsigned long cpt_nb_lieu = 0;
    List_lieu = getListeLieu();
    Lieu Lieu1,Lieu2;
    double** point_lieu_lat_lon;

    if((atoi(argv[1]) != 0) && (atoi(argv[1]) != 2)){

        // ========= trame 1 ===========
        //gps_device = fopen("/dev/ttyUSB0", "r");
        trame1_txt = fopen(argv[2], "r");
        
        // Vérifiez si l'ouverture du fichier a réussi
        if (trame1_txt == NULL) {
            perror("Erreur lors de l'ouverture du fichier");
            return 1;
        }
       
        // Compte le nombre de trame
        while (fgets(ligne, sizeof(ligne), trame1_txt) != NULL) {
            nb_ligne1++;
        }
            // On replace le curseur au debut du fichier
            rewind(trame1_txt);


        // Utilisez fscanf pour lire une chaîne depuis le fichier
        while( nb_trame1 < nb_ligne1)
        {
            // Récupération de la trame ( ligne par ligne )
            fscanf(trame1_txt, "%s", str);

            // Enregistrement des données dans le fichier donnees.txt
            fprintf(fichierDonnees, "%s\n", str);

            // Traitement des données gps
            analyse_gps(str, fichierDonneesGPS, nb_trame1, trame_1_lat_lon, temps_1); 
        
            // Nettoyage str
            memset(str, 0, sizeof(str));
            nb_trame1++;
            
        }

        // Fermez le fichier après utilisation
        fclose(fichierDonnees);
        fclose(fichierDonneesGPS);
        fclose(trame1_txt);

        index_trame_1 = index_trame;
        
        

        if(atoi(argv[1])== 4){
            index_trame = 0;
            // ========= trame 2 ===========
            trame2_txt = fopen(argv[3], "r");

            if (trame2_txt == NULL) {
                perror("Erreur lors de l'ouverture du fichier");
                return 1;
            }

            // Compte le nombre de trame
            while (fgets(ligne2, sizeof(ligne2), trame2_txt) != NULL) {
                nb_ligne2++;
            }
                // On replace le curseur au debut du fichier
                rewind(trame2_txt);

            // Utilisez fscanf pour lire une chaîne depuis le fichier
            while( nb_trame2 < nb_ligne2)
            {
                // Récupération de la trame ( ligne par ligne )
                fscanf(trame2_txt, "%s", str2);


                // Traitement des données gps
                analyse_gps(str2, fichierDonneesGPS2, nb_trame2, trame_2_lat_lon, temps_2); 
            
                // Nettoyage str
                memset(str2, 0, sizeof(str2));
                nb_trame2++;
                
            }
            
            fclose(trame2_txt);
            fclose(fichierDonneesGPS2);
        }



    }


    //==================================== Fonctions de traitement des trames ===============================

    switch (atoi(argv[1]))
    {
    case 0:
        printf("Affiche les lieux\n");
        while (List_lieu[cpt_nb_lieu+1].nom != NULL )
        {
            printf("le lieu %lu est %s \n",cpt_nb_lieu, List_lieu[cpt_nb_lieu].nom);
            cpt_nb_lieu++;
        }
        
        break;

    case 1:
        
        // Permet de calculer la distance totale et l'heure d'un itinéraire
        for(int j=0;j<nb_trame1-3;j++){
            dist_km = distance_haversine(trame_1_lat_lon[0][j], trame_1_lat_lon[1][j], trame_1_lat_lon[0][j+1], trame_1_lat_lon[1][j+1]);
            dist_tot = dist_tot + dist_km;
        }
    
        timeDif(temps_1[nb_trame1-1],temps_1[0],temps_total_1);

        printf("Distance total : %4.0lf m\nTemps total    : %0.0lf:%0.0lf:%0.0lf \n",dist_tot*1000,temps_total_1[0],temps_total_1[1],temps_total_1[2]);

        break;

    case 2:
        
        printf("Distance entre 2 lieux :\n");
        while (List_lieu[cpt_nb_lieu+1].nom != NULL )
        {
            if(strcmp(List_lieu[cpt_nb_lieu].nom,argv[2])==0 ){
                Lieu1=List_lieu[cpt_nb_lieu];
            }

            if(strcmp(List_lieu[cpt_nb_lieu].nom,argv[3])==0 ){
                Lieu2=List_lieu[cpt_nb_lieu];
            }
            cpt_nb_lieu++;
        }

        dist_km = distance_haversine(getPoints((int)Lieu1.identifiant)[0][0], getPoints((int)Lieu1.identifiant)[1][0], getPoints((int)Lieu2.identifiant)[0][0], getPoints((int)Lieu2.identifiant)[1][0]);

        printf("Distance entre %s et %s est de %3.0lf m\n",Lieu1.nom, Lieu2.nom, dist_km*1000);

        break;

    case 3:
        printf("Analyse l'itinéraire en proposant pour chaque point la distance qui le sépare du lieu\n");
        
        while (List_lieu[cpt_nb_lieu+1].nom != NULL )
        {
            if(strcmp(List_lieu[cpt_nb_lieu].nom,argv[3])==0 ){
                Lieu1=List_lieu[cpt_nb_lieu];
            }
            cpt_nb_lieu++;
        }

        point_lieu_lat_lon = getPoints((int)Lieu1.identifiant);

        dist_km_min = 5000;
        
        for(int j=0;j<index_trame;j++){
            for(int i=0;i<(Lieu1.nombre_de_points);i++){
                dist_km = distance_haversine(trame_1_lat_lon[0][j], trame_1_lat_lon[1][j], point_lieu_lat_lon[0][i], point_lieu_lat_lon[1][i]);
                
                if(dist_km<dist_km_min){
                    dist_km_min = dist_km;
                }

            }
            if(dist_avant != dist_km_min){
                printf(" proche de %lf m du %s \n", dist_km_min*1000, Lieu1.nom);
                dist_avant = dist_km_min;
            }
            dist_km_min = 5000;
        }
        break;
    
    

    case 4:
        printf("Les points de rencontre ( 100m ) entre 2 itinéraires \n");
        for(int j=0;j<index_trame_1;j++){
            for(int i=0;i<index_trame;i++){
                dist_km = distance_haversine(trame_1_lat_lon[0][j], trame_1_lat_lon[1][j], trame_2_lat_lon[0][i], trame_2_lat_lon[1][i]);

                if(dist_avant != dist_km){
                    if((dist_km <= 0.1) & (dist_km != 0)){
                        printf("trame1 : point %d  et trame2 : point %d sont proche de %.2f m  \n",j/2,i/2, dist_km*1000);
                        dist_avant = dist_km;
                    }
                }

               
                //printf("coordonne : lat1=%lf lon1=%lf lat2=%lf lon2=%lf \n",trame_1_lat_lon[0][j], trame_1_lat_lon[1][j], trame_2_lat_lon[0][i], trame_1_lat_lon[1][i]);
            }
        }
        break;

    
    default:
        break;
    }

    //system("./nmea_to_gpx.bash donnees.nmea");

    return 0;
}
