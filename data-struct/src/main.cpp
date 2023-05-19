#include "LinerLink.h"
#include <iostream>
#include <string>
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using elem_t = char;
template <typename T> bool listReverse(LinerLink<T> *&lnk);
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    LinerLink<int> *lnk = new LinerLink<int>;
    int a[5] = {1, 2, 3, 4, 5};
    lnk->initializeR(a, 5);
    cout << *lnk << endl;
    listReverse(lnk);
    cout << *lnk << endl;
    return 0;
}
template <typename T> bool listReverse(LinerLink<T> *&lnk) {
    T tmp;
    link_size_t length = lnk->length();
    LinerLink<T> *new_lnk = new LinerLink<T>;
    while (length--) {
        tmp = lnk->tail()->value();
        if (lnk->remove(-1) == false)
            return false;
        if (new_lnk->insert(-1, tmp) == false)
            return false;
    }
    delete lnk;
    lnk = new_lnk;
    return true;
}
