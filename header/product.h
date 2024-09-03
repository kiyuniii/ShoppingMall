#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

using namespace std;

class Product
{
public:
    Product();
    Product(int pid);
    Product(int pid, const string& name, int price);

    int getPid() const;
    string getName() const;
    int getPrice() const;
    
    void setPid(int);
    void setName(string);
    void setPrice(int);

private:
    int m_pid;
    string m_name;
    int m_price;
};

#endif // PRODUCT_H
