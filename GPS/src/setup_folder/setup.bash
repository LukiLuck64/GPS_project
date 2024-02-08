#!/bin/bash

cd /
cd dev/
sudo chmod 777 ttyUSB0 
stty -F /dev/ttyUSB0 4800
cd /home/luc/Documents/GPS_project/GPS/src
gcc code_file.c -o trame_gps -lm
./trame_gps
