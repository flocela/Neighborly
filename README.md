# Neighborly


https://github.com/flocela/Neighborly/assets/4298622/26b4f36d-855a-46f3-aafd-f18c75749d8d


## Introduction

Neighborly simulates two groups of residents living in a city. In each iteration residents are moved into houses based on their prospective happiness. Each resident belongs to a group, and their happiness depends on the ratio of like to disparate neighbors. At the end of each iteration the residents' happiness values are calculated and the city's residents and the group's happiness values are printed. Residents are drawn as squares where their color is determined by their group and happiness value.

At the beginning of each iteration a Simulator decides which residents are chosen to move, the houses that are available to them, and whether they do ultimately move. A Simulator may take into account a resident’s happiness with a house, how far the resident can move, and other Resident attributes.

Each group's residents have the same happiness function. A resident’s happiness depends on their number of disparate neighbors and their total number of neighbors.

Say there exists a Group1 resident whose happiness is found using the following function, where happiness decreases as the number of disparate neighbors increases.
<pre><code>
Happiness = 100 - ( 100 * (number of disparate neighbors / total number of neighbors) )
</code></pre>
Also say the Group1 resident is at at coordinate (1, 1) in the city below. It has 3 disparate neighbors out of 8 total neighbors, then its happiness will be 62.5.
<pre><code>
   00 01 02
00 G2 G1 G2
01 G2 G1 G1
02 G1 G1 G1
</code></pre>
If a Group1 resident is surrounded by Group 2 residents, then its happiness will be zero.

## Code

[README.pdf](README.pdf) gives a full explanation of the code including inputs (Section 4), outputs (Section 5), and UML diagrams (Section 6).

## Copyrights

Neighborly was completed in September 2023 by Aurea F. Maldonado.

The idea of Neighborly is based on the simulation “Parable of the Polygons” at https://ncase.me/polygons/.

The code which allows rendering of text and blocks on a window is by Amine Ben Hassouna and can be found at https://github.com/aminosbh/sdl2-ttf-sample/blob/master/src/main.c. I cloned Hassouna’s project, changed the main.c file to main.cpp, and then in the CMakeLists.txt file I changed file(GLOB SOURCES “src/*.c”) to file(GLOB Sources “src/*.cpp”) on line 39.

I am using the same copyright as Amine Ben Hassouna, see comments in main.cpp, lines 3 -43.

Music for README video is from Kevin MacLeod. "Wallpaper" Kevin MacLeod (incompetech.com) Licensed under Creative Commons: By Attribution 4.0 License http://creativecommons.org/licenses/by/4.0/

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).

Also I received a lot of help from the mentors at Udacity. So, thank you Udacity mentors.

## Build Instructions

### Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_ttf][] library

### Clone This Repo

In a folder, clone the repository. This will create the Neighborly folder.

```sh
git clone https://github.com/flocela/Neighborly.git
```

### Make the code

On Debian/Ubuntu based distributions, use the following command in the Neighborly folder to install the SDL2_ttf library.

```sh
sudo apt-get install libsdl2-ttf-dev
```

Create a build folder inside of the Neighborly folder. In the Neighborly/build folder type
```sh
cmake .. && make
```

## Run The Project

In the build folder type

```sh
.sdl2-ttf-sample
```

Alternatively you could use an input file when running the program
```sh
./sdl2-ttf-sample txt-inputs/txt-ex0simA.txt
```
To start with, I suggest just typing './sdl2-ttf-sample' without the text file.

If you do not include the text file, then you will be asked if you want to use a pre-made-example simulation or go through a series of questions to create the simulation. I suggest, on first try, use one of the pre-made-example simulations (type ‘1’).

## Run The Tests

Tests (written in Catch2) can be found in the [tests](tests) directory. In the build folder type
```sh
./RunTests
```

[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
