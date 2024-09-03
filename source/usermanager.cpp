#include "usermanager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

const string userListPath = "data/userList.csv";

void UserManager::readUserCSV() {
    ifstream file;
    file.open(userListPath);
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                string nm = row[1].c_str();
                string ph = row[2].c_str();
                string ad = row[3].c_str();                
                User* p = new User(id, nm, ph, ad);  
                userList.insert({id, p});    
            }                                   
        }                                      
    }
    file.close();
}

/* userList -> userList.csv */
void UserManager::writeUserCSV() {
    ofstream file;
    file.open(userListPath);
    if(!file.fail()) {
        for (const auto& v : userList) {
            User* p = v.second;
            file << p->getId() << ", ";
            file << p->getName() << ", ";
            file << p->getPhone() << ", ";
            file << p->getAddress() << endl;
            delete v.second;
        }
    }
    userList.clear();
    file.close();
}

vector<string> UserManager::parseCSV(istream& file, char delimiter) {
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";
    while(!file.eof()) {
        char c = file.get();
        if( c == delimiter || c == '\r' || c == '\n') {
            if(file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}

UserManager::UserManager() { 
    readUserCSV();
}

UserManager::~UserManager() {
    writeUserCSV();
}

/*  ===============================================
    ===============================================
    ===============================================
    ===============================================
    =============================================== */


void UserManager::displayMenu(int id) {
    int ch;

    /* ADMIN */
    if(id == 0) {
        while(true) {
            cout << "===============================" << endl
                 << "=            USER             =" << endl
                 << "===============================" << endl
                 << " 1. 계정 리스트                  " << endl
                 << " 2. 메인메뉴로 이동               " << endl
                 << "===============================" << endl;
            cout << " >> "; cin >> ch;

            switch(ch) {
                case 1: 
                    displayInfo();
                    break;
                case 2:
                    return;
                default:
                    cout << "옵션을 다시 선택해주세요." << endl;
                    continue;
            }
            break;
        }
    }

    /* CLIENT */
    else {
        while(true) {
            cout << "===============================" << endl
                 << "=            USER             =" << endl
                 << "===============================" << endl
                 << " 1. 내 정보                      " << endl
                 << " 2. 개인정보 수정                 " << endl
                 << " 3. 회원탈퇴                     " << endl
                 << " 4. 메인메뉴로 이동                " << endl
                 << "================================" << endl;
            cout << " >> "; cin >> ch;

            switch(ch) {
                case 1: 
                    displayUser(id);
                    break;
                case 2:
                    modifyUser(id);
                    break;
                case 3:
                    deleteUser(id);
                    break;
                case 4:
                    return;
                default:
                    cout << "옵션을 다시 선택해주세요." << endl;
                    continue;
            }
            break;
        }
    }
}


void UserManager::displayInfo() {
    /* .csv 열고닫고 안하고 userList로 접근(업데이트)하면 되겠지...? */
    cout << endl 
         << setw(5) << "ID" << " | " 
         << setw(15) << left << "Name" << " | "
         << setw(15) << left << "Phone" << " | " 
         << setw(20) << left << "Address" << endl;
    cout << string(60, '-') << endl;  // 구분선 추가

    for (const auto& v : userList) {
        User* p = v.second;
        cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << setfill(' ') << p->getPhone() << " | ";
        cout << setw(12) << p->getAddress() << endl;
    }
}

void UserManager::displayUser(int id) {
    // userList에 id가 있는지 확인
    if (userList.find(id) != userList.end()) {
        cout << "   ID   : " << userList[id]->getId() << endl;
        cout << "  NAME  : " << userList[id]->getName() << endl;
        cout << " PHONE  : " << userList[id]->getPhone() << endl;
        cout << "ADDRESS : " << userList[id]->getAddress() << endl;
    } else {
        cout << "Error: User with ID " << id << " not found." << endl;
    }
}

void UserManager::deleteUser(int id) {
    // userList에 id가 있는지 확인
    auto it = userList.find(id);
    if (it != userList.end()) {
        delete it->second;  // 메모리 해제
        userList.erase(it); // 요소 삭제
        cout << "User with ID " << id << " deleted." << endl;
    } else {
        cout << "Error: User with ID " << id << " not found." << endl;
    }
}

void UserManager::modifyUser(int id) {
    // userList에 id가 있는지 확인
    if (userList.find(id) != userList.end()) {
        string name, phone, address;
        cout << "  NAME  : "; cin >> name;  
        cout << " PHONE  : "; cin >> phone;
        cout << "ADDRESS : "; cin >> address;

        userList[id]->setName(name);
        userList[id]->setPhone(phone);
        userList[id]->setAddress(address);
        cout << "User with ID " << id << " updated." << endl;
    } else {
        cout << "Error: User with ID " << id << " not found." << endl;
    }
}
