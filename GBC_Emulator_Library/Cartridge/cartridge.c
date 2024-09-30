#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "cartridge.h"
#include "mbc.h"
#include "structs.h"

// Used in testing
#define debugging false
#define byte_length 16

#define rom_bank_size (16 * 1024)               // 16 KiB of ROM per bank
#define min_rom_size (rom_bank_size * 2)        // 32 KiB minimum size
#define max_rom_size (rom_bank_size * 512)      // 8 MiB maximum size

#define rom_code_addr 0x148                     // Points to the ROM code
#define high_rom_value 72                       // Used to calculate the # of banks with 0x52, 0x53, & 0x54

#define ram_code_addr 0x149                     // Points to the RAM code
#define ram_bank_size (8 * 1024)                // 8 KiB of RAM per bank

#define title_addr 0x134                        // Points to the ROM's title
#define title_length 16                         // The ROM typically sets aside 16 bytes for the title
                                                // Backfills with 0's if indicies are unused

#define cbg_flag_addr 0x143                     // Points to the CGB flag
#define sgb_flag_addr 0x146                     // Points to the SGB flag
#define cart_type_addr 0x147

void initialize_cart(GB *gb) {
    // Initialize the CART structure
    gb->cartridge.cart_rom = NULL;
    gb->cartridge.rom_code = 0;
    gb->cartridge.rom_size = 0;

    gb->cartridge.cart_ram = NULL;
    gb->cartridge.ram_code = 0;
    gb->cartridge.ram_size = 0;
}

void print_cart(GB *gb) {
    // Print the initial values of the CART structure
    printf("\n");
    printf("Initial values:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("cart_rom: %p\n", (void *)gb->cartridge.cart_rom);
    printf("rom_code: %u\n", gb->cartridge.rom_code);
    printf("rom_size: %u\n", gb->cartridge.rom_size);
    printf("num_of_rom_banks: %u\n\n", gb->cartridge.num_of_rom_banks);

    printf("cart_ram: %p\n", (void *)gb->cartridge.cart_ram);
    printf("ram_code: %u\n", gb->cartridge.ram_code);
    printf("ram_size: %u\n", gb->cartridge.ram_size);
    printf("num_of_ram_banks: %u", gb->cartridge.num_of_ram_banks);

    print_mbc_type(gb);
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

static void load_title(GB *gb) {
    char character;
    int i;

    for (i = 0; i < title_length; i++) {
        character = gb->cartridge.cart_rom[title_addr + i];

        // The titles are filled with 0's whenever they end
        if (character == 0) {
            break;
        }

        gb->cartridge.title[i] = character;
    }

    gb->cartridge.title[i] = '\0';
}

static void print_title(GB *gb) {
    printf("%s", gb->cartridge.title);
}

static void load_cgb_flag(GB *gb) {
    gb->cartridge.cgb = false;

    if ((gb->cartridge.cart_rom[cbg_flag_addr] & 0x80) ||
        (gb->cartridge.cart_rom[cbg_flag_addr] & 0xC0)) {
        gb->cartridge.cgb = true;

        printf("--- CGB Triggered ---\n");
        return;
    }
}

static void print_cgb_flag(GB *gb) {
    if (gb->cartridge.cgb == 0) {
        printf("False");
    }
    else {
        printf("True");
    }
}

static void load_rom_banks(GB *gb) {
    uint8_t rom_value = gb->cartridge.cart_rom[rom_code_addr];
    gb->cartridge.rom_code = rom_value;

    switch (rom_value) {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
            gb->cartridge.num_of_rom_banks = (1 << (rom_value + 1));
        break;

        case 0x52:
        case 0x53:
        case 0x54:
            gb->cartridge.num_of_rom_banks = high_rom_value + (8 * ((rom_value - 0x52) * (rom_value - 0x52 + 0x1) / 2));
        break;

        default:
            printf("Unknown # of ROM banks");
    }

    if (debugging) {
        printf("\n\nSuccessfully set the # of ROM banks");
    }
}

static void print_rom_code(GB *gb) {
    printf("%d", gb->cartridge.rom_code);
}

static void print_rom_banks(GB *gb) {
    printf("%d", gb->cartridge.num_of_rom_banks);
}

static void load_ram(GB *gb) {
    int exponent;

    uint8_t ram_value = gb->cartridge.cart_rom[ram_code_addr];
    gb->cartridge.ram_code = ram_value;

    switch (ram_value) {
        case 0x00:
        case 0x01:
            gb->cartridge.cart_ram = 0;
            gb->cartridge.num_of_ram_banks = 0;
        break;

        case 0x02:
        case 0x03:
        case 0x04:
            exponent = ram_value - 0x02;
            gb->cartridge.ram_size = 8 << (2 * exponent);
            gb->cartridge.num_of_ram_banks = gb->cartridge.ram_size / 8;
        break;

        case 0x05:
            gb->cartridge.ram_size = 64;
            gb->cartridge.num_of_ram_banks = gb->cartridge.ram_size / 8;
        break;

        default:
            printf("\nUnknown size of RAM");
            printf("\nUnknown # of RAM banks");
    }
}

static void print_ram_code(GB *gb) {
    printf("\nRAM code is ---> %d", gb->cartridge.ram_code);
}

static void print_ram_size(GB *gb) {
    printf("\nSize of RAM is ---> %d", gb->cartridge.ram_size);
}

static void print_ram_banks(GB *gb) {
    printf("\n# of RAM banks is ---> %d", gb->cartridge.num_of_ram_banks);
}

void load_cartridge(GB *gb, const char *rom_path) {
    int test_size = 64;
    FILE *file = fopen(rom_path, "rb");

    // Error handling for failed file opening
    if (file == NULL) {
        perror("Cannot open ROM");
        return;
    }

    // *-*-* Set the cartridge ROM

    // Get the length of the file
    fseek(file, 0, SEEK_END);

    int length_of_file = ftell(file);

    if (debugging) {
        printf("Length of ROM: %d in bytes", (length_of_file / 8));
    }

    // Makes sure that the rom is bigger than 32 KiB
    if (length_of_file < min_rom_size) {
        perror("ROM file smaller than 32 KiB");
        return;
    }

    // Makes sure that the rom is smaller than 1.5 MiB
    if (length_of_file > max_rom_size) {
        perror("ROM file larger than 1.5 MiB");
        return;
    }

    // Set the file back to the beginning
    fseek(file, 0, SEEK_SET);

    // Sets the correct size of the cart's rom based on the
    // length of the file found above.
    gb->cartridge.rom_size = length_of_file;
    gb->cartridge.cart_rom = calloc(1, gb->cartridge.rom_size);

    if (debugging) {
        printf("\nAllocated memory for ROM");
    }

    size_t bytes = fread(gb->cartridge.cart_rom, 1, gb->cartridge.rom_size, file);

    if (debugging) {
        printf("\n\nFirst instruction at $101 - $103");
        printf("\n0x%02X ", gb->cartridge.cart_rom[0x00000101]);
        printf("0x%02X ", gb->cartridge.cart_rom[0x00000102]);
        printf("0x%02X ", gb->cartridge.cart_rom[0x00000103]);

        printf("\n\nRemember that this is LITTLE ENDIAN format!");

        printf("\n\nThe first %d bytes of the ROM file are: ", test_size);
        for (int i = 0; i < test_size; i++) {
            if (i % byte_length == 0) {
                printf("\n0x%02X ", gb->cartridge.cart_rom[i + 0x100]);
            }
            else {
                printf("0x%02X ", gb->cartridge.cart_rom[i + 0x100]);
            }
        }
    }

    // *-*-* Set the cartridge # of ROM banks

    load_rom_banks(gb);

    if (debugging) {
        printf("\n# of ROM banks set as --- > ");
        print_rom_banks(gb);
        printf("\n");
    }

    // Make sure that the # of ROM banks fits the ROM size
    if (gb->cartridge.rom_size < gb->cartridge.num_of_rom_banks * rom_bank_size) {
        printf("ROM file cannot hold the %d ROM banks", gb->cartridge.num_of_rom_banks);
        return;
    }

    // *-*-* Set the cartridge RAM
    load_ram(gb);

    if (debugging) {
        print_ram_code(gb);
        print_ram_size(gb);
        print_ram_banks(gb);
    }

    load_mbc_flag(gb);

    if (debugging) {
        print_mbc_type(gb);
    }

    // You need to make sure to allocate this with the total # of bytes
    // I.e. # of banks * 8 KiB (8 * 1024 bits)
    gb->cartridge.cart_ram = calloc(1, gb->cartridge.num_of_ram_banks * ram_bank_size);

    if (debugging) {
        printf("\nAllocated memory size of RAM ---> %d in bytes", (gb->cartridge.num_of_ram_banks * ram_bank_size));
    }

    // *-*-* Set the cartridge title
    
    load_title(gb);

    if (debugging) {
        printf("\n\nLoading title --- > ");
        printf("%s", gb->cartridge.title);
        //print_title(gb);
        printf("\n");
    }

    // *-*-* Set the cartridge CGB flag
    
    load_cgb_flag(gb);

    if (debugging) {
        printf("\nCGB flag set as --- > ");
        print_cgb_flag(gb);
        printf("\n");
    }

    // Success
     fclose(file);
}