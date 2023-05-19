#ifndef LINKSTACK_H
#define LINKSTACK_H


#include "Link.h"

////////////////////////////////////////////////////////////////////////////////
template<typename T>
class LinkStack : public Link<T>
{
    public:
    LinkStack() = default;
    ~LinkStack(){
        Link<T>::clear();
    }

    bool push(T _Element);
    bool pop(void);
    bool pop(T & _Destination);
    bool GetTop(T & _Destination) const;

    private:
    using Link<T>::_len;
    using Link<T>::_head_ptr;
    using Link<T>::_tail_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool LinkStack<T>::push(T _Element)
{
    if (_len == 0)
        return Link<T>::initialize(_Element);
    else
    {
        if(!(_tail_ptr->insert_behind(_Element)))
            return false;
        _tail_ptr = _tail_ptr->_next_ptr;
    }
    ++_len;
    return true;
}


template <typename T>
bool LinkStack<T>::pop(void)
{
    if(_len <= 0)
        return false;
    LinkNode<T> *pre = _tail_ptr->_prev_ptr;
    if (pre == nullptr)
        _head_ptr = pre;
    delete _tail_ptr;
    _tail_ptr = pre;
    --_len;
    return true;
}


template <typename T>
bool LinkStack<T>::pop(T & _Destination)
{
    if(_len <= 0)
        return false;
    _Destination = _tail_ptr->value();
    LinkNode<T> *pre = _tail_ptr->_prev_ptr;
    if (pre == nullptr)
        _head_ptr = pre;
    delete _tail_ptr;
    _tail_ptr = pre;
    --_len;
    return true;
}


template <typename T>
bool LinkStack<T>::GetTop(T & _Destination) const
{
    if(_len <= 0)
        return false;
    else
        _Destination = _tail_ptr->value();
    return true;
}


#endif