#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct registers {
    uint16_t AF;                        // 8-bit General Register
    uint16_t BC;                        //          |
    uint16_t DE;                        //          |
    uint16_t HL;                        // _____________________

    bool HALT;
} REGS;

typedef struct cpu {
    REGS regs;                          // CPU register struct

    uint16_t SP;                        // Stack Pointer
    uint16_t PC;                        // Program Counter

    int cycle;                          // Cycle count for debugging
    int cycle_count;                    // Contains the cycle count to increment by
    
    bool prefix_cb_check;               // 
    uint8_t opcode;                     // Contains the instruction opcode
} CPU;

typedef struct cart {
    uint8_t *cart_rom;                  // Reads in the entire ROM | Dynamically set
    unsigned int rom_size;              // Stores the size of the ROM in bytes

    uint8_t rom_code;                   // Houses the ROM identifier code
    uint16_t num_of_rom_banks;          // Stores the number of ROM banks (2 - 512)
    uint8_t curr_rom_bank;              // Stores the current ROM bank (2 - 512)

    uint8_t *cart_ram;                  // Dynamically set amount based on cart specs
    unsigned int ram_size;              // Stores the size of the RAM in bytes
    
    uint8_t ram_code;                   // Houses the RAM identifier code
    uint8_t num_of_ram_banks;           // Stores the number of RAM banks (0 - 16)
    uint8_t curr_ram_bank;              // Stores the current ROM bank (0 - 16)

    char title[17];                     // Stores the title of the game

    bool cgb;                           // Stores the flag for CGB mode
    
    uint8_t mbc_code;                  // Stores the MBC type code
    uint8_t mbc_type;                  // Stores the generic MBC type

} CART;

typedef struct gameboy {
    // I want to read from the cart first because it contains all the necessary
    // information for the CPU, MBC, and possibly the rest
    CART cartridge;
    
    // Add the code and struct for the MBC. This probably isn't necessary, but
    // it will make it easier for me to visualize the overall structure

    // Initialize the CPU
    CPU cpu;

    // Simulated hardware of the Gameboy Color
    // The write up is included in day2.txt section on memory management
    uint8_t fixed_rom[0x4000];          // 16 KiB ROM Bank 00           (16 KiB)
    uint8_t bank_rom[0x4000];           // 16 KiB ROM Bank 01 - NN      (16 KiB)

    // The RAM may need to be dynamically allocated.
    // However, I suspect that I won't need to do that
    // because a Gameboy can play GB Color games just fine.
    // Pokemon Silver runs just fine on the normal GB.

    uint8_t vram[0x2000];               // 8 KiB VRAM                   (8 KiB)
    uint8_t external_ram[0x2000];       // 8 KiB External RAM           (8 KiB)
    
    uint8_t fixed_work_ram[0x1000];     // 4 KiB Work RAM               (4 KiB)
    uint8_t bank_work_ram[0x1000];      // 4 KiB Work RAM (banked)      (4 KiB)

    uint8_t oam[0xA0];                  // Object Attribute Memory      (160 bytes)
    uint8_t io_registers[0x80];         // I/O Registers                (128 bytes)
    uint8_t hi_ram[0x7F];               // High RAM                     (127 bytes)
    uint8_t interrupt_enable[0x1];      // Interrupt Enable Register    (1 byte)
} GB;

// Declare the instructions array
typedef void (*main_instruction_set)(GB* gb);
typedef void (*cb_prefix_instruction_set)(GB* gb);

#endif