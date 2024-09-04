#include "cartmanager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
const string productListPath = "data/productList.csv";

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

void CartManager::readProductCSV() {
    ifstream file;
    file.open(productListPath);
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int f_pid = atoi(row[0].c_str());
                string f_name = row[1];
                int f_price = atoi(row[2].c_str());

                Product* p = new Product(f_pid, f_name, f_price);
                productList.insert( {f_pid, p});
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

void CartManager::writeProductCSV() {
    ofstream file;
    file.open(productListPath);
    if(!file.fail()) {
        for (const auto& v : productList) {
            Product* p = v.second;
            file << p->getPid() << ", ";
            file << p->getName() << ", ";
            file << p->getPrice() << endl;
            delete v.second;
        }
    }
    productList.clear();
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

bool CartManager::displayMenu(int id) {
    int ch, pid;

    cout << "\033[2J\033[1;1H";
    cout << "===============================" << endl
         << "=           장바구니            =" << endl
         << "===============================" << endl
         << " 1. 장바구니 목록                 " << endl
         << " 2. 장바구니 추가                 " << endl
         << " 3. 장바구니 삭제                 " << endl
         << " 4. 장바구니 수정                 " << endl
         << " 5. 메인메뉴로 이동                " << endl
         << "===============================" << endl;
    cout << " >> "; cin >> ch;

    switch (ch) {
        case 1: 
            displayInfo(id);
            cin.ignore();
            getchar();
            break;
        case 2:
            productManager.displayInfo();
            inputCart(id);
            cin.ignore();
            getchar();
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
            return false;
        default:
            cout << "옵션을 다시 선택해주세요." << endl;
            cin.ignore();
            getchar();
    }
    return true;
}

void CartManager::displayInfo(int id) {
    int result = 0;
    cout << endl << "  ID  |     Name     |   Price   |  Qty  | Total Price |" << endl;
    cout << "------------------------------------------------------" << endl;
    
    
    for (const auto& v : userCartList[id]) {
        Cart* cart = v.second;
        int cart_pid = cart->getPid();
        
   
        Product* product = productList[cart_pid];


        int _id = product->getPid();
        string _name = product->getName();
        int _price = product->getPrice();
        int _quantity = cart->getNum();
        int _totalprice = _price * _quantity;
        
        if(userCartList[id].find(cart_pid) != userCartList[id].end()) {
            cout << setw(5) << setfill('0') << right << _id << " | ";
            cout << setw(12) << setfill(' ') << left << _name << " | ";
            cout << setw(9) << setfill(' ') << right << fixed << setprecision(2) << _price << " | ";
            cout << setw(3) << setfill(' ') << right << (_quantity < 10 ? " " : "") << _quantity << " | ";
            cout << setw(11) << setfill(' ') << right << fixed << setprecision(2) << _totalprice << " | ";
            cout << endl;
        } else {
            cout << setw(5) << setfill('0') << right << id << " | ";
            cout << setw(12) << setfill(' ') << left << "Unknown" << " | ";
            cout << setw(9) << setfill(' ') << right << "N/A" << " | ";
            cout << setw(3) << setfill(' ') << right << (cart->getNum() < 10 ? " " : "") << cart->getNum() << " | ";
            cout << setw(11) << setfill(' ') << right << "N/A" << " | ";        
        }
        result += _totalprice;
    }
    cout << "------------------------------------------------------" << endl;
    cout << "TOTAL PRICE : " << result << endl;
}

/* vector<map<int, Cart*>> userCartList */
void CartManager::inputCart(int id) {
    int pid, num;
    cout << " 번호 : "; cin >> pid;
    cout << " 수량 : "; cin >> num;
    Cart* cart = new Cart(pid, num);
    userCartList[id][pid] = cart;
}

void CartManager::deleteCart(int id, int pid) {
    userCartList[id].erase(pid);
}

void CartManager::modifyCart(int id, int pid) {
    Cart* cart = userCartList[id][pid];
    int cnum;
    cout << " 수량 : "; cin >> cnum;
    cart->setNum(cnum);
    userCartList[id][pid] = cart;
}