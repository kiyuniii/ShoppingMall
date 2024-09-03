#include "login.h"
#include "loginmanager.h"
#include "clientmanager.h"
#include "client.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

string tempID;

const string LoginManager::loginListPath = "data/loginlist.csv";
const string LoginManager::clientListPath = "data/clientlist.csv";

void LoginManager::readLoginCSV() {
    ifstream file;
    file.open(loginListPath);
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                string un = row[1].c_str();
                string pw = row[2].c_str();
                Login* p = new Login(id, un, pw);  
                loginList.insert({id, p});    
            }                                   
        }                                      
    }
    file.close();
}

void LoginManager::writeLoginCSV() {
    ofstream file;
    file.open(loginListPath);
    if(!file.fail()) {
        for (const auto& v : loginList) {
            Login* p = v.second;
            file << p->getId() << ", " << p->getUsername() << ", ";
            file << p->getPassword() << endl;
            delete v.second;
        }
    }
    loginList.clear();
    file.close();
}

void LoginManager::writeClientCSV() {
    ofstream file;
    file.open(clientListPath);
    if(!file.fail()) {
        for (const auto& v : loginClientInfo) {
            Client* p = v.second.second;
            file << p->getId() << ", " 
                 << p->getName() << ", "
                 << p->getPhoneNumber() << ", ";
            file << p->getAddress() << endl;
        }
    }
    file.close();
}

vector<string> LoginManager::parseCSV(istream& file, char delimiter) {
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

LoginManager::LoginManager() { 
    loginList.clear();
    readLoginCSV();
}

LoginManager::~LoginManager() { 
    writeLoginCSV();
    writeClientCSV();
}

bool LoginManager::displayMenu() {
    int ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                   프로그램                    " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. 로그인                                   " << endl;
    cout << "  2. 계정 생성                                 " << endl;
    cout << "  3. 프로그램 종료                              " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " 옵션 : ";
    cin >> ch;

    switch(ch) {
        case 1:
            if(checkLogin()) {
                Main m;
                m.displayMenu();
            } else {
                checkLogin();  // 잘못된 로그인 재시도
            }
            break;
        case 2: {
            string username = "";
            // 유효한 username을 얻을 때까지 checkRegister 호출
            while (true) {
                username = checkRegister();
                if (!username.empty()) {  // 유효한 username이 입력된 경우 루프 탈출
                    addInfo(username);  // username을 addInfo에 전달
                    break;
                }
            }
            break;
        }
        case 3:
            return false;
    }
    return true;
}

bool LoginManager::checkLogin() {
    string username, password;
    cout << "username : "; cin >> username;
    cout << "password : "; cin >> password;

    for(const auto& v : loginList) {
        Login* p = v.second;
        if(p->getUsername() == username && p->getPassword() == password) {
            puts("로그인 성공!");
            return true;
        } 
    }
    puts("로그인 실패! 다시 입력해주세요.");
    return false;
}

/* username 중복체크 */
string LoginManager::checkRegister() {
    string username;
    cout << "username : "; 
    cin >> username;

    for(const auto& v : loginList) {
        Login* p = v.second;
        if(p->getUsername() == username) {
            puts("입력하신 username이 이미 존재합니다. 다른 username을 입력해주세요.");
            return "";  // 이미 존재하는 경우 빈 문자열을 반환
        }
    }

    puts("사용가능한 username입니다.");
    return username;  // 사용 가능한 경우 입력한 username을 반환
}

Login* LoginManager::search(int id) {
    return loginList[id];
}

int LoginManager::makeId() {
    if (loginList.size() == 0) {
        return 0;
    } else {
        auto elem = loginList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

void LoginManager::addInfo(const string& username) {
    int id = makeId();
    string name, phoneNumber, address;
    string password;
    
    cout << "이름을 입력하세요: "; cin >> name;
    cout << "번호를 입력하세요: "; cin >> phoneNumber;
    cout << "주소를 입력하세요: "; cin >> address;
    puts("==============================================");
    cout << "비밀번호를 입력하세요: "; cin >> password;
    
    Client* c = new Client(id, name, phoneNumber, address);
    Login* p = new Login(id, username, password);

    loginClientInfo[id] = make_pair(p, c);
    loginList[id] = p;

    ClientManager* cm = new ClientManager();
    cm->clientList[id] = c;
}
