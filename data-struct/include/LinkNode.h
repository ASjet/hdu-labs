#ifndef NODE_H
#define NODE_H


template <typename T> class Link;
template <typename T> class LinerLink;
template <typename T> class CLink;
template <typename T> class LinkStack;
template <typename T> class LinkQueue;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class LinkNode
{
public:
    LinkNode() = default;
    LinkNode(T _Element)
    {
        _body = _Element;
    }
    ~LinkNode()
    {
        LinkNode<T> * prev = _prev_ptr;
        LinkNode<T> * next = _next_ptr;
        if(next != nullptr)
            next->_prev_ptr = prev;
        if(prev != nullptr)
            prev->_next_ptr = next;
    }
    friend class Link<T>;
    friend class LinerLink<T>;
    friend class CLink<T>;
    friend class LinkStack<T>;
    friend class LinkQueue<T>;

    LinkNode<T> * next(void) const;
    LinkNode<T> * prev(void) const;

    bool insert_ahead(T _Element);
    bool insert_behind(T _Element);

    T &value(void);

private:
    LinkNode<T> *_next_ptr = nullptr;
    LinkNode<T> *_prev_ptr = nullptr;
    T _body = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkNode<T> *LinkNode<T>::next(void) const
{
    return _next_ptr;
}


template <typename T>
LinkNode<T> *LinkNode<T>::prev(void) const
{
    return _prev_ptr;
}


template <typename T>
T &LinkNode<T>::value(void)
{
    return _body;
}


template <typename T>
bool LinkNode<T>::insert_ahead(T _Element)
{
    LinkNode<T> * p = new LinkNode<T>(_Element);
    if(p == nullptr)
        return false;

    p->_next_ptr = this;
    p->_prev_ptr = _prev_ptr;
    if(_prev_ptr != nullptr)
        _prev_ptr->_next_ptr = p;
    _prev_ptr = p;
    return true;
}


template <typename T>
bool LinkNode<T>::insert_behind(T _Element)
{
    LinkNode<T> * p = new LinkNode<T>(_Element);
    if(p == nullptr)
        return false;

    p->_prev_ptr = this;
    p->_next_ptr =_next_ptr;
    if(_next_ptr != nullptr)
        _next_ptr->_prev_ptr = p;
    _next_ptr = p;
    return true;
}


#endif