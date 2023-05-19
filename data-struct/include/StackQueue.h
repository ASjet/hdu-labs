#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "LinkStack.h"
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class StackQueue
{
    public:
    StackQueue(){
        _s1 = new LinkStack<int>;
        _s2 = new LinkStack<int>;
    }
    ~StackQueue(){
        delete _s1;
        delete _s2;
    }
    bool push(T _Element);
    bool pop(void);
    bool pop(T &_Destination);
    bool empty(void) const;

    private:
    void swap(void);
    link_size_t _len = 0;
    LinkStack<T> * _s1, *_s2;
};
////////////////////////////////////////////////////////////////////////////////
template<typename T>
void StackQueue<T>::swap(void)
{
    T tmp;
    while(!_s1->empty())
    {
        _s1->pop(tmp);
        _s2->push(tmp);
    }
}


template<typename T>
bool StackQueue<T>::push(T _Element)
{
    if(!(_s1->push(_Element)))
        return false;

    ++_len;
    return true;
}

template<typename T>
bool StackQueue<T>::pop(void)
{
    if(_s2->empty())
        swap();
    --_len;
    return _s2->pop();
}

template<typename T>
bool StackQueue<T>::pop(T &_Destination)
{
    if(_s2->empty())
        swap();
    --_len;
    return _s2->pop(_Destination);
}

template<typename T>
bool StackQueue<T>::empty(void) const
{
    return (_len == 0);
}


#endif