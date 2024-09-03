#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include "loginmanager.h"

#include <map>
#include <vector>

class Client;
class LoginManager;
using namespace std;

class ClientManager {
public:
    ClientManager();
    ~ClientManager();

    void readLoginCSV();
    void writeLoginCSV();

    void inputClient();
    void deleteClient(int);
    void modifyClient(int);
    Client* search(int);

    int makeId();
    void displayInfo();
    vector<string> parseCSV(istream&, char);

    bool displayMenu();

    static const string clientListPath;

    map<int, Client*> clientList;
private:
};

#endif    // __CLIENT_MANAGER_H__


