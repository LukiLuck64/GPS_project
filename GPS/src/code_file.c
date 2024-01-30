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
    double dist_km=0, dist_tot=0;
    double temps[NB_TRAME][3];

    
    //gps_device = fopen("/dev/ttyUSB0", "r");
    gps_device = fopen("/media/21902988/Z/GPS_project/GPS/src/output.txt", "r");

    // Vérifiez si l'ouverture du fichier a réussi
    if (gps_device == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    
    // Utilisez fscanf pour lire une chaîne depuis le fichier
    while(fgetc(gps_device) != EOF)
    {
        nb_trame++;
        // Récupération de la trame ( ligne par ligne )
        fscanf(gps_device, "%s", str);
        
        // Enregistrement des données dans le fichier donnees.txt
        //fprintf(fichierDonnees, "\nChaine n°%d lue : %s\n\n", nb_trame, str);
        fprintf(fichierDonnees, "%s\n", str);

        // Traitement des données gps
        analyse_gps(str, fichierDonneesGPS, nb_trame, lat_lon, temps); 

        // Nettoyage str
        memset(str, 0, sizeof(str));
    }

    // for(int j=0;j<NB_TRAME;j++){
        //     for(int i=0;i<NB_TRAME;i++){
        //         dist_km = distance_haversine(lat_lon[0][j], lat_lon[1][j], lat_lon[0][i], lat_lon[1][i]);
        //         if((dist_km <= atoi(argv[1])) & (dist_km != 0)){
        //         printf("proche de %.2f km   | ", dist_km);
        //         printf("coordonne : lat1=%lf lon1=%lf lat2=%lf lon2=%lf \n",lat_lon[0][j], lat_lon[1][j], lat_lon[0][i], lat_lon[1][i]);
        //         }
        //     }
        // }

    // Permet de calculer la distance totale et l'heure d'un itinéraire
    for(int j=0;j<NB_TRAME-3;j++){
        dist_km = distance_haversine(lat_lon[0][j], lat_lon[1][j], lat_lon[0][j+1], lat_lon[1][j+1]);
        //printf("dist %lf\n , coordonne : lat1=%lf lon1=%lf lat2=%lf lon2=%lf \n",dist_km, lat_lon[0][j], lat_lon[1][j], lat_lon[0][j+1], lat_lon[1][j+1]);
        dist_tot = dist_tot + dist_km;
    }
    printf("%lf:%lf:%lf\n\n", temps[NB_TRAME][0],temps[NB_TRAME][1],temps[NB_TRAME][3]);
     printf("distance total %lf km\n heure total %lf:%lf:%lf",dist_tot,temps[NB_TRAME-2][0]-temps[0][0],temps[NB_TRAME-2][1]-temps[0][1],temps[NB_TRAME-2][2]-temps[0][2]);

        

    //Exemple d'utilisation de la fonction
    double lat1 = 49.179880; // Latitude de San Francisco
    double lon1 = -0.363955; // Longitude de San Francisco

    double lat2 = 49.179179; // Latitude de Los Angeles
    double lon2 = -0.363955; // Longitude de Los Angeles

    double dist = distance_haversine(lat1, lon1, lat2, lon2);

    //printf("Distance entre San Francisco et Los Angeles : %.2f km\n", dist);
    
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