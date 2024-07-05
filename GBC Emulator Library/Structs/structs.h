#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct gameboy {
    CPU cpu;
    CART cartridge;

    // Simulated hardware of the Gameboy
    // The write up is included in day2.txt section on memory management
    uint8_t fixed_rom[0x4000];          // 16 KiB ROM Bank 00           (16 KiB)
    uint8_t bank_rom[0x4000];           // 16 KiB ROM Bank 01 - NN      (16 KiB)

    uint8_t vram[0x2000];               // 8 KiB VRAM                   (8 KiB)
    uint8_t external_ram[0x2000];       // 8 KiB External RAM           (8 KiB)
    
    uint8_t fixed_work_ram[0x1000];     // 4 KiB Work RAM               (4 KiB)
    uint8_t bank_work_ram[0x1000];      // 4 KiB Work RAM (banked)      (4 KiB)

    uint8_t oam[0xA0];                  // Object Attribute Memory      (160 bytes)
    uint8_t io_registers[0x80];         // I/O Registers                (128 bytes)
    uint8_t hi_ram[0x7F];               // High RAM                     (127 bytes)
    uint8_t interrupt_enable[0x1];      // Interrupt Enable Register    (1 byte)
} GB;

typedef struct cpu {
    REGS regs;

    uint16_t SP;                        // Stack Pointer
    uint16_t PC;                        // Program Counter
} CPU;

typedef struct registers {
    uint8_t A;                          // 8-bit Accumulator Register
    uint8_t B;                          // 8-bit General Register
    uint8_t C;                          //          |
    uint8_t D;                          //          |
    uint8_t E;                          //          |
    uint8_t H;                          //          |
    uint8_t L;                          // _____________________

    bool ZF;                            // Zero Flag
    bool SF;                            // Subtract Flag
    bool HC;                            // Half-Carry Flag - (Nibble Carry)
    bool C;                             // Carry Flag      - (Byte Carry)
} REGS;

typedef struct cart {
    uint8_t *cart_rom;                  // Reads in the entire ROM

    
} CART;

#endif