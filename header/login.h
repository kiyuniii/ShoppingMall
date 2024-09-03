#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <iostream>
using namespace std;

class Login {
public:
    Login();
    Login(int, string, string);
    Login(int);

    int getId() const;
    string getUsername() const;
    string getPassword() const;
    void setId(int);
    void setUsername(string);
    void setPassword(string);

private:
    int m_id;
    string m_username, m_password;
};


#endif//__LOGIN_H__
