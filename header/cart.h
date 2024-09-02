#ifndef CART_H
#define CART_H

#include <iostream>

using namespace std;

class Cart
{
public:
    Cart(int id, const std::string& name, double price);
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    void setName(const std::string& name);
    void setPrice(double price);
private:
    int m_id;
    std::string m_name;
    double m_price;

};

#endif // CART_H
