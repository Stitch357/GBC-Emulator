#include "mi.h"
#include "cpu.h"
#include "structs.h"
#include "misc.h"

#define debugging true

// General Helper Function
void increase_cycle_and_pc(GB* gb, uint8_t cc, uint8_t pc) {
    gb->cpu.cycle_count = cc;
    gb->cpu.PC += pc;
}

void set_temp_register(GB* gb, uint8_t reg) {
    switch (reg) {
        case 0x00:  // B
            gb->cpu.regs.temp_reg = (gb->cpu.regs.BC >> 8) & 0xFF;
        break;

        case 0x01:  // C
            gb->cpu.regs.temp_reg = (gb->cpu.regs.BC) & 0xFF;
        break;

        case 0x02:  // D
            gb->cpu.regs.temp_reg = (gb->cpu.regs.DE >> 8) & 0xFF;
        break;

        case 0x03:  // E
            gb->cpu.regs.temp_reg = (gb->cpu.regs.DE) & 0xFF;
        break;

        case 0x04:  // H
            gb->cpu.regs.temp_reg = (gb->cpu.regs.HL >> 8) & 0xFF;
        break;

        case 0x05:  // L
            gb->cpu.regs.temp_reg = (gb->cpu.regs.HL) & 0xFF;
        break;

        case 0x06:  // HL
            gb->cpu.regs.temp_reg = (gb->cpu.regs.HL) & 0xFFFF;
        break;

        case 0x07:  // A
            gb->cpu.regs.temp_reg = (gb->cpu.regs.AF >> 8) & 0xFF;
        break;
    }
}

// Access proper registers
void access_register(GB* gb) {   
    uint8_t opcode_pos = gb->cpu.opcode & 0xF;

    if (opcode_pos > 7) {
        opcode_pos = opcode_pos - 8;
    }

    if (debugging) {
        printf("Opcode: 0x%02X", opcode_pos);
    }

    char* registers[8] = { "B", "C", "D", "E", "H", "L", "HL", "A" };

    set_temp_register(gb, opcode_pos);

    if (debugging) {
        printf("\nSelected register: %s\n", registers[opcode_pos]);
        printf("Temp Register Value: 0x%04X", gb->cpu.regs.temp_reg);
    }
}

void cpu_sub_set_flags(GB* gb) {
    uint8_t value = gb->cartridge.cart_rom[gb->cpu.PC + 1];
    
    // uint16_t remainder = a - b;
    uint8_t A = (gb->cpu.regs.AF >> 8) & 0xFF;
    uint8_t result = A - value;

    // Set the Zero flag (Z)
    if (result == 0) {
        gb->cpu.regs.AF |= (1 << 7);
    }
    else {
        gb->cpu.regs.AF &= ~(1 << 7);
    }

    // Set the Subtract flag (N)
    gb->cpu.regs.AF |= (1 << 6);

    // Set the Half-Carry flag
    uint8_t lower_nibble_A = A & 0x0F;
    uint8_t lower_nibble_value = value & 0x0F;

    if (lower_nibble_A < lower_nibble_value) {
        gb->cpu.regs.AF |= (1 << 5);
    }
    else {
        gb->cpu.regs.AF &= ~(1 << 5);
    }

    // Set the Carry flag
    if (A < value) {
        gb->cpu.regs.AF |= (1 << 4);
    }
    else {
        gb->cpu.regs.AF &= ~(1 << 4);
    }
}

void set_inc_flags(GB* gb, uint16_t temp) {
    // Set the Z flag
    if ((temp + 1) == 0) {
        gb->cpu.regs.AF |= (1 << 7);
    }
    else {
        gb->cpu.regs.AF &= ~(1 << 7);
    }

    // Reset the N flag
    gb->cpu.regs.AF &= ~(1 << 6);

    // Set the H flag
    // 0xF = 1111, add one and you get 0001 0000
    if ((temp & 0xF) == 0xF) {
        gb->cpu.regs.AF |= (1 << 5);
    }
}

// 0x00 - 1 M-Cycle, PC++
void mi_nop(GB* gb) {
    if (debugging) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Executing nop instruction... \n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    increase_cycle_and_pc(gb, 1, 1);
}

// 0x01
void mi_ld_bc_d16(GB* gb) {

}

// 0x02
void mi_ld_bc_a(GB* gb) {

}

// 0x03 - 2 M-Cycle, PC++
void mi_inc_bc(GB* gb) {
    gb->cpu.regs.BC += 1;

    increase_cycle_and_pc(gb, 2, 1);
}

// 0x04 - 1 M-Cycle, PC++
void mi_inc_b(GB* gb) {
    uint16_t temp_b = (gb->cpu.regs.BC >> 8) & 0xFF;
    uint16_t temp_c = (gb->cpu.regs.BC) & 0xFF;

    set_inc_flags(gb, temp_b);

    gb->cpu.regs.BC = ((temp_b + 1) << 8) | temp_c;

    increase_cycle_and_pc(gb, 1, 1);
}

// 0x05
void mi_dec_b(GB* gb) {

}

// 0x06
void mi_ld_b_d8(GB* gb) {

}

// 0x07
void mi_rlca(GB* gb) {

}

// 0x08
void mi_ld_a16_sp(GB* gb) {

}

// 0x09
void mi_add_hl_bc(GB* gb) {

}

// 0x0A
void mi_ld_a_bc(GB* gb) {

}

// 0x0B
void mi_dec_bc(GB* gb) {

}

// 0x0C
void mi_inc_c(GB* gb) {

}

// 0x0D
void mi_dec_c(GB* gb) {

}

// 0x0E
void mi_ld_c_d8(GB* gb) {

}

// 0x0F
void mi_rrca(GB* gb) {

}

// 0x10
void mi_stop_0(GB* gb) {

}

// 0x11
void mi_ld_de_d16(GB* gb) {

}

// 0x12
void mi_ld_de_a(GB* gb) {

}

// 0x13 - 2 M-Cycle, PC++
void mi_inc_de(GB* gb) {
    gb->cpu.regs.DE += 1;

    increase_cycle_and_pc(gb, 2, 1);
}

// 0x14 - 1 M-Cycle, PC++
void mi_inc_d(GB* gb) {
    uint16_t temp_d = (gb->cpu.regs.DE >> 8) & 0xFF;
    uint16_t temp_e = (gb->cpu.regs.DE) & 0xFF;

    set_inc_flags(gb, temp_d);

    gb->cpu.regs.DE = ((temp_d + 1) << 8) | temp_e;

    increase_cycle_and_pc(gb, 1, 1);
}

// 0x15
void mi_dec_d(GB* gb) {

}

// 0x16
void mi_ld_d_d8(GB* gb) {

}

// 0x17
void mi_rla(GB* gb) {

}

// 0x18 - 3 M-Cycle, PC = address + value
void mi_jr_r8(GB* gb) {
    int8_t offset = gb->cartridge.cart_rom[gb->cpu.PC + 1];

    // Make sure to increase the PC by
    // instruction length before adding offset
    gb->cpu.PC += 2;

    if (debugging) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Executing jr r8 instruction... \n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    gb->cpu.cycle_count = 3;
    gb->cpu.PC += offset;
}

// 0x19
void mi_add_hl_de(GB* gb) {

}

// 0x1A
void mi_ld_a_de(GB* gb) {

}

// 0x1B
void mi_dec_de(GB* gb) {

}

// 0x1C
void mi_inc_e(GB* gb) {

}

// 0x1D
void mi_dec_e(GB* gb) {

}

// 0x1E
void mi_ld_e_d8(GB* gb) {

}

// 0x1F
void mi_rra(GB* gb) {

}

// 0x20
void mi_jr_nz_r8(GB* gb) {

}

// 0x21
void mi_ld_hl_d16(GB* gb) {

}

// 0x22
void mi_ld_hlp_a(GB* gb) {

}

// 0x23 - 2 M-Cycle, PC++
void mi_inc_hl_value(GB* gb) {
    gb->cpu.regs.HL += 1;

    increase_cycle_and_pc(gb, 2, 1);
}

// 0x24 - 1 M-Cycle, PC++
void mi_inc_h(GB* gb) {
    uint16_t temp_h = (gb->cpu.regs.HL >> 8) & 0xFF;
    uint16_t temp_l = (gb->cpu.regs.HL) & 0xFF;

    set_inc_flags(gb, temp_h);

    gb->cpu.regs.HL = ((temp_h + 1) << 8) | temp_l;

    increase_cycle_and_pc(gb, 1, 1);
}

// 0x25
void mi_dec_h(GB* gb) {

}

// 0x26
void mi_ld_h_d8(GB* gb) {

}

// 0x27
void mi_daa(GB* gb) {

}

// 0x28 - 3/2 M-Cycles, PC is based on results
void mi_jr_z_r8(GB* gb) {
    if (debugging) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Executing jr z, r8... \n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    int8_t byte = (int8_t)gb->cartridge.cart_rom[gb->cpu.PC + 1];

    uint8_t zero_flag = access_zero_flag(gb->cpu.regs.AF);
    if (zero_flag == 1) {
        gb->cpu.PC += byte;
        gb->cpu.cycle_count = 3;
    }
    else {
        gb->cpu.PC += 2;
        gb->cpu.cycle_count = 2;
    }
}

// 0x29
void mi_add_hl_hl(GB* gb) {

}

// 0x2A
void mi_ld_a_hlp(GB* gb) {

}

// 0x2B
void mi_dec_hl_value(GB* gb) {

}

// 0x2C
void mi_inc_l(GB* gb) {

}

// 0x2D
void mi_dec_l(GB* gb) {

}

// 0x2E
void mi_ld_l_d8(GB* gb) {

}

// 0x2F
void mi_cpl(GB* gb) {

}

// -----

// 0x30
void mi_jr_nc_r8(GB* gb) {

}

// 0x31
void mi_ld_sp_d16(GB* gb) {

}

// 0x32
void mi_ld_hlm_a(GB* gb) {

}

// 0x33 - 2 M-Cycles, PC++
void mi_inc_sp(GB* gb) {
    gb->cpu.SP += 1;

    increase_cycle_and_pc(gb, 2, 1);
}

// 0x34 - 3 M-Cycles, PC++
// Come back to this once you study
// up on memory accessing and MBCs
void mi_inc_hl_address(GB* gb) {

}

// 0x35
void mi_dec_hl_address(GB* gb) {

}

// 0x36
void mi_ld_hl_d8(GB* gb) {

}

// 0x37
void mi_scf(GB* gb) {

}

// 0x38
void mi_jr_c_r8(GB* gb) {
    
}

// 0x39
void mi_add_hl_sp(GB* gb) {

}

// 0x3A
void mi_ld_a_hlm(GB* gb) {

}

// 0x3B
void mi_dec_sp(GB* gb) {

}

// 0x3C
void mi_inc_a(GB* gb) {

}

// 0x3D
void mi_dec_a(GB* gb) {

}

// 0x3E
void mi_ld_a_d8(GB* gb) {

}

// 0x3F
void mi_ccf(GB* gb) {

}

// 0x40 - B
void mi_ld_b(GB* gb) {

}

// 0x41 - C
// 0x42 - D
// 0x43 - E
// 0x44 - H
// 0x45 - L
// 0x46 - HL
// 0x47 - A

// 0x48 - B
void mi_ld_c(GB* gb) {

}

// 0x49 - C
// 0x4A - D
// 0x4B - E
// 0x4C - H
// 0x4D - L
// 0x4E - HL
// 0x4F - A

// 0x50 - B
void mi_ld_d(GB* gb) {

}

// 0x51 - C
// 0x52 - D
// 0x53 - E
// 0x54 - H
// 0x55 - L
// 0x56 - HL
// 0x57 - A

// 0x58 - B
void mi_ld_e(GB* gb) {

}

// 0x59 - C
// 0x5A - D
// 0x5B - E
// 0x5C - H
// 0x5D - L
// 0x5E - HL
// 0x5F - A

// 0x60 - B
void mi_ld_h(GB* gb) {

}

// 0x61 - C
// 0x62 - D
// 0x63 - E
// 0x64 - H
// 0x65 - L
// 0x66 - HL
// 0x67 - A

// 0x68 - B
void mi_ld_l(GB* gb) {

}

// 0x69 - C
// 0x6A - D
// 0x6B - E
// 0x6C - H
// 0x6D - L
// 0x6E - HL
// 0x6F - A

// 0x70 - B
void mi_ld_hl(GB* gb) {

}

// 0x71 - C
// 0x72 - D
// 0x73 - E
// 0x74 - H
// 0x75 - L
// 0x76 - HL
void mi_halt(GB* gb) {

}

// 0x77 - A

// 0x78 - B
void mi_ld_a(GB* gb) {

}

// 0x79 - C
// 0x7A - D
// 0x7B - E
// 0x7C - H
// 0x7D - L
// 0x7E - HL
// 0x7F - A

// 0x80 - B
void mi_add_a(GB* gb) {

}

// 0x81 - C
// 0x82 - D
// 0x83 - E
// 0x84 - H
// 0x85 - L
// 0x86 - HL
// 0x87 - A

// 0x88 - B
void mi_adc_a(GB* gb) {

}

// 0x89 - C
// 0x8A - D
// 0x8B - E
// 0x8C - H
// 0x8D - L
// 0x8E - HL
// 0x8F - A

// 0x90 - B
void mi_sub(GB* gb) {

}

// 0x91 - C
// 0x92 - D
// 0x93 - E
// 0x94 - H
// 0x95 - L
// 0x96 - HL
// 0x97 - A

// 0x98 - B
void mi_sbc_a(GB* gb) {

}

// 0x99 - C
// 0x9A - D
// 0x9B - E
// 0x9C - H
// 0x9D - L
// 0x9E - HL
// 0x9F - A

// 0xA0 - B
void mi_and(GB* gb) {

}

// 0xA1 - C
// 0xA2 - D
// 0xA3 - E
// 0xA4 - H
// 0xA5 - L
// 0xA6 - HL
// 0xA7 - A

// 0xA8 - B - 1 M-Cycles, PC++
void mi_xor(GB* gb) {
    uint8_t reg_a = (gb->cpu.regs.AF >> 8) & 0xFF;
    uint16_t temp = gb->cpu.regs.temp_reg;

    uint8_t result = reg_a ^ temp;
    
    if (debugging) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Executing xor instruction...\n");

        access_register(gb);
        printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    // Set the Zero flag (Z)
    if (result == 0) {
        gb->cpu.regs.AF |= (1 << 7);
    }
    else {
        gb->cpu.regs.AF &= ~(1 << 7);
    }

    // Reset the N (Subtract) Flag
    gb->cpu.regs.AF &= ~(1 << 6);

    // Reset the H (Half-Carry) Flag
    gb->cpu.regs.AF &= ~(1 << 5);

    // Reset the C (Carry) Flag
    gb->cpu.regs.AF &= ~(1 << 4);

    // Increase the cycle count and PC
    gb->cpu.cycle_count = 1;
    gb->cpu.PC += 1;

    // Reset the temp_reg since it isn't
    // used beyond this function
    gb->cpu.regs.temp_reg &= 0x0000;
}

// 0xA9 - C
// 0xAA - D
// 0xAB - E
// 0xAC - H
// 0xAD - L
// 0xAE - HL
// 0xAF - A

// 0xB0 - B
void mi_or(GB* gb) {

}

// 0xB1 - C
// 0xB2 - D
// 0xB3 - E
// 0xB4 - H
// 0xB5 - L
// 0xB6 - HL
// 0xB7 - A

// 0xB8 - B
void mi_cp(GB* gb) {

}

// 0xB9 - C
// 0xBA - D
// 0xBB - E
// 0xBC - H
// 0xBD - L
// 0xBE - HL
// 0xBF - A

// 0xC0
void mi_ret_nz(GB* gb) {

}

// 0xC1
void mi_pop_bc(GB* gb) {

}

// 0xC2
void mi_jp_nz_a16(GB* gb) {

}

// 0xC3 - 2 M-Cycles, PC = address
void mi_jp_a16(GB* gb) {
    if (debugging) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Executing jp a16 instruction...\n");
    }
    uint8_t top_byte = gb->cartridge.cart_rom[gb->cpu.PC + 2];
    uint8_t bottom_byte = gb->cartridge.cart_rom[gb->cpu.PC + 1];

    if (debugging) {
        printf("Top Byte: 0x%02X --- Bottom Byte: 0x%02X\n", top_byte, bottom_byte);
    }

    // uint16_t combined = ((uint16_t)(high_byte & 0xFF) << 8) | (low_byte & 0xFF);

    uint16_t address = ((uint8_t)(top_byte & 0xFF) << 8) | ((uint8_t)(bottom_byte & 0xFF));
    if (debugging) {
        printf("Address: 0x%04X\n", address);
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    gb->cpu.cycle_count = 2;
    gb->cpu.PC = address;
}

// 0xC4
void mi_call_nz_a16(GB* gb) {

}

// 0xC5
void mi_push_bc(GB* gb) {

}

// 0xC6
void mi_add_a_d8(GB* gb) {

}

// 0xC7
void mi_rst_00h(GB* gb) {

}

// 0xC8
void mi_ret_z(GB* gb) {

}

// 0xC9
void mi_ret(GB* gb) {

}

// 0xCA
void mi_jp_z_a16(GB* gb) {

}

// 0xCB
void mi_prefix_cb(GB* gb) {

}

// 0xCC
void mi_call_z_a16(GB* gb) {

}

// 0xCD
void mi_call_a16(GB* gb) {

}

// 0xCE
void mi_adc_a_d8(GB* gb) {

}

// 0xCF
void mi_rst_08h(GB* gb) {

}

// 0xD0
void mi_ret_nc(GB* gb) {

}

// 0xD1
void mi_pop_de(GB* gb) {

}

// 0xD2
void mi_jp_nc_a16(GB* gb) {

}

// 0xD3 - Empty

// 0xD4
void mi_call_nc_a16(GB* gb) {

}

// 0xD5
void mi_push_de(GB* gb) {

}

// 0xD6
void mi_sub_d8(GB* gb) {

}

// 0xD7
void mi_rst_10h(GB* gb) {

}

// 0xD8
void mi_ret_c(GB* gb) {

}

// 0xD9
void mi_reti(GB* gb) {

}

// 0xDA
void mi_jp_c_a16(GB* gb) {

}

// 0xDB - Empty

// 0xDC
void mi_call_c_a16(GB* gb) {

}

// 0xDD - Empty


// 0xDE
void mi_sbc_a_d8(GB* gb) {

}

// 0xDF
void mi_rst_18h(GB* gb) {

}

// 0xE0
void mi_ldh_a8_a(GB* gb) {

}

// 0xE1
void mi_pop_hl(GB* gb) {

}

// 0xE2
void mi_ld_c_a(GB* gb) {

}

// 0xE3 - Empty
// 0xE4 - Empty

// 0xE5
void mi_push_hl(GB* gb) {

}

// 0xE6
void mi_and_d8(GB* gb) {

}

// 0xE7
void mi_rst_20h(GB* gb) {

}

// 0xE8
void mi_add_sp_r8(GB* gb) {

}

// 0xE9
void mi_jp_hl(GB* gb) {

}

// 0xEA
void mi_ld_a16_a(GB* gb) {

}

// 0xEB - Empty
// 0xEC - Empty
// 0xED - Empty

// 0xEE
void mi_xor_d8(GB* gb) {

}

// 0xEF
void mi_rst_28h(GB* gb) {

}

// 0xF0
void mi_ldh_a_a8(GB* gb) {

}

// 0xF1
void mi_pop_af(GB* gb) {

}

// 0xF2
void mi_ld_a_c(GB* gb) {

}

// 0xF3
void mi_di(GB* gb) {

}

// 0xF4 - Empty

// 0xF5
void mi_push_af(GB* gb) {

}

// 0xF6
void mi_or_d8(GB* gb) {

}

// 0xF7
void mi_rst_30h(GB* gb) {

}

// 0xF8
void mi_ld_hl_sp_p_r8(GB* gb) {

}

// 0xF9
void mi_ls_sp_hl(GB* gb) {

}

// 0xFA
void mi_ld_a_a16(GB* gb) {

}

// 0xFB
void mi_ei(GB* gb) {

}

// 0xFC - Empty
// 0xFD - Empty

// 0xFE - 2 M-Cycles, PC += 2
void mi_cp_d8(GB* gb) {
    if (debugging) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Executing cp d8... \n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    cpu_sub_set_flags(gb);

    gb->cpu.cycle_count = 2;
    gb->cpu.PC += 2;
}

// 0xFF
void mi_rst_38h(GB* gb) {

}

int indicies[0x100] = {
    0,             // 0x00
    1,             // 0x01
    2,             // 0x02
    3,             // 0x03
    4,             // 0x04
    5,             // 0x05
    6,             // 0x06
    7,             // 0x07
    8,             // 0x08
    9,             // 0x09
    10,            // 0x0A
    11,            // 0x0B
    12,            // 0x0C
    13,            // 0x0D
    14,            // 0x0E
    15,            // 0x0F
    16,            // 0x10
    17,            // 0x11
    18,            // 0x12
    19,            // 0x13
    20,            // 0x14
    21,            // 0x15
    22,            // 0x16
    23,            // 0x17
    24,            // 0x18
    25,            // 0x19
    26,            // 0x1A
    27,            // 0x1B
    28,            // 0x1C
    29,            // 0x1D
    30,            // 0x1E
    31,            // 0x1F
    32,            // 0x20
    33,            // 0x21
    34,            // 0x22
    35,            // 0x23
    36,            // 0x24
    37,            // 0x25
    38,            // 0x26
    39,            // 0x27
    40,            // 0x28
    41,            // 0x29
    42,            // 0x2A
    43,            // 0x2B
    44,            // 0x2C
    45,            // 0x2D
    46,            // 0x2E
    47,            // 0x2F
    48,            // 0x30
    49,            // 0x31
    50,            // 0x32
    51,            // 0x33
    52,            // 0x34
    53,            // 0x35
    54,            // 0x36
    55,            // 0x37
    56,            // 0x38
    57,            // 0x39
    58,            // 0x3A
    59,            // 0x3B
    60,            // 0x3C
    61,            // 0x3D
    62,            // 0x3E
    63,            // 0x3F
    64,            // 0x40
    64,            // 0x41
    64,            // 0x42
    64,            // 0x43
    64,            // 0x44
    64,            // 0x45
    64,            // 0x46
    64,            // 0x47
    65,            // 0x48
    65,            // 0x49
    65,            // 0x4A
    65,            // 0x4B
    65,            // 0x4C
    65,            // 0x4D
    65,            // 0x4E
    65,            // 0x4F
    66,            // 0x50
    66,            // 0x51
    66,            // 0x52
    66,            // 0x53
    66,            // 0x54
    66,            // 0x55
    66,            // 0x56
    66,            // 0x57
    67,            // 0x58
    67,            // 0x59
    67,            // 0x5A
    67,            // 0x5B
    67,            // 0x5C
    67,            // 0x5D
    67,            // 0x5E
    67,            // 0x5F
    68,            // 0x60
    68,            // 0x61
    68,            // 0x62
    68,            // 0x63
    68,            // 0x64
    68,            // 0x65
    68,            // 0x66
    68,            // 0x67
    69,            // 0x68
    69,            // 0x69
    69,            // 0x6A
    69,            // 0x6B
    69,            // 0x6C
    69,            // 0x6D
    69,            // 0x6E
    69,            // 0x6F
    70,            // 0x70
    70,            // 0x71
    70,            // 0x72
    70,            // 0x73
    70,            // 0x74
    70,            // 0x75
    71,            // 0x76
    70,            // 0x77
    72,            // 0x78
    72,            // 0x79
    72,            // 0x7A
    72,            // 0x7B
    72,            // 0x7C
    72,            // 0x7D
    72,            // 0x7E
    72,            // 0x7F
    73,            // 0x80
    73,            // 0x81
    73,            // 0x82
    73,            // 0x83
    73,            // 0x84
    73,            // 0x85
    73,            // 0x86
    73,            // 0x87
    74,            // 0x88
    74,            // 0x89
    74,            // 0x8A
    74,            // 0x8B
    74,            // 0x8C
    74,            // 0x8D
    74,            // 0x8E
    74,            // 0x8F
    75,            // 0x90
    75,            // 0x91
    75,            // 0x92
    75,            // 0x93
    75,            // 0x94
    75,            // 0x95
    75,            // 0x96
    75,            // 0x97
    76,            // 0x98
    76,            // 0x99
    76,            // 0x9A
    76,            // 0x9B
    76,            // 0x9C
    76,            // 0x9D
    76,            // 0x9E
    76,            // 0x9F
    77,            // 0xA0
    77,            // 0xA1
    77,            // 0xA2
    77,            // 0xA3
    77,            // 0xA4
    77,            // 0xA5
    77,            // 0xA6
    77,            // 0xA7
    78,            // 0xA8
    78,            // 0xA9
    78,            // 0xAA
    78,            // 0xAB
    78,            // 0xAC
    78,            // 0xAD
    78,            // 0xAE
    78,            // 0xAF
    79,            // 0xB0
    79,            // 0xB1
    79,            // 0xB2
    79,            // 0xB3
    79,            // 0xB4
    79,            // 0xB5
    79,            // 0xB6
    79,            // 0xB7
    80,            // 0xB8
    80,            // 0xB9
    80,            // 0xBA
    80,            // 0xBB
    80,            // 0xBC
    80,            // 0xBD
    80,            // 0xBE
    80,            // 0xBF
    81,            // 0xC0
    82,            // 0xC1
    83,            // 0xC2
    84,            // 0xC3
    85,            // 0xC4
    86,            // 0xC5
    87,            // 0xC6
    88,            // 0xC7
    89,            // 0xC8
    90,            // 0xC9
    91,            // 0xCA
    92,            // 0xCB
    93,            // 0xCC
    94,            // 0xCD
    95,            // 0xCE
    96,            // 0xCF
    97,            // 0xD0
    98,            // 0xD1
    99,            // 0xD2
    -1,            // 0xD3
    100,           // 0xD4
    101,           // 0xD5
    102,           // 0xD6
    103,           // 0xD7
    104,           // 0xD8
    105,           // 0xD9
    106,           // 0xDA
    -1,            // 0xDB
    107,           // 0xDC
    -1,            // 0xDD
    108,           // 0xDE
    109,           // 0xDF
    110,           // 0xE0
    111,           // 0xE1
    112,           // 0xE2
    -1,            // 0xE3
    -1,            // 0xE4
    113,           // 0xE5
    114,           // 0xE6
    115,           // 0xE7
    116,           // 0xE8
    117,           // 0xE9
    118,           // 0xEA
    -1,            // 0xEB
    -1,            // 0xEC
    -1,            // 0xED
    119,           // 0xEE
    120,           // 0xEF
    121,           // 0xF0
    122,           // 0xF1
    123,           // 0xF2
    124,           // 0xF3
    -1,            // 0xF4
    125,           // 0xF5
    126,           // 0xF6
    127,           // 0xF7
    128,           // 0xF8
    129,           // 0xF9
    130,           // 0xFA
    131,           // 0xFB
    -1,            // 0xFC
    -1,            // 0xFD
    132,           // 0xFE
    133            // 0xFF
};

main_instruction_set main_instructions[0x86] = {
    // 0x00
    mi_nop,             // 1
    mi_ld_bc_d16,       // 2
    mi_ld_bc_a,         // 3
    mi_inc_bc,          // 4
    mi_inc_b,           // 5
    mi_dec_b,           // 6
    mi_ld_b_d8,         // 7
    mi_rlca,            // 8
    mi_ld_a16_sp,       // 9
    mi_add_hl_bc,       // 10
    mi_ld_a_bc,         // 11
    mi_dec_bc,          // 12
    mi_inc_c,           // 13
    mi_dec_c,           // 14
    mi_ld_c_d8,         // 15
    mi_rrca,            // 16

    // 0x10 - 0x1F
    mi_stop_0,          // 17
    mi_ld_de_d16,       // 18
    mi_ld_de_a,         // 19
    mi_inc_de,          // 20
    mi_inc_d,           // 21
    mi_dec_d,           // 22
    mi_ld_d_d8,         // 23
    mi_rla,             // 24
    mi_jr_r8,           // 25
    mi_add_hl_de,       // 26
    mi_ld_a_de,         // 27
    mi_dec_de,          // 28
    mi_inc_e,           // 29
    mi_dec_e,           // 30
    mi_ld_e_d8,         // 31
    mi_rra,             // 32

    // 0x20 - 0x2F
    mi_jr_nz_r8,        // 33
    mi_ld_hl_d16,       // 34
    mi_ld_hlp_a,        // 35
    mi_inc_hl_value,    // 36
    mi_inc_h,           // 37
    mi_dec_h,           // 38
    mi_ld_h_d8,         // 39
    mi_daa,             // 40
    mi_jr_z_r8,         // 41
    mi_add_hl_hl,       // 42
    mi_ld_a_hlp,        // 43
    mi_dec_hl_value,    // 44
    mi_inc_l,           // 45
    mi_dec_l,           // 46
    mi_ld_l_d8,         // 47
    mi_cpl,             // 48

    // 0x30 - 0x3F
    mi_jr_nc_r8,        // 49
    mi_ld_sp_d16,       // 50
    mi_ld_hlm_a,        // 51
    mi_inc_sp,          // 52
    mi_inc_hl_address,  // 53
    mi_dec_hl_address,  // 54
    mi_ld_hl_d8,        // 55
    mi_scf,             // 56
    mi_jr_c_r8,         // 57
    mi_add_hl_sp,       // 58
    mi_ld_a_hlm,        // 59
    mi_dec_sp,          // 60
    mi_inc_a,           // 61
    mi_dec_a,           // 62
    mi_ld_a_d8,         // 63
    mi_ccf,             // 64

    // 0x40 - 0x47
    mi_ld_b,            // 65

    // 0x48 - 0x4F
    mi_ld_c,            // 66

    // 0x50 - 0x57
    mi_ld_d,            // 67

    // 0x58 - 0x5F
    mi_ld_e,            // 68

    // 0x60 - 0x67
    mi_ld_h,            // 69

    // 0x68 - 0x6F
    mi_ld_l,            // 70

    // 0x70 - 0x77
    mi_ld_hl,           // 71

    // 0x76
    mi_halt,            // 72

    // 0x78 - 0x7F
    mi_ld_a,            // 73

    // 0x80 - 0x87
    mi_add_a,           // 74

    // 0x88 - 0x8F
    mi_adc_a,           // 75

    // 0x90 - 0x97
    mi_sub,             // 76

    // 0x98 - 0x9F
    mi_sbc_a,           // 77

    // 0xA0 - 0xA7
    mi_and,             // 78

    // 0xA8 - 0xAF
    mi_xor,             // 79

    // 0xB0 - 0xB7
    mi_or,              // 80

    // 0xB8 - 0xBF
    mi_cp,              // 81

    // 0xC0 - 0xCF
    mi_ret_nz,          // 82
    mi_pop_bc,          // 83
    mi_jp_nz_a16,       // 84
    mi_jp_a16,          // 85
    mi_call_nz_a16,     // 86
    mi_push_bc,         // 87
    mi_add_a_d8,        // 88
    mi_rst_00h,         // 89
    mi_ret_z,           // 90
    mi_ret,             // 91
    mi_jp_z_a16,        // 92
    mi_prefix_cb,       // 93
    mi_call_z_a16,      // 94
    mi_call_a16,        // 95
    mi_adc_a_d8,        // 96
    mi_rst_08h,         // 97

    // 0xD0 - 0xDF
    mi_ret_nc,          // 98
    mi_pop_de,          // 99
    mi_jp_nc_a16,       // 100
    mi_call_nc_a16,     // 101
    mi_push_de,         // 102
    mi_sub_d8,          // 103
    mi_rst_10h,         // 104
    mi_ret_c,           // 105
    mi_reti,            // 106
    mi_jp_c_a16,        // 107
    mi_call_c_a16,      // 108
    mi_sbc_a_d8,        // 109
    mi_rst_18h,         // 110

    // 0xE0 - 0xEF
    mi_ldh_a8_a,        // 111
    mi_pop_hl,          // 112
    mi_ld_c_a,          // 113
    mi_push_hl,         // 114
    mi_and_d8,          // 115
    mi_rst_20h,         // 116
    mi_add_sp_r8,       // 117
    mi_jp_hl,           // 118
    mi_ld_a16_a,        // 119
    mi_xor_d8,          // 120
    mi_rst_28h,         // 121

    // 0xF0 - 0xFF
    mi_ldh_a_a8,        // 122
    mi_pop_af,          // 123
    mi_ld_a_c,          // 124
    mi_di,              // 125
    mi_push_af,         // 126
    mi_or_d8,           // 127
    mi_rst_30h,         // 128
    mi_ld_hl_sp_p_r8,   // 129
    mi_ls_sp_hl,        // 130
    mi_ld_a_a16,        // 131
    mi_ei,              // 132
    mi_cp_d8,           // 133
    mi_rst_38h          // 134
};