#ifndef LINERLINK_H
#define LINERLINK_H

#include <iostream>
#include "Link.h"

template <typename T>
class LinerLink;

template <typename T>
std::ostream &operator<<(std::ostream &_Ostream, LinerLink<T> &_LinerLink);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class LinerLink : public Link<T>
{

public:
    LinerLink() = default;
    ~LinerLink()
    {
        Link<T>::clear();
    }

    friend std::ostream &operator<<<T>(std::ostream &_Ostream, LinerLink<T> &_LinerLink);

    link_size_t find(T _Element) const;
    bool insert(link_size_t _Index, T _Element);
    bool remove(link_size_t _Index);
    bool listReverse(void);

private:
    using Link<T>::_len;
    using Link<T>::_head_ptr;
    using Link<T>::_tail_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream &operator<<(std::ostream &_Ostream, LinerLink<T> &_LinerLink)
{
    LinkNode<T> *head = _LinerLink._head_ptr;
    LinkNode<T> *p = head;
    for (LinkNode<T> *p = head; p != nullptr; p = p->next())
        _Ostream << ((p == head) ? '\0' : ' ') << p->value();
    return _Ostream;
}

template <typename T>
bool LinerLink<T>::insert(link_size_t _Index, T _Element)
{
    if (_len == 0)
        return Link<T>::initialize(_Element);
    LinkNode<T> * p = nullptr;
    if (_Index >= 0)
    {
        if (_Index >= _len)
            return false;
        p = (*this)[_Index];
        if (p == nullptr || p->insert_ahead(_Element) == false)
            return false;
        if (p == _head_ptr)
            _head_ptr = _tail_ptr->_prev_ptr;
    }
    else
    {
        if (-_Index > _len)
            return false;
        p = (*this)[_Index];
        if(p == nullptr || p->insert_behind(_Element) == false)
            return false;
        if(p == _tail_ptr)
            _tail_ptr = _tail_ptr->_next_ptr;
    }
    ++_len;
    return true;
}

template <typename T>
bool LinerLink<T>::remove(link_size_t _Index)
{
    if(_len == 0)
        return false;
    LinkNode<T> *p = nullptr;
    if (_Index >= 0)
    {
        if (_Index > _len)
            return false;
        p = (*this)[_Index];
        if (p == _head_ptr)
            _head_ptr = _head_ptr->_next_ptr;
    }
    else
    {
        if (-_Index > _len + 1)
            return false;
        p = (*this)[_Index];
        if(p == _tail_ptr)
            _tail_ptr = _tail_ptr->_prev_ptr;
    }
    delete p;
    --_len;
    return true;
}

template <typename T>
link_size_t LinerLink<T>::find(T _Element) const
{
    link_size_t cnt = 0;
    LinkNode<T> *p = _head_ptr;
    while (p != nullptr && p->value() != _Element)
    {
        p = p->_next_ptr;
        ++cnt;
    }
    if (cnt == _len)
        return -1;
    else
        return cnt;
}


#endif