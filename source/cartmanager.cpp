#include "cartmanager.h"
#include "cart.h"

#include <sstream>
#include <iomanip>

const string CartManager::productListPath = "data/productlist.csv";

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
            file << p->getId() << ", ";
            file << p->getNum() << endl;
        }
    }
    file.close();
}

CartManager::CartManager(int userId, const string& username) : userId(userId), username(username) {
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

bool CartManager::displayMenu(int userId, const string& username) {
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "             Shopping Cart Manager           " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. DISPLAY Cart List                       " << endl;
    cout << "  2. INPUT Cart                              " << endl;
    cout << "  3. DELETE Cart                             " << endl;
    cout << "  4. MODIFY Cart                             " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
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
        cout << "   Choose Key : ";
        cin >> key;
        deleteCart(userId, key);
        break;
    case 4:
        displayInfo(userId);
        cout << "   Choose Key : ";
        cin >> key;
        modifyCart(userId, key);
        break;
    case 5:
        return false;
    default:
        std::cout << '\n' << "Wrong input... try again." << '\n';
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
    cout << endl << "  ID  |     Name     |   Price   |  Qty  | Total Price |" << endl;
    cout << "------------------------------------------------------" << endl;
    for (const auto& v : userCarts[userId]->cartList) {
        Cart* p = v.second;
        int id = p->getId();
        int quantity = p->getNum();
        int price = productInfo[id].second;
        int totalPrice = price * quantity;
        if (productInfo.find(id) != productInfo.end()) {
            cout << setw(5) << setfill('0') << right << id << " | ";
            cout << setw(12) << setfill(' ') << left << productInfo[id].first << " | ";
            cout << setw(9) << setfill(' ') << right << fixed << setprecision(2) << price << " | ";
            cout << setw(3) << setfill(' ') << right << (quantity < 10 ? " " : "") << quantity << " | ";
            cout << setw(11) << setfill(' ') << right << fixed << setprecision(2) << totalPrice << " | ";
            cout << endl;
        } else {
            cout << setw(5) << setfill('0') << right << id << " | ";
            cout << setw(12) << setfill(' ') << left << "Unknown" << " | ";
            cout << setw(9) << setfill(' ') << right << "N/A" << " | ";
            cout << setw(3) << setfill(' ') << right << (p->getNum() < 10 ? " " : "") << p->getNum() << " | ";
            cout << setw(11) << setfill(' ') << right << "N/A" << " | ";
            cout << endl;
        }
        result += totalPrice;
    }
    cout << "------------------------------------------------------" << endl;
    cout << "TOTAL PRICE : " << result;
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
