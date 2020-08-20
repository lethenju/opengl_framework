# opengl_framework

A simple 2D openGL Framework written in C++

My ambition was to get familiar with modern C++ development, and to better understand the secrets of openGL development. 

The project in itself is in development, and might never actually get finished. 

## Presentation

The framework resolve around several blocks :

* A `Ogl_Wrapper` object that deals with OpenGL itself, shader loading, GLFW Window management etc
* A `Ogl_world` object that manages the world and all the elements inside. 
* A `Physics` object that manages the physics engine, wrapping world elements with velocity and acceleration parameters.

## Installation

You first need cmake, and C++ compilation tools if you dont have it already :
``` bash 
sudo apt install cmake make g++
```

This repository does not include OpenGL.

You can install OpenGL and the needed libraries with the following command 
``` bash
sudo apt install libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev
```

Then type the following commands to build the project : 

```bash
mkdir build
cd build
cmake ..
cp -r ../include/* /usr/local/include
sudo make install
cp ../src/*.shader .
```

Then launch tests from the build dir : 
```bash
./tests/pong_exe
```

And it should work fine.
