#ifndef __CARTMANAGER_H__
#define __CARTMANAGER_H__

#include <iostream>
#include <vector>
#include <map>

/* 필요한 헤더 포함 */
#include "login.h"
#include "user.h"
#include "cart.h"
#include "productmanager.h"

class UserCart {
public:
    UserCart(int);
    ~UserCart();

private:
    int m_id;
};

class CartManager {
public:
    CartManager(int, int);
    CartManager();
    ~CartManager();

    void readCartCSV(int, int);
    void writeCartCSV(int, int);
    void readProductCSV();
    void writeProductCSV();

    void initializeUserLoginList();
    void initializeUserCartList();
    vector<string> parseCSV(istream&, char);

    bool displayMenu(int);

    void displayInfo(int);
    void inputCart(int);
    void deleteCart(int, int);
    void modifyCart(int, int);

    string cartListUserPath(int, int);

    static const string productListPath;

private:
    ProductManager productManager;

    map<int, Product*> productList;
    vector<map<int, Login*>> userLoginList;
    vector<map<int, Cart*>> userCartList;

    int userID, productID;
};

#endif //__CARTMANAGER_H__
