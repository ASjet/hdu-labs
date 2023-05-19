#ifndef ARRAY_H
#define ARRAY_H


#include <cstring>
#include <cassert>
using array_size_t = int;
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Array
{
    public:
        Array() = default;
        Array(array_size_t _Size)
        {
            _base = new T[_Size];
            _size = _Size;
        }
        Array(T *_Array, array_size_t _Length)
        {
            initialize(_Array, _Length);
        }
        virtual ~Array()
        {
            delete [] _base;
        }

        void clear(void);
        bool initialize(T *_Array, array_size_t _Length);
        bool resize(array_size_t _Size);
        bool empty(void) const;
        array_size_t length(void) const;
        bool move(array_size_t _Begin, array_size_t _End, array_size_t _Offset);

    protected:
        array_size_t _tail = 0;
        array_size_t _size = 0;
        array_size_t _len = 0;
        T * _base = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void Array<T>::clear(void)
{
    _len = 0;
    _tail = 0;
}


template <typename T>
bool Array<T>::initialize(T *_Array, array_size_t _Length)
{
    clear();
    if(_base == nullptr)
        _base = new T[_Length];
    if(_base == nullptr)
        return false;

    if(_size < _Length)
        if(!resize(_Length))
            return false;

    _size = _Length;
    _len = _Length;
    _tail = _Length-1;

    T * p = _base;
    while(_Length--)
        *p++ = *_Array++;
}


template <typename T>
bool Array<T>::resize(array_size_t _Size)
{
    if(_Size < _len)
        return false;
    else
    {
        T * new_base = new T[_Size];
        if(new_base == nullptr)
            return false;
        T * p_old = _base;
        T * p_new = new_base;
        array_size_t cnt = _len;
        while(cnt--)
            *p_new++ = *p_old++;
        delete []_base;
        _base = new_base;
        _size = _Size;
    }
    return true;
}


template <typename T>
bool Array<T>::empty(void) const
{
    return (_len == 0);
}


template <typename T>
array_size_t Array<T>::length(void) const
{
    return _len;
}


template <typename T>
bool Array<T>::move(array_size_t _Begin, array_size_t _End, array_size_t _Offset)
{
    if((_Begin + _Offset) < 0 || (_End + _Offset) >= _size)
        return false;

    if(_Offset == 0)
        return false;

    T *source, *target;

    array_size_t seg_len = _End - _Begin + 1;
    if(_Offset > 0)
    {
        target = _base + _End + _Offset;
        source = _base + _End;
        while(seg_len--)
            *target-- = *source--;
        memset(_base+_Begin, 0, sizeof(T)*_Offset);
    }
    else
    {
        target = _base + _Begin + _Offset;
        source = _base + _Begin;
        while(seg_len--)
            *target++ = *source++;
        memset(_base+_End+1+_Offset, 0, sizeof(T)*(-_Offset));
    }
    return true;
}


#endif