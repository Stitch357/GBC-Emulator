#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"
#include "cartridge.h"

#define debugging false

int main(int argc, char *argv[]) {
    GB gbc;
    CART test_cart;

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

    initialize_cart(&gbc.cartridge);

    if (debugging) {
        print_cart(&gbc.cartridge);

        printf("\n");
        printf("-------------------------------\n");
        printf("Program is working for GB\n");
        printf("-------------------------------\n");
    }

    initialize_cart(&test_cart);

    if (debugging) {
        print_cart(&test_cart);

        printf("\n");
        printf("-------------------------------\n");
        printf("Program is working for CART\n");
        printf("-------------------------------\n");
    }

    load_cartridge(&test_cart, rom_path);

    return 0;
}