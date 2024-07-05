#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

/*
    Emulator Parts
    |Cartridge|
    |CPU|
    |Address Bus|
    |PPU|
    |Timer|
*/

/*
    Necessary Emulator Components

    8-bit Central Processing Unit
    32Kb Work Random Access Memory (RAM)
    16Kb VRAM
    Liquid Crystal Display Screen
    Read Only Memory (ROM) AKA the external video game cartridge
    Joypad Input
    Audio Speaker
    Serial Transfer Port (link cable)
*/

/*
    Necessary Memory Components

    Work RAM
    Video RAM
    Cartridge ROM
    External RAM
*/

