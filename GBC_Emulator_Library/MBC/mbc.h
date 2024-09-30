#ifndef MBC_H
#define MBC_H

#include "structs.h"
#include "enum.h"

void initialize_mbc(GB *gb);

void load_mbc_flag(GB *gb);
void print_mbc_type(GB *gb);

uint8_t read_rom_with_mbc_bank(GB* gb, uint16_t address);

#endif