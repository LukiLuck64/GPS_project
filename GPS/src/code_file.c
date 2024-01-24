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

int main()
{
    FILE *gps_device;
    FILE *fichierDonnees = fopen("donnees.nmea", "w");
    FILE *fichierDonneesGPS = fopen("donnees_gps.txt", "w");

    char str[256];
    char reponse = 'a';
    int bytesRead, ch, nb_trame=0;

    gps_device = fopen("/dev/ttyUSB0", "r");
    //gps_device = fopen("/home/luc/Documents/Esix/GPS/sauvegarde.txt", "r");

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
        analyse_gps(str, fichierDonneesGPS, nb_trame); 

        // Nettoyage str
        memset(str, 0, sizeof(str));

        // 50 trames récupérées
        if(nb_trame==50){
            break;
        }
        
    }

    // Exemple d'utilisation de la fonction
    double lat1 = 37.809326; // Latitude de San Francisco
    double lon1 = -122.409981; // Longitude de San Francisco

    double lat2 = 34.052235; // Latitude de Los Angeles
    double lon2 = -118.243683; // Longitude de Los Angeles

    double dist = distance_haversine(lat1, lon1, lat2, lon2);

    printf("Distance entre San Francisco et Los Angeles : %.2f km\n", dist);
    
    // // Exemple d'utilisation de la fonction de Vincenty
    //double distance = distance_vincenty(lat1, lon1, lat2, lon2);
    //printf("Distance entre San Francisco et Los Angeles : %.2f km\n", distance);


    // Fermez le fichier après utilisation
    fclose(fichierDonnees);
    fclose(fichierDonneesGPS);
    fclose(gps_device);

    //system("./nmea_to_gpx.bash output.nmea");


    return 0;
}