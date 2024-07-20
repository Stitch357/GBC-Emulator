#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "cartridge.h"
#include "structs.h"

// Used in testing
#define debugging false
#define byte_length 16

#define rom_bank_size (16 * 1024)               // 16 KiB per bank
#define min_rom_size (rom_bank_size * 2)        // 32 KiB minimum size
#define max_rom_size (rom_bank_size * 96)       // 1.5 MiB maximum size

#define title_addr 0x134
#define gbc_flag_addr 0x143
#define sgb_flag_addr 0x146
#define cart_type_addr 0x147

#define rom_code_addr 0x148
#define ram_code_addr 0x149

void initialize_cart(CART *cart) {
    // Initialize the CART structure
    cart->cart_rom = NULL;
    cart->rom_code = 0;
    cart->rom_size = 0;
    cart->num_of_rom_banks = 0;
    cart->cart_ram = NULL;
    cart->ram_code = 0;
    cart->ram_size = 0;
    cart->num_of_ram_banks = 0;
}

void print_cart(CART *cart) {
    // Print the initial values of the CART structure
    printf("\n");
    printf("Initial values:\n");
    printf("----------------------------------------------------\n");
    printf("cart_rom: %p\n", (void *)cart->cart_rom);
    printf("rom_code: %u\n", cart->rom_code);
    printf("rom_size: %u\n", cart->rom_size);
    printf("num_of_rom_banks: %u\n", cart->num_of_rom_banks);
    printf("cart_ram: %p\n", (void *)cart->cart_ram);
    printf("ram_code: %u\n", cart->ram_code);
    printf("ram_size: %u\n", cart->ram_size);
    printf("num_of_ram_banks: %u\n", cart->num_of_ram_banks);
    printf("----------------------------------------------------\n");
}

void load_rom_from_cart(CART *cart, const char *rom_path) {
    int test_size = 64;
    FILE *file = fopen(rom_path, "rb");

    // Error handling for failed file opening
    if (file == NULL) {
        perror("Cannot open ROM");
        return;
    }

    // Get the length of the file
    fseek(file, 0, SEEK_END);

    int length_of_file = ftell(file);

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

    printf("Length of ROM: %d", length_of_file);

    // Set the file back to the beginning
    fseek(file, 0, SEEK_SET);

    // Sets the correct size of the cart's rom based on the
    // length of the file found above.
    cart->rom_size = length_of_file;
    cart->cart_rom = calloc(1, cart->rom_size);

    size_t bytes = fread(cart->cart_rom, 1, cart->rom_size, file);

    printf("\n0x%02X ", cart->cart_rom[0x00000100]);

    // Used in debugging purposes - REMOVE -->
    if (debugging) {
        printf("\n0x%02X ", cart->cart_rom[0x0009AA50]);
        printf("0x%02X ", cart->cart_rom[0x0009AA51]);
        printf("0x%02X ", cart->cart_rom[0x0009AA52]);

        printf("\n\nThe first %d bytes of the ROM file are: ", test_size);
        for (int i = 0; i < test_size; i++) {
            if (i % byte_length == 0) {
                printf("\n0x%02X ", cart->cart_rom[i]);
            }
            else {
                printf("0x%02X ", cart->cart_rom[i]);
            }
        }
    }

    // <---
}