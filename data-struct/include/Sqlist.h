#ifndef SQLIST_H
#define SQLIST_H


#include <iostream>
#include "Array.h"

template <typename T>
class Sqlist;

template <typename T>
std::ostream& operator<<(std::ostream& _Ostream, Sqlist<T> & _Sqlist);
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Sqlist : public Array<T>
{
    public:
    Sqlist() = default;
    Sqlist(array_size_t _Size):Array<T>(_Size){}
    ~Sqlist() = default;

    friend std::ostream& operator<<<T>(std::ostream& _Ostream, Sqlist<T> & _Sqlist);
    T& operator[](array_size_t _Index);

    array_size_t find(T _Element) const;
    bool insert(array_size_t _Index, T _Element);
    bool remove(array_size_t _Index);
    void unique(void);
    using Array<T>::move;

    private:
    using Array<T>::_size;
    using Array<T>::_len;
    using Array<T>::_base;
    using Array<T>::_tail;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& _Ostream, Sqlist<T> & _Sqlist)
{
    array_size_t length = _Sqlist._len;
    T * base = _Sqlist._base;
    for(array_size_t i = 0; i != length; ++i)
        _Ostream << ((i == 0)? '\0' : ' ') << base[i];
    return _Ostream;
}


template <typename T>
T& Sqlist<T>::operator[](array_size_t _Index)
{
    return _base[_Index];
}


template <typename T>
array_size_t Sqlist<T>::find(T _Element) const
{
    for(array_size_t i = 0; i != _len; ++i)
        if(_base[i] == _Element)
            return i;
    return -1;
}


template <typename T>
bool Sqlist<T>::insert(array_size_t _Index, T _Element)
{
    if((_len + 1) > _size)
        return false;

    if(move(_Index, _tail, 1))
    {
        _base[_Index] = _Element;
        ++_len;
        _tail = (_len == 0) ? 0 : _len - 1;
        return true;
    }
    else
        return false;
}


template <typename T>
bool Sqlist<T>::remove(array_size_t _Index)
{
    if(_Index >= _len)
        return false;
    else
    {
        if(move(_Index+1, _tail, -1))
        {
            --_len;
            _tail = (_len == 0) ? 0 : _len - 1;
            return true;
        }
        else
            return false;
    }
}


template <typename T>
void Sqlist<T>::unique(void)
{
    T cur;
    array_size_t i = 0;
    while(i < _len)
    {
        if(i != 0 && cur == _base[i])
        {
            assert(move(i+1, _tail, -1) && "Unexpect error.");
            --_len;
        }
        else
            cur = _base[i++];
    }
}


#endif