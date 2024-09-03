#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <iostream>
using namespace std;

class Login {
private:
    int m_id;
    string m_username, m_password;
public:
    Login();
    Login(int, string, string);

    int getId() const;
    string getUsername() const;
    string getPassword() const;
    void setId(int);
    void setUsername(string);
    void setPassword(string);
};


#endif//__LOGIN_H__