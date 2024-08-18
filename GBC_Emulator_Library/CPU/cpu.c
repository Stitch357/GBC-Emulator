#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "cpu.h"
#include "mi.h"
#include "cbi.h"
#include "structs.h"

// Used in testing
#define debugging true

void set_register_top_byte(uint16_t* reg, uint8_t value) {
    *reg = (*reg & 0x00FF) | ((uint16_t)value << 8);
}

void set_register_bottom_byte(uint16_t* reg, uint8_t value) {
    *reg = (*reg & 0xFF00) | (uint16_t)value;
}

uint8_t access_register_top_byte(uint16_t reg) {
    uint8_t temp_value = (reg >> 8) & 0xFF;

    return temp_value;
}

uint8_t access_register_bottom_byte(uint16_t reg) {
    uint8_t temp_value = reg & 0xFF;

    return temp_value;
}

uint8_t access_zero_flag(uint16_t reg) {
    uint8_t F = access_register_bottom_byte(reg);
    uint8_t temp_value = (F >> 7) & 1;

    return temp_value;
}

uint8_t access_sub_flag(uint16_t reg) {
    uint8_t F = access_register_bottom_byte(reg);
    uint8_t temp_value = (F >> 6) & 1;

    return temp_value;
}

uint8_t access_half_carry_flag(uint16_t reg) {
    uint8_t F = access_register_bottom_byte(reg);
    uint8_t temp_value = (F >> 5) & 1;

    return temp_value;
}

uint8_t access_carry_flag(uint16_t reg) {
    uint8_t F = access_register_bottom_byte(reg);
    uint8_t temp_value = (F >> 4) & 1;

    return temp_value;
}

void cpu_initialize(GB *gb) {
    gb->cpu.regs.AF = 0x0000;
    gb->cpu.regs.BC = 0x0000;
    gb->cpu.regs.DE = 0x0000;
    gb->cpu.regs.HL = 0x0000;

    // Set the PC & SP
    gb->cpu.PC = 0x100;
    gb->cpu.SP = 0xFFFE;

    // Check out the Pan Doc on the start up sequence linked in day9.txt
    if (gb->cartridge.cgb == true) {
        set_register_top_byte(&gb->cpu.regs.AF, 0x11);
    }

    // Set the initial cycle & cycle count
    gb->cpu.cycle = 0;
    gb->cpu.cycle_count = 0;

    gb->cpu.prefix_cb_check = false;
    gb->cpu.opcode = 0x00;
}

void print_cpu_stats(GB *gb) {
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Cycle        ---> %d\n", gb->cpu.cycle);
    printf("Opcode       ---> 0x%02X\n", gb->cpu.opcode);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("        ┏━━━━━━━━━━━━┓                  ┏━━━━━━━━━━━━┓\n");
    printf("        ┃     A      ┃        =         ┃    0x%02X    ┃\n", access_register_top_byte(gb->cpu.regs.AF));
    printf("        ┗━━━━━━━━━━━━┛                  ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓\n");
    printf("┃     B      ┃ ┃     C      ┃ = ┃    0x%02X    ┃ ┃    0x%02X    ┃\n", access_register_top_byte(gb->cpu.regs.BC), access_register_bottom_byte(gb->cpu.regs.BC));
    printf("┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓\n");
    printf("┃     D      ┃ ┃     E      ┃ = ┃    0x%02X    ┃ ┃    0x%02X    ┃\n", access_register_top_byte(gb->cpu.regs.DE), access_register_bottom_byte(gb->cpu.regs.DE));
    printf("┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓\n");
    printf("┃     H      ┃ ┃     L      ┃ = ┃    0x%02X    ┃ ┃    0x%02X    ┃\n", access_register_top_byte(gb->cpu.regs.HL), access_register_bottom_byte(gb->cpu.regs.HL));
    printf("┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛\n");
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("0 = false                       1 = true\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Zero Flag       = %d            Subtract Flag = %d\n", access_zero_flag(gb->cpu.regs.AF), access_sub_flag(gb->cpu.regs.AF));
    printf("Half-Carry Flag = %d            Carry Flag    = %d\n", access_half_carry_flag(gb->cpu.regs.AF), access_carry_flag(gb->cpu.regs.AF));
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃             SP            ┃ = ┃           0x%04X          ┃\n", gb->cpu.SP);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃             PC            ┃ = ┃           0x%04X          ┃\n", gb->cpu.PC);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("\n");
}

static void process_instruction(GB *gb) {
    // Get the current opcode from the cartridge ROM
    uint8_t opcode = gb->cartridge.cart_rom[gb->cpu.PC];

    // Set the gb's CPU current opcode
    gb->cpu.opcode = opcode;
    
    if (opcode != 0xCB) {
        main_instructions[indicies[opcode]](gb);
    }
    else if (opcode == 0xCB) {
        opcode = gb->cartridge.cart_rom[gb->cpu.PC + 1];

        cb_prefix_instructions[indicies[opcode]](gb);
    }
}

static void increment_cycle(GB *gb) {
    // Cycles are in M-Cycles rather than T-cycles
    gb->cpu.cycle += gb->cpu.cycle_count;
}

void cycle_cpu(GB *gb) {
    // Reset the cycle count
    gb->cpu.cycle_count = 0;

    process_instruction(gb);

    increment_cycle(gb);
}

static cb_prefix_instruction_set prefix_cb_instructions[0x100] = {

};