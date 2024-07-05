#include <stdlib.h>
#include "cartridge.h"
#include "structs.h"

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