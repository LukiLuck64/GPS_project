#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction_analyse_gps.h"
#include "base_de_donne_lieu.h"


int main(int , char* argv[])
{
    //Initialisation variable analyse trame
    FILE *trame_txt;
    FILE *fichierDonnees = fopen("donnees.nmea", "w");
    FILE *fichierDonneesGPS = fopen("donnees_gps.txt", "w");

    char str[256];
    char ligne[256];
    int  nb_trame=0, cpt=0, nb_ligne=0;
    double lat_lon[2][NB_TRAME];
    double dist_km=0, dist_tot=0;
    double temps[NB_TRAME][3];
    double temps_total[3];

    //Initialisation base donnée
    Lieu* List_lieu;

    List_lieu = getListeLieu();

    
    //gps_device = fopen("/dev/ttyUSB0", "r");
    trame_txt = fopen(argv[2], "r");

    // Vérifiez si l'ouverture du fichier a réussi
    if (trame_txt == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    
    // Compte le nombre de trame
    while (fgets(ligne, sizeof(ligne), trame_txt) != NULL) {
        nb_ligne++;
    }
        // On replace le curseur au debut du fichier
        rewind(trame_txt);

    // Utilisez fscanf pour lire une chaîne depuis le fichier
    while( cpt < nb_ligne)
    {
        nb_trame++; 
        // Récupération de la trame ( ligne par ligne )
        fscanf(trame_txt, "%s", str);
        
        // Enregistrement des données dans le fichier donnees.txt
        //fprintf(fichierDonnees, "\nChaine n°%d lue : %s\n\n", nb_trame, str);
        fprintf(fichierDonnees, "%s\n", str);

        // Traitement des données gps
        analyse_gps(str, fichierDonneesGPS, nb_trame, lat_lon, temps); 
       
        // Nettoyage str
        memset(str, 0, sizeof(str));
        cpt++;
        
    }





    //==================================== Fonctions de traitement des trames ===============================

    switch (atoi(argv[1]))
    {
    case 0:
        printf("Affiche les lieux\n");
        break;

    case 1:
        // Permet de calculer la distance totale et l'heure d'un itinéraire
        for(int j=0;j<nb_ligne-3;j++){
            dist_km = distance_haversine(lat_lon[0][j], lat_lon[1][j], lat_lon[0][j+1], lat_lon[1][j+1]);
            //printf("dist %lf\n , coordonne : lat1=%lf lon1=%lf lat2=%lf lon2=%lf \n",dist_km, lat_lon[0][j], lat_lon[1][j], lat_lon[0][j+1], lat_lon[1][j+1]);
            dist_tot = dist_tot + dist_km;
        }
    
        timeDif(temps[nb_ligne-1],temps[0],temps_total);

        printf("Distance total : %4.0lf m\nTemps total : %0.0lf:%0.0lf:%0.0lf \n",dist_tot*1000,temps_total[0],temps_total[1],temps_total[2]);

        break;

    case 2:
        // for(int j=0;j<NB_TRAME;j++){
        //     for(int i=0;i<NB_TRAME;i++){
        //         dist_km = distance_haversine(lat_lon[0][j], lat_lon[1][j], lat_lon[0][i], lat_lon[1][i]);
        //         if((dist_km <= atoi(argv[1])) & (dist_km != 0)){
        //         printf("proche de %.2f km   | ", dist_km);
        //         printf("coordonne : lat1=%lf lon1=%lf lat2=%lf lon2=%lf \n",lat_lon[0][j], lat_lon[1][j], lat_lon[0][i], lat_lon[1][i]);
        //         }
        //     }
        // }
        printf("entre 2 lieux");
        break;

    case 3:
        printf("Analyse l'itinéraire en proposant pour chaque point la distance qui le sépare du lieu");
        break;
    
    case 4:
        printf("Les point de rencontre ( 50m ) entre 2 itinéraires ");
        break;

    
    default:
        break;
    }
    

    // Fermez le fichier après utilisation
    fclose(fichierDonnees);
    fclose(fichierDonneesGPS);
    fclose(trame_txt);

    //system("./nmea_to_gpx.bash donnees.nmea");

    return 0;
}
