#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LA_LO_OLD 0 //latitude_longitude_old
#define LA_LO_NEW 1 //latitude_longitude_new
#define RAYON_TERRE 6371.0 // Rayon moyen de la Terre en kilomètres

// Convertir les degrés en radians
double deg2rad(double deg) {
   return deg * (M_PI / 180.0);
}

// Calculer la distance entre deux points en utilisant la formule de Vincenty
double distance_vincenty(double lat1, double lon1, double lat2, double lon2) {
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    double a = RAYON_TERRE;
    double b = RAYON_TERRE;

    double U1 = atan((1.0 - 1.0 / 298.257223563) * tan(lat1));
    double U2 = atan((1.0 - 1.0 / 298.257223563) * tan(lat2));
    double cosU1 = cos(U1);
    double cosU2 = cos(U2);
    double sinU1 = sin(U1);
    double sinU2 = sin(U2);
    double cosU1cosU2 = cosU1 * cosU2;
    double cosU1sinU2 = cosU1 * sinU2;
    double sinU1sinU2 = sinU1 * sinU2;
    double sinU1cosU2 = sinU1 * cosU2;

    double lambda = lon2 - lon1;
    double lambdaP = M_PI + atan2(sin(lambda), cosU1cosU2 - sinU1sinU2 * cos(lambda));

    double sinSigma;
    double cosSigma;
    double sigma;
    double sinAlpha;
    double cos2Alpha;
    double cos2SigmaM;
    double deltaSigma;

    do {
        double sinLambda = sin(lambda);
        double cosLambda = cos(lambda);

        sinSigma = sqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) +
                        (cosU1sinU2 - sinU1cosU2 * cosLambda) *
                        (cosU1sinU2 - sinU1cosU2 * cosLambda));

        if (sinSigma == 0.0) {
            return 0.0;  // Coïncidence des points
        }

        cosSigma = sinU1sinU2 + cosU1cosU2 * cosLambda;
        sigma = atan2(sinSigma, cosSigma);

        sinAlpha = cosU1cosU2 * sinLambda / sinSigma;
        cos2Alpha = 1.0 - sinAlpha * sinAlpha;
        cos2SigmaM = cosSigma - 2.0 * sinU1sinU2 / cos2Alpha;
        deltaSigma = sinSigma * sinAlpha * (cosSigma + cos2SigmaM);

        lambda = atan2(sinLambda * sinU1cosU2, cosU1sinU2 - sinU1cosU2 * cosLambda);
    } while (fabs(deltaSigma) > 1e-12);

    double u2 = cos2Alpha * (a * a - b * b) / (b * b);
    double A = 1.0 + u2 / 16384.0 * (4096.0 + u2 * (-768 + u2 * (320 - 175 * u2)));
    double B = u2 / 1024.0 * (256.0 + u2 * (-128.0 + u2 * (74.0 - 47.0 * u2)));
    double deltaSigma1 =
        B *
        sinSigma *
        (cos2SigmaM + B / 4.0 * (cosSigma * (-1.0 + 2.0 * cos2SigmaM * cos2SigmaM) -
                                 B / 6.0 * cos2SigmaM * (-3.0 + 4.0 * sinSigma * sinSigma) *
                                 (-3.0 + 4.0 * cos2SigmaM * cos2SigmaM)));

    double distance = b * A * (sigma - deltaSigma1);

    return distance;
}

// Calculer la distance entre deux points en utilisant la formule de Haversine
double distance_haversine(double lat1, double lon1, double lat2, double lon2) {
   // Convertir les degrés en radians
   lat1 = deg2rad(lat1);
   lon1 = deg2rad(lon1);
   lat2 = deg2rad(lat2);
   lon2 = deg2rad(lon2);

   // Calcul des différences de coordonnées
   double dlat = lat2 - lat1;
   double dlon = lon2 - lon1;

   // Formule de Haversine
   double a = sin(dlat / 2.0) * sin(dlat / 2.0) + cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
   double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

   // Distance en kilomètres
   double distance = RAYON_TERRE * c;

   return distance;
}



void init_heure(double heure, double* temps){

   temps[0]=((int)heure/10000);
   temps[1]=(int)(((heure/10000)-temps[0])*100);
   temps[2]=((((heure/10000)-temps[0])*100)-temps[1])*100;

}

double init_long_or_lat(double longitude){

   double coord[3];

   coord[0]=((int)longitude/100);
   coord[1]=(int)(((longitude/100)-coord[0])*100);
   coord[2]=((((longitude/100)-coord[0])*100)-coord[1])*1000;

   return (coord[0]+(coord[1]/60)+(coord[2]/3600)); //en degres

}

void decode_GGA(const char* s, FILE *fichierDonneesGPS){
   
   double latitude[2];
   double longitude[2];
   double heure;
   char* NS = malloc(2 * sizeof *NS);
   double temps[3];
   
   if((latitude == NULL)||(longitude == NULL)||(NS == NULL)||(temps == NULL)){
      exit(1);
   }

   heure = atof(strtok(NULL,s));
   latitude[0] = atof(strtok(NULL,s));
   NS = strtok(NULL,s);
   longitude[0] = atof(strtok(NULL,s));

   //printf("heure : %s, latitude : %s, NS : %s, longitude : %s",heure, latitude, NS, longitude);
   
   fprintf(fichierDonneesGPS, "heure : %0.3lf, latitude : %0.3lf, NS : %s, longitude : %0.3lf\n",heure, latitude[LA_LO_OLD], NS, longitude[LA_LO_OLD]);
   
   // initialisation de l'heure
   init_heure(heure, temps); // initialisation de l'heure

   // initialisation longitude et latitude
   longitude[1] = init_long_or_lat(longitude[0]);
   latitude[1] = init_long_or_lat(latitude[0]);

   fprintf(fichierDonneesGPS, "heure : %0.0lf:%0.0lf:%0.0lf, latitude : %0.3lf, NS : %s, longitude : %0.3lf\n\n",temps[0],temps[1],temps[2], latitude[LA_LO_NEW], NS, longitude[LA_LO_NEW]);
   //free(NS);
}


void decode_GPRMC(const char* s, FILE *fichierDonneesGPS){

   double heure;
   char* NS = malloc(2 * sizeof(char));
   char* WE = malloc(2 * sizeof(char));
   double temps[3];
   double latitude[2];
   double longitude[2];

   if((latitude == NULL)||(longitude == NULL)||(NS == NULL)||(temps == NULL)||(WE == NULL)){
      exit(1);
   }

   
   latitude[0] = atof(strtok(NULL,s));
   NS = strtok(NULL,s);
   longitude[0] = atof(strtok(NULL,s));

   
   WE = strtok(NULL,s);
   heure = atof(strtok(NULL,s));

   fprintf(fichierDonneesGPS, "latitude : %0.3lf, NS : %s, longitude : %0.3lf, WE : %s,  heure : %0.3lf\n", latitude[LA_LO_OLD], NS, longitude[LA_LO_OLD], WE, heure);
   init_heure(heure, temps); // initialisation de l'heure

   fprintf(fichierDonneesGPS, "heure : %0.3lf, minute : %0.3lf, seconde : %0.3lf\n", temps[0],temps[1],temps[2]);

   // initialisation longitude et latitude
   longitude[1] = init_long_or_lat(longitude[0]);
   latitude[1] = init_long_or_lat(latitude[0]);

   fprintf(fichierDonneesGPS, "latitude : %0.3lf, NS : %s, longitude : %0.3lf, WE : %s, heure : %0.3lf\n\n", latitude[LA_LO_NEW], NS, longitude[LA_LO_NEW], WE, heure);
   //free(NS);
   //free(WE);
}



void analyse_gps(char* str, FILE* fichierDonneesGPS, int nb_trame)
{
   //char str[80] = "$GPGGA,123519,4807.038,N,01131.324,E,1,08,0.9,545.4,M,46.9,M, , *42";
   const char s[2] = ","; 
   char *token;
   char *str_copy;
   str_copy = malloc(strlen(str)*sizeof(char));

   strcpy(str_copy, str);
   token = strtok(str, s); 		/* get the first token */

   if((token == NULL)||(str_copy == NULL)){
      
      exit(1);
   }


   if(strcmp(token,"$GPGGA")==0){
      fprintf(fichierDonneesGPS, "trame n°%d : %s\n", nb_trame, str_copy );
      decode_GGA(s,fichierDonneesGPS);
      
   }
   if(strcmp(token,"$GPRMC")==0){
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      if(strcmp(token,"A")==0){
         fprintf(fichierDonneesGPS, "trame n°%d : %s\n", nb_trame, str_copy );
         decode_GPRMC(s,fichierDonneesGPS);
      }
   }
   free(str_copy);

}