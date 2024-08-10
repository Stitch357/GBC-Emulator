#include <stdio.h>
#include <stdlib.h>
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