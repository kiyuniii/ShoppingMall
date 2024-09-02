#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "cartmanager.h"

#include <map>
#include <vector>

class Product;

using namespace std;

class ProductManager
{
public:
    ProductManager();
    ProductManager(CartManager* cm);
    ~ProductManager();

    void readProductCSV();
    void writeProductCSV();

    //friend class CartManager;

    void inputProduct();
    void addProduct(Product *);
    void deleteProduct(int);
    void modifyProduct(int);
    Product* search(int);
    int makeId();
    void displayInfo();
    vector<string> parseCSV(istream&, char);
    bool displayMenu();

    //void saveList();
private:
    map<int, Product*> productList;
    map<int, Product*> cartList;
    
    CartManager* cartManager;
};

#endif // PRODUCTMANAGER_H
