# 2D Aim Training App - "Sasta Aimlabs"

Welcome to **Sasta Aimlabs**, a simple 2D version of the popular aim training app, "Aimlabs," built using SDL2. This app is designed to help improve your aim with different training modes.

## Features

- **Gridshot**: Shoot targets appearing on a grid.
- **Microflicking**: Practice flicking to small targets.
- **Tracking**: Track moving targets.
- **Sensitivity**: Sensitivity can be increased/decreased using the up/down arrows respectively.

## Requirements

- SDL2
- SDL2_ttf

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Emosans/Sasta-Aimlabs.git
   cd Sasta-Aimlabs
   cd src
   ```
2. Now compile all the files present in the src folder and include the different binary files present in the 'bin' folder.
   ```bash
   g++ -I../bin/include -L../bin/x64 *.cpp -o ../build/main -lsdl2 -lsdl2_ttf
   ```
3. Now to go to the 'build' folder and run 'main.exe'.
   ```bash
   cd ..
   cd build
   main.exe
   ```
## Documentation

- **Installation** : Follow the steps in the link to install and configure SDL <a href="https://wiki.libsdl.org/SDL2/Installation">click here</a>
- **Functions** : API's in SDL are categorized and explained <a href="https://wiki.libsdl.org/SDL2/CategoryAPI">here</a>

## Demo
[![Watch the video](https://img.youtube.com/vi/ypSTLVRqFuQ/hqdefault.jpg)](https://youtu.be/ypSTLVRqFuQ)

<p><h4>Enjoy Aim Training</h4></p>
