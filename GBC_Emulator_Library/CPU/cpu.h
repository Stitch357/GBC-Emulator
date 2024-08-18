#ifndef CPU_H
#define CPU_H

#include "mi.h"
#include "cbi.h"
#include "structs.h"

void set_register_top_byte(uint16_t* reg, uint8_t value);
void set_register_bottom_byte(uint16_t* reg, uint8_t value);

// Used to access registers A, B, D, & H
uint8_t access_register_top_byte(uint16_t reg);

// Used to access registers C, E, & L
uint8_t access_register_bottom_byte(uint16_t reg);

// Used to access the flags F
uint8_t access_zero_flag(uint16_t reg);
uint8_t access_sub_flag(uint16_t reg);
uint8_t access_half_carry_flag(uint16_t reg);
uint8_t access_carry_flag(uint16_t reg);

void cpu_initialize(GB *gb);
void print_cpu_stats(GB *gb);

void mi_nop();

static void process_instruction(GB *gb);
static void increment_instruction(GB *gb);

void cycle_cpu(GB *gb);

#endif