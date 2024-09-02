#ifndef CART_H
#define CART_H

#include <iostream>

using namespace std;

class Cart
{
public:
    Cart(int id, int num);

    int getId() const;
    int getNum() const;
    void setId(int id);
    void setNum(int num);
    
private:
    int m_id;
    int m_num;
};

#endif // CART_H
