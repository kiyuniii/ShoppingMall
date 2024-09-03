#include "cart.h"

Cart::Cart() : m_pid(0), m_num(0) { }

Cart::Cart(int pid, int num) {
    m_pid = pid; m_num = num;
}

int Cart::getPid() const {
    return m_pid;
}
int Cart::getNum() const {
    return m_num;
}

void Cart::setPid(int id) {
    m_pid = id;
}
void Cart::setNum(int num) {
    m_num = num;
}