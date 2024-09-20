#ifndef MBC_H
#define MBC_H

#include "structs.h"
#include "enum.h"

uint8_t read_rom_with_mbc_bank(GB* gb, uint16_t address);

#endif