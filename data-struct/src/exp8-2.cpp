#include <iostream>
#include "GraphLnk.h"
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using weight_t = int;
using elem_t = int;
const graph_size_t MAXV = 6;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    weight_t A[MAXV][MAXV] = {
        {0, 5, INF, 7, INF, INF},
        {INF, 0, 4, INF, INF, INF},
        {8, INF, 0, INF, INF, 9},
        {INF, INF, 5, 0, INF, 6},
        {INF, INF, INF, 5, 0, INF},
        {3, INF, INF, INF, 1, 0}};
    graph_size_t ec = 10;
    graph_size_t vc = MAXV;
    elem_t E[MAXV] = {0, 1, 2, 3, 4, 5};
    LinerLink<elem_t> lnk;

    GraphLnk<weight_t, elem_t> gl((weight_t **)A, E, vc, ec);
    cout << "图G的邻接表:" << endl
         << gl << endl;
    gl.DFS(lnk);
    cout << "从顶点0开始的DFS(递归算法):" << endl
         << lnk << endl;
    lnk.clear();
    gl.BFS(lnk);
    cout << "从顶点0开始的BFS:" << endl
         << lnk << endl;
    lnk.clear();
    cout << "==========附加题==========" << endl;
    elem_t v1, v2;
    cout << "第一个节点:";
    cin >> v1;
    cout << "第二个节点:";
    cin >> v2;
    gl.findPath(lnk, v1, v2);
    cout << "节点" << v1 << "到节点" << v2 << "的路径为:" << endl << lnk << endl;
    return 0;
}
