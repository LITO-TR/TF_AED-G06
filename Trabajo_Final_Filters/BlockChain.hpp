#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <functional>

using uint = unsigned int;

template<class T>
class BlockNode {
    T transaction;
    BlockNode* previus;
    string hash;

public:
    BlockNode(T _transaction, BlockNode* _previus = nullptr) : transaction(_transaction), previus(_previus) {
        static int indx = 0;
        this->hash = std::to_string(indx++);
    }

    ~BlockNode() {
        if (previus != nullptr) {
            delete previus;
        }
    }

    T& gTransaction() {
        return this->transaction;
    }

    void setPrevius(BlockNode* _previus) {
        this->previus = _previus;
    }

    BlockNode*& gPrevius() {
        return this->previus;
    }
};

template<class T>
class BlockChain
{
private:
    BlockNode<T>* root;
    BlockNode<T>* last;
    uint size;

    BlockNode<T>* _insert(T _e) {
        BlockNode<T>* nNode = new BlockNode<T>(_e);
        if (size == 0) {
            root = last = nNode;
        }
        else {
            nNode->setPrevius(last);
            last = nNode;
        }
        size++;
        return nNode;
    }

    void _free(BlockNode<T>*& _node) {
        if (_node == nullptr) return;
        _free(_node->gPrevius());
        delete _node;
    }

public:
    BlockChain() : root(nullptr), last(nullptr), size(0) {}
    ~BlockChain() {
        _free(root);
        size = 0;
    }

    BlockNode<T>* insert(T _e) {
        return _insert(_e);
    }

    void forEach(std::function<void(T, uint)> _todo) {
        BlockNode<T>* current = last;
        uint indx = size - 1;
        while (current != nullptr)
        {
            _todo(current->gTransaction(), indx--);
            current = current->gPrevius();
        }
    }

    class iterator {
        BlockNode<T>* current;
        uint count;
    public:
        friend class BlockChain;
        iterator() :current(nullptr), count(0) {}
        ~iterator() {}

        bool operator !=(const iterator& _other) {
            return this->count != _other.count;
        }

        void operator ++() {
            if (current == nullptr) return;
            count--;
            current = current->gPrevius();
        }

        BlockNode<T>* operator *() {
            return current;
        }
    };

public:
    iterator begin() {
        iterator ret;
        ret.count = size;
        ret.current = this->last;
        return ret;
    }
    iterator end() {
        iterator ret;
        ret.count = 0;
        ret.current = nullptr;
        return ret;
    }
};

#endif BLOCKCHAIN_HPP