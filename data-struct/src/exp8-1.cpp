#include <iostream>
#include "GraphMat.h"
#include "GraphLnk.h"
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

    GraphMat<weight_t, elem_t> gm((weight_t **)A, E, vc, ec);
    GraphLnk<weight_t, elem_t> *gl = new GraphLnk<weight_t, elem_t>(gm);
    cout << "(1)图G的邻接矩阵:" << endl
         << gm << endl;
    cout << "(2)图G的邻接表:" << endl
         << *gl << endl;
    cout << "(3)销毁图G的邻接表" << endl;
    delete gl;
    return 0;
}
