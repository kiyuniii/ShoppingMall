#include "product.h"

Product::Product() : m_pid(0), m_name(""), m_price(0) { }

Product::Product(int pid) : m_pid(pid) {
    m_name = ""; m_price = 0;
}

Product::Product(int id, const string& name, int price) {
    m_pid = id; m_name = name; m_price = price;
}

int Product::getPid() const {
    return m_pid;
}
string Product::getName() const {
    return m_name;
}
int Product::getPrice() const {
    return m_price;
}

void Product::setPid(int id) {
    m_pid = id;
}
void Product::setName(string name) {
    m_name = name;
}
void Product::setPrice(int price) {
    m_price = price;
}

