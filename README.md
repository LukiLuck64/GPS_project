# GPS_project

## Sommaire
 - [Utilisation appareil gps](#utilisation-appareil-gps)
 - [Simulation des points gps](#simulation-des-points-gps)
 - [Analyse des trames](#analyse-des-trames)


## Introduction
Les trames GPS, ou messages NMEA, sont des données formatées transmises par les récepteurs GPS pour fournir des informations sur la position, la vitesse et d'autres paramètres associés à un appareil de localisation. Ces trames suivent un format standardisé, ce qui les rend compatibles avec différents récepteurs GPS et systèmes de navigation. Elles sont utilisées dans une variété d'applications telles que la navigation automobile, la cartographie et la géolocalisation des biens.

Trois types de trames GPS :

 - GPGGA (Global Positioning System Fix Data) :
        Fournit des données de position précises telles que la latitude, la longitude, l'altitude et le nombre de satellites utilisés.
 - GPRMC (Recommended Minimum Specific GPS/Transit Data) :
        Donne des informations de navigation essentielles comme la latitude, la longitude, la vitesse et le cap.
 - GPGLL (Geographic Position – Latitude/Longitude) :
        Transmet les données de position sous forme de latitude et de longitude, souvent utilisées dans les applications de navigation et de suivi.

Ces trames sont largement utilisées pour obtenir des informations de localisation précises à partir des récepteurs GPS. Chacune d'elles offre des détails spécifiques sur la position et est utilisée dans diverses applications de navigation et de suivi.

## Architecture logiciel
- ![](GPS/src/data/architecture_logiciel.png)


# Architecture base de donnée
- ![](GPS/src/data/architecture_base_de_donnees.png)


## Utilisation appareil gps

```bash
./setup.bash
```

## Simulation des points gps
Avoir des trames valide lors de leurs acquisition. 
 - setup nmeasimulator : https://github.com/panaaj/nmeasimulator/releases
 - https://help.ubuntu.com/kubuntu/desktopguide/fr/manual-install.html

Remarque : regarder le fichier output.nmea comme exemple
```bash
nmeasimulator
```

Faire cette commande pour lancer le programme et visualiser le chemin qu'a fait la personne.

Ensuite cliquer sur le logo en haut à droite ( follow track ) pour visualiser la trame sur la mini map. 
Avec le programme il est même possible de le faire en temps réel.

## Analyse des trames

```bash
make
./script_trajectoire arg[1] arg[2] arg[3]
```

### Le programme prend des arguments en ligne de commande pour effectuer différentes actions :
---
- `0` : Affiche les lieux enregistrés
---
- `1` : Calcul de la distance parcourue et la durée de cet itinéraire
  - `arg[2]` : Fichier d'itinéraire (itineraire.txt)
---
- `2` : Calcul la distance entre deux lieux
  - `arg[2]` : Premier lieu
  - `arg[3]` : Deuxième lieu
---
- `3` : Analyse l'itinéraire en proposant pour chaque point la distance qui le sépare du lieu
  - `arg[2]` : Fichier d'itinéraire (itineraire1.txt)
  - `arg[3]` : Lieu à comparer
---
- `4` : Les points de rencontre (100m) entre deux itinéraires
  - `arg[2]` : Premier itinéraire
  - `arg[3]` : Deuxième itinéraire
---

### The program takes command-line arguments to perform different actions:

---

- `0`: Displays registered locations
-  Chateau
-  ![](GPS/src/data/chateau.png)
-  Abbaye aux Hommes
-  ![](GPS/src/data/abbaye_aux_hommes.png)

---

- `1`: Calculates the distance traveled and the duration of this route
  - `arg[2]`: Route file (itineraire.txt)

---

- `2`: Calculates the distance between two locations
  - `arg[2]`: First location
  - `arg[3]`: Second location

---

- `3`: Analyzes the route by proposing for each point the distance separating it from the location
  - `arg[2]`: Route file (itineraire1.txt)
  - `arg[3]`: Location to compare

---

- `4`: Meeting points (100m) between two routes
  - `arg[2]`: First route
  - 
  ![](GPS/src/data/trame1.png)
  - `arg[3]`: Second route
  - 
  ![](GPS/src/data/trame2.png)

---


