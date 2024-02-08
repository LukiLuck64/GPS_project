# GPS_project

## Utilisation de l'appareil gps

```bash
./setup.bash
```

## Simulation des points gps
Avoir des trames valide lors de l'acquisition des trames. 
    - setup nmeasimulator : https://github.com/panaaj/nmeasimulator/releases
    - https://help.ubuntu.com/kubuntu/desktopguide/fr/manual-install.html

Remarque : regarder le fichier output.nmea comme exemple
```bash
nmeasimulator
```

Faire cette commande pour lancer le programme et visualiser le chemin qu'a fait la personne

Ensuite cliquer sur le logo en haut à droite ( follow track ) pour visualiser la trame sur la mini map. 
Avec le programme il est même possible de le faire en temps réel.

## Analyse des trames

```bash
make
./script_trajectoire arg[1] arg[2] arg[3]
```

arg[1] = numéros ci-dessous

    - 0 : Affiche les lieux enregistrés

    - 1 : Calcul de la distance parcourue et la durée de cet iténéraire 
        - arg [2] = itineraire.txt

    - 2 : Calcul la ditance entre les 2 lieux 
        - arg[2] = 1er lieu 
        - arg[3] = 2ième lieu 

    - 3 : Analyse l'itinéraire en proposant pour chaque point la distance qui le sépare du lieu
        - arg[2] = itineraire1.txt

    - 4 : Les point de rencontre ( 50m ) entre 2 itinéraires 
        - arg[2] = itineraire1.txt 
        - arg[3] = itineraire2.txt 

[NOTE!]Ceci est une note 2023-2024
