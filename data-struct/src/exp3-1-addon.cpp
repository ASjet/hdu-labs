#include <iostream>
#include <string>
#include <vector>
#include "LinkStack.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
typedef int elem_t;
typedef LinkStack<elem_t> Stack;
void addon1(int _Cases);
void addon2(int _Cases);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    cout << "附加题1" << endl;
    addon1(2);
    cout << "附加题2" << endl;
    addon2(2);
    return 0;
}
void addon1(int _Cases)
{
    Stack * l = new Stack;
    Stack * m = new Stack;
    Stack * s = new Stack;
    std::string exp;
    while(_Cases--)
    {
        l->clear();
        m->clear();
        s->clear();
        bool flag_l, flag_m, flag_s;
        getline(cin, exp);
        for(auto i = exp.begin(); i != exp.end(); ++i)
        {
            flag_l = true;
            flag_m = true;
            flag_s = true;
            switch(*i)
            {
                case '{':
                    l->push(*i);
                    break;
                case '}':
                    flag_l = l->pop();
                    break;
                case '[':
                    m->push(*i);
                    break;
                case ']':
                    flag_m = m->pop();
                    break;
                case '(':
                    s->push(*i);
                    break;
                case ')':
                    flag_s = s->pop();
                    break;
                default:
                    break;
            }
            if(flag_l != true)
                cout << "Expected '{' in expression" << endl;
            if(flag_m != true)
                cout << "Expected '[' in expression" << endl;
            if(flag_s != true)
                cout << "Expected '(' in expression" << endl;
        }
        if(l->length() != 0)
            cout << "Expected '}' in expression" << endl;
        if(m->length() != 0)
            cout << "Expected ']' in expression" << endl;
        if(s->length() != 0)
            cout << "Expected ')' in expression" << endl;
    }
    delete l;
    delete m;
    delete s;

}
////////////////////////////////////////////////////////////////////////////////
void addon2(int _Cases)
{
    Stack * s = new Stack;
    std::string exp;
    while(_Cases--)
    {
        s->clear();
        getline(cin,exp);
        for(auto i = exp.begin(); i != exp.end(); ++i)
        {
            if(*i == '+')
            {
                s->push(std::stoi(exp.substr(0,i-exp.begin())));
                s->push(std::stoi(exp.substr(i-exp.begin()+1)));
                break;
            }
        }
        int op1,op2,res;
        s->pop(op1);
        s->pop(op2);
        s->push(op1+op2);
        s->pop(res);
        cout << res << endl;
    }
    delete s;
}