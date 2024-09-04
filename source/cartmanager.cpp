#include "cartmanager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/* cartList_[username] : pid, num */
string CartManager::cartListUserPath(int id, int pid) {
    Login* value = userLoginList[id][pid];
    return "data/cartlist_" + to_string(id) + "_" + value->getUsername() + ".csv";
}

void CartManager::readCartCSV(int id, int pid) {
    ifstream file;
    file.open(cartListUserPath(id, pid));
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int f_pid = atoi(row[0].c_str());
                int f_num = atoi(row[1].c_str());
                Cart* c = new Cart(f_pid, f_num);

                userCartList[id].insert({f_pid, c});
            }                                   
        }                                      
    }
    file.close();
}

void CartManager::writeCartCSV(int id, int pid) {
    ofstream file;
    file.open(cartListUserPath(id, pid));
    if (!file.fail()) {
        for (const auto& v : userCartList[id]) {
        /* map<int, User*> userList; */

            Cart* c = v.second;
            file << c->getPid() << ", ";
            file << c->getNum() << endl;
            delete v.second;
        }
    }
    userCartList[id].clear();
    file.close();
}

vector<string> CartManager::parseCSV(istream& file, char delimiter) {
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";
    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
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
CartManager::CartManager() : userID(0), productID(0) {

}

CartManager::CartManager(int id, int pid){
    readCartCSV(id, pid);
}

//##########################################################
/* writeCartCSV(0, 0) -> ADMIN 파일 손상?? */
CartManager::~CartManager() {
    writeCartCSV(userID, productID);
}

void CartManager::displayMenu(int id) {
    int ch, pid;

    while (true) {
        cout << "===============================" << endl
             << "=           장바구니            =" << endl
             << "===============================" << endl
             << " 1. 장바구니 목록                 " << endl
             << " 2. 장바구니 추가                 " << endl
             << " 3. 장바구니 삭제                 " << endl
             << " 4. 장바구니 수정                 " << endl
             << " 5. 메인메뉴로 이동                " << endl
             << "================================" << endl;
        cout << " >> "; cin >> ch;

        switch (ch) {
            case 1: 
                displayInfo(id);
                break;
            case 2:
                productManager.displayInfo();
                inputCart(id);
                break;
            case 3:
                displayInfo(id);
                cout << "   Choose Key : ";
                cin >> pid;
                deleteCart(id, pid);
                break;
            case 4:
                displayInfo(id);
                cout << "   Choose Key : ";
                cin >> pid;
                modifyCart(id, pid);
                break;
            case 5:
                return;
            default:
                cout << "옵션을 다시 선택해주세요." << endl;
                continue;
        }
        break;
    }
}

void CartManager::displayInfo(int id) {

}


void CartManager::inputCart(int id) {
    int pid, num;
    cout << " 번호 : "; cin >> pid;
    cout << " 수량 : "; cin >> num;

    
}

void CartManager::deleteCart(int id, int pid) {

}

void CartManager::modifyCart(int id, int pid) {

}
