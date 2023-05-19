#include <iostream>
#include "Sqlist.h"
#define MAX_SIZE 50
typedef char elem_t;
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
void addon1(void);
template <typename T> void addon2(void);
struct stru1
{
    char name[10];
    int id;
};
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Sqlist<elem_t> * L = new Sqlist<elem_t>(MAX_SIZE);
    cout << "顺序表的基本运算如下:" << endl
         << " (1)初始化顺序表L" << endl;
    cout << " (2)依次插入a,b,c,d,e元素" << endl;
    L->insert(0, 'a');
    L->insert(1, 'b');
    L->insert(2, 'c');
    L->insert(3, 'd');
    L->insert(4, 'e');
    cout << " (3)输出顺序表L:" << *L << endl;
    cout << " (4)顺序表L长度:" << L->length() << endl;
    cout << " (5)顺序表L为" << ((L->empty())? "空" : "非空") << endl;
    cout << " (6)顺序表L的第3个元素:" << (*L)[2] << endl;
    cout << " (7)元素a的位置:" << L->find('a') + 1 << endl;
    cout << " (8)在第4个元素位置上插入f元素" << endl;
    L->insert(3, 'f');
    cout << " (9)输出顺序表L:" << *L << endl;
    cout << " (10)删除L的第3个元素" << endl;
    L->remove(2);
    cout << " (11)输出顺序表L:" << *L << endl;
    cout << " (12)释放顺序表L" << endl;
    delete L;

    cout << "附加题1:" << endl;
    addon1();
    cout << "附加题2:" << endl
         << "char型:" << endl;
    addon2<char>();
    cout << "int型:" << endl;
    addon2<int>();
    cout << "float型:" << endl;
    addon2<float>();
    cout << "double型:" << endl;
    addon2<double>();
    cout << "自定义结构体{char[10], int}:" << endl;
    addon2<stru1>();

    return 0;
}

void addon1(void)
{
    Sqlist<int> *L = new Sqlist<int>(50);
    L->insert(0, 0);
    L->insert(1, 0);
    L->insert(2, 2);
    L->insert(3, 4);
    L->insert(4, 4);
    L->insert(5, 4);
    L->insert(6, 7);
    L->insert(7, 7);
    cout << *L << endl;
    L->unique();
    cout << *L << endl;
    delete L;
}

template <typename T>
void addon2(void)
{
    int var1, i;
    T var2[5];
    printf("var1 变量的地址： %p\n", &var1);
    for (i = 0; i < 2; i++)
        printf("var2[%d] 变量的地址： %p\n", i, &var2[i]);
}