# Fil de fer
Create a wireframe projection from a heightmap

![Screenshot](./screenshot-42.png)

## Description
A C program that parses height values from a text file and renders the plane as a wireframe, connecting each point to adjacent ones. Each point can include a RGBA color value in hexadecimal. This will be used to color the point, lines connecting the points will be drawn with a gradient calculated from their respective color values. 

Runs on Linux and macOS.

## Installation
Clone this repository and then run: 

    make

The makefile will clone MLX42 from [here](https://github.com/codam-coding-college/MLX42) and build the executable. 

## Usage

Run the program with a map file:

    ./fdf ./test_maps/42.fdf

Test maps are included in the `test_maps` folder. Maps must have a `.fdf` ending. 


