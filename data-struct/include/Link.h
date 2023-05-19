#ifndef LINK_H
#define LINK_H


#include <cassert>
#include "LinkNode.h"
using link_size_t = int;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Link
{
public:
    Link() = default;
    virtual ~Link()
    {
        clear();
    }
    LinkNode<T> *operator[](link_size_t _Index);
    bool initialize(T _Element);
    void initialize(LinkNode<T> *_HeadPtr, LinkNode<T> *_TailPtr, link_size_t _Length);
    bool initializeL(T *_Base, link_size_t _Length);
    bool initializeR(T *_Base, link_size_t _Length);
    void clear(void);
    LinkNode<T> *head(void) const;
    LinkNode<T> *tail(void) const;
    bool empty(void) const;
    link_size_t length(void) const;

protected:
    LinkNode<T> *_head_ptr = nullptr;
    LinkNode<T> *_tail_ptr = nullptr;
    link_size_t _len = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkNode<T> *Link<T>::operator[](link_size_t _Index)
{
    LinkNode<T> *p = nullptr;
    if(_Index >= 0)
    {
        assert((_Index < _len) && "Error: Index out of range\n");
        p = _head_ptr;
        for (link_size_t i = 0; i < _Index; ++i)
            p = p->_next_ptr;
    }
    else
    {
        assert((-_Index <= _len) && "Error: Index out of range\n");
        p = _tail_ptr;
        for(link_size_t i = _Index; i < -1; ++i)
            p = p->_prev_ptr;
    }
    return p;
}


template <typename T>
bool Link<T>::initialize(T _Element)
{
    clear();
    _head_ptr = new LinkNode<T>(_Element);
    if(_head_ptr == nullptr)
        return false;

    _tail_ptr = _head_ptr;
    _len = 1;
    return true;
}


template <typename T>
bool Link<T>::initializeL(T *_Base, link_size_t _Length)
{
    if(initialize(_Base[0]) == false)
    {
        clear();
        return false;
    }
    LinkNode<T> *p = _head_ptr;
    for (link_size_t i = 1; i < _Length; ++i)
    {
        if(p->insert_ahead(_Base[i]) == false)
        {
            clear();
            return false;
        }
        p = p->_prev_ptr;
        ++_len;
    }
    _head_ptr = p;
    return true;
}


template <typename T>
bool Link<T>::initializeR(T *_Base, link_size_t _Length)
{
    if(initialize(_Base[0]) == false)
    {
        clear();
        return false;
    }

    LinkNode<T> *p = _tail_ptr;
    for(link_size_t i = 1; i < _Length; ++i)
    {
        if(p->insert_behind(_Base[i]) == false)
        {
            clear();
            return false;
        }
        p = p->_next_ptr;
        ++_len;
    }
    _tail_ptr = p;
    return true;
}


template <typename T>
void Link<T>::initialize(LinkNode<T> *_HeadPtr, LinkNode<T> *_TailPtr, link_size_t _Length)
{
    _head_ptr = _HeadPtr;
    _tail_ptr = _TailPtr;
    _len = _Length;
    _head_ptr->_prev_ptr = nullptr;
    _tail_ptr->_next_ptr = nullptr;
}


template <typename T>
void Link<T>::clear()
{
    LinkNode<T> *cur = _head_ptr, *next;
    while (_len--)
    {
        next = cur->_next_ptr;
        delete cur;
        cur = next;
    }
    _head_ptr = nullptr;
    _tail_ptr = nullptr;
    _len = 0;
}


template <typename T>
bool Link<T>::empty(void) const
{
    return (_len == 0);
}


template <typename T>
LinkNode<T> *Link<T>::head(void) const
{
    return _head_ptr;
}


template <typename T>
LinkNode<T> *Link<T>::tail(void) const
{
    return _tail_ptr;
}


template <typename T>
link_size_t Link<T>::length(void) const
{
    return _len;
}


#endif
