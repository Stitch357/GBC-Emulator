#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"
#include "cartridge.h"
#include "cpu.h"
#include "mbc.h"
#include "misc.h"

// Used in testing
#define debugging true

int main(int argc, char *argv[]) {
    GB gbc;                                             // Initialize the Gameboy

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

    initialize_cpu(&gbc);                               // Make sure to initialize the CPU stats

    initialize_mbc(&gbc);                               // Initialize the MBC before cart

    initialize_cart(&gbc);                              // Initialize the cartridge
    load_cartridge(&gbc, rom_path);                     // Load the cartridge ROM to memory

    if (debugging) {
        print_cart(&gbc);

        printf("\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Cart initialization is working.....\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    }

    int ch;
    bool running = true;

    while (running) {
        cycle_cpu(&gbc);

        print_cpu_stats(&gbc);

        printf("Press Enter to continue CPU cycling.....\n");
        printf("Press anykey to quit.....\n\n");
        ch = getch();
        //printf("\nYou pressed: %c (ASCII: %d)\n", ch, ch);

        if (ch != 10) {
            running = false;
        }
    }

    return 0;
}