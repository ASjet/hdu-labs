#ifndef SHARESTACK_H
#define SHARESTACK_H


#include "Array.h"
enum STACK_FLAG
{
    LEFT_STACK,
    RIGHT_STACK
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ShareStack : public Array<T>
{
public:
    ShareStack() = default;
    ShareStack(array_size_t _Size) : Array<T>(_Size) {
        _spl = 0;
        _spr = _size - 1;
        _lenl = 0;
        _lenr = 0;
    }
    ~ShareStack() = default;

    void clear(STACK_FLAG _Flag);
    bool push(T _Element, STACK_FLAG _Flag);
    bool pop(STACK_FLAG _Flag);
    bool pop(T *_Destination, STACK_FLAG _Flag);
    bool GetTop(T *_Destination, STACK_FLAG _Flag) const;
    bool isEmpty(STACK_FLAG _Flag) const;
    bool isFull(void) const;

private:
    using Array<T>::_base;
    using Array<T>::_size;
    array_size_t _spl;
    array_size_t _spr;
    array_size_t _lenl;
    array_size_t _lenr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void ShareStack<T>::clear(STACK_FLAG _Flag)
{
    if (_Flag == RIGHT_STACK)
    {
        _spr = _size - 1;
        _lenr = 0;
    }
    else
    {
        _spl = 0;
        _lenl = 0;
    }
}


template <typename T>
bool ShareStack<T>::push(T _Element, STACK_FLAG _Flag)
{
    if (isFull())
        return false;

    if (_Flag == RIGHT_STACK)
    {
        _base[_spr] = _Element;
        --_spr;
        ++_lenr;
    }
    else
    {
        _base[_spl] = _Element;
        ++_spl;
        ++_lenl;
    }
    return true;
}


template <typename T>
bool ShareStack<T>::pop(STACK_FLAG _Flag)
{
    if (isEmpty(_Flag))
        return false;

    if (_Flag == RIGHT_STACK)
    {
        ++_spr;
        --_lenr;
    }
    else
    {
        --_spl;
        --_lenl;
    }
    return true;
}


template <typename T>
bool ShareStack<T>::pop(T *_Destination, STACK_FLAG _Flag)
{
    if (pop(_Flag) == false)
        return false;

    int sp = (_Flag == RIGHT_STACK) ? _spr : _spl;
    *_Destination = _base[sp];
    return true;
}


template <typename T>
bool ShareStack<T>::GetTop(T *_Destination, STACK_FLAG _Flag) const
{
    if (isEmpty(_Flag))
        return false;

    if(_Flag == RIGHT_STACK)
        *_Destination = _base[_spr+1];
    else
        *_Destination = _base[_spl-1];
    return true;
}


template <typename T>
bool ShareStack<T>::isEmpty(STACK_FLAG _FLAG) const
{
    int len = (_FLAG == RIGHT_STACK) ? _lenr : _lenl;
    return (len == 0);
}


template <typename T>
bool ShareStack<T>::isFull(void) const
{
    return (_spl > _spr);
}


#endif