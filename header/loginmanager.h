#ifndef __LOGINMANAGER_H__
#define __LOGINMANAGER_H__

#include <vector>
#include <map>
using namespace std;

/* LoginManager --> MainMenu (연결) */
#include "mainmenu.h"
/* LoginManager --> UserManager (연결) */
#include "usermanager.h"

/* Login -> LoginManager */
#include "login.h"
class Login;

class LoginManager {
public:
    LoginManager();
    ~LoginManager();
    
    void readLoginCSV();
    void writeLoginCSV();
    vector<string> parseCSV(istream&, char);

    void displayMenu(); 
    int checkLogin();
    int checkRegister(string); //UserManager::addInfo
    string tempUsername(string);
    void addPassword(int, string);

    int makeId();

    static const string loginListPath;
    //static const string clientListpath;

private:
    MainMenu mainMenu;
    UserManager userManager;
    map<int, Login*> loginList;
};


#endif//__LOGINMANAGER_H__