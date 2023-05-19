#include <iostream>
#include <string>
#include "LinerLink.h"
#define MAX_SIZE 50
typedef char elem_t;
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    LinerLink<elem_t> *A = new LinerLink<elem_t>;
    cout << "单链表的基本运算如下:" << endl
         << " (1)初始化单链表L" << endl;
    cout << " (2)依次插入a,b,c,d,e元素" << endl;
    A->insert(-1, 'a');
    A->insert(-1, 'b');
    A->insert(-1, 'c');
    A->insert(-1, 'd');
    A->insert(-1, 'e');
    cout << " (3)输出单链表L:";
    cout << *A << endl;
    cout << " (4)单链表L长度:" << A->length() << endl;
    cout << " (5)单链表L为" << ((A->empty()) ? "空" : "非空") << endl;
    cout << " (6)单链表L的第3个元素:" << (*A)[2]->value() << endl;
    cout << " (7)元素a的位置:" << A->find('a') + 1 << endl;
    cout << " (8)在第4个元素位置上插入f元素" << endl;
    A->insert(3, 'f');
    cout << " (9)输出单链表L:" << *A << endl;
    cout << " (10)删除L的第3个元素" << endl;
    A->remove(2);
    cout << " (11)输出单链表L:" << *A << endl;
    cout << " (12)释放单链表L" << endl;

    // Addon
    cout << "附加题:" << endl
         << *A << endl;

    LinerLink<elem_t> *B = new LinerLink<elem_t>;
    LinkNode<elem_t> *sep, *B_head, *B_tail;
    link_size_t B_len = 0, len = A->length();
    elem_t tmp;

    sep = ((len & 1 == 1) ? A->tail() : A->tail()->next());

    for (link_size_t i = 0, j = 0; i < len; ++i)
    {
        if (i & 0x1 == 1)
        {
            tmp = (*A)[j]->value();
            A->remove(j);
            A->insert(-1, tmp);
            ++B_len;
        }
        else
            ++j;
    }
    B_head = sep->next();
    B_tail = A->tail();
    A->initialize(A->head(), sep, len - B_len);
    B->initialize(B_head, B_tail, B_len);
    cout << *A << endl
         << *B << endl;
    delete A;
    delete B;
    return 0;
}