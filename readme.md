# PMD Engine Coded in C #
This is simply a PMD clone engine coded in C. Working on a Linux port.

## Dependencies ##
This project requires CMake to be built. Also, requires the following libraries to be installed:
* OpenAL
* pthreads / pthreads-w32
* GLEW
* GLFW
* LibOGG
* LibVorbis
* LibPNG
* SDL2
* Zlib
* SOIL (Simple OpenGL Image Library)

## Compiling ##
Make a `build` directory, run `cmake ..` and then `make` on it. If no errors, the executable should be in that folder.

## Coding style
* Use spaces
* Indent amount is 4 spaces
* Curly brackets go underneath the function
* Use typedef for structs and enums
* Camel notation for structs and enums
* Function names are camel notation (not always though)
* Function parameters are lowercase with underscores
* Macros are in Caps with underscores unless it's a function
