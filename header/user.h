#ifndef __USER_H__
#define __USER_H__

#include <iostream>
using namespace std;

class User {
public:
    User();
    User(int, string, string, string);

    int getId() const;
    string getName() const;
    string getPhone() const;
    string getAddress() const;

    void setId(int);
    void setName(string);
    void setPhone(string);
    void setAddress(string); 

private:
    int m_id;
    string m_name, m_phone, m_address;
};

#endif//__USER_H__