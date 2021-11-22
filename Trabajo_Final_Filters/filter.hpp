#ifndef FILTER_HPP
#define FILTER_HPP

#include "Register.hpp"
#include "binarytree.hpp"
#include "BlockChain.hpp"

template<class T, class Q>
struct BlockCompareNode
{
    T data;
    BlockNode<std::vector<Q>>* block;
};

template<class T, class Q>
class Filter
{
protected:
    BinaryTree<BlockCompareNode<T, Q>> tree;
    std::string name;
public:
    Filter() {
        this->name = "filter";
    }
    virtual ~Filter() {};

    virtual BlockCompareNode<T, Q> searchFirst(T _toCompare) = 0;

    virtual std::vector<BlockCompareNode<T, Q>> searchAll(T _toCompare) = 0;

    virtual void insert(Q _reg, BlockNode<std::vector<Q>>* _node) {};

    std::string gName() {
        return this->name;
    }
};

#endif FILTER_HPP