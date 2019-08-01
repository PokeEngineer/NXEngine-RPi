# NXEngine-RPi
A rewrite of the original port of NXEngine for the Raspberry Pi.
---
I noticed the downloads for the original port were broken and the source code was missing, so I took it upon myself to rewrite it.

![Screenshot](https://raw.githubusercontent.com/PokeEngineer/NXEngine-RPi/master/screenshots/nxengine1.png)

## Upgrades from the original port:
* Source code is now available!
* Can now play on both the desktop and in a headless enviroment!

## Dependencies:
You need to install:
* libsdl1.2-dev
* libsdl-ttf2.0-dev
* libegl1-mesa-dev
* libx11-dev

## Building:
* To build for the Raspberry Pi 1/Zero and for the desktop run: `./build_rpi1_x11.sh`

* To build for the Raspberry Pi 1/Zero in headless mode run: `./build_rpi1_headless.sh`

* To build for the Raspberry Pi 2/3/4 in any enviroment run: `./build_rpi2_3_4.sh`

## Running the game:
Copy the files from the bin folder into a separate folder. Then, copy the Cave Story data files, specifically the data folder and Doukutsu.exe, into that same folder.

Finally go into the folder where everything is located and

* On the Raspberry Pi 1/Zero run: `sudo ./run.sh`\
(you have to run it with sudo because of some weird bug with not being able to access the video device as the default user.)

* On the Raspberry Pi 2/3/4 run: `./nx`

## Known issues:
* The original Raspberry Pi runs the game at damn near 60 fps, but falls short a few frames.

* The Raspberry Pi 1 and Zero can only run the game in fullscreen. This is due to the version of SDL included, which has a DispmanX backend. The Raspberry Pi 2, 3, and 4 have the horsepower to run without it.

* On the Raspberry Pi 1/Zero, the run script has to be run with sudo because of some bug with SDL not being able to access the video device as the default user (this was mentioned above).

* If there are other applications open on the Raspberry Pi 1/Zero, the game will lag at random intervals.
