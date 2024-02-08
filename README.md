# GPS_project

## Sommaire
 - [Utilisation de l'appareil gps](#utilisation-de-lappareil-gps)
 - [Simulation des points gps](#simulation-des-points-gps)
 - [Analyse des trames](#analyse-des-trames)

## Utilisation de l'appareil gps

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

Faire cette commande pour lancer le programme et visual//**--iser le chemin qu'a fait la personne.

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
---
- `4` : Les points de rencontre (50m) entre deux itinéraires
  - `arg[2]` : Premier itinéraire
  - `arg[3]` : Deuxième itinéraire
---

