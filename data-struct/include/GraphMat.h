#ifndef GRAPHMAT_H
#define GRAPHMAT_H

#include <iostream>
#include <string>

#include "CirQueue.h"
#include "Graph.h"
#include "LinerLink.h"
#include "SeqStack.h"

template <typename W, typename E> class GraphMat;
template <typename W, typename E> class GraphLnk;
#include "GraphLnk.h"
template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphMat<W, E> &_GraphMat);

template <typename W, typename E> class GraphMat {
  public:
    GraphMat() = default;
    GraphMat(W **_EdgeMat, E *_Elements, graph_size_t _VertexCount,
             graph_size_t _EdgeCount) {
        _size = _VertexCount;
        _vc = _size;
        _ec = _EdgeCount;
        _edgemat = new W *[_size];
        for (graph_size_t i = 0; i < _size; ++i)
            _edgemat[i] = new W[_size];
        _elems = new E[_size];
        _sels = new E[_size];

        for (graph_size_t i = 0; i < _size; ++i) {
            _elems[i] = _Elements[i];
            for (graph_size_t j = 0; j < _size; ++j)
                _edgemat[i][j] = *((W *)_EdgeMat + i * _size + j);
        }
    }
    GraphMat(GraphLnk<W, E> &_GraphLnk) {
        _size = _GraphLnk._vc;
        _vc = _size;
        _ec = _GraphLnk._ec;
        _edgemat = new W *[_size];
        for (graph_size_t i = 0; i < _size; ++i)
            _edgemat[i] = new W[_size];
        _elems = new E[_size];
        _sels = new E[_size];

        VertexNode<W, E> *v = _GraphLnk._head;
        for (graph_size_t i = 0; v != nullptr && i < _size; ++i, v = v->_next)
            _elems[i] = v->_value;

        EdgeNode<W, E> *e = nullptr;
        v = _GraphLnk._head;
        for (graph_size_t i = 0; v != nullptr && i < _size; ++i, v = v->_next) {
            v->firstNeibor();
            e = v->_sel;
            if (e == nullptr)
                continue;
            for (graph_size_t j = 0; j < _size; ++j) {
                if (i == j)
                    _edgemat[i][j] = 0;
                else if (_elems[j] == e->out()->value()) {
                    _edgemat[i][j] = e->weight();
                    if (v->nextNeibor() == nullptr)
                        continue;
                    e = v->_sel;
                } else
                    _edgemat[i][j] = INF;
            }
        }
    }
    ~GraphMat() {
        for (graph_size_t i = 0; i < _vc; ++i)
            delete[] _edgemat[i];
        delete[] _edgemat;
        delete[] _elems;
        delete[] _sels;
    }

    friend std::ostream &operator<<<>(std::ostream &_Ostream,
                                      GraphMat<W, E> &_GraphMat);
    friend class GraphLnk<W, E>;

    bool insertVertex(E _Vertex, E _Value);
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
    graph_size_t findVertex(E _Vertex) const;
    void DFS(graph_size_t _CurLocal, LinerLink<E> &_Lnk, bool *_Visit);
    graph_size_t _size = 0;
    graph_size_t _vc = 0;
    graph_size_t _ec = 0;
    W **_edgemat = nullptr;
    E *_elems = nullptr;
    E *_sels = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphMat<W, E> &_GraphMat) {
    graph_size_t length = _GraphMat._size;
    E *es = _GraphMat._elems;
    W **em = _GraphMat._edgemat;
    for (graph_size_t i = 0; i < length; ++i)
        _Ostream << ((i == 0) ? "  " : " ") << es[i];
    _Ostream << std::endl;
    for (graph_size_t i = 0; i < length; ++i) {
        _Ostream << es[i];
        for (graph_size_t j = 0; j < length; ++j)
            _Ostream << ' '
                     << ((em[i][j] == INF) ? std::string("∞")
                                           : std::to_string(em[i][j]));
        _Ostream << std::endl;
    }
    return _Ostream;
}

template <typename W, typename E>
graph_size_t GraphMat<W, E>::findVertex(E _Vertex) const {
    for (graph_size_t i = 0; i < _size; ++i)
        if (_elems[i] == _Vertex)
            return i;
    return -1;
}

template <typename W, typename E>
bool GraphMat<W, E>::insertVertex(E _Vertex, E _Value) {
    if (_vc == _size)
        return false;
    _elems[_vc] = _Value;
    ++_vc;
    return true;
}

template <typename W, typename E>
bool GraphMat<W, E>::insertEdge(E _Vertex1, E _Vertex2, W _Weight) {
    graph_size_t v1 = findVertex(_Vertex1);
    graph_size_t v2 = findVertex(_Vertex2);

    if (v1 == -1 || v2 == -1)
        return false;
    _edgemat[v1][v2] = _Weight;
    ++_ec;
    return true;
}

template <typename W, typename E> bool GraphMat<W, E>::removeVertex(E _Vertex) {
    graph_size_t v = findVertex(_Vertex);
    if (v == -1)
        return false;
    for (graph_size_t i = 0; i < _size; ++i)
        _edgemat[v][i] = INF;
    _elems[v] = 0;
    --_vc;
    return true;
}

template <typename W, typename E>
bool GraphMat<W, E>::removeEdge(E _Vertex1, E _Vertex2) {
    graph_size_t v1 = findVertex(_Vertex1);
    graph_size_t v2 = findVertex(_Vertex2);

    if (v1 == -1 || v2 == -1)
        return false;
    _edgemat[v1][v2] = INF;
    --_ec;
    return true;
}

template <typename W, typename E> bool GraphMat<W, E>::empty(void) const {
    return (_vc == 0);
}

template <typename W, typename E>
bool GraphMat<W, E>::getWeight(E _Vertex1, E _Vertex2, W &_Dest) const {
    graph_size_t v1 = findVertex(_Vertex1);
    graph_size_t v2 = findVertex(_Vertex2);

    if (v1 == -1 || v2 == -1)
        return false;
    _Dest = _edgemat[v1][v2];
    return true;
}

template <typename W, typename E>
bool GraphMat<W, E>::getFirstNeibor(E _Vertex, E &_Dest) {
    graph_size_t v = findVertex(_Vertex);
    if (v == -1)
        return false;

    W *em = _edgemat[v];
    _sels[v] = 0;
    for (graph_size_t i = 0; i < _size; ++i)
        if (em[i] != INF && i != v) {
            _sels[v] = i;
            break;
        }
    _Dest = _elems[_sels[v]];
    return true;
}

template <typename W, typename E>
bool GraphMat<W, E>::getNextNeibor(E _Vertex, E &_Dest) {
    graph_size_t v = findVertex(_Vertex);
    if (v == -1)
        return false;
    W *em = _edgemat[v];
    for (graph_size_t i = _sels[v] + 1; i < _size; ++i) {
        if (em[i] != INF && i != v) {
            _sels[v] = i;
            _Dest = _elems[_sels[v]];
            return true;
        }
    }
    return false;
}

template <typename W, typename E> void GraphMat<W, E>::DFS(LinerLink<E> &_Lnk) {
    bool visit[_vc] = {false};
    DFS(0, _Lnk, visit);
}

template <typename W, typename E>
void GraphMat<W, E>::DFS(graph_size_t _CurLocal, LinerLink<E> &_Lnk,
                         bool *_Visit) {
    E value = _elems[_CurLocal], neibor = 0;
    _Visit[_CurLocal] = true;
    _Lnk.insert(-1, value);
    if (getFirstNeibor(value, neibor) == true) {
        graph_size_t i = findVertex(neibor);
        while (i != -1) {
            if (_Visit[i] == false)
                DFS(i, _Lnk, _Visit);
            if (getNextNeibor(value, neibor) == false)
                break;
            i = findVertex(neibor);
        }
    }
}

template <typename W, typename E> void GraphMat<W, E>::BFS(LinerLink<E> &_Lnk) {
    bool visit[_vc] = {false};
    CirQueue<graph_size_t> cq(_size);
    cq.push(0);
    E value = 0, neibor = 0;
    graph_size_t i = 0;
    while (cq.pop(i)) {
        if (visit[i] == true)
            continue;
        visit[i] = true;
        value = _elems[i];
        _Lnk.insert(-1, value);
        if (getFirstNeibor(value, neibor) == true) {
            i = findVertex(neibor);
            while (i != -1) {
                if (visit[i] == false)
                    cq.push(i);
                if (getNextNeibor(value, neibor) == false)
                    break;
                i = findVertex(neibor);
            }
        }
    }
}

template <typename W, typename E>
bool GraphMat<W, E>::findPath(LinerLink<E> &_Lnk, E _Vertex1, E _Vertex2) {
    graph_size_t v1 = findVertex(_Vertex1);
    graph_size_t v2 = findVertex(_Vertex2);
    if (v1 == -1 || v2 == -1)
        return false;

    bool visit[_vc] = {false};
    CirQueue<graph_size_t> cq(_size);
    SeqStack<graph_size_t> s(_size);
    cq.push(v1);
    E value = 0, neibor = 0;
    graph_size_t i = 0, j = 0;
    while (cq.pop(i)) {
        if (visit[i] == true)
            continue;
        visit[i] = true;
        value = _elems[i];
        s.push(i);
        if (value == _Vertex2) {
            while (!s.empty()) {
                s.pop(j);
                if (_edgemat[j][i] != INF) {
                    _Lnk.insert(0, _elems[j]);
                    i = j;
                }
            }
            break;
        }
        if (getFirstNeibor(value, neibor) == true) {
            i = findVertex(neibor);
            while (i != -1) {
                if (visit[i] == false)
                    cq.push(i);
                if (getNextNeibor(value, neibor) == false)
                    break;
                i = findVertex(neibor);
            }
        }
    }
    return true;
}

#endif