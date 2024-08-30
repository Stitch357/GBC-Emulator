#ifndef MI_H
#define MI_H

#include "structs.h"

// Define main_instructions array
extern int indicies[0x100];
extern main_instruction_set main_instructions[0x86];

// General helper function
void increase_cycle_and_pc(GB* gb, uint8_t cc, uint8_t pc);

// Used in instructions 0x40 - 0xBF
void set_temp_register(GB* gb, uint8_t reg);
void access_register(GB* gb);

void cpu_sub_set_flags(GB* gb);
void set_inc_flags(GB* gb, uint16_t temp);

// 0x00 - 0x0F
void mi_nop(GB* gb);
void mi_ld_bc_d16(GB* gb);
void mi_ld_bc_a(GB* gb);
void mi_inc_bc(GB* gb);
void mi_inc_b(GB* gb);
void mi_dec_b(GB* gb);
void mi_ld_b_d8(GB* gb);
void mi_rlca(GB* gb);
void mi_ld_a16_sp(GB* gb);
void mi_add_hl_bc(GB* gb);
void mi_ld_a_bc(GB* gb);
void mi_dec_bc(GB* gb);
void mi_inc_c(GB* gb);
void mi_dec_c(GB* gb);
void mi_ld_c_d8(GB* gb);
void mi_rrca(GB* gb);

// 0x10 - 0x1F
void mi_stop_0(GB* gb);
void mi_ld_de_d16(GB* gb);
void mi_ld_de_a(GB* gb);
void mi_inc_de(GB* gb);
void mi_inc_d(GB* gb);
void mi_dec_d(GB* gb);
void mi_ld_d_d8(GB* gb);
void mi_rla(GB* gb);
void mi_jr_r8(GB* gb);
void mi_add_hl_de(GB* gb);
void mi_ld_a_de(GB* gb);
void mi_dec_de(GB* gb);
void mi_inc_e(GB* gb);
void mi_dec_e(GB* gb);
void mi_ld_e_d8(GB* gb);
void mi_rra(GB* gb);

// 0x20 - 0x2F
void mi_jr_nz_r8(GB* gb);
void mi_ld_hl_d16(GB* gb);
void mi_ld_hlp_a(GB* gb);
void mi_inc_hl_value(GB* gb);
void mi_inc_h(GB* gb);
void mi_dec_h(GB* gb);
void mi_ld_h_d8(GB* gb);
void mi_daa(GB* gb);
void mi_jr_z_r8(GB* gb);
void mi_add_hl_hl(GB* gb);
void mi_ld_a_hlp(GB* gb);
void mi_dec_hl_value(GB* gb);
void mi_inc_l(GB* gb);
void mi_dec_l(GB* gb);
void mi_ld_l_d8(GB* gb);
void mi_cpl(GB* gb);

// 0x30 - 0x3F
void mi_jr_nc_r8(GB* gb);
void mi_ld_sp_d16(GB* gb);
void mi_ld_hlm_a(GB* gb);
void mi_inc_sp(GB* gb);
void mi_inc_hl_address(GB* gb);
void mi_dec_hl_address(GB* gb);
void mi_ld_hl_d8(GB* gb);
void mi_scf(GB* gb);
void mi_jr_c_r8(GB* gb);
void mi_add_hl_sp(GB* gb);
void mi_ld_a_hlm(GB* gb);
void mi_dec_sp(GB* gb);
void mi_inc_a(GB* gb);
void mi_dec_a(GB* gb);
void mi_ld_a_d8(GB* gb);
void mi_ccf(GB* gb);

// 0x40 - 0x47
void mi_ld_b(GB* gb);

// 0x48 - 0x4F
void mi_ld_c(GB* gb);

// 0x50 - 0x57
void mi_ld_d(GB* gb);

// 0x58 - 0x5F
void mi_ld_e(GB* gb);

// 0x60 - 0x67
void mi_ld_h(GB* gb);

// 0x68 - 0x6F
void mi_ld_l(GB* gb);

// 0x70 - 0x77
void mi_ld_hl(GB* gb);

// 0x76
void mi_halt(GB* gb);

// 0x78 - 0x7F
void mi_ld_a(GB* gb);

// 0x80 - 0x87
void mi_add_a(GB* gb);

// 0x88 - 0x8F
void mi_adc_a(GB* gb);

// 0x90 - 0x97
void mi_sub(GB* gb);

// 0x98 - 0x9F
void mi_sbc_a(GB* gb);

// 0xA0 - 0xA7
void mi_and(GB* gb);

// 0xA8 - 0xAF
void mi_xor(GB* gb);

// 0xB0 - 0xB7
void mi_or(GB* gb);

// 0xB8 - 0xBF
void mi_cp(GB* gb);

// 0xC0 - 0xCF
void mi_ret_nz(GB* gb);
void mi_pop_bc(GB* gb);
void mi_jp_nz_a16(GB* gb);
void mi_jp_a16(GB* gb);
void mi_call_nz_a16(GB* gb);
void mi_push_bc(GB* gb);
void mi_add_a_d8(GB* gb);
void mi_rst_00h(GB* gb);
void mi_ret_z(GB* gb);
void mi_ret(GB* gb);
void mi_jp_z_a16(GB* gb);
void mi_prefix_cb(GB* gb);
void mi_call_z_a16(GB* gb);
void mi_call_a16(GB* gb);
void mi_adc_a_d8(GB* gb);
void mi_rst_08h(GB* gb);

// 0xD0 - 0xDF
void mi_ret_nc(GB* gb);
void mi_pop_de(GB* gb);
void mi_jp_nc_a16(GB* gb);
void mi_call_nc_a16(GB* gb);
void mi_push_de(GB* gb);
void mi_sub_d8(GB* gb);
void mi_rst_10h(GB* gb);
void mi_ret_c(GB* gb);
void mi_reti(GB* gb);
void mi_jp_c_a16(GB* gb);
void mi_call_c_a16(GB* gb);
void mi_sbc_a_d8(GB* gb);
void mi_rst_18h(GB* gb);

// 0xE0 - 0xEF
void mi_ldh_a8_a(GB* gb);
void mi_pop_hl(GB* gb);
void mi_ld_c_a(GB* gb);
void mi_push_hl(GB* gb);
void mi_and_d8(GB* gb);
void mi_rst_20h(GB* gb);
void mi_add_sp_r8(GB* gb);
void mi_jp_hl(GB* gb);
void mi_ld_a16_a(GB* gb);
void mi_xor_d8(GB* gb);
void mi_rst_28h(GB* gb);

// 0xF0 - 0xFF
void mi_ldh_a_a8(GB* gb);
void mi_pop_af(GB* gb);
void mi_ld_a_c(GB* gb);
void mi_di(GB* gb);
void mi_push_af(GB* gb);
void mi_or_d8(GB* gb);
void mi_rst_30h(GB* gb);
void mi_ld_hl_sp_p_r8(GB* gb);
void mi_ls_sp_hl(GB* gb);
void mi_ld_a_a16(GB* gb);
void mi_ei(GB* gb);
void mi_cp_d8(GB* gb);
void mi_rst_38h(GB* gb);

#endif