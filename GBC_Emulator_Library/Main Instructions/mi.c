#include "cpu.h"
#include "structs.h"

// Access proper registers
void access_register(GB *gb) {   
    char* registers[8] = { "B", "C", "D", "E", "H", "L", "HL", "A" };
}

// 0x00
void mi_nop() {

}

// 0x01

void mi_ld_bc_d16() {

}

// 0x02
void mi_ld_bc_a() {

}

// 0x03
void mi_inc_bc() {

}

// 0x04
void mi_inc_b() {

}

// 0x05
void mi_dec_b() {

}

// 0x06
void mi_ld_b_d8() {

}

// 0x07
void mi_rlca() {

}

// 0x08
void mi_ld_a16_sp() {

}

// 0x09
void mi_add_hl_bc() {

}

// 0x0A
void mi_ld_a_bc() {

}

// 0x0B
void mi_dec_bc() {

}

// 0x0C
void mi_inc_c() {

}

// 0x0D
void mi_dec_c() {

}

// 0x0E
void mi_ld_c_d8() {

}

// 0x0F
void mi_rrca() {

}

// 0x10
void mi_stop_0() {

}

// 0x11
void mi_ld_de_d16() {

}

// 0x12
void mi_ld_de_a() {

}

// 0x13
void mi_inc_de() {

}

// 0x14
void mi_inc_d() {

}

// 0x15
void mi_dec_d() {

}

// 0x16
void mi_ld_d_d8() {

}

// 0x17
void mi_rla() {

}

// 0x18
void mi_jr_r8() {

}

// 0x19
void mi_add_hl_de() {

}

// 0x1A
void mi_ld_a_de() {

}

// 0x1B
void mi_dec_de() {

}

// 0x1C
void mi_inc_e() {

}

// 0x1D
void mi_dec_e() {

}

// 0x1E
void mi_ld_e_d8() {

}

// 0x1F
void mi_rra() {

}

// 0x20
void mi_jr_nz_r8() {

}

// 0x21
void mi_ld_hl_d16() {

}

// 0x22
void mi_ld_hlp_a() {

}

// 0x23
void mi_inc_hl() {

}

// 0x24
void mi_inc_h() {

}

// 0x25
void mi_dec_h() {

}

// 0x26
void mi_ld_h_d8() {

}

// 0x27
void mi_daa() {

}

// 0x28
void mi_jr_z_r8() {

}

// 0x29
void mi_add_hl_hl() {

}

// 0x2A
void mi_ld_a_hlp() {

}

// 0x2B
void mi_dec_hl() {

}

// 0x2C
void mi_inc_l() {

}

// 0x2D
void mi_dec_l() {

}

// 0x2E
void mi_ld_l_d8() {

}

// 0x2F
void mi_cpl() {

}

// -----

// 0x30
void mi_jr_nc_r8() {

}

// 0x31
void mi_ld_sp_d16() {

}

// 0x32
void mi_ld_hlm_a() {

}

// 0x33
void mi_inc_sp() {

}

// 0x34
void mi_inc_hl() {

}

// 0x35
void mi_dec_hl() {

}

// 0x36
void mi_ld_hl_d8() {

}

// 0x37
void mi_scf() {

}

// 0x38
void mi_jr_c_r8() {
    
}

// 0x39
void mi_add_hl_sp() {

}

// 0x3A
void mi_ld_a_hlm() {

}

// 0x3B
void mi_dec_sp() {

}

// 0x3C
void mi_inc_a() {

}

// 0x3D
void mi_dec_a() {

}

// 0x3E
void mi_ld_a_d8() {

}

// 0x3F
void mi_ccf() {

}

// 0x40 - B
void mi_ld_b() {

}

// 0x41 - C
// 0x42 - D
// 0x43 - E
// 0x44 - H
// 0x45 - L
// 0x46 - HL
// 0x47 - A

// 0x48 - B
void mi_ld_c() {

}

// 0x49 - C
// 0x4A - D
// 0x4B - E
// 0x4C - H
// 0x4D - L
// 0x4E - HL
// 0x4F - A

// 0x50 - B
void mi_ld_d() {

}

// 0x51 - C
// 0x52 - D
// 0x53 - E
// 0x54 - H
// 0x55 - L
// 0x56 - HL
// 0x57 - A

// 0x58 - B
void mi_ld_e() {

}

// 0x59 - C
// 0x5A - D
// 0x5B - E
// 0x5C - H
// 0x5D - L
// 0x5E - HL
// 0x5F - A

// 0x60 - B
void mi_ld_h() {

}

// 0x61 - C
// 0x62 - D
// 0x63 - E
// 0x64 - H
// 0x65 - L
// 0x66 - HL
// 0x67 - A

// 0x68 - B
void mi_ld_l() {

}

// 0x69 - C
// 0x6A - D
// 0x6B - E
// 0x6C - H
// 0x6D - L
// 0x6E - HL
// 0x6F - A

// 0x70 - B
void mi_ld_hl() {

}

// 0x71 - C
// 0x72 - D
// 0x73 - E
// 0x74 - H
// 0x75 - L
// 0x76 - HL
// 0x77 - A

// 0x78 - B
void mi_ld_a() {

}

// 0x79 - C
// 0x7A - D
// 0x7B - E
// 0x7C - H
// 0x7D - L
// 0x7E - HL
// 0x7F - A

// 0x80 - B
void mi_add_a() {

}

// 0x81 - C
// 0x82 - D
// 0x83 - E
// 0x84 - H
// 0x85 - L
// 0x86 - HL
// 0x87 - A

// 0x88 - B
void mi_adc_a() {

}

// 0x89 - C
// 0x8A - D
// 0x8B - E
// 0x8C - H
// 0x8D - L
// 0x8E - HL
// 0x8F - A

// 0x90 - B
void mi_sub() {

}

// 0x91 - C
// 0x92 - D
// 0x93 - E
// 0x94 - H
// 0x95 - L
// 0x96 - HL
// 0x97 - A

// 0x98 - B
void mi_sbc_a() {

}

// 0x99 - C
// 0x9A - D
// 0x9B - E
// 0x9C - H
// 0x9D - L
// 0x9E - HL
// 0x9F - A

// 0xA0 - B
void mi_and() {

}

// 0xA1 - C
// 0xA2 - D
// 0xA3 - E
// 0xA4 - H
// 0xA5 - L
// 0xA6 - HL
// 0xA7 - A

// 0xA8 - B
void mi_xor() {

}

// 0xA9 - C
// 0xAA - D
// 0xAB - E
// 0xAC - H
// 0xAD - L
// 0xAE - HL
// 0xAF - A

// 0xB0 - B
void mi_or() {

}

// 0xB1 - C
// 0xB2 - D
// 0xB3 - E
// 0xB4 - H
// 0xB5 - L
// 0xB6 - HL
// 0xB7 - A

// 0xB8 - B
void mi_cp() {

}

// 0xB9 - C
// 0xBA - D
// 0xBB - E
// 0xBC - H
// 0xBD - L
// 0xBE - HL
// 0xBF - A

// 0xC0
void mi_ret_nz() {

}

// 0xC1
void mi_pop_bc() {

}

// 0xC2
void mi_jp_nz_a16() {

}

// 0xC3
void mi_jp_a16() {

}

// 0xC4
void mi_call_nz_a16() {

}

// 0xC5
void mi_push_bc() {

}

// 0xC6
void mi_add_a_d8() {

}

// 0xC7
void mi_rst_00h() {

}

// 0xC8
void mi_ret_z() {

}

// 0xC9
void mi_ret() {

}

// 0xCA
void mi_jp_z_a16() {

}

// 0xCB
void mi_prefix_cb() {

}

// 0xCC
void mi_call_z_a16() {

}

// 0xCD
void mi_call_a16() {

}

// 0xCE
void mi_adc_a_d8() {

}

// 0xCF
void mi_rst_08h() {

}

// 0xD0
void mi_ret_nc() {

}

// 0xD1
void mi_pop_de() {

}

// 0xD2
void mi_jp_nc_a16() {

}

// 0xD3 - Empty

// 0xD4
void mi_call_nc_a16() {

}

// 0xD5
void mi_push_de() {

}

// 0xD6
void mi_sub_d8() {

}

// 0xD7
void mi_rst_10h() {

}

// 0xD8
void mi_ret_c() {

}

// 0xD9
void mi_reti() {

}

// 0xDA
void mi_jp_c_a16() {

}

// 0xDB - Empty

// 0xDC
void mi_call_c_a16() {

}

// 0xDD - Empty


// 0xDE
void mi_sbc_a_d8() {

}

// 0xDF
void mi_rst_18h() {

}

// 0xE0
void mi_ldh_a8_a() {

}

// 0xE1
void mi_pop_hl() {

}

// 0xE2
void mi_ld_c_a() {

}

// 0xE3 - Empty
// 0xE4 - Empty

// 0xE5
void mi_push_hl() {

}

// 0xE6
void mi_and_d8() {

}

// 0xE7
void mi_rst_20h() {

}

// 0xE8
void mi_add_sp_r8() {

}

// 0xE9
void mi_jp_hl() {

}

// 0xEA
void mi_ld_a16_a() {

}

// 0xEB - Empty
// 0xEC - Empty
// 0xED - Empty

// 0xEE
void mi_xor_d8() {

}

// 0xEF
void mi_rst_28h() {

}

// 0xF0
void mi_ldh_a_a8() {

}

// 0xF1
void mi_pop_af() {

}

// 0xF2
void mi_ld_a_c() {

}

// 0xF3
void mi_di() {

}

// 0xF4 - Empty

// 0xF5
void mi_push_af() {

}

// 0xF6
void mi_or_d8() {

}

// 0xF7
void mi_rst_30h() {

}

// 0xF8
void mi_ld_hl_sp_p_r8() {

}

// 0xF9
void mi_ls_sp_hl() {

}

// 0xFA
void mi_ld_a_a16() {

}

// 0xFB
void mi_ei() {

}

// 0xFC - Empty
// 0xFD - Empty

// 0xFE
void mi_cp_d8() {

}

// 0xFF
void mi_rst_38h() {

}