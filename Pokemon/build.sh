#!/bin/bash

sudo apt install libsdl2-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev

mkdir build
cd build
cmake ..
make
