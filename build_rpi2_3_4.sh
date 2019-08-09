#!/bin/bash

# Remove files specific to the RPi 1 build if they exist
if [ -d "./bin/lib" ]; then
rm -r ./bin/lib
fi

if [ -f "./bin/run.sh" ]; then
rm ./bin/run.sh
fi

# Build NXEngine
make clean
make