#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

using namespace std;

class Product
{
public:
    Product(int id, const std::string& name, int price);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    void setName(const std::string& name);
    void setPrice(int price);
private:
    int m_id;
    std::string m_name;
    int m_price;

};

#endif // PRODUCT_H
