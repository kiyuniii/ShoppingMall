#include "cartmanager.h"
#include "cart.h"

#include <sstream>
#include <iomanip>

const string CartManager::productListPath = "data/productlist.csv";
const string CartManager::cartListPath = "data/cartlist.csv";

void CartManager::readCartCSV() {
    ifstream file;
    file.open(cartListPath);
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = atoi(row[0].c_str());
                int num = atoi(row[1].c_str());
                Cart* p = new Cart(id, num);
                cartList.insert( {id, p });                
            }
        }
    }
    file.close();
}

void CartManager::writeCartCSV() {
    ofstream file;
    file.open(cartListPath);
    if(!file.fail()) {
        for (const auto& v : cartList) {
            Cart *p = v.second;
            file << p->getId() << ", ";
            file << p->getNum() << endl;
            //delete v.second;
        }
    }
    //cartList.clear();
    file.close();
}

CartManager::CartManager() {
    cartList.clear();   //객체 생성하자마자 cartList 호출
    readCartCSV();
}

CartManager::~CartManager() {
    writeCartCSV();
}

vector<string> CartManager::parseCSV(istream &file, char delimiter) {
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

bool CartManager::displayMenu() {
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
    switch(ch) {
    case 1:
        displayInfo();
        cin.ignore();
        getchar();
        break;
    case 2: 
        inputCart();
        cin.ignore();   //#############
        getchar();
        break;
    case 3:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        deleteCart(key);
        break;
    case 4:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        modifyCart(key);
        break;
    case 5:
        //saveList();
        return false;
    default:
        std::cout << '\n' << "Wrong input... try again." << '\n';
        std::cin.ignore();
        getchar();
        cin.clear();
    }
    return true;
}

void CartManager::displayInfo() {
    //readCartCSV();
    
    // `productList.csv` 파일을 열고 데이터를 읽습니다.
    ifstream productFile(productListPath);
    if (!productFile.is_open()) {
        cout << "Error: Unable to open productlist.csv" << endl;
        return;
    }
    map<int, pair<string, int>> productInfo;

    // CSV 파일에서 데이터를 읽어 제품 정보를 저장합니다.
    while (!productFile.eof()) {
        vector<string> row = parseCSV(productFile, ',');
        if (row.size() == 3) {
            int id = atoi(row[0].c_str());
            string name = row[1];
            int price = atoi(row[2].c_str());
            productInfo[id] = make_pair(name, price);
        }
    }
    productFile.close(); // 파일 닫기

    int result = 0;
    cout << endl << "  ID  |     Name     |   Price   |  Qty  | Total Price |" << endl;
    cout << "------------------------------------------------------" << endl; // 추가한 구분선
    for (const auto& v : cartList) {
        Cart* p = v.second;
        int id = p->getId();
        
        int quantity = p->getNum();
        int price = productInfo[id].second;
        int totalPrice = price * quantity;
        // 제품 ID에 해당하는 이름과 가격을 검색하여 출력
        if (productInfo.find(id) != productInfo.end()) {

            cout << setw(5) << setfill('0') << right << id << " | "; // ID 출력
            cout << setw(12) << setfill(' ') << left << productInfo[id].first << " | "; // Name 출력
            cout << setw(9) << setfill(' ') << right << fixed << setprecision(2) << price << " | "; // Price 출력, 우측 정렬
            cout << setw(3) << setfill(' ') << right << (quantity < 10 ? " " : "") << quantity << " | "; // Qty 출력, 가운데 정렬
            cout << setw(11) << setfill(' ') << right << fixed << setprecision(2) << totalPrice << " | "; // Total Price 출력, 우측 정렬
            cout << endl;
        } else {
            // 제품 정보가 없는 경우에 대한 처리 (예: 오류 메시지)
            cout << setw(5) << setfill('0') << right << id << " | ";
            cout << setw(12) << setfill(' ') << left << "Unknown" << " | ";
            cout << setw(9) << setfill(' ') << right << "N/A" << " | ";
            cout << setw(3) << setfill(' ') << right << (p->getNum() < 10 ? " " : "") << p->getNum() << " | "; // Qty 출력, 가운데 정렬
            cout << setw(11) << setfill(' ') << right << "N/A" << " | "; // Total Price 출력, 우측 정렬
            cout << endl;
        }
        result += totalPrice;
    }
     

    cout << "------------------------------------------------------" << endl; // 추가한 구분선
    cout << "TOTAL PRICE : " << result;
}

void CartManager::inputCart() {
    int id, num;
    cout << "ID : "; cin >> id;
    cout << "num : "; cin >> num;

    //makeId()하지 않고 단순히 id값을 넣음
    Cart* q = new Cart(id, num);
    cartList.insert({id, q});
}

void CartManager::deleteCart(int key) {
    cartList.erase(key);   
    //saveList();
}

/* 구매수량 변경 */
void CartManager::modifyCart(int key) {
    Cart* q = search(key);

    int num;
    cout << "num : "; cin >> num;

    q->setNum(num);
    cartList[key] = q;
}

Cart *CartManager::search(int id) {
    return cartList[id];
}
