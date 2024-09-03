#ifndef __USERMANAGER_H__
#define __USERMANAGER_H__

#include <iostream>
#include <vector>
#include <map>

/* User -> UserManger */
#include "user.h"
class User;

class UserManager {
public:
    UserManager();
    ~UserManager();

    void readUserCSV();
    void writeUserCSV();
    vector<string> parseCSV(istream&, char);

    void displayMenu(int);  //ADMIN, CLIENT
    void displayInfo();
    void displayUser(int);
    void deleteUser(int);
    void modifyUser(int);
    
    static const string userListPath;

private:
    map<int, User*> userList;
};

#endif//__USERMANAGER_H__