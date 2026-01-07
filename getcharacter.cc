#include <termios.h>
#include <unistd.h>
#include <cstdio>

char getcharacter()
{
    char c = 0;
    char asterisk = '*';
    char bs = 0x8;
    char sp = ' ';
    struct termios old = {0};
    
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    
    if (read(STDIN_FILENO, &c, 1) < 0)
        perror("read()");

    if (c == 8 || c == 127 || c == 10 || c == 32) // BSP || DEL || RET || SPC
    {
        write(STDOUT_FILENO, &bs, 1); // BS
        write(STDOUT_FILENO, &sp, 1); // SP
        write(STDOUT_FILENO, &bs, 1); // BS
    }
    else
    {
        write(STDOUT_FILENO, &c, 1);        // show entered character
        usleep(100000);                     // wait 0.1 sec
        write(STDOUT_FILENO, &bs, 1);       // delete character from terminal
        write(STDOUT_FILENO, &asterisk, 1); // show asterisk
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return (c);
}
