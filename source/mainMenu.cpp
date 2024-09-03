#include "mainMenu.h"
#include "shoppingmanager.h"
#include "clientmanager.h"
#include "productmanager.h"
#include "cartmanager.h"

Main::Main() { }
Main::~Main() { }

using namespace std::string_literals;

bool Main::displayMenu() {
    int option = 0;
    int userId = 0;  // 임의로 사용자 ID를 0으로 설정 (사용자 ID를 다르게 설정할 수 있습니다)
    string username; // 사용자의 이름을 저장할 변수
    cout << "Enter your username: ";
    cin >> username;

    string mainDisplay = R"delimiter(*** 쇼핑몰 프로그램 ***
1. 쇼핑몰
2. 고객 관리
3. 제품 관리
4. 카트 목록
5. quit
어떤 메뉴를 선택하시겠습니까?)delimiter";

    while (true) {
        cout << "\033[2J\033[1;1H";
        cout << mainDisplay;

        ShoppingManager* sm = new ShoppingManager();
        ClientManager* cm = new ClientManager();
        ProductManager* pm = new ProductManager();
        CartManager* tm = new CartManager(userId, username);  // userId와 username을 전달하도록 수정

        if (!(cin >> option)) {
            cout << '\n' << "Wrong input... try again." << '\n';
            cin.clear();
            cin.ignore();
        }

        switch (option) {
            case 1:
                while (sm->displayMenu());
                delete sm;
                break;
            case 2:
                while (cm->displayMenu());
                delete cm;
                break;
            case 3:
                while (pm->displayMenu());
                delete pm;
                break;
            case 4:
                while (tm->displayMenu(userId, username));  // userId와 username을 전달하도록 수정
                delete tm;
                break;
            case 5:
                delete sm;
                delete cm;
                delete pm;
                delete tm;
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
