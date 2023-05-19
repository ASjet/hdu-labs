#include <iostream>
#include "ShareStack.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
typedef int elem_t;
const array_size_t MAX_SIZE = 10;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    elem_t *e = new elem_t;
    STACK_FLAG flag;
    ShareStack<elem_t> *s = new ShareStack<elem_t>(MAX_SIZE);

    cout << "(1)initialize size of " << MAX_SIZE << endl;
    bool empty = s->isEmpty(LEFT_STACK) && s->isEmpty(RIGHT_STACK);

    cout << "(2)is empty? " << ((empty) ? "Yes" : "No") << endl;

    cout << "(3)push elem:" << endl;
    flag = LEFT_STACK;
    for (elem_t i = 0; i <= 5; ++i)
    {
        if (s->push(i, flag))
            cout << i << " has been pushed into stack1" << endl;
        else
            cout << "stack1 is full" << endl;
    }
    flag = RIGHT_STACK;
    for (elem_t i = 0; i <= 5; ++i)
    {
        if (s->push(i, flag))
            cout << i << " has been push into stack2" << endl;
        else
            cout << "stack2 is full" << endl;
    }

    cout << "(4)pop elem:" << endl;
    flag = LEFT_STACK;
    for (int i = 0; i <= 2; ++i)
    {
        if (s->pop(e, flag))
            cout << *e << " has been popped from stack1" << endl;
        else
            cout << "stack1 is empty" << endl;
    }
    flag = RIGHT_STACK;
    for (int i = 0; i <= 3; ++i)
    {
        if (s->pop(e, flag))
            cout << *e << " has been popped from stack2" << endl;
        else
            cout << "stack2 is empty" << endl;
    }

    cout << "(4)GetTop Elem:" << endl;
    s->GetTop(e, LEFT_STACK);
    cout << "top of stack1 is " << *e << endl;

    cout << "(5)clear stack" << endl;
    s->clear(LEFT_STACK);
    s->clear(RIGHT_STACK);
    delete s;
    delete e;
    return 0;
}