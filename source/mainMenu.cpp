#include "mainMenu.h"

Main::Main() { }
Main::~Main() { }

using namespace std::string_literals;

bool Main::displayMenu() {    
    int option = 0;
    string mainDisplay = R"delimiter(*** 쇼핑몰 프로그램 ***
1. 쇼핑몰
2. 고객 관리
3. 제품 관리
4. 카트 목록
5. quit
어떤 메뉴를 선택하시겠습니까?)delimiter";

    while(true) {
        cout << "\033[2J\033[1;1H";
        cout << mainDisplay;

        ShoppingManager* sm = new ShoppingManager();
        ClientManager* cm = new ClientManager();
        ProductManager* pm = new ProductManager();
        CartManager* tm = new CartManager();

        if( !(cin >> option) ) {
            cout << '\n' << "Wrong input... try again." << '\n';
            cin.clear();
            cin.ignore();
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
            cout << "올바른 옵션을 선택해주세요." << '\n';
            cin.ignore();
            getchar();
            cin.clear();
            continue;
        }
    }
    return true;
}