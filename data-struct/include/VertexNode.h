#ifndef VERTEXNODE_H
#define VERTEXNODE_H

#include <cassert>
template <typename W, typename E>
class VertexNode;
#include "EdgeNode.h"

template <typename W, typename E>
class GraphLnk;
template <typename W, typename E>
class GraphMat;

template <typename W, typename E>
std::ostream& operator<<(std::ostream& _Ostream, GraphLnk<W, E>& _GraphLnk);
template <typename W, typename E>
class VertexNode
{
public:
    VertexNode() = default;
    VertexNode(E _Value, VertexNode<W, E> *_Prev)
    {
        _value = _Value;
        _prev = _Prev;
        if(_prev != nullptr)
            _prev->_next = this;

    }
    ~VertexNode()
    {
        if(_prev != nullptr)
            _prev->_next = nullptr;
        if(_next != nullptr)
            _next->_prev = nullptr;
        EdgeNode<W, E> *cur = _edge_tail, *pre = nullptr;
        while (cur != nullptr)
        {
            pre = cur->_prev;
            delete cur;
            cur = pre;
        }
    }
    friend std::ostream& operator<<<>(std::ostream& _Ostream, GraphLnk<W, E>& _GraphLnk);
    friend class GraphLnk<W, E>;
    friend class GraphMat<W, E>;
    VertexNode<W, E> * operator[](graph_size_t _Index);
    bool setNeibor(VertexNode<W, E> * _Head, W * _Edges, graph_size_t _Length);
    VertexNode<W, E> *firstNeibor(void);
    VertexNode<W, E> *nextNeibor(void);
    EdgeNode<W, E> * findEdgeNode(E _Vertex);
    bool addNeibor(VertexNode<W, E>* _Out, W _Weight);
    bool haveNeibor(VertexNode<W, E>* _Out);
    E value(void) const;

private:
    VertexNode<W, E> *_prev = nullptr;
    VertexNode<W, E> *_next = nullptr;
    E _value;
    EdgeNode<W, E> *_edge_head = nullptr;
    EdgeNode<W, E> *_edge_tail = nullptr;
    EdgeNode<W, E> *_sel = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
VertexNode<W, E> * VertexNode<W, E>::operator[](graph_size_t _Index)
{
    VertexNode<W, E> * p = this;
    for(graph_size_t i = 0; i < _Index; ++i)
    {
        assert((p != nullptr) && "Index out of range.");
        p = p->_next;
    }
    return p;
}


template <typename W, typename E>
VertexNode<W, E> *VertexNode<W, E>::firstNeibor(void)
{
    _sel = _edge_head;
    if(_sel == nullptr)
        return nullptr;
    return _sel->out();
}


template <typename W, typename E>
VertexNode<W, E> * VertexNode<W,E>::nextNeibor(void)
{
    if(_sel == nullptr)
        return nullptr;

    _sel = _sel->_next;

    if(_sel == nullptr)
        return nullptr;

    return _sel->out();
}


template <typename W, typename E>
bool VertexNode<W, E>::setNeibor(VertexNode<W, E> * _Head, W * _Edges, graph_size_t _Length)
{
    EdgeNode<W, E> *p = nullptr;
    for (graph_size_t i = 0; i < _Length; ++i)
    {
        VertexNode<W, E>* out = (*_Head)[i];
        if(_Edges[i] == INF || this == out)
            continue;
        p = new EdgeNode<W, E>(this, out, _Edges[i], _edge_tail);
        if(p == nullptr)
            return false;
        if(_edge_head == nullptr)
            _edge_head = p;
        _edge_tail = p;
    }
    return true;
}


template <typename W, typename E>
EdgeNode<W, E> * VertexNode<W, E>::findEdgeNode(E _Out)
{
    for(EdgeNode<W, E>* p = _edge_head; p != nullptr; p = p->_next)
        if(p->_out->_value == _Out)
            return p;
    return nullptr;
}


template <typename W, typename E>
E VertexNode<W, E>::value(void) const
{
    return _value;
}


template <typename W, typename E>
bool VertexNode<W, E>::addNeibor(VertexNode<W, E>* _Out, W _Weight)
{
    EdgeNode<W, E> * p = new EdgeNode<W, E>(this, _Out, _Weight, _edge_tail);
    if(p == nullptr)
        return false;
    _edge_tail = p;
    return true;
}


template <typename W, typename E>
bool VertexNode<W, E>::haveNeibor(VertexNode<W, E>* _Out)
{
    for(EdgeNode<W, E> * p = _edge_head; p != nullptr; p = p->_next)
        if(p->_out == _Out)
            return true;
    return false;
}


#endif