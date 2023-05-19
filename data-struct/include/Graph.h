#ifndef GRAPH_H
#define GRAPH_H


#define INF -1
using graph_size_t = int;


template <typename W, typename E>
class Graph
{
    public:
    Graph() = default;
    virtual bool insertVertex() = 0;
    virtual bool insertEdge() = 0;
    virtual bool removeVertex() = 0;
    virtual bool removeEdge() = 0;
    virtual bool empty(void) const = 0;
    virtual bool getWeight() const = 0;
    virtual bool getFirstNeibor()= 0;
    virtual bool getNextNeibor()= 0;
    virtual void DFS() = 0;
    virtual void BFS() = 0;
};

#endif