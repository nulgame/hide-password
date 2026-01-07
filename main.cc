// #include <string>
#include <iostream>

#include "getcharacter.h"

// test driver
std::string get_admin_password()
{
    char password[65] = {0};
    char c = 0;
    int i = 0;

    while (10 != (c = getcharacter())) // until RETURN pressed
    {
        if (i > 64) // max password length
            break;

        if (c > 32 && c < 127) // allowed only ASCII characters
        {
            password[i++] = c;
        }
        else if (c == 8 || c == 127) // BS and DEL
        {
            i--; // if BS pressed -> ungetchar (back)
            i = i < 0 ? 0 : i;
        }
    }
    password[i] = 0;
    return password;
}


int main()
{
    std::string password;

    while (0 == password.length()) {
        std::cout << "Enter the password (will be semi masked):" << std::endl;
        password = get_admin_password();
        if (0 == password.length()) {
            std::cout << "No password provided!" << std::endl;
        } else {
            std::cout << "Password is: " << password << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
