#include "mainmenu.h"

#include <iostream>

using namespace std;

MainMenu::MainMenu() { }

bool MainMenu::displayMenu(int id) {
    int ch;
    /* ADMIN */
    if(id == 0) {

        while(true) {
            ShoppingManager* shoppingManager = new ShoppingManager;
            UserManager* userManager = new UserManager;
            ProductManager* productManager = new ProductManager;

            cout << "\033[2J\033[1;1H";
            cout << "===============================" << endl
                 << "=            ADMIN             =" << endl
                 << "===============================" << endl
                 << " 1. 쇼핑몰                      " << endl
                 << " 2. 고객관리                     " << endl
                 << " 3. 제품관리                     " << endl
                 << " 4. 로그아웃                     " << endl
                 << "================================" << endl;
            cout << " >> "; cin >> ch;    

            switch(ch) {
                case 1: 
                    shoppingManager->displayMenu();
                    delete shoppingManager;
                    break;
                case 2:
                    userManager->displayMenu(id);   //분기(ADMIN/CLIENT)
                    delete userManager;
                    break;
                case 3:
                    productManager->displayMenu();
                    delete productManager;
                    break;
                case 4:
                    return false;
                default:
                    cout << "옵션을 다시 선택해주세요." << endl;
                    continue;
            }
        }
    } 
    
    /* CLIENT */
    if (id != 0) {
        while (true) {
            ShoppingManager* shoppingManager = new ShoppingManager;
            UserManager* userManager = new UserManager;
            CartManager* cartManager = new CartManager(id);

            cout << "\033[2J\033[1;1H";
            cout << "===============================" << endl
                 << "=           CLIENT            =" << endl
                 << "===============================" << endl
                 << " 1. 쇼핑몰                      " << endl
                 << " 2. 개인정보 수정                 " << endl
                 << " 3. 장바구니                     " << endl
                 << " 4. 로그아웃                     " << endl
                 << "================================" << endl;
            cout << " >> "; cin >> ch;    

            switch(ch) {
                case 1: 
                    shoppingManager->displayMenu();
                    delete shoppingManager;
                    break;
                case 2:
                    userManager->displayMenu(id);   //분기(ADMIN/CLIENT)
                    delete userManager;
                    break;
                case 3:
                    cartManager->displayMenu(id);   //key를 받아서 멤버함수의 key로 사용
                    delete cartManager;
                    break;
                case 4:
                    delete shoppingManager;
                    delete userManager;
                    delete cartManager;
                    return false;  // 프로그램 종료
                default:
                    cout << "옵션을 다시 선택해주세요." << endl;
                    cin.ignore();
                    getchar();
                    break;  // 잘못된 입력이 있는 경우 루프 유지
            }
        }
    } 

    /* ADMIN */
    // 다른 부분은 변경하지 않아도 됩니다.
    
    return false;
}