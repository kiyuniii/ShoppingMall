#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "shoppingmanager.h"
#include "usermanager.h"
#include "productmanager.h"
#include "cartmanager.h"

class MainMenu {
public:
    MainMenu();

    bool displayMenu(int);
    
private:
    /* MainMenu의 lifetime에 종속 */
};

//Mainmenu admin; Mainmenu client;

#endif//__MAINMENU_H__