#include <iostream>
#include "CirQueue.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
const int MaxSize = 5;
using elem_t = char;
bool comp(int a, int b)
{
    return a < b;
}
void addon(void);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    cout << "环形队列基本运算如下:" << endl;
    cout << "\t(1)初始化队列q" << endl;
    CirQueue<elem_t> *cq = new CirQueue<elem_t>(MaxSize);
    cout << "\t(2)依次进队元素a,b,c,d,e" << endl;
    for (elem_t i = 'a'; i <= 'e'; ++i)
    {
        cout << "\t   进队" << i << endl;
        cq->push(i);
        cout << "\t   当前队列元素: " << *cq << endl;
    }
    cout << "\t(3)队列为" << ((cq->empty()) ? "空" : "非空") << endl;
    elem_t e;
    cout << "\t(4)出队序列: ";
    while (!cq->empty())
    {
        cq->pop(e);
        cout << e << ((cq->empty()) ? '\0' : ',');
    }
    cout << endl;
    cout << "\t(5)释放队列" << endl;
    delete cq;
    addon();
    return 0;
}
void addon(void)
{
    cout << "附加题" << endl;
    CirQueue<int> *cq = new CirQueue<int>(10);
    int e;
    int cnt = 6;

    for(int i = 0; i < 7; ++i)
        cq->push(i);
    while(!cq->empty())
        cq->pop();

    while (cnt--)
    {
        cin >> e;
        cq->push(e);
    }
    cout << "排序前队列元素: " << *cq << endl;
    cq->sort(comp);
    cout << "排序后队列元素: " << *cq << endl;
    delete cq;
}