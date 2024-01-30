#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "code_gps.c"

/*
cd /
cd dev/
sudo chmod 777 ttyUSB0 
stty -F /dev/ttyUSB0 4800
cd ~/Documents/Esix/GPS/
gcc code_file.c -o trame_gps -lm
./trame_gps
*/


int main(int argc, char* argv[])
{
    FILE *gps_device;
    FILE *fichierDonnees = fopen("donnees.nmea", "w");
    FILE *fichierDonneesGPS = fopen("donnees_gps.txt", "w");

    char str[256];
    char reponse = 'a';
    int bytesRead, ch, nb_trame=0;
    double lat_lon[2][NB_TRAME];
    double dist_km=0;
    

    //gps_device = fopen("/dev/ttyUSB0", "r");
    gps_device = fopen("/media/21902988/Z/GPS_project/GPS/src/output.txt", "r");

    // Vérifiez si l'ouverture du fichier a réussi
    if (gps_device == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    
    // Utilisez fscanf pour lire une chaîne depuis le fichier
    while(!feof(gps_device))
    {
        nb_trame++;
        // Récupération de la trame ( ligne par ligne )
        fscanf(gps_device, "%s", str);
        
        // Enregistrement des données dans le fichier donnees.txt
        //fprintf(fichierDonnees, "\nChaine n°%d lue : %s\n\n", nb_trame, str);
        fprintf(fichierDonnees, "%s\n", str);

        // Traitement des données gps
        analyse_gps(str, fichierDonneesGPS, nb_trame, lat_lon); 

        // Nettoyage str
        memset(str, 0, sizeof(str));

        // 50 trames récupérées
        if(nb_trame==10){

            // for(int j=0;j<NB_TRAME;j++){
            //     for(int i=0;i<NB_TRAME;i++){
            //         dist_km = distance_haversine(lat_lon[0][j], lat_lon[1][j], lat_lon[0][i], lat_lon[1][i]);
            //         if((dist_km <= atoi(argv[1])) & (dist_km != 0)){
            //         printf("proche de %.2f km   | ", dist_km);
            //         printf("coordonne : lat1=%lf lon1=%lf lat2=%lf lon2=%lf \n",lat_lon[0][j], lat_lon[1][j], lat_lon[0][i], lat_lon[1][i]);
            //         }
            //     }
            // }

            break;
        }

        
        
    }

    // Exemple d'utilisation de la fonction
    // double lat1 = 37.809326; // Latitude de San Francisco
    // double lon1 = -122.409981; // Longitude de San Francisco

    // double lat2 = 34.052235; // Latitude de Los Angeles
    // double lon2 = -118.243683; // Longitude de Los Angeles

    // lat1=49.288333; lon1=0.463889; lat2=49.289444; lon2=0.486944;

    // double dist = distance_haversine(lat1, lon1, lat2, lon2);

    // printf("Distance entre San Francisco et Los Angeles : %.2f km\n", dist);
    
    // // Exemple d'utilisation de la fonction de Vincenty
    //double distance = distance_vincenty(lat1, lon1, lat2, lon2);
    //printf("Distance entre San Francisco et Los Angeles : %.2f km\n", distance);


    // Fermez le fichier après utilisation
    fclose(fichierDonnees);
    fclose(fichierDonneesGPS);
    fclose(gps_device);

    //system("./nmea_to_gpx.bash donnees.nmea");

    return 0;
}