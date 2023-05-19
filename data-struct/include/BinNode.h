#ifndef BINNODE_H
#define BINNODE_H

////////////////////////////////////////////////////////////////////////////////
template <typename T> class BinTree;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class BinNode
{
    public:
    BinNode(void)
    {
        _body = new T;
    }
    BinNode(BinNode<T>* _Root)
    {
        _body = new T;
        _pnode = _Root;
    }
    BinNode(T _Element)
    {
        _body = new T;
        *_body = _Element;
    }
    BinNode(BinNode<T>* _Root, T _Element)
    {
        _pnode = _Root;
        _body = new T;
        *_body = _Element;
    }
    ~BinNode()
    {
        if(_body != nullptr)
            delete _body;

        if(_pnode != nullptr)
        {
            if(this == _pnode->_lnode)
                _pnode->_lnode = nullptr;
            if(this == _pnode->_rnode)
                _pnode->_rnode = nullptr;
        }

        if(_lnode != nullptr)
            delete _lnode;
        if(_rnode != nullptr)
            delete _rnode;
    }

    friend class BinTree<T>;

    BinNode<T> * lnode(void) const;
    BinNode<T> * rnode(void) const;
    BinNode<T> * pnode(void) const;
    T &value(void);
    bool ltag(void) const;
    bool rtag(void) const;

    private:
    BinNode<T>* _pnode = nullptr;
    BinNode<T>* _lnode = nullptr;
    BinNode<T>* _rnode = nullptr;
    bool _ltag = false;
    bool _rtag = false;
    T *_body = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
BinNode<T> * BinNode<T>::lnode(void) const
{
    return _lnode;
}

template <typename T>
BinNode<T> * BinNode<T>::rnode(void) const
{
    return _rnode;
}

template <typename T>
BinNode<T> *BinNode<T>::pnode(void) const
{
    return _pnode;
}

template <typename T>
T& BinNode<T>::value(void)
{
    return *_body;
}

template <typename T>
bool BinNode<T>::ltag(void) const
{
    return _ltag;
}

template <typename T>
bool BinNode<T>::rtag(void) const
{
    return _rtag;
}

#endif