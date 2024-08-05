#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "cpu.h"
#include "structs.h"

// Used in testing
#define debugging false

void cpu_initialize(GB *gb) {
    gb->cpu.regs.A = 0;
    gb->cpu.regs.B = 0;
    gb->cpu.regs.C = 0;
    gb->cpu.regs.D = 0;
    gb->cpu.regs.E = 0;
    gb->cpu.regs.H = 0;
    gb->cpu.regs.L = 0;

    gb->cpu.regs.ZF = false;
    gb->cpu.regs.SF = false;
    gb->cpu.regs.HC = false;
    gb->cpu.regs.CA = false;

    gb->cpu.PC = 0x100;
    gb->cpu.SP = 0xFFFE;

    // Check out the Pan Doc on the start up sequence linked in day9.txt
    if (gb->cartridge.cgb == true) {
        gb->cpu.regs.A = 0x11;
    }
}

void print_cpu_stats(GB *gb) {
    uint8_t test_8_int = 8;
    uint16_t test_16_int = 16;

    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Cycle ---> %d\n", test_8_int);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("        ┏━━━━━━━━━━━━┓                  ┏━━━━━━━━━━━━┓\n");
    printf("        ┃     A      ┃        =         ┃     %d      ┃\n", test_8_int);
    printf("        ┗━━━━━━━━━━━━┛                  ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓\n");
    printf("┃     B      ┃ ┃     C      ┃ = ┃     %d      ┃ ┃     %d      ┃\n", test_8_int, test_8_int);
    printf("┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓\n");
    printf("┃     D      ┃ ┃     E      ┃ = ┃     %d      ┃ ┃     %d      ┃\n", test_8_int, test_8_int);
    printf("┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━┓\n");
    printf("┃     H      ┃ ┃     L      ┃ = ┃     %d      ┃ ┃     %d      ┃\n", test_8_int, test_8_int);
    printf("┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃             SP            ┃ = ┃             %d            ┃\n", test_16_int);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃             PC            ┃ = ┃             %d            ┃\n", test_16_int);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}