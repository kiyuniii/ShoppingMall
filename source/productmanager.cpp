
#include "productmanager.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <iomanip>  // setw, setfill 등을 사용하기 위해 필요
using namespace std;

void ProductManager::readProductCSV() {
    ifstream file;
    file.open(productListPath);
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int pid = atoi(row[0].c_str());
                int price = atoi(row[2].c_str());
                Product* p = new Product(pid, row[1], price);    //productList: 맵{키, 값}
                productList.insert({pid, p});    //productList(헤더에서 선언)에 읽은데이터 저장
            }                                   //lifetime: main의 객체, pm이 종료될 때까지
        }                                       //객체(p)가 productList로 들어감 -> p의 lifetime == lifetime(productList) 
    }
    file.close();
}

void ProductManager::writeProductCSV() {
    ofstream file;
    file.open(productListPath);
    if(!file.fail()) {
        for (const auto& v : productList) {
            Product* p = v.second;
            file << p->getPid() << ", " << p->getName() << ", ";
            file << p->getPrice() << endl;
            delete v.second;
        }
    }
    productList.clear();
    file.close();
}

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

ProductManager::ProductManager() {
    readProductCSV();
}

ProductManager::~ProductManager() {
    writeProductCSV();
}


void ProductManager::displayMenu() {
    int ch, key;

    while(true) {
        cout << "===============================" << endl
            << "=             제품             =" << endl
            << "===============================" << endl
            << "  1. 제품 목록" << endl
            << "  2. 제품 추가" << endl
            << "  3. 제품 삭제" << endl
            << "  4. 제품 수정" << endl
            << "  5. 메인메뉴로 이동" << endl
            << "===============================" << endl
            << " >> " << endl; cin >> ch;
        
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
            default:
                cout << "옵션을 다시 선택해주세요." << endl;
                continue;
        }
        break;
    }
}

void ProductManager::inputProduct()
{
    string name;
    int price;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> price;

    int pid = makePid();      //새로운 제품의 고유 ID를 할당
    Product* p = new Product(pid, name, price);  //Product 객체(p) 생성
    productList.insert({pid, p});                //각 객체가 고유한 ID를 가지므로 덮어쓰여지지 않고 이어쓰기가 된다.
                                                //(= 기존 값이 저장된다.)
}

void ProductManager::deleteProduct(int key)
{
    productList.erase(key);
}

void ProductManager::modifyProduct(int key)
{
    Product* p = productList[key];
    cout << " PID  |     Name     | Price | " << endl;
    cout << setw(5) << setfill('0') << right << p->getPid() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getPrice() << endl;

    /* 새로운 값(이름, 가격) 입력 */
    string name;
    int price = 0.0;
    cout << "name : "; cin.ignore(); getline(cin, name, '\n');
    cout << "price : "; cin >> price;

    p->setName(name);
    p->setPrice(price);
    productList[key] = p;
    writeProductCSV();
}

int ProductManager::makePid()
{
    if (productList.size() == 0) {
        return 0;
    } else {
        auto elem = productList.end();
        int pid = (--elem)->first;
        return ++pid;
    }
}


void ProductManager::displayInfo()
{
    readProductCSV();
    cout << endl 
         << setw(4) << "PID" << " | " 
         << setw(15) << left << "Name" << " | "
         << setw(10) << left << "Price" << endl;
    cout << string(40, '-') << endl;  // 구분선 추가

    for (const auto& v : productList) {
        Product* p = v.second;
        cout << setw(5) << setfill('0') << right << p->getPid() << " | ";  // ID는 오른쪽 정렬, 빈 공간은 '0'으로 채움
        cout << setw(15) << setfill(' ') << left << p->getName() << " | ";  // 이름은 왼쪽 정렬
        cout << setw(10) << setfill(' ') << left << p->getPrice() << endl; // 가격은 왼쪽 정렬
    }
}
