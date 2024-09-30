#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "structs.h"
#include "enum.h"

// Testing functions
void initialize_cart(GB *gb);
void print_cart(GB *gb);

void load_cartridge(GB *gb, const char *rom_path);
static void load_ram(GB *gb);
static void load_title(GB *gb);

static void load_cgb_flag(GB *gb);

// Functions used with debugging
static void print_title(GB *gb);
static void print_cgb_flag(GB *gb);

static void print_rom_code(GB *gb);
static void print_rom_banks(GB *gb);

static void print_ram_code(GB *gb);
static void print_ram_size(GB *gb);
static void print_ram_banks(GB *gb);

#endif