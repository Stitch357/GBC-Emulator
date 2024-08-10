#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "cpu.h"
#include "mi.h"
#include "cbi.h"
#include "structs.h"

// Used in testing
#define debugging false

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
    uint8_t temp_value = reg & 0x80;

    return temp_value;
}

uint8_t access_sub_flag(uint16_t reg) {
    uint8_t temp_value = reg & 0x40;

    return temp_value;
}

uint8_t access_half_carry_flag(uint16_t reg) {
    uint8_t temp_value = reg & 0x20;

    return temp_value;
}

uint8_t access_carry_flag(uint16_t reg) {
    uint8_t temp_value = reg & 0x10;

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
    gb->cpu.first_byte = 0x00;
    gb->cpu.second_byte = 0x00;
}

void print_cpu_stats(GB *gb) {
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Cycle        ---> %d\n", gb->cpu.cycle);
    printf("Opcode       ---> 0x%02X\n", gb->cpu.opcode);
    printf("First Byte   ---> 0x%02X\n", gb->cpu.first_byte);
    printf("Second Byte  ---> 0x%02X\n", gb->cpu.second_byte);
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

static void fetch_instruction(GB *gb) {

}

static void decode_instruction(GB *gb) {

}

static void execute_instruction(GB *gb) {

}

static void process_instruction(GB *gb) {

}

static void increment_instruction(GB *gb) {

}

void cycle_cpu(GB *gb) {
    process_instruction(gb);

    increment_instruction(gb);
}

static main_instruction_set main_instructions[0x100] = {
    // 0x00
    mi_nop,
    
};

static cb_prefix_instruction_set prefix_cb_instructions[0x100] = {

};