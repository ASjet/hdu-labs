#include <iostream>
#include <string>
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    LinerLink<int> * LF = new LinerLink<int>;
    LinerLink<int> * LR = new LinerLink<int>;
    for(link_size_t i = 0; i != 10; ++i)
    {
        LF->insert(0,i);
        LR->insert(-1,i);
    }
    cout << *LF << endl << *LR << endl;
    delete LF;
    delete LR;
    return 0;
}