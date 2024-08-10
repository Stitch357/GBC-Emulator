#ifndef MI_H
#define MI_H

void access_register(GB *gb);

// 0x00 - 0x0F
void mi_nop();
void mi_ld_bc_d16();
void mi_ld_bc_a();
void mi_inc_bc();
void mi_inc_b();
void mi_dec_b();
void mi_ld_b_d8();
void mi_rlca();
void mi_ld_a16_sp();
void mi_add_hl_bc();
void mi_ld_a_bc();
void mi_dec_bc();
void mi_inc_c();
void mi_dec_c();
void mi_ld_c_d8();
void mi_rrca();

// 0x10 - 0x1F
void mi_stop_0();
void mi_ld_de_d16();
void mi_ld_de_a();
void mi_inc_de();
void mi_inc_d();
void mi_dec_d();
void mi_ld_d_d8();
void mi_rla();
void mi_jr_r8();
void mi_add_hl_de();
void mi_ld_a_de();
void mi_dec_de();
void mi_inc_e();
void mi_dec_e();
void mi_ld_e_d8();
void mi_rra();

// 0x20 - 0x2F
void mi_jr_nz_r8();
void mi_ld_hl_d16();
void mi_ld_hlp_a();
void mi_inc_hl();
void mi_inc_h();
void mi_dec_h();
void mi_ld_h_d8();
void mi_daa();
void mi_jr_z_r8();
void mi_add_hl_hl();
void mi_ld_a_hlp();
void mi_dec_hl();
void mi_inc_l();
void mi_dec_l();
void mi_ld_l_d8();
void mi_cpl();

// 0x30 - 0x3F
// 0x40 - 0x4F
// 0x50 - 0x5F
// 0x60 - 0x6F
// 0x70 - 0x7F
// 0x80 - 0x8F
// 0x90 - 0x9F
// 0xA0 - 0xAF
// 0xB0 - 0xBF
// 0xC0 - 0xCF
// 0xD0 - 0xDF
// 0xE0 - 0xEF
// 0xF0 - 0xFF

#endif