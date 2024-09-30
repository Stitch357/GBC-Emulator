#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "cartridge.h"
#include "structs.h"

#define debugging true

#define rom_bank_size (16 * 1024)               // 16 KiB of ROM per bank

#define cart_type_addr 0x147                    // Address that houses MBC type

void initialize_mbc(GB *gb) {
    gb->mbc.mbc_code = 0;
    gb->mbc.mbc_type = 0;

    gb->mbc.num_of_rom_banks = 0;
    gb->mbc.curr_rom_bank = 1;

    gb->mbc.num_of_ram_banks = 0;
    gb->mbc.curr_ram_bank = 0;
}

void load_mbc_flag(GB *gb) {
    // cart_type_addr
    gb->mbc.mbc_code = gb->cartridge.cart_rom[cart_type_addr];

    switch (gb->mbc.mbc_code) {
        case 0x00:                          // NO MBC
            gb->mbc.mbc_type = MBC_NONE;
        break;

        case 0x01:                          // MBC1
        case 0x02:                          // MBC1 + RAM
        case 0x03:                          // MBC1 + RAM + BATTERY
            gb->mbc.mbc_type = MBC1;
        break;

        // MBC 2
        case 0x05:                          // MBC2
        case 0x06:                          // MBC2 + BATTERY
            gb->mbc.mbc_type = MBC2;

            gb->mbc.num_of_ram_banks = 1;
            gb->mbc.ram_size = 512 * 8;
        break;

        // MBC 3
        case 0x0F:                          // MBC3 + TIMER + BATTERY
        case 0x10:                          // MBC3 + TIMER + RAM + BATTERY
        case 0x11:                          // MBC3
        case 0x12:                          // MBC3 + RAM
        case 0x13:                          // MBC3 + RAM + BATTERY
            gb->mbc.mbc_type = MBC3;
        break;

        // MBC 5
        case 0x19:                          // MBC5
        case 0x1A:                          // MBC5 + RAM
        case 0x1B:                          // MBC5 + RAM + BATTERY
            gb->mbc.mbc_type = MBC5;
        break;

        default:
            printf("Unrecognized MBC type");
    }
}

void print_mbc_type(GB *gb) {
    switch (gb->mbc.mbc_type) {
        case 0:     // No MBC
            printf("\n\nDoesn't have an MBC");
        break;

        case 1:     // MBC 1
            printf("\n\nMBC type is ---> MBC 1");
        break;

        case 2:     // MBC 2
            printf("\n\nMBC type is ---> MBC 2");
        break;

        case 3:     // MBC 3
            printf("\n\nMBC type is ---> MBC 3");
        break;

        case 4:     // MBC 5
            printf("\n\nMBC type is ---> MBC 5");
        break;

        default:
            printf("Unrecognized MBC type");
    }
}

// NOTE: 9/30/24 - I'm only working on MBC3 at the moment
uint8_t read_rom_with_mbc_bank(GB* gb, uint16_t address) {
    unsigned rom_offset = address;

    switch (gb->mbc.mbc_type) {
        case 0:     // No MBC
            if (debugging) {
                printf("\n\nDoesn't have an MBC");
            }
        break;

        case 1:     // MBC 1
            if (debugging) {
                printf("\n\nMBC type is ---> MBC 1");
            }
        break;

        case 2:     // MBC 2
            if (debugging) {
                printf("\n\nMBC type is ---> MBC 2");
            }
        break;

        case 3:     // MBC 3
            if (debugging) {
                printf("\n\nMBC type is ---> MBC 3");
            }

            if (address >= rom_bank_size) {
                rom_offset += (gb->mbc.curr_rom_bank - 1) * rom_bank_size;
            }
        break;

        case 4:     // MBC 5
            if (debugging) {
                printf("\n\nMBC type is ---> MBC 5");
            }
        break;

        default:
            if (debugging) {
                printf("Unrecognized MBC type");
            }
    }

    return gb->cartridge.cart_rom[rom_offset];
}