#ifndef __CARTMANAGER_H__
#define __CARTMANAGER_H__

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

    void readCartCSV();
    void writeCartCSV();        
    vector<string> parseCSV(istream &file, char);

    bool displayMenu();
    void displayInfo();

    void inputCart();
    void deleteCart(int);
    void modifyCart(int);

    Cart* search(int);
    //void saveList();

    static const string productListPath;
    static const string cartListPath;

private:
    map<int, Cart*> cartList;
};


#endif//C__ARTMANAGER_H__