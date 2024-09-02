#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "product.h"
#include "productmanager.h"

const string ProductManager::productListPath = "data/productlist.csv";
const string ProductManager::cartListPath = "data/cartlist.csv";

/* 모든건 productList를 중심으로 동작한다. */

/* productList.csv 읽기 */
// 파일열기(.csv) -> productList에 저장
void ProductManager::readProductCSV() {
    ifstream file;
    file.open(productListPath);
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                double price = atof(row[2].c_str());
                Product* p = new Product(id, row[1], price);    //productList: 맵{키, 값}
                productList.insert({id, p});    //productList(헤더에서 선언)에 읽은데이터 저장
            }                                   //lifetime: main의 객체, pm이 종료될 때까지
        }                                       //객체(p)가 productList로 들어감 -> p의 lifetime == lifetime(productList) 
    }
    file.close();
}

/* productList.csv 쓰기 */
// productList의 값을 파일(.csv)에 저장
void ProductManager::writeProductCSV() {
    ofstream file;
    file.open(productListPath);
    if(!file.fail()) {
        for (const auto& v : productList) {
            Product* p = v.second;
            file << p->getId() << ", " << p->getName() << ", ";
            file << p->getPrice() << endl;
            delete v.second;
        }
    }
    productList.clear();
    file.close();
}

ProductManager::ProductManager() {
    readProductCSV();
}

ProductManager::~ProductManager(){
    writeProductCSV();
    // productList에 저장된 모든 Product 객체의 메모리를 해제  //  p : std::map <int, Product*>
    for (auto& pair : productList) {                    //pair: std::pair<int, Product*>
        delete pair.second; // 동적으로 할당된 Product 객체를 해제
    }
    //productList.clear(); // 맵을 비웁니다. -> 소멸자에서 자동으로 정리됨(선택사항)
}

/* 사용자로부터 새로운 제품 추가 */
void ProductManager::inputProduct()
{
    std::string name;
    double price;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> price;

    int id = makeId();      //새로운 제품의 고유 ID를 할당
    Product* p = new Product(id, name, price);  //Product 객체(p) 생성
    productList.insert({id, p});                //각 객체가 고유한 ID를 가지므로 덮어쓰여지지 않고 이어쓰기가 된다.
                                                //(= 기존 값이 저장된다.)
}

void ProductManager::deleteProduct(int key)
{
    productList.erase(key);
}

void ProductManager::modifyProduct(int key)
{
    Product* p = search(key);
    cout << "  ID  |     Name     | Price | " << endl;
    cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getPrice() << endl;

    /* 새로운 값(이름, 가격) 입력 */
    string name;
    double price = 0.0;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> price;

    p->setName(name);
    p->setPrice(price);
    productList[key] = p;
    writeProductCSV();
}

Product *ProductManager::search(int id)
{
    return productList[id];
}

/* 제품이 추가될 때마다 고유 ID 생성 */
int ProductManager::makeId()
{
    if (productList.size() == 0) {
        return 0;
    } else {
        auto elem = productList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

void ProductManager::displayInfo()
{
    readProductCSV();
    cout << endl << "  ID  |     Name     | Price | "<< endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        cout << setw(5) << setfill('0') << right << p->getId() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getPrice() << endl;
    }
}

/* .csv의 각 줄을 파싱하고, row란 vector<string>에 저장 */
vector<string> ProductManager::parseCSV(istream &file, char delimiter)
{
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

bool ProductManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                    " << endl;
    cout << "  2. input Product                           " << endl;
    cout << "  3. Delete Product                          " << endl;
    cout << "  4. Modify Product                          " << endl;
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
        inputProduct();
        break;
    case 3:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        deleteProduct(key);
        break;
    case 4:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        modifyProduct(key);
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



