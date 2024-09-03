#include "login.h"

Login::Login() : m_id(0), m_username(""), m_password("") { }
Login::Login(int id, string username, string password) {
    m_id = id; m_username = username; m_password = password;
}
Login::Login(int id) : m_id(id), m_username(""), m_password("") { }

int Login::getId() const {
    return m_id;
}
string Login::getUsername() const {
    return m_username;
}
string Login::getPassword() const {
    return m_password;
}

void Login::setId(int id) {
    m_id = id;
}
void Login::setUsername(string username) {
    m_username = username;
}
void Login::setPassword(string password) {
    m_password = password;
}