#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"
#include "cartridge.h"
#include "cpu.h"

// Used in testing
#define debugging false

int main(int argc, char *argv[]) {
    GB gbc;
    
    cpu_initialize(&gbc);     // Make sure to initialize the CPU stats
    print_cpu_stats(&gbc);

    if (argc < 2) {
        printf("Usage: %s <ROM file path>\n", argv[0]);
        return 1;
    }

    const char *rom_path = argv[1];
    //const char *rom_path = "../../Roms/Pokemon Red.gb";
    //const char *rom_path = "../../Roms/Pokemon Silver.gbc";

    if (debugging) {
        printf("Loading ROM: %s\n", rom_path);
    }

    initialize_cart(&gbc);
    load_cartridge(&gbc, rom_path);

    if (debugging) {
        print_cart(&gbc);

        printf("\n");
        printf("-------------------------------\n");
        printf("Program is working for GB\n");
        printf("-------------------------------\n");
    }

    return 0;
}