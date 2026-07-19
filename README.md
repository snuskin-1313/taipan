# Snake game

Built in C23 using Raylib 6.0-1

The makefile contains instructions for building on a Linux machine.

You can try compiling in Windows with the following command, although you may have to adjust for your compiler/video settings.

```
gcc -o game main.c engine.c draw.c data.c -lraylib -lgdi32 -lwinmm
```
