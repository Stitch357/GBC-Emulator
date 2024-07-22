#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "structs.h"

// Testing functions
void initialize_cart(CART *cart);
void print_cart(CART *cart);

void load_cartridge(CART *cart, const char *rom_path);
static void load_ram(CART *cart);
static void load_title(CART *cart);
static void load_cgb_flag(CART *cart);

// Functions used with debugging
static void print_title(CART *cart);
static void print_cgb_flag(CART *cart);

static void print_rom_code(CART *cart);
static void print_rom_banks(CART *cart);

static void print_ram_code(CART *cart);
static void print_ram_size(CART *cart);
static void print_ram_banks(CART *cart);

#endif