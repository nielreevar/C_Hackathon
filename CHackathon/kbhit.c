#include "hackathonapp.h"

// Function to configure terminal to non-canonical mode
void initTermios(int echo)
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt); // get current terminal state
    newt.c_lflag &= ~ICANON; // disable canonical mode
    if (echo) 
    {
        newt.c_lflag |= ECHO; // enable echo
    } else 
    {
        newt.c_lflag &= ~ECHO; // disable echo
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set new terminal state
}

// Function to restore terminal to its previous state
void resetTermios()
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt); // get current terminal state
    newt.c_lflag |= ICANON; // enable canonical mode
    newt.c_lflag |= ECHO; // enable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // set new terminal state
}

// Function to check if a key has been pressed
int kbhit() 
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}