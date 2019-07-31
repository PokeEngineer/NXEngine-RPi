#!/bin/bash

# Build SDL with DispmanX backend
cd ./SDL
./configure --disable-video-opengl --disable-video-directfb --disable-cdrom --disable-oss --disable-alsatest --disable-pulseaudio --disable-pulseaudio-shared --disable-arts --disable-nas --disable-esd --disable-nas-shared --disable-diskaudio --disable-dummyaudio --disable-mintaudio --disable-video-x11 --enable-video-dispmanx --disable-input-tslib
make

# Make library directory if it doesn't exist
if [ ! -d "../bin/lib" ]; then
mkdir ../lib
fi

# Copy the library to the correct directory if the file is updated or it doesn't exist
cp -u ./build/.libs/libSDL-1.2.so.0 ../bin/lib

# Build NXEngine
cd ../
make clean
make RPI1=1

# Copy the run script for the RPi 1 if the file is updated or it doesn't exist
cp -u ./runscripts/run_rpi1.sh ./bin/run.sh
