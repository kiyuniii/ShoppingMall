#include "cartmanager.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// 정적 변수 정의 및 초기화
const string CartManager::productListPath = "data/productList.csv";

string CartManager::cartListUserPath(int id, int pid) {
    // Check for invalid user ID or product ID
    if (id < 0 || id >= userLoginList.size() || userLoginList[id].find(pid) == userLoginList[id].end()) {
        cout << "Error: Invalid user ID or product ID for creating file path." << endl;
        return "";
    }

    Login* value = userLoginList[id][pid];
    if (!value) {
        cout << "Error: Null login pointer encountered." << endl;
        return "";
    }

    // Construct the file path
    return "data/cartlist_" + to_string(id) + "_" + value->getUsername() + ".csv";
}



void CartManager::readCartCSV(int id, int pid) {
    // userCartList 초기화 검사
    if (userCartList.empty()) {
        userCartList.resize(userLoginList.size());  // userLoginList 크기에 맞게 초기화
    }

    if (id < 0 || static_cast<size_t>(id) >= userCartList.size()) {
        cout << "Error: Invalid user ID for reading cart CSV." << endl;
        return;
    }

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
                productList.insert({f_pid, p});
            }                                   
        }                                      
    }
    file.close();
}

void CartManager::writeCartCSV(int id, int pid) {
    // Check for invalid user ID
    if (id < 0 || id >= userCartList.size()) {
        cout << "Error: Invalid user ID for writing cart CSV." << endl;
        return;
    }

    // Get the file path
    string filename = cartListUserPath(id, pid);
    if (filename.empty()) {
        cout << "Error: File path is empty." << endl;
        return;
    }

    // Open the file for writing
    ofstream file;
    file.open(filename, ios::out | ios::trunc);  // Open in write mode and truncate if exists
    if (!file.is_open()) {
        cout << "Error: Could not open file for writing, creating new file." << endl;
        // Attempt to create the file
        file.clear();
        file.open(filename, ios::out);  // Try opening again, now in create mode
        if (!file.is_open()) {
            cout << "Error: Failed to create file." << endl;
            return;
        }
    }

    // Write cart data to file
    for (const auto& v : userCartList[id]) {
        Cart* c = v.second;
        file << c->getPid() << ", ";
        file << c->getNum() << endl;
        delete c;
    }
    userCartList[id].clear();
    file.close();
}


void CartManager::writeProductCSV() {
    ofstream file;
    file.open(productListPath);
    if (!file.fail()) {
        for (const auto& v : productList) {
            Product* p = v.second;
            file << p->getPid() << ", ";
            file << p->getName() << ", ";
            file << p->getPrice() << endl;
            delete p;  // 메모리 해제
        }
        productList.clear();
    } else {
        cout << "Error: Could not open product list file for writing." << endl;
    }
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
    // 모든 사용자 및 로그인 정보를 초기화하고 로드합니다.
    userCartList.resize(10);  // 필요한 초기 크기만큼 크기 조정
}

CartManager::CartManager(int id, int pid) {
    userCartList.resize(10);  // 필요한 초기 크기만큼 크기 조정
    readCartCSV(id, pid);
}

CartManager::~CartManager() {
    writeCartCSV(userID, productID);
}

bool CartManager::displayMenu(int id) {
    int ch, pid;

    while (true) {
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
                return false;  // 메인 메뉴로 이동
            default:
                cout << "옵션을 다시 선택해주세요." << endl;
                cin.ignore();
                getchar();
                break;  // 다시 장바구니 메뉴로 돌아감
        }
    }

    return true;  // 이 줄은 실제로 도달하지 않습니다.
}


void CartManager::displayInfo(int id) {
    if (id < 0 || id >= userCartList.size()) {
        cout << "Error: Invalid user ID." << endl;
        return;
    }

    readProductCSV(); // 제품 정보를 다시 읽습니다.

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
            cout << setw(5) << setfill('0') << right << _id << " | "; // ID 출력
            cout << setw(12) << setfill(' ') << left << _name << " | "; // Name 출력
            cout << setw(9) << setfill(' ') << right << fixed << setprecision(2) << _price << " | "; // Price 출력, 우측 정렬
            cout << setw(4) << setfill(' ') << right << _quantity << " | "; // Qty 출력, 우측 정렬 (너비 4로 조정)
            cout << setw(12) << setfill(' ') << right << fixed << setprecision(2) << _totalprice << " | "; // Total Price 출력, 우측 정렬
            cout << endl;
        } else {
            cout << setw(5) << setfill('0') << right << id << " | ";
            cout << setw(12) << setfill(' ') << left << "Unknown" << " | ";
            cout << setw(9) << setfill(' ') << right << "N/A" << " | ";
            cout << setw(4) << setfill(' ') << right << _quantity << " | "; // Qty 출력, 우측 정렬 (너비 4로 조정)
            cout << setw(12) << setfill(' ') << right << "N/A" << " | ";        
        }
        result += _totalprice;
    }

    cout << "------------------------------------------------------" << endl;
    cout << "TOTAL PRICE : " << result << endl;

    writeProductCSV(); // 변경된 내용을 저장합니다.
}

void CartManager::inputCart(int id) {
    if (id < 0 || static_cast<size_t>(id) >= userCartList.size()) {
        cout << "Error: Invalid user ID for input cart." << endl;
        return;
    }

    int pid, num;
    cout << " 번호 : "; cin >> pid;
    cout << " 수량 : "; cin >> num;

    Cart* cart = new Cart(pid, num);
    userCartList[id][pid] = cart;
}

void CartManager::deleteCart(int id, int pid) {
    if (id < 0 || static_cast<size_t>(id) >= userCartList.size()) {
        cout << "Error: Invalid user ID for deleting cart." << endl;
        return;
    }

    if (userCartList[id].find(pid) == userCartList[id].end()) {
        cout << "Error: Product ID not found in cart." << endl;
        return;
    }

    userCartList[id].erase(pid);
}

void CartManager::modifyCart(int id, int pid) {
    if (id < 0 || static_cast<size_t>(id) >= userCartList.size()) {
        cout << "Error: Invalid user ID for modifying cart." << endl;
        return;
    }

    if (userCartList[id].find(pid) == userCartList[id].end()) {
        cout << "Error: Product ID not found in cart." << endl;
        return;
    }

    Cart* cart = userCartList[id][pid];
    int cnum;
    cout << " 수량 : "; cin >> cnum;
    cart->setNum(cnum);
    userCartList[id][pid] = cart;
}
