#include "cart.h"


Cart::Cart(int id, int num) : m_id(id), m_num(num) { }

int Cart::getId() const {
    return m_id;
}
int Cart::getNum() const {
    return m_num;
}
void Cart::setId(int id) {
    m_id = id;
}
void Cart::setNum(int num) {
    m_num = num;
}
