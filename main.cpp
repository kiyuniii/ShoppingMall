#include <iostream>
#include "shoppingmanager.h"
#include "clientmanager.h"
#include "productmanager.h"
#include "cartmanager.h"
#include <string>
#include <cstdlib>

using namespace std::string_literals;

bool Display() {
    int option = 0;
    string mainDisplay = R"delimiter(*** 쇼핑몰 프로그램 ***
1. 쇼핑몰
2. 고객 관리
3. 제품 관리
4. 카트 목록
5. quit
어떤 메뉴를 선택하시겠습니까?)delimiter";

    cout << "\033[2J\033[1;1H";
    std::cout << mainDisplay;

    ShoppingManager* sm = new ShoppingManager();
    ClientManager* cm = new ClientManager();
    ProductManager* pm = new ProductManager();
    CartManager* tm = new CartManager();

    if( !(std::cin >> option) ) {
        std::cout << '\n' << "Wrong input... try again." << '\n';
        std::cin.clear();
        std::cin.ignore();
    }

    switch(option) {
    case 1:
        while(sm->displayMenu());
        delete sm;
        break;
    case 2:
        while(cm->displayMenu());
        delete cm;
        break;
    case 3:
        while(pm->displayMenu());
        delete pm;
        break;
    case 4:
        while(tm->displayMenu());
        delete tm;
        break;
    case 5:
        return false;
    default:
        std::cout << "put the right number." << '\n';
        std::cin.ignore();
        getchar();
        cin.clear();

    }
    return true;
}

int main()
{
    /* 터미널 크기 : 80(가로) x 24(세로) */
    int terminalSize = system("printf '\\e[8;200;200t'"); 
    if (terminalSize != 0) return 1;

    while(Display());
    return 0;
}
