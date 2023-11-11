#include <iostream>
#include "PasswordManager.h"

void welcome()
{
    std::cout << "========================== PASSWORD MANAGER v1.0 ==========================" << std::endl;
    std::cout << "projekt na potrzeby zajec Programowanie w Jezykach C i C++" << std::endl;
    std::cout << "by Cezary Danilowski, s25901" << std::endl;

    for (int i = 0; i < 4; i++)
        std::cout << "===" << std::endl;
}

int main() {
    welcome();
    PasswordManager passwordManager = PasswordManager();

    return 0;
}