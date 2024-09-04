#ifndef __PRODUCTMANAGER_H__
#define __PRODUCTMANAGER_H__

#include <map>
#include <vector>
#include <iostream>

using namespace std;

/* Product -> ProductManager */
#include "product.h"
class Product;

class ProductManager  {
public:
    ProductManager();
    ~ProductManager();

    void readProductCSV();
    void writeProductCSV();
    vector<string> parseCSV(istream&, char);

    bool displayMenu();
    void displayInfo();
    void deleteProduct(int);
    void modifyProduct(int);

    void inputProduct();
    int makePid();

    static const string productListPath;
    //const string cartListPath;
    
private:
    map<int, Product*> productList;
};

#endif // __PRODUCTMANAGER_H__
