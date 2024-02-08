
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LA_LO_OLD 0 //latitude_longitude_old
#define LA_LO_NEW 1 //latitude_longitude_new
#define RAYON_TERRE 6371.0 // Rayon moyen de la Terre en kilomètres
#define NB_TRAME 100
#define PI 3.14159265358979323846


double deg2rad(double );
double distance_haversine(double , double , double , double );
void timeDif(double* , double* , double[3] );
void init_heure(double , double* );
double init_long_or_lat(double );
void decode_GGA(const char* , FILE *, double [2][NB_TRAME],double [NB_TRAME][3]);
void decode_GPRMC(const char* , FILE *, double [2][NB_TRAME], double [NB_TRAME][3]);
void analyse_gps(char* , FILE* , int , double [2][NB_TRAME], double [NB_TRAME][3]);
