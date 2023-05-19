#ifndef CLink_H
#define CLink_H

#include <iostream>
#include "Link.h"
using clink_size_t = int;

template <typename T>
class CLink;

template <typename T>
std::ostream &operator<<(std::ostream &_Ostream, CLink<T> &_Clink);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class CLink : public Link<T>
{

public:
    CLink() = default;
    ~CLink()
    {
        Link<T>::clear();
    }
    friend std::ostream &operator<<<T>(std::ostream &_Ostream, CLink<T> &_Clink);

    bool initialize(T _Element);
    bool initializeL(T *_Base, link_size_t _Length);
    bool initializeR(T *_Base, link_size_t _Length);
    using Link<T>::clear;
    void disp(bool _Inverse) const;
    link_size_t find(T _Element) const;
    bool insert(link_size_t _Index, T _Element);
    T remove(link_size_t _Index);

private:
    using Link<T>::tail;
    using Link<T>::_len;
    using Link<T>::_head_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CLink<T>::disp(bool _Inverse) const
{
    LinkNode<T> *head = _head_ptr;
    LinkNode<T> *p = head;
    do
    {
        std::cout << ((p == _head_ptr) ? '\0' : ' ') << p->value();
        p = (_Inverse) ? p->_prev_ptr : p->_next_ptr;
    }while(p != head);
    std::cout << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &_Ostream, CLink<T> &_Clink)
{
    LinkNode<T> *head = _Clink._head_ptr;
    LinkNode<T> *p = head;
    do
    {
        _Ostream << ((p == head) ? '\0' : ' ') << p->value();
        p = p->next();
    } while (p != head);
    return _Ostream;
}

template <typename T>
bool CLink<T>::initialize(T _Element)
{
    clear();
    _head_ptr = new LinkNode<T>(_Element);
    if (_head_ptr == nullptr)
        return false;
    _head_ptr->_next_ptr = _head_ptr;
    _head_ptr->_prev_ptr = _head_ptr;
    _len = 1;
    return true;
}

template <typename T>
bool CLink<T>::initializeL(T *_Base, link_size_t _Length)
{
    clear();
    _head_ptr = new LinkNode<T>;
    if (_head_ptr == nullptr)
        return false;
    LinkNode<T> *p = _head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->_prev_ptr = new LinkNode<T>;
            if (p->_prev_ptr == nullptr)
            {
                clear();
                return false;
            }
            p->_prev_ptr->_next_ptr = p;
            p = p->_prev_ptr;
        }
        p->value() = _Base[i];
        ++_len;
    }
    p->_prev_ptr = _head_ptr;
    _head_ptr->_next_ptr = p;
    _head_ptr = p;
    return true;
}

template <typename T>
bool CLink<T>::initializeR(T *_Base, link_size_t _Length)
{
    clear();
    _head_ptr = new LinkNode<T>;
    if (_head_ptr == nullptr)
        return false;
    LinkNode<T> *p = _head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->_next_ptr = new LinkNode<T>;
            if (p->_next_ptr == nullptr)
            {
                clear();
                return false;
            }
            p->_next_ptr->_prev_ptr = p;
            p = p->_next_ptr;
        }
        ++_len;
        p->value() = _Base[i];
    }
    p->_next_ptr = _head_ptr;
    _head_ptr->_prev_ptr = p;
    return true;
}

template <typename T>
bool CLink<T>::insert(link_size_t _Index, T _Element)
{
    if (_len == 0)
        return initialize(_Element);
    else if (_Index == _len || _Index == -1)
    {
        _head_ptr->_prev_ptr->_next_ptr = new LinkNode<T>(_Element);
        if (_head_ptr->_prev_ptr->_next_ptr == nullptr)
        {
            _head_ptr->_prev_ptr->_next_ptr = _head_ptr;
            return false;
        }
        _head_ptr->_prev_ptr->_next_ptr->_next_ptr = _head_ptr;
        _head_ptr->_prev_ptr = _head_ptr->_prev_ptr->_next_ptr;
    }
    else
    {
        LinkNode<T> *cur = (*this)[_Index];
        cur->_next_ptr->_prev_ptr = new LinkNode<T>(_Element);
        if (cur->_next_ptr->_prev_ptr == nullptr)
        {
            cur->_next_ptr->_prev_ptr = cur;
            return false;
        }
        cur->_next_ptr->_prev_ptr->_prev_ptr = cur;
        cur->_next_ptr = cur->_next_ptr->_prev_ptr;
        if (cur == _head_ptr)
            _head_ptr = cur->_prev_ptr;
    }
    ++_len;
    return true;
}

template <typename T>
T CLink<T>::remove(link_size_t _Index)
{
    T res;
    LinkNode<T> *p = (*this)[_Index];
    res = p->value();
    if (p == _head_ptr)
    {
        _head_ptr = p->_next_ptr;
        _head_ptr->_prev_ptr = p->_prev_ptr;
    }
    delete p;
    --_len;
    return res;
}

template <typename T>
link_size_t CLink<T>::find(T _Element) const
{
    link_size_t cnt = 0;
    LinkNode<T> *p = _head_ptr;
    while (p->value() != _Element)
    {
        p = p->_next_ptr;
        ++cnt;
    }
    return cnt;
}

#endif