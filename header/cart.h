#ifndef __CART_H__
#define __CART_H__


class Cart {
public:
    Cart();
    Cart(int, int);
    
    int getPid() const;
    int getNum() const;
    
    void setPid(int pid);
    void setNum(int num);

private:
    int m_pid, m_num;
};
#endif//__CART_H__