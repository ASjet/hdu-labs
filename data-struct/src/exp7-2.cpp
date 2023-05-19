#include <iostream>
#include <string>
#include "BinTree.h"
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using elem_t = char;
const string str("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
void addon(void);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    BinTree<elem_t> * bt = new BinTree<elem_t>;
    LinerLink<elem_t> * lnk = new LinerLink<elem_t>;
    bt->initializeTable(str);
    cout << "二叉树b:" << *bt << endl;
    bt->levelOrder(lnk);
    cout << "层次遍历序列:" << *lnk << endl;
    cout << "先序遍历序列:" << endl;
    bt->preOrder(lnk);
    cout << "递归算法:" << *lnk << endl;

    cout << "中序遍历序列:" << endl;
    bt->inOrder(lnk);
    cout << "递归算法:" << *lnk << endl;

    cout << "后续遍历序列:" << endl;
    bt->postOrder(lnk);
    cout << "递归算法:" << *lnk << endl;


    delete bt;
    delete lnk;
    addon();
    return 0;
}
void addon(void)
{
    cout << "=====附加题=====" << endl;
    elem_t e;
    BinTree<elem_t> * bt = new BinTree<elem_t>;
    // LinerLink<elem_t> * lnk = new LinerLink<elem_t>;
    bt->initializeTable(str);
    cout << "二叉树:" << *bt << endl << "要删除的子树根结点:";
    cin >> e;
    bt->remove(e);
    cout << "删除" << e << "后的二叉树:" << *bt << endl;
    delete bt;
    // delete lnk;
}