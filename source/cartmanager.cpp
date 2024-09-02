#include "cartmanager.h"
#include "cart.h"
#include "product.h"    
#include "productmanager.h"

#include <sstream>
#include <iomanip>

void CartManager::readCartCSV() {
    ifstream file;
    file.open("data/cartlist.txt");
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = atoi(row[0].c_str());
                double price = atof(row[2].c_str());
                Cart* p = new Cart(id, row[1], price);
                cartList.insert( {id, p });                
            }
        }
    }
    file.close();
}

void CartManager::writeCartCSV() {
    ofstream file;
    file.open("data/cartList.txt");
    if(!file.fail()) {
        for (const auto& v : cartList) {
            Cart *p = v.second;
            file << p->getId() << ", " << p->getName() << ", ";
            file << p->getPrice() << endl;
            delete v.second;
        }
    }
    cartList.clear();
    file.close();
}

CartManager::CartManager() {
}

CartManager::~CartManager() {
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
        addCart();
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
        saveList();
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
    ifstream file;
    file.open("data/cartList.txt");

    if(!file.fail()) {
        cartList.clear();  // 기존 데이터를 지우고 새로 읽어옴

        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size() == 3) {  // 파일 형식이 ID, Name, Price인지 확인
                int id = atoi(row[0].c_str());
                double price = atof(row[2].c_str());
                Cart* p = new Cart(id, row[1], price);
                cartList.insert({id, p});
            }
        }
    } else {
        cerr << "Failed to open cartList.txt for reading." << endl;
    }
    file.close();

    cout << endl << "  ID  |     Name     | Price | "<< endl;
    for (const auto& v : cartList) {
        Cart* p = v.second;
        cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getPrice() << endl;
    }
}

void CartManager::addCart() {
    ProductManager productManager;
    productManager.displayInfo();
    
    int id;
    cout << "Enter Product ID to ADD to your cart: ";
    cin >> id;

    cout << endl << endl;
    Product* product = productManager.search(id);

    if(product)  {
        Cart* cartItem = new Cart(product->getId(), product->getName(), product->getPrice());
        cartList.insert({id, cartItem});
        puts("product added successfully");
    } else {
        puts("product not found");
    }
    saveList();
}

void CartManager::deleteCart(int key) {
    cartList.erase(key);   
    saveList();
}

/* 구매수량 변경 */
void CartManager::modifyCart(int key) {
    Cart* p = search(key);
    cout << "  ID  |     Name     | Price | " << endl;
    cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getPrice() << endl;

    string name;
    double price = 0.0;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> price;

    p->setName(name);
    p->setPrice(price);
    cartList[key] = p;   

    saveList();
}

Cart *CartManager::search(int id) {
    return cartList[id];
}

void CartManager::saveList() {
    ofstream file;
    file.open("data/cartList.txt");

    if(!file.fail()) {
        for(const auto& v : cartList) {
            Cart *p = v.second;
            file << p->getId() << ", " << p->getName() << ", " <<p->getPrice() << endl; 
        }
    } else {
        cerr << "Failed to open the file for writing" << endl;
    }
    file.close();
}

/* modifyProduct --(같은ID)--> cartList 수정 */
void CartManager::updateCartItem(int id, const string& name, double price) {
    auto it = cartList.find(id);
    if (it != cartList.end()) {
        Cart* cartItem = it->second;
        cartItem->setName(name);
        cartItem->setPrice(price);
        saveList();  
        cout << "Cart item updated successfully." << endl;
    } else {
        cout << "Product ID not found in cart." << endl;
    }
}
