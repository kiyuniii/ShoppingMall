#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <map>
#include <vector>

class Product;

using namespace std;

class ProductManager
{
public:
    ProductManager();
    ~ProductManager();

    void readProductCSV();
    void writeProductCSV();
    vector<string> parseCSV(istream&, char);

    bool displayMenu();
    stringstream displayInfo();
    void deleteProduct(int);
    void modifyProduct(int);

    void inputProduct();
    Product* search(int);
    int makeId();

    static const string productListPath;
    static const string cartListPath;
    //void saveList();
private:
    map<int, Product*> productList;
};

#endif // PRODUCTMANAGER_H
