#ifndef __CARTMANAGER_H__
#define __CARTMANAGER_H__

#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "cart.h"

using namespace std;

// UserCart 클래스 정의 추가
class UserCart {
public:
    int userId;
    map<int, Cart*> cartList; // 사용자별 장바구니 목록

    UserCart(int id) : userId(id) {}

    ~UserCart() {
        for (auto& v : cartList) {
            delete v.second;
        }
        cartList.clear();
    }
};

class CartManager
{
public:
    CartManager(int userId);  // 생성자에 userId와 username 추가
    ~CartManager();

    void readCartCSV(int userId);  // 사용자별로 읽기
    void writeCartCSV(int userId); // 사용자별로 쓰기
    vector<string> parseCSV(istream &file, char);

    bool displayMenu(int userId); // 사용자별로 메뉴 표시
    void displayInfo(int userId);  // 사용자별로 정보 표시

    void inputCart(int userId);  // 사용자별로 항목 추가
    void deleteCart(int userId, int); // 사용자별로 항목 삭제
    void modifyCart(int userId, int); // 사용자별로 항목 수정

    Cart* search(int userId, int);

    static const string productListPath;

private:
    static map<int, UserCart*> userCarts;  // 사용자 ID별로 UserCart 관리
    string getCartFilename(int userId); // 사용자 ID별 파일명 생성

    int userId; // 현재 CartManager 인스턴스의 사용자 ID
    string username; // 현재 CartManager 인스턴스의 사용자 이름
};

#endif //__CARTMANAGER_H__