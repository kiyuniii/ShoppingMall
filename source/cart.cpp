#include "cart.h"


Cart::Cart(int id, const string &name, double price) : m_id(id), m_name(name), m_price(price) {}

int Cart::getId() const
{
    return m_id;
}

string Cart::getName() const
{
    return m_name;
}

double Cart::getPrice() const
{
    return m_price;
}

void Cart::setName(const string &name)
{
    m_name = name;
}

void Cart::setPrice(double price)
{
    m_price = price;
}

