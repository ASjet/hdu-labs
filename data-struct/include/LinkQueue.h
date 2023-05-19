#ifndef LINKQUEUE_H
#define LINKQUEUE_H


#include <iostream>
#include "Link.h"

template <typename T>
class LinkQueue;

template <typename T>
std::ostream &operator<<(std::ostream &_Ostream, LinkQueue<T> &_LinkQueue);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class LinkQueue : public Link<T>
{
public:
    LinkQueue() = default;
    ~LinkQueue()
    {
        Link<T>::clear();
    }
    using Link<T>::initialize;
    bool push(T _Element);
    bool pop(T &_Destination);
    bool pop(void);
    friend std::ostream &operator<<<T>(std::ostream &_Ostream, LinkQueue<T> &_LinkQueue);

private:
    using Link<T>::_len;
    using Link<T>::_head_ptr;
    using Link<T>::_tail_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream &operator<<(std::ostream &_Ostream, LinkQueue<T> &_LinkQueue)
{
    LinkNode<T> *head = _LinkQueue._head_ptr;
    for(LinkNode<T>* p = head; p != nullptr; p->next())
        _Ostream << ((p == head) ? '\0' : ' ') << p->value();
    return _Ostream;
}


template <typename T>
bool LinkQueue<T>::push(T _Element)
{
    if (_len == 0)
        return initialize(_Element);
    else
    {
        if (_tail_ptr->insert_behind(_Element))
            _tail_ptr = _tail_ptr->_next_ptr;
        else
            return false;
    }
    ++_len;
    return true;
}


template <typename T>
bool LinkQueue<T>::pop(void)
{
    if (_len <= 0)
        return false;
    LinkNode<T> *next = _head_ptr->_next_ptr;
    delete _head_ptr;
    _head_ptr = next;
    --_len;
    return true;
}


template <typename T>
bool LinkQueue<T>::pop(T &_Destination)
{
    if (_len <= 0)
        return false;
    _Destination = _head_ptr->value();
    LinkNode<T> *next = _head_ptr->_next_ptr;
    delete _head_ptr;
    _head_ptr = next;
    --_len;
    return true;
}


#endif