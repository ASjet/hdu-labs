#ifndef GRAPHLNK_H
#define GRAPHLNK_H

#include <iostream>
#include <cassert>
#include <map>
#include "Graph.h"
#include "VertexNode.h"
#include "EdgeNode.h"
#include "LinerLink.h"
#include "SeqStack.h"
#include "CirQueue.h"

template <typename W, typename E>
class GraphLnk;
template <typename W, typename E>
class GraphMat;
#include "GraphMat.h"

template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphLnk<W, E> &_GraphLnk);

template <typename W, typename E>
class GraphLnk
{
public:
    GraphLnk() = default;
    GraphLnk(W **_EdgeMat, E *_Elements, graph_size_t _VertexCount, graph_size_t _EdgeCount)
    {
        _vc = _VertexCount;
        _ec = _EdgeCount;
        VertexNode<W, E> *p = nullptr;
        for (graph_size_t i = 0; i < _vc; ++i)
        {
            p = new VertexNode<W, E>(_Elements[i], p);
            assert((p != nullptr) && "Memory alloc error.");
            if (_head == nullptr)
                _head = p;
        }
        _tail = p;
        p = _head;
        for (graph_size_t i = 0; i < _vc; ++i)
        {
            p->setNeibor(_head, (E *)_EdgeMat + i * _vc, _vc);
            p = p->_next;
        }
    }
    GraphLnk(GraphMat<W, E> &_GraphMat)
    {
        _vc = _GraphMat._size;
        _ec = _GraphMat._ec;
        W **em = _GraphMat._edgemat;
        E *elems = _GraphMat._elems;

        VertexNode<W, E> *p = nullptr;
        for (graph_size_t i = 0; i < _vc; ++i)
        {
            p = new VertexNode<W, E>(elems[i], p);
            assert((p != nullptr) && "Memory alloc error.");
            if (_head == nullptr)
                _head = p;
        }
        _tail = p;
        p = _head;
        for (graph_size_t i = 0; i < _vc; ++i)
        {
            p->setNeibor(_head, em[i], _vc);
            p = p->_next;
        }
    }
    ~GraphLnk()
    {
        VertexNode<W, E> *cur = _head, *next = nullptr;
        while (cur != nullptr)
        {
            next = cur->_next;
            delete cur;
            cur = next;
        }
    }
    friend std::ostream &operator<<<>(std::ostream &_Ostream, GraphLnk<W, E> &_GraphLnk);
    friend class GraphMat<W, E>;

    bool insertVertex(E _Vertex);
    bool insertEdge(E _Vertex1, E _Vertex2, W _Weight);
    bool removeVertex(E _Vertex);
    bool removeEdge(E _Vertex1, E _Vertex2);
    bool empty(void) const;
    bool getWeight(E _Vertex1, E _Vertex2, W &_Dest) const;
    bool getFirstNeibor(E _Vertex, E &_Dest);
    bool getNextNeibor(E _Vertex, E &_Dest);
    void DFS(LinerLink<E> &_Lnk);
    void BFS(LinerLink<E> &_Lnk);
    bool findPath(LinerLink<E> &_Lnk, E _Vertex1, E _Vertex2);

private:
    EdgeNode<W, E> *findEdge(E _Vertex1, E _Vertex2) const;
    VertexNode<W, E> *findVertex(E _Vertex) const;
    void DFS(VertexNode<W, E> *_CurNode, LinerLink<E> &_Lnk, std::map<VertexNode<W, E> *, bool> &_Visit);

    graph_size_t _vc = 0;
    graph_size_t _ec = 0;
    VertexNode<W, E> *_head = nullptr;
    VertexNode<W, E> *_tail = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphLnk<W, E> &_GraphLnk)
{
    VertexNode<W, E> *p = _GraphLnk._head;
    EdgeNode<W, E> *e = nullptr;
    while (p != nullptr)
    {
        _Ostream << p->_value << ":\t";
        e = p->_edge_head;
        while (e != nullptr)
        {
            _Ostream << e->_out->_value << '[' << e->_weight << "]->";
            e = e->_next;
        }
        _Ostream << "∧" << std::endl;
        p = p->_next;
    }
    return _Ostream;
}

template <typename W, typename E>
EdgeNode<W, E> *GraphLnk<W, E>::findEdge(E _Vertex1, E _Vertex2) const
{
    VertexNode<W, E> *in = nullptr, *out = nullptr;
    for (VertexNode<W, E> *p = _head; p != nullptr; p->_next)
        if (p->_value == _Vertex1)
        {
            in = p;
            break;
        }
    out = in->firstNeibor();
    while (out != nullptr)
    {
        if (out->_value == _Vertex2)
            break;
        out = in->nextNeibor();
    }
    return in->_sel;
}

template <typename W, typename E>
VertexNode<W, E> *GraphLnk<W, E>::findVertex(E _Vertex) const
{
    VertexNode<W, E> *p = _head;
    while (p != nullptr)
    {
        if (p->_value == _Vertex)
            return p;
        p = p->_next;
    }
    return nullptr;
}

template <typename W, typename E>
bool GraphLnk<W, E>::insertVertex(E _Vertex)
{
    VertexNode<W, E> *p = new VertexNode<W, E>(_Vertex, _tail);
    if (p == nullptr)
        return false;
    _tail = p;
    ++_vc;
    return true;
}

template <typename W, typename E>
bool GraphLnk<W, E>::insertEdge(E _Vertex1, E _Vertex2, W _Weight)
{
    VertexNode<W, E> *in = findVertex(_Vertex1);
    VertexNode<W, E> *out = findVertex(_Vertex2);
    if (in == nullptr || out == nullptr)
        return false;

    if (!in->addNeibor(out, _Weight))
        return false;
    ++_ec;
    return true;
}

template <typename W, typename E>
bool GraphLnk<W, E>::removeVertex(E _Vertex)
{
    VertexNode<W, E> *p = findVertex(_Vertex);
    if (p == nullptr)
        return false;
    delete p;
    --_vc;
    return true;
}

template <typename W, typename E>
bool GraphLnk<W, E>::removeEdge(E _Vertex1, E _Vertex2)
{
    EdgeNode<W, E> *p = findEdge(_Vertex1, _Vertex2);
    if (p == nullptr)
        return false;
    --_ec;
    return true;
}

template <typename W, typename E>
bool GraphLnk<W, E>::empty(void) const
{
    return (_vc == 0);
}

template <typename W, typename E>
bool GraphLnk<W, E>::getWeight(E _Vertex1, E _Vertex2, W &_Dest) const
{
    EdgeNode<W, E> *p = findEdge(_Vertex1, _Vertex2);
    if (p == nullptr)
        return false;
    return p->weight();
}

template <typename W, typename E>
bool GraphLnk<W, E>::getFirstNeibor(E _Vertex, E &_Dest)
{
    VertexNode<W, E> *p = findVertex(_Vertex);
    if (p == nullptr)
        return false;
    p = p->firstNeibor();
    if (p == nullptr)
        return false;
    _Dest = p->_value;
    return true;
}

template <typename W, typename E>
bool GraphLnk<W, E>::getNextNeibor(E _Vertex, E &_Dest)
{
    VertexNode<W, E> *p = findVertex(_Vertex);
    if (p == nullptr)
        return false;
    p = p->nextNeibor();
    if (p == nullptr)
        return false;
    _Dest = p->_value;
    return true;
}

template <typename W, typename E>
void GraphLnk<W, E>::DFS(LinerLink<E> &_Lnk)
{
    std::map<VertexNode<W, E> *, bool> visit;
    for (VertexNode<W, E> *p = _head; p != nullptr; p = p->_next)
        visit[p] = false;
    DFS(_head, _Lnk, visit);
}

template <typename W, typename E>
void GraphLnk<W, E>::DFS(VertexNode<W, E> *_CurNode, LinerLink<E> &_Lnk, std::map<VertexNode<W, E> *, bool> &_Visit)
{
    _Lnk.insert(-1, _CurNode->_value);
    _Visit[_CurNode] = true;
    VertexNode<W, E> *neibor = _CurNode->firstNeibor();
    while (neibor != nullptr)
    {
        if (_Visit[neibor] == false)
            DFS(neibor, _Lnk, _Visit);
        neibor = _CurNode->nextNeibor();
    }
}

template <typename W, typename E>
void GraphLnk<W, E>::BFS(LinerLink<E> &_Lnk)
{
    std::map<VertexNode<W, E> *, bool> visit;
    for (VertexNode<W, E> *p = _head; p != nullptr; p = p->_next)
        visit[p] = false;
    CirQueue<VertexNode<W, E> *> cq(_vc);
    cq.push(_head);
    VertexNode<W, E> *p = nullptr, *neibor = nullptr;
    while (cq.pop(p))
    {
        if (visit[p] == true)
            continue;
        visit[p] = true;
        _Lnk.insert(-1, p->_value);
        neibor = p->firstNeibor();
        while (neibor != nullptr)
        {
            if (visit[neibor] == false)
                cq.push(neibor);
            neibor = p->nextNeibor();
        }
    }
}

template <typename W, typename E>
bool GraphLnk<W, E>::findPath(LinerLink<E> &_Lnk, E _Vertex1, E _Vertex2)
{
    std::map<VertexNode<W, E> *, bool> visit;
    for (VertexNode<W, E> *p = _head; p != nullptr; p = p->_next)
        visit[p] = false;

    VertexNode<W, E> * v1 = findVertex(_Vertex1);
    VertexNode<W, E> * v2 = findVertex(_Vertex2);
    if(v1 == nullptr || v2 == nullptr)
        return false;

    CirQueue<VertexNode<W, E> *> cq(_vc);
    SeqStack<VertexNode<W, E> *> s(_vc);
    cq.push(v1);
    VertexNode<W, E> *p = nullptr, *neibor = nullptr, *back = nullptr;
    while (cq.pop(p))
    {
        if (visit[p] == true)
            continue;
        visit[p] = true;
        s.push(p);
        // _Lnk.insert(-1, p->_value);
        if(p->_value == _Vertex2)
        {
            _Lnk.insert(0, p->_value);
            while(!s.empty())
            {
                s.pop(back);
                if(back->haveNeibor(p))
                {
                    _Lnk.insert(0, back->_value);
                    p = back;
                }
            }
            break;
        }
        neibor = p->firstNeibor();
        while (neibor != nullptr)
        {
            if (visit[neibor] == false)
                cq.push(neibor);
            neibor = p->nextNeibor();
        }
    }
    return true;
}

#endif