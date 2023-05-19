#include <iostream>
#include <string>
#include <vector>
#include "BinTree.h"
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using elem_t = char;
string str("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
btree_size_t commonRoot(btree_size_t _I, btree_size_t _J);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    cout << "二叉树的基本运算如下:" << endl;
    cout << "\t(1)创建二叉树" << endl;
    BinTree<elem_t> * bt = new BinTree<elem_t>;
    BinNode<elem_t> * p;
    bt->initializeTable(str);
    cout << "\t(2)输出二叉树:" << *bt << endl;
    p = bt->find('H');
    cout << "\t(3)H节点:左孩子为" << p->lnode()->value()
         << " 右孩子为" << p->rnode()->value() << endl;
    cout << "\t(4)二叉树b的高度:" << bt->height() << endl;
    cout << "\t(5)释放二叉树" << endl;
    delete bt;
    cout << "附加题:" << endl;
    btree_size_t i, j;
    while(cin >> i >> j)
        cout << commonRoot(i, j) << endl;
    return 0;
}
btree_size_t commonRoot(btree_size_t _I, btree_size_t _J)
{
    if(_I < 2 || _J < 2)
        return 0;

    btree_size_t ri, rj;
    for( ri = _I/2; ri != 0; ri /= 2)
    {
        for(rj = _J/2; ri < rj; rj /= 2);
        if(ri == rj)
            break;
    }
    return ri;
}