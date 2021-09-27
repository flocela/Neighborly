# About

This project is a city simulation where in each loop, residents buy the home that makes them the happiest.

There are some restrictions on which homes are available to each resident. The city simulation is extensible 
and the coder can create new restrictions. For now, the user can opt into restrictions of distance from previous home to new home. The residents may be forced to buy a home if it makes them happy enough instead of waiting to find a better home.

The resident types are also extensible. Currently a residents' happiness is determined by the ratio of like residents to different residents that are direct neighbors. New resident types can be designed whose happiness functions are quadratic, or another type of function. New resident types can have different values for when they are sufficiently happy (happy enough).

The city and its residents are shown for each loop graphically.

## Starting Code is by aminoshbh, Amine B. Hassouna
Original code contains the CMakeLists.txt file and the code to be able to use the SDL_image library so that graphics can be used.
Please find the original code at https://gitlab.com/aminosbh/sdl2-ttf-sample.git

## Dependencies
- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_ttf][] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-ttf-dev
```

**Optional packages:**

- [SDL2_image][] library
- [SDL2_net][] library
- [SDL2_mixer][] library
- [SDL2_gfx][] library

```sh
sudo apt install libsdl2-image-dev libsdl2-net-dev libsdl2-mixer-dev libsdl2-gfx-dev
```

## Build instructions

```sh
# Clone this repo
git clone https://gitlab.com/aminosbh/sdl2-ttf-sample.git
cd sdl2-ttf-sample

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./sdl2-ttf-sample
```

***Note:*** To use SDL2_image, SDL2_net, SDL2_mixer or SDL2_gfx, you should
uncomment some instructions in the CMakeLists.txt file and re-execute the
`make` command.

### Open the project with an IDE under Linux

See [IDE_USAGE.md](IDE_USAGE.md) for details.

## License

Author: Amine B. Hassouna [@aminosbh](https://gitlab.com/aminosbh)

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).



[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
[SDL2_net]: https://www.libsdl.org/projects/SDL_net
[SDL2_mixer]: https://www.libsdl.org/projects/SDL_mixer
[SDL2_gfx]: http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx
