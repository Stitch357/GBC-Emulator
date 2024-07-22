#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "cartridge.h"
#include "structs.h"

// Used in testing
#define debugging true
#define byte_length 16

#define rom_bank_size (16 * 1024)               // 16 KiB per bank
#define min_rom_size (rom_bank_size * 2)        // 32 KiB minimum size
#define max_rom_size (rom_bank_size * 512)      // 8 MiB maximum size

#define rom_code_addr 0x148                     //
#define high_rom_value 72                       // Used to calculate the # of banks with 0x52, 0x53, & 0x54

#define title_addr 0x134                        // Points to the ROM's title
#define title_length 16                         // The ROM typically sets aside 16 bytes for the title
                                                // Backfills with 0's if indicies are unused

#define cbg_flag_addr 0x143

#define sgb_flag_addr 0x146
#define cart_type_addr 0x147

#define ram_code_addr 0x149
#define ram_bank_size (8 * 1024)

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

static void load_title(CART *cart) {
    char character;
    int i;

    for (i = 0; i < title_length; i++) {
        character = cart->cart_rom[title_addr + i];

        // The titles are filled with 0's whenever they end
        if (character == 0) {
            break;
        }

        cart->title[i] = character;
    }

    cart->title[i] = '\0';
}

static void print_title(CART *cart) {
    printf("%s", cart->title);
}

static void load_cgb_flag(CART *cart) {
    cart->cgb = false;

    if ((cart->cart_rom[cbg_flag_addr] & 0x80) ||
        (cart->cart_rom[cbg_flag_addr] & 0xC0)) {
        cart->cgb = true;
        return;
    }
}

static void print_cgb_flag(CART *cart) {
    if (cart->cgb == 0) {
        printf("False");
    }
    else {
        printf("True");
    }
}

static void load_rom_banks(CART *cart) {
    uint8_t rom_value = cart->cart_rom[rom_code_addr];
    cart->rom_code = rom_value;

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
            cart->num_of_rom_banks = (1 << (rom_value + 1));
        break;

        case 0x52:
        case 0x53:
        case 0x54:
            cart->num_of_rom_banks = high_rom_value + (8 * ((rom_value - 0x52) * (rom_value - 0x52 + 0x1) / 2));
        break;

        default:
            printf("Unknown # of ROM banks");
    }

    if (debugging) {
        printf("\n\nSuccessfully set the # of ROM banks");
    }
}

static void print_rom_code(CART *cart) {
    printf("%d", cart->rom_code);
}

static void print_rom_banks(CART *cart) {
    printf("%d", cart->num_of_rom_banks);
}

static void load_ram(CART *cart) {
    int exponent;

    uint8_t ram_value = cart->cart_rom[ram_code_addr];
    cart->ram_code = ram_value;

    switch (ram_value) {
        case 0x00:
        case 0x01:
            cart->cart_ram = 0;
            cart->num_of_ram_banks = 0;
        break;

        case 0x02:
        case 0x03:
        case 0x04:
            exponent = ram_value - 0x02;
            cart->ram_size = 8 << (2 * exponent);
            cart->num_of_ram_banks = cart->ram_size / 8;
        break;

        case 0x05:
            cart->ram_size = 64;
            cart->num_of_ram_banks = cart->ram_size / 8;
        break;

        default:
            printf("\nUnknown size of RAM");
            printf("\nUnknown # of RAM banks");
    }
}

static void print_ram_code(CART *cart) {
    printf("\nRAM code is ---> %d", cart->ram_code);
}

static void print_ram_size(CART *cart) {
    printf("\nSize of RAM is ---> %d", cart->ram_size);
}

static void print_ram_banks(CART *cart) {
    printf("\n# of RAM banks is ---> %d", cart->num_of_ram_banks);
}

void load_cartridge(CART *cart, const char *rom_path) {
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
    cart->rom_size = length_of_file;
    cart->cart_rom = calloc(1, cart->rom_size);

    if (debugging) {
        printf("\nAllocated memory for ROM");
    }

    size_t bytes = fread(cart->cart_rom, 1, cart->rom_size, file);

    if (debugging) {
        printf("\n\nFirst instruction at $101 - $103");
        printf("\n0x%02X ", cart->cart_rom[0x00000101]);
        printf("0x%02X ", cart->cart_rom[0x00000102]);
        printf("0x%02X ", cart->cart_rom[0x00000103]);

        printf("\n\nRemember that this is LITTLE ENDIAN format!");

        printf("\n\nThe first %d bytes of the ROM file are: ", test_size);
        for (int i = 0; i < test_size; i++) {
            if (i % byte_length == 0) {
                printf("\n0x%02X ", cart->cart_rom[i + 0x100]);
            }
            else {
                printf("0x%02X ", cart->cart_rom[i + 0x100]);
            }
        }
    }

    // *-*-* Set the cartridge # of ROM banks

    load_rom_banks(cart);

    if (debugging) {
        printf("\n# of ROM banks set as --- > ");
        print_rom_banks(cart);
        printf("\n");
    }

    // Make sure that the # of ROM banks fits the ROM size
    if (cart->rom_size < cart->num_of_rom_banks * rom_bank_size) {
        printf("ROM file cannot hold the %d ROM banks", cart->num_of_rom_banks);
        return;
    }

    // *-*-* Set the cartridge RAM
    load_ram(cart);

    if (debugging) {
        print_ram_code(cart);
        print_ram_size(cart);
        print_ram_banks(cart);
    }

    cart->cart_ram = calloc(1, cart->num_of_ram_banks * ram_bank_size);

    if (debugging) {
        printf("\nAllocated memory size of RAM ---> %d in bytes", (cart->num_of_ram_banks * ram_bank_size));
    }

    // *-*-* Set the cartridge # of RAM banks

    // *-*-* Set the cartridge title
    
    load_title(cart);

    if (debugging) {
        printf("\n\nLoading title --- > ");
        print_title(cart);
        printf("\n");
    }

    // *-*-* Set the cartridge CGB flag
    
    load_cgb_flag(cart);

    if (debugging) {
        printf("\nCGB flag set as --- > ");
        print_cgb_flag(cart);
        printf("\n");
    }


}