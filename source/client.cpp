#include "client.h"

#include <iostream>

using namespace std;

/* Client::Client() {
    m_id = 0; m_name = "", m_phoneNumber = "", m_address = "";
} */
Client::Client(int id, string name, string phoneNumber, string address)
    : m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address) {
}

string Client::getName() const
{
    return m_name;
}

void Client::setName(string& name)
{
    m_name = name;
}

string Client::getPhoneNumber() const
{
    return m_phoneNumber;
}

void Client::setPhoneNumber(string& phone)
{
    m_phoneNumber = phone;
}

string Client::getAddress() const
{
    return m_address;
}

void Client::setAddress(string& address)
{
    m_address = address;
}

int Client::getId() const {
    return m_id;
}

// Define copy assignment operator.
bool Client::operator==(const Client &other) const {
    return (this->m_id == other.m_id);
}
