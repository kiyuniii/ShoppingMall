#ifndef __CARTMANAGER_H__
#define __CARTMANAGER_H__

#include <iostream>
#include <vector>
#include <map>

/* Login/User -> CartManager */
#include "login.h"
#include "user.h" 
class Login;
class User;

/* Cart -> CartManager */
#include "cart.h"
class Cart;

/* Login -> CartManager */
#include "login.h"
class Login;

#include "productmanager.h"

class UserCart {    //Cart usercart[];
public:
    UserCart(int);  //id(key)별로 Cart
    ~UserCart();

private:
    int m_id;
};

class CartManager {
public:
    CartManager(int, int);
    CartManager();;
    ~CartManager();

    void readCartCSV(int, int);
    void writeCartCSV(int, int);
    void readProductCSV();
    void writeProductCSV();

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
    //vector<map<int, pair<Product*, Cart*>>> shoppingCart;

    int userID, productID;
};

#endif//__CARTMANAGER_H__