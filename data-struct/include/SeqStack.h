#ifndef SEQSTACK_H
#define SEQSTACK_H


#include "Array.h"
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class SeqStack : public Array<T>
{
    public:
    SeqStack() = default;
    SeqStack(array_size_t _Size):Array<T>(_Size){}
    SeqStack(T *_Base, array_size_t _Length)
    {
        for(array_size_t i = 0; i < _Length; ++i)
            push(_Base[i]);
        _len = _Length;
        _sp = _Length;
    }
    ~SeqStack() = default;

    bool push(T _Element);
    bool pop(void);
    bool pop(T & _Destination);
    bool GetTop(T &_Destination) const;

    private:
    using Array<T>::_len;
    using Array<T>::_base;
    using Array<T>::_size;
    array_size_t _sp = 0;
};
////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool SeqStack<T>::push(T _Element)
{
    if(_len == _size)
        return false;
    _base[_sp] = _Element;
    ++_sp;
    ++_len;
    return true;
}


template <typename T>
bool SeqStack<T>::pop(void)
{
    if(_len <= 0)
        return false;
    --_sp;
    --_len;
    return true;
}


template <typename T>
bool SeqStack<T>::pop(T & _Destination)
{
    if(_len <= 0)
        return false;
    --_sp;
    _Destination = _base[_sp];
    --_len;
    return true;
}


template<typename T>
bool SeqStack<T>::GetTop(T& _Destination) const
{
    if(_len <= 0)
        return false;
    _Destination = _base[_sp];
    return true;
}


#endif