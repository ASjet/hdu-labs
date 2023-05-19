#include <iostream>
#include "LinkQueue.h"
#include "StackQueue.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using elem_t = char;
bool comp(int a, int b)
{
    return a < b;
}
void addon(void);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    cout << "链队的基本运算如下:" << endl;
    cout << "\t(1)初始化链队q" << endl;
    LinkQueue<elem_t> *lq = new LinkQueue<elem_t>;
    elem_t e;
    cout << "\t(2)依次进链队元素a,b,c" << endl;
    for (elem_t i = 'a'; i <= 'c'; ++i)
        lq->push(i);
    cout << "\t(3)队列为" << ((lq->empty()) ? "空" : "非空") << endl;
    lq->pop(e);
    cout << "\t(4)出队一个元素" << e << endl;
    cout << "\t(5)依次进链队元素d,e,f" << endl;
    for(elem_t i = 'd'; i <= 'f'; ++i)
        lq->push(i);
    cout << "\t(6)出队序列:";
    while (!lq->empty())
    {
        lq->pop(e);
        cout << e << ((lq->empty()) ? '\0' : ' ');
    }
    cout << endl;
    cout << "\t(7)释放队列" << endl;
    delete lq;
    addon();
    return 0;
}
void addon(void)
{
    cout << "==========附加题==========" << endl;
    cout << "\t(1)初始化栈队列" << endl;
    StackQueue<int> * sq = new StackQueue<int>;
    int e;
    cout << "\t(2)入队1,2,3" << endl;
    for(int i = 1; i <= 3; ++i)
        sq->push(i);
    cout << "\t(3)出队";
    sq->pop(e);
    cout << e << ' ';
    sq->pop(e);
    cout << e << endl;
    cout << "\t(4)入队4,5" << endl;
    sq->push(4);
    sq->push(5);
    cout << "\t(5)出队";
    sq->pop(e);
    cout << e << ' ';
    sq->pop(e);
    cout << e << ' ';
    sq->pop(e);
    cout << e << endl;
    delete sq;
}