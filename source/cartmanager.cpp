#include "cartmanager.h"
#include "cart.h"

#include <iostream>
#include <sstream>
#include <iomanip>

const string CartManager::productListPath = "data/productList.csv";

// 모든 사용자별 장바구니를 저장하는 맵
map<int, UserCart*> CartManager::userCarts;

// 사용자 ID별 파일명을 반환하는 함수 추가
string CartManager::getCartFilename(int userId) {
    return "data/cartlist_" + to_string(userId) + "_" + username + ".csv";
}

void CartManager::readCartCSV(int userId) {
    ifstream file;
    string filename = getCartFilename(userId);  // 사용자별 파일명 생성
    file.open(filename);
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                int num = atoi(row[1].c_str());
                Cart* p = new Cart(id, num);

                // 해당 사용자의 장바구니에 추가
                userCarts[userId]->cartList.insert({id, p});
            }
        }
    }
    file.close();
}

void CartManager::writeCartCSV(int userId) {
    ofstream file;
    string filename = getCartFilename(userId);  // 사용자별 파일명 생성
    file.open(filename);
    if (!file.fail()) {
        // 해당 사용자의 장바구니를 파일에 기록
        for (const auto& v : userCarts[userId]->cartList) {
            Cart* p = v.second;
            file << p->getPid() << ", ";
            file << p->getNum() << endl;
        }
    }
    file.close();
}

CartManager::CartManager(int userId) : userId(userId) {
    // 사용자별 장바구니 생성
    if (userCarts.find(userId) == userCarts.end()) {
        userCarts[userId] = new UserCart(userId);
    }
    readCartCSV(userId);
}

CartManager::~CartManager() {
    // 모든 사용자의 장바구니를 파일에 저장
    for (const auto& userCart : userCarts) {
        writeCartCSV(userCart.first);
        delete userCart.second;
    }
    userCarts.clear();
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

bool CartManager::displayMenu(int userId) {
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                    장바구니                   " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. 장바구니 목록                              " << endl;
    cout << "  2. 장바구니 추가                             " << endl;
    cout << "  3. 장바구니 삭제                             " << endl;
    cout << "  4. 장바구니 수정                             " << endl;
    cout << "  5. 메인메뉴로 이동                            " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " >> ";
    cin >> ch;

    switch (ch) {
    case 1:
        displayInfo(userId);
        cin.ignore();
        getchar();
        break;
    case 2:
        inputCart(userId);
        cin.ignore();
        getchar();
        break;
    case 3:
        displayInfo(userId);
        cout << "   상품번호 : ";
        cin >> key;
        deleteCart(userId, key);
        break;
    case 4:
        displayInfo(userId);
        cout << "   상품번호 : ";
        cin >> key;
        modifyCart(userId, key);
        break;
    case 5:
        return false;
    default:
        std::cout << '\n' << "잘못 입력하셨습니다. 다시 입력해주세요" << '\n';
        std::cin.ignore();
        getchar();
        cin.clear();
    }
    return true;
}

void CartManager::displayInfo(int userId) {
    ifstream productFile(productListPath);
    if (!productFile.is_open()) {
        cout << "Error: Unable to open productlist.csv" << endl;
        return;
    }
    map<int, pair<string, int>> productInfo;
    while (!productFile.eof()) {
        vector<string> row = parseCSV(productFile, ',');
        if (row.size() == 3) {
            int id = atoi(row[0].c_str());
            string name = row[1];
            int price = atoi(row[2].c_str());
            productInfo[id] = make_pair(name, price);
        }
    }
    productFile.close();

    int result = 0;
    cout << endl << "상품번호  |     상품이름     |   가격   |  수량  |  합계가격  |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (const auto& v : userCarts[userId]->cartList) {
        Cart* p = v.second;
        int id = p->getPid();
        int quantity = p->getNum();
        int price = productInfo[id].second;
        int totalPrice = price * quantity;

        if (productInfo.find(id) != productInfo.end()) {
            cout << "   " << setw(7) << setfill(' ') << right << setw(4) << setfill('0') << id << setw(3) << setfill(' ') << "   | ";  // 상품번호: 4자리 숫자, 나머지 공백
            cout << setw(15) << setfill(' ') << left << productInfo[id].first << "  | ";  // 상품이름 열 폭 조정
            cout << setw(8) << setfill(' ') << right << price << " | ";  // 가격 열 폭 조정
            cout << setw(5) << setfill(' ') << right << quantity << "  | ";  // 수량 열 폭 조정
            cout << setw(10) << setfill(' ') << right << totalPrice << " | ";  // 합계가격 열 폭 조정
            cout << endl;
        } else {
            cout <<  "   " << setw(7) << setfill(' ') << right << setw(4) << setfill('0') << id << setw(3) << setfill(' ') << "  | ";  // 상품번호: 4자리 숫자, 나머지 공백
            cout << setw(15) << setfill(' ') << left << "Unknown" << "  | ";
            cout << setw(8) << setfill(' ') << right << "N/A" << " | ";
            cout << setw(5) << setfill(' ') << right << quantity << " | ";
            cout << setw(10) << setfill(' ') << right << "N/A" << " | ";
            cout << endl;
        }

        result += totalPrice;
    }
    cout << "---------------------------------------------------------------" << endl;
    cout << "주문금액 : " << result << endl;
}

void CartManager::inputCart(int userId) {
    int id, num;
    cout << "ID : "; cin >> id;
    cout << "num : "; cin >> num;
    Cart* q = new Cart(id, num);
    userCarts[userId]->cartList.insert({id, q});
}

void CartManager::deleteCart(int userId, int key) {
    userCarts[userId]->cartList.erase(key);
}

void CartManager::modifyCart(int userId, int key) {
    Cart* q = search(userId, key);
    int num;
    cout << "num : "; cin >> num;
    q->setNum(num);
    userCarts[userId]->cartList[key] = q;
}

Cart* CartManager::search(int userId, int id) {
    return userCarts[userId]->cartList[id];
}