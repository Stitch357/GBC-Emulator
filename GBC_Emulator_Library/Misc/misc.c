#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "misc.h"

int getch(void) {
    struct termios oldt, newt;
    
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);  // Get the current terminal attributes
    
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new terminal attributes
    
    ch = getchar();  // Read a character
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore old terminal attributes
    
    return ch;  // Return the character
}

void print_bits(uint16_t value) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0) {
            printf(" "); // Add a space every 4 bits for readability
        }
    }
    printf("\n");
}