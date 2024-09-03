#include "user.h"

User::User() : m_id(0), m_name(""), m_phone(""), m_address("") { }

User::User(int id, string name, string phone, string address) {
    m_id = id; m_name = name; m_phone = phone; m_address = address;
}

int User::getId() const {
    return m_id;
}
string User::getName() const {
    return m_name;
}
string User::getPhone() const {
    return m_phone;
}
string User::getAddress() const {
    return m_address;
}

void User::setId(int id) {
    m_id = id;
}
void User::setName(string name) {
    m_name = name;
}
void User::setPhone(string phone) {
    m_phone = phone;
}
void User::setAddress(string address) {
    m_address = address;
}