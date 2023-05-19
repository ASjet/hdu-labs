#ifndef EDGENODE_H
#define EDGENODE_H

template <typename W, typename E>
class EdgeNode;

#include "VertexNode.h"

template <typename W, typename E>
class GraphLnk;
template <typename W, typename E>
std::ostream& operator<<(std::ostream& _Ostream, GraphLnk<W, E>& _GraphLnk);

template <typename W, typename E>
class EdgeNode
{
    public:
    EdgeNode() = default;
    EdgeNode(VertexNode<W, E> * _In, VertexNode<W, E> * _Out, W _Weight, EdgeNode<W, E> * _Prev)
    {
        _in = _In;
        _out = _Out;
        _weight = _Weight;
        _prev = _Prev;
        if(_prev != nullptr)
            _prev->_next = this;
    }
    ~EdgeNode()
    {
        if(_prev != nullptr)
            _prev->_next = _next;
        if(_next != nullptr)
            _next->_prev = _prev;
    }
    friend std::ostream& operator<<<>(std::ostream& _Ostream, GraphLnk<W, E>& _GraphLnk);
    friend class VertexNode<W, E>;
    VertexNode<W, E> * out(void) const;
    W weight(void) const;
    private:
    VertexNode<W, E> * _in = nullptr;
    VertexNode<W, E> * _out = nullptr;
    EdgeNode<W, E> * _prev = nullptr;
    EdgeNode<W, E> * _next = nullptr;
    E _weight;
};


template <typename W, typename E>
VertexNode<W,E> * EdgeNode<W, E>::out(void) const
{
    return _out;
}


template <typename W, typename E>
W EdgeNode<W, E>::weight(void) const
{
    return _weight;
}



#endif