#ifndef CARTMANAGER_H
#define CARTMANAGER_H

#include <fstream>
#include <map>
#include <vector>

class Cart;

using namespace std;

class CartManager
{
public:
    CartManager();
    ~CartManager();

    vector<string> parseCSV(istream &file, char);
    void readCartCSV();
    void writeCartCSV();        

    bool displayMenu();
    void displayInfo();
    void addCart();
    void deleteCart(int);
    void modifyCart(int);

    void updateCartItem(int id, const string& name, double price);

    Cart* search(int);
    void saveList();

private:
    map<int, Cart*> cartList;
};


#endif//CARTMANAGER_H