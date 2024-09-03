#include <iostream>

#include "mainMenu.h"
#include "shoppingmanager.h"
#include "clientmanager.h"
#include "productmanager.h"
#include "cartmanager.h"
#include <string>
#include <cstdlib>
#include <memory>

unique_ptr<Main> m = make_unique<Main>();
using namespace string_literals;

int main()
{
    /* 터미널 크기 : 100(가로) x 24(세로) */
    int terminalSize = system("printf '\\e[8;24;120t'"); 
    if (terminalSize != 0) return 1;

    LoginManager l;
    while(l.displayMenu());

    return 0;
}
