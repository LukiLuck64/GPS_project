#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LA_LO_OLD 0 //latitude_longitude_old
#define LA_LO_NEW 1 //latitude_longitude_new
#define RAYON_TERRE 6371.0 // Rayon moyen de la Terre en kilomètres
#define NB_TRAME 14

// variable globlal
int index_trame = 0;
char decimal = 1;

// Convertir les degrés en radians
double deg2rad(double deg) {
   return deg * (M_PI / 180.0);
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

// Fonction pour calculer la différence entre deux moments en temps
void timeDif(double* temps1, double* temps2, double difference[3]){
      
   // Convertir les heures, minutes et secondes en secondes
   int totalSeconds1 = temps1[0] * 3600 + temps1[1] * 60 + temps1[2];
   int totalSeconds2 = temps2[0] * 3600 + temps2[1] * 60 + temps2[2];

   // Calculer la différence en secondes
   int differenceInSeconds = totalSeconds1 - totalSeconds2;

   // Convertir la différence en heures, minutes et secondes
   difference[0] = differenceInSeconds / 3600;
   differenceInSeconds %= 3600;
   difference[1] = differenceInSeconds / 60;
   difference[2] = differenceInSeconds%60;
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

void decode_GGA(const char* s, FILE *fichierDonneesGPS, double lat_lon[2][NB_TRAME],double temps[NB_TRAME][3]){
   
   double latitude[2];
   double longitude[2];
   double heure;
   char* NS = malloc(2 * sizeof *NS);
   
   if((latitude == NULL)||(longitude == NULL)||(NS == NULL)||(temps == NULL)){
      exit(1);
   }

   heure = atof(strtok(NULL,s));
   latitude[0] = atof(strtok(NULL,s));
   NS = strtok(NULL,s);
   longitude[0] = atof(strtok(NULL,s));

   //printf("heure : %s, latitude : %s, NS : %s, longitude : %s",heure, latitude, NS, longitude);
   
   fprintf(fichierDonneesGPS, "heure : %0.3lf, latitude : %0.6lf, NS : %s, longitude : %0.6lf\n",heure, latitude[LA_LO_OLD], NS, longitude[LA_LO_OLD]);
   
   // initialisation de l'heure
   init_heure(heure, temps[index_trame]); // initialisation de l'heure

   // initialisation longitude et latitude
   if(decimal == 0){
      longitude[1] = init_long_or_lat(longitude[0]);
      latitude[1] = init_long_or_lat(latitude[0]);
   }else{
      longitude[1] = longitude[0];
      latitude[1] = latitude[0];
   }

   fprintf(fichierDonneesGPS, "heure : %0.0lf:%0.0lf:%0.0lf, latitude : %0.6lf, NS : %s, longitude : %0.6lf\n\n",temps[index_trame][0],temps[index_trame][1],temps[index_trame][2], latitude[LA_LO_NEW], NS, longitude[LA_LO_NEW]);
   //free(NS);

   lat_lon[0][index_trame]=latitude[LA_LO_NEW];
   lat_lon[1][index_trame]=longitude[LA_LO_NEW];
   index_trame++;
}


void decode_GPRMC(const char* s, FILE *fichierDonneesGPS, double lat_lon[2][NB_TRAME], double temps[NB_TRAME][3]){

   double heure;
   char* NS = malloc(2 * sizeof(char));
   char* WE = malloc(2 * sizeof(char));
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

   fprintf(fichierDonneesGPS, "latitude : %0.6lf, NS : %s, longitude : %0.6lf, WE : %s,  heure : %0.3lf\n", latitude[LA_LO_OLD], NS, longitude[LA_LO_OLD], WE, heure);
   
   // initialise l'heure
   init_heure(heure, temps[index_trame]); // initialisation de l'heure

   fprintf(fichierDonneesGPS, "heure : %0.3lf, minute : %0.3lf, seconde : %0.3lf\n", temps[index_trame][0],temps[index_trame][1],temps[index_trame][2]);

   // initialisation longitude et latitude
   if(decimal == 0){
      longitude[1] = init_long_or_lat(longitude[0]);
      latitude[1] = init_long_or_lat(latitude[0]);
   }else{
      longitude[1] = longitude[0];
      latitude[1] = latitude[0];
   }
   fprintf(fichierDonneesGPS, "latitude : %0.6lf, NS : %s, longitude : %0.6lf, WE : %s, heure : %0.0lf:%0.0lf:%0.0lf\n\n", latitude[LA_LO_NEW], NS, longitude[LA_LO_NEW], WE, temps[index_trame][0],temps[index_trame][1],temps[index_trame][2]);
   //free(NS);
   //free(WE);

   lat_lon[0][index_trame]=latitude[LA_LO_NEW];
   lat_lon[1][index_trame]=longitude[LA_LO_NEW];

   index_trame++;

}



void analyse_gps(char* str, FILE* fichierDonneesGPS, int nb_trame, double lat_lon[2][NB_TRAME], double temps[NB_TRAME][3])
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
      decode_GGA(s,fichierDonneesGPS, lat_lon, temps);
      
   }

   if(strcmp(token,"$GPRMC")==0){
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      if(strcmp(token,"A")==0){
         fprintf(fichierDonneesGPS, "trame n°%d : %s\n", nb_trame, str_copy );
         decode_GPRMC(s,fichierDonneesGPS, lat_lon, temps);
      }
   }
   if((strcmp(token,"$GPGLL")==0)|(strcmp(token,"GPGLL")==0)){
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      token = strtok(NULL, s);
      if(strcmp(token,"A")==0){
         strcpy(str, str_copy);
         token = strtok(str, s);
         fprintf(fichierDonneesGPS, "trame n°%d : %s\n", nb_trame, str_copy );
         decode_GPRMC(s,fichierDonneesGPS, lat_lon, temps);
      }
   }

   
   free(str_copy);

}