#include "loginmanager.h"

#include <fstream>
#include <sstream>

const string LoginManager::loginListPath = "data/loginList.csv";

/* loginList.csv -> loginList */
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

/* loginList -> loginList.csv */
void LoginManager::writeLoginCSV() {
    ofstream file;
    file.open(loginListPath);
    if(!file.fail()) {
        for (const auto& v : loginList) {
            Login* p = v.second;
            file << p->getId() << ", ";
            file << p->getUsername() << ", ";
            file << p->getPassword() << endl;
            delete v.second;
        }
    }
    loginList.clear();
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
    readLoginCSV();
}

LoginManager::~LoginManager() {
    writeLoginCSV();    //loginList.clear()하면 loginList 컨테이너가 비워지므로 멤버함수에서 사용하지 않기.
                        //대신 loginList[key]->getter 사용하기
}

/*  ===============================================
    ===============================================
    ===============================================
    ===============================================
    =============================================== */


bool LoginManager::displayMenu() {
    int ch, key;
    string un;

    while(true) {
        cout << "\033[2J\033[1;1H";
        cout << "===============================" << endl
             << "=           LOGIN             =" << endl
             << "===============================" << endl
             << " 1. 로그인                      " << endl
             << " 2. 계정생성                     " << endl
             << " 3. 프로그램 종료                 " << endl
             << "================================" << endl;
        cout << " >> "; cin >> ch;

        switch(ch) {
            case 1: // >> mainMenu(ADMIN, CLIENT)
                key = checkLogin();
                mainMenu.displayMenu(key);
                break;
            case 2:
                cout << " USERNAME : "; cin >> un;
                key = checkRegister(un);
                addPassword(key);
                userManager.addUser(key);
                puts("다시 로그인헤주세요.");
                break;
            case 3:
                return false;
            default:
                cout << "옵션을 다시 선택해주세요." << endl;
                continue;
        }
        return true;
    }
}

int LoginManager::checkLogin() {
    string username, password;

    while(true) {
        cout << "  USERNAME : "; cin >> username;
        cout << "  PASSWORD : "; cin >> password;
    
        for(const auto& v : loginList) {
            int k = v.first;
            Login* p = v.second;        // lifetime : 각 loop
            if(p->getUsername() == username && p->getPassword() == password) {
                puts("로그인 성공!");
                return k;
            } 
        }
        puts("로그인 실패! 다시 입력해주세요.");
    }
}

int LoginManager::makeId()
{
    if (loginList.size() == 0) {
        return 0;
    } else {
        auto elem = loginList.end();
        int pid = (--elem)->first;
        return ++pid;
    }
}

int LoginManager::checkRegister(string username) {
    while(true) {
        bool isDuplicate = false;

        /* 중복인 경우 (if(!isDuplicate) 건너뜀) */
        for(const auto& v : loginList) {
            Login* p = v.second;        // lifetime : 각 loop
            if(p->getUsername() == username) {
                puts("중복된 username 존재!");
                isDuplicate = true;
                break;  //break(for)
            }
        }

        /* 중복이 아닌 경우 */
        if(!isDuplicate) {
            int id = makeId();
            Login* p = new Login(id, username, "");
            loginList[id] = p;

            tempUsername(username);
            puts("사용가능한 username입니다.");
            return id;
        }   
    }
}

void LoginManager::addPassword(int id) {
    string password = "";
    cout << "PASSWORD : "; cin >> password;

    if (loginList.find(id) != loginList.end()) {
        loginList[id]->setPassword(password); // 기존 객체의 패스워드 설정
    } else {
        cout << "Error: Invalid ID. No matching user found." << endl;
    }
}

/* ############################### */
string LoginManager::tempUsername(string username) {
    return username;
}

