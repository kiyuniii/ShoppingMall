#ifndef __USERMANAGER_H__
#define __USERMANAGER_H__

#include <iostream>
#include <vector>
#include <map>

/* User -> UserManger */
#include "user.h"
class User;
#include "login.h"

class UserManager {
public:
    UserManager();
    ~UserManager();

    void readUserCSV();
    void writeUserCSV();

    vector<string> parseCSV(istream&, char);

    bool displayMenu(int);  //ADMIN, CLIENT
    void displayInfo();
    void displayUser(int);
    bool deleteUser(int);
    void modifyUser(int);
    void addUser(int);
    int makeId();
    
    static const string loginListPath;
    static const string userListPath;

private:
    map<int, Login*> loginList;
    map<int, User*> userList;
};

#endif//__USERMANAGER_H__