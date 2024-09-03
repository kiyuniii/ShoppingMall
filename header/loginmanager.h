#ifndef __LOGINMANAGER_H__
#define __LOGINMANAGER_H__

#include "login.h"
#include "clientmanager.h"
#include "client.h"
#include "mainMenu.h"

#include <map>
#include <vector>
#include <iostream>
#include <string>

class ClientManager;

using namespace std;

class LoginManager {
public:
    LoginManager();
    ~LoginManager();

    void readLoginCSV();
    void writeLoginCSV();
    void writeClientCSV();
    vector<string> parseCSV(istream&, char);

    bool displayMenu(); //로그인 화면
    bool checkLogin();
    string checkRegister();
    void addInfo(const string&);

    Login* search(int);
    //void displayInfo(); //현재 사용자의 정보 출력

    int makeId();

    /* checkLogin() */
    /*  - clientlist.csv와 idInput 비교, 맞으면 true 
        - 일치하는 map있으면 true, 없다면 false 반환
        - true  -> main.cpp의 Display()로 연결
        - false -> 에러메시지 + 재입력요구 (while 루프)  */
    
    static const string loginListPath;
    static const string clientListPath;

private:
    map<int, pair<Login*, Client*>> loginClientInfo;
    map<int, Login*> loginList;
};


#endif//__LOGINMANAGER_H__