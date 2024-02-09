#!/bin/bash

cd /
cd dev/
sudo chmod 777 ttyUSB0 
stty -F /dev/ttyUSB0 4800
cd /home/luc/Documents/GPS_project/GPS/src
make
./script_trajectoire 2 /dev/ttyUSB0 chateau
