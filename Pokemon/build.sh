#!/bin/bash

sudo apt install libsdl2-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libsdl2-image-dev

mkdir build
cd build
cmake ..
make
