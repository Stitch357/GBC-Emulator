#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "structs.h"

// Testing functions
void initialize_cart(CART *cart);
void print_cart(CART *cart);

void load_rom_from_cart(CART *cart, const char *rom_path);

#endif