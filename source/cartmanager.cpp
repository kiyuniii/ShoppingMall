#include "cartmanager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

string CartManager::cartListUserPath(int id) {
    return "data/cartlist_" + to_string(id) + "_" + loginList[id]->getUsername() + ".csv";
}

void CartManager::readCartCSV(int id) {
    if (static_cast<size_t>(id) >= shoppingCart.size()) {
        shoppingCart.resize(id + 1);
    }
    ifstream file;
    file.open(cartListUserPath(id));
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int pid = atoi(row[0].c_str());
                int num = atoi(row[1].c_str());
                Cart* p = new Cart(pid, num);
                Product* prod = new Product(pid);  // 예시로 새로운 Product 생성
                shoppingCart[id].insert({pid, {prod, p}});    
            }                                   
        }                                      
    }
    file.close();
}

void CartManager::writeCartCSV(int id) {
    ofstream file;
    file.open(cartListUserPath(id));
    if (!file.fail()) {
        for (const auto& v : shoppingCart[id]) {
            Cart* p = v.second.second;
            Product* prod = v.second.first;
            file << p->getPid() << ", ";
            file << p->getNum() << endl;
            delete p;
            delete prod;
        }
    }
    shoppingCart[id].clear();
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
CartManager::CartManager() : userID(0) {
}

CartManager::CartManager(int id) : userID(id) {
    if (id >= shoppingCart.size()) {
        shoppingCart.resize(id + 1);
    }
    readCartCSV(id);
}

CartManager::~CartManager() {
    writeCartCSV(userID);
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

void CartManager::inputCart(int id) {
    if (static_cast<size_t>(id) >= shoppingCart.size()) {
        shoppingCart.resize(id + 1); // 벡터 크기 조정
    }
    int pid, num;
    cout << " 번호 : "; cin >> pid;
    cout << " 수량 : "; cin >> num;

    // 사용자 인덱스(id)가 shoppingCart의 범위 내에 있는지 확인
    if (id >= shoppingCart.size()) {
        shoppingCart.resize(id + 1); // 사용자 벡터 크기를 조정하여 새로운 사용자의 장바구니 생성
    }

    // 제품 ID(pid)가 사용자의 장바구니에 있는지 확인
    auto& userCart = shoppingCart[id];  // 사용자의 장바구니에 대한 참조 가져오기
    auto it = userCart.find(pid);  // 제품 ID를 가진 항목을 찾기

    if (it != userCart.end()) {
        Cart* p = it->second.second;  // Cart*에 접근 (pair의 second 부분)
        Product* product = it->second.first;  // Product*에 접근 (pair의 first 부분)

        // 예시로 Cart 객체의 메서드 호출
        if (p != nullptr) {
            cout << "Product ID: " << p->getPid() << ", Quantity: " << p->getNum() << endl;
        }

        // 예시로 Product 객체의 메서드 호출
        if (product != nullptr) {
            cout << "Product Name: " << product->getName() << endl;
        }
    } else {
        // 새로운 Cart 객체와 Product 객체 생성
        Cart* p = new Cart(pid, num);
        Product* product = new Product(pid); // Product 객체를 생성하거나 가져옴
        userCart.insert({pid, {product, p}});  // productId를 키로 사용하여 Cart 포인터를 저장
        cout << "Product added to cart." << endl;
    }
}

void CartManager::deleteCart(int id, int pid) {
    if (static_cast<size_t>(id) >= shoppingCart.size()) {
        cout << "Error: User ID " << id << " is out of range." << endl;
        return;
    }    
    
    if (id >= shoppingCart.size()) {
        cout << "Error: User ID " << id << " is out of range." << endl;
        return;
    }

    auto& userCart = shoppingCart[id];
    auto it = userCart.find(pid);

    if (it != userCart.end()) {
        Product* p = it->second.first;
        Cart* c = it->second.second;

        if (p) delete p;
        if (c) delete c;
        
        userCart.erase(it);
        cout << "Product ID " << pid << " removed from user " << id << "'s cart." << endl;
    } else {
        cout << "Error: Product ID " << pid << " not found in user " << id << "'s cart." << endl;
    }
}

void CartManager::modifyCart(int id, int pid) {
    if (static_cast<size_t>(id) >= shoppingCart.size()) {
        cout << "Error: User ID " << id << " is out of range." << endl;
        return;
    }

    if (id >= shoppingCart.size()) {
        cout << "Error: User ID " << id << " is out of range." << endl;
        return;
    }

    auto& userCart = shoppingCart[id]; // 사용자의 장바구니를 참조로 가져옴

    if (userCart.find(pid) == userCart.end()) {
        cout << "Error: Product ID " << pid << " not found in user " << id << "'s cart." << endl;
        return;
    }

    Cart* p = userCart[pid].second; // Cart*를 얻기 위해 .second 사용
    Product* product = userCart[pid].first; // Product*를 얻기 위해 .first 사용

    if (!p) {
        cout << "Error: Cart pointer is null." << endl;
        return;
    }

    // 제품 정보 출력
    cout << " PID  |     Name     | Price | " << endl;
    cout << setw(5) << setfill('0') << right << p->getPid() << " | " << left;
    if (product) {
        cout << setw(12) << setfill(' ') << product->getName() << " | ";
        cout << setw(12) << setfill(' ') << product->getPrice() << endl;
    } else {
        cout << "Error: Product not found." << endl;
        return;
    }

    // 새로운 값(이름, 가격) 입력
    string name;
    int price = 0; // 정수형으로 수정
    cout << "New name : "; cin.ignore(); getline(cin, name);
    cout << "New price : "; cin >> price;

    // 제품 정보 수정
    product->setName(name);
    product->setPrice(price);
}
