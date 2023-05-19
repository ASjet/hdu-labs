#include <iostream>
#include <string>
#include "SeqStack.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
typedef int elem_t;
typedef SeqStack<elem_t> Stack;
const array_size_t MAX_SIZE = 50;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    elem_t e;
    cout << "顺序栈S的基本运算如下:" << endl;
    cout << "    (1)初始化栈S" << endl;
    Stack *S = new Stack(MAX_SIZE);
    cout << "    (2)栈为" << ((S->empty()) ? "空" : "非空") << endl;
    cout << "    (3)依次进栈元素";
    for (int i = 1; i < 7; ++i)
    {
        cout << ((i == 1)? '\0': ',') << i;
        S->push(i);
    }
    cout << endl;
    S->GetTop(e);
    cout << "    GetTop()=" << e << endl;

    cout << "    (4)栈为" << ((S->empty()) ? "空" : "非空") << endl;
    cout << "    (5)出栈序列:";
    while(!S->empty())
    {
        S->pop(e);
        cout << e << ((S->empty())?'\0':' ');
    }
    cout << endl;
    cout << "    (6)栈为" << ((S->empty()) ? "空" : "非空") << endl;
    cout << "    (7)释放栈" << endl;
    delete S;
    return 0;
}