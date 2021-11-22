#ifndef FILTERS_HPP
#define FILTERS_HPP

#include <sstream>

#include "filter.hpp"

using StringCompareNode = BlockCompareNode<std::string, Register*>;
using LongComapreNode = BlockCompareNode<long, Register*>;

class StringFilter : public Filter<std::string, Register*> {
public:
    StringFilter() :Filter<std::string, Register*>() {
        this->name = "string";
        auto compareStrings = [](StringCompareNode a1, StringCompareNode a2) {
            return a1.data.compare(a2.data);
        };
        this->tree.setSeachCriteria(
            compareStrings
        );
        this->tree.setInsertionCriteria(
            compareStrings
        );
    }

    StringCompareNode searchFirst(std::string _toCompare) override {
        StringCompareNode nodeFind;
        nodeFind.data = _toCompare;
        return this->tree.searchFirst(nodeFind);
    }

    std::vector<StringCompareNode> searchAll(std::string _toCompare) override {
        StringCompareNode nodeFind;
        nodeFind.data = _toCompare;
        return this->tree.searchAll(nodeFind);
    }
};

class LongFilter : public Filter<long, Register*> {
public:
    LongFilter() :Filter<long, Register*>() {
        this->name = "long";
        auto compareLongs = [](LongComapreNode a1, LongComapreNode a2) {
            return a1.data - a2.data;
        };
        this->tree.setInsertionCriteria(
            compareLongs
        );
        this->tree.setInsertionCriteria(
            compareLongs
        );
    }

    LongComapreNode searchFirst(long _toCompare) override {
        LongComapreNode nodeFind;
        nodeFind.data = _toCompare;
        return this->tree.searchFirst(nodeFind);
    }

    std::vector<LongComapreNode> searchAll(long _toCompare) override {
        LongComapreNode nodeFind;
        nodeFind.data = _toCompare;
        return this->tree.searchAll(nodeFind);
    }
};

class PublisherFilter : public StringFilter
{
public:
    PublisherFilter() : StringFilter() {
        this->name = "publisher";
    }
    ~PublisherFilter() {}

    void insert(Register* _reg, BlockNode<std::vector<Register*>>* _block) override {
        StringCompareNode _nNode;
        _nNode.block = _block;
        _nNode.data = _reg->gPublisher();
        this->tree.insert(_nNode);
    }
};


class NameFilter : public StringFilter
{
public:
    NameFilter() : StringFilter() {
        this->name = "name";
    }
    ~NameFilter() {}

    void insert(Register* _reg, BlockNode<std::vector<Register*>>* _block) override {
        StringCompareNode _nNode;
        _nNode.block = _block;
        _nNode.data = _reg->gName();
        this->tree.insert(_nNode);
    }
};

class StartWithFilter : public NameFilter
{
    std::string comp;
public:
    StartWithFilter() :comp(""), NameFilter() {}
    StartWithFilter(std::string _comp) :comp(_comp), NameFilter() {
        this->name = "empieza_con";
        this->tree.setInsertionCriteria(
            [&](StringCompareNode _parameter, StringCompareNode _node) {
                std::string compElement = comp;
                std::string nodeElement = _parameter.data;

                if (nodeElement.size() < compElement.size())
                    return _node.data.compare(_comp);

                for (size_t i = 0; i < compElement.size(); i++)
                {
                    const auto& charNodo = nodeElement[i];
                    const auto& charComp = compElement[i];
                    if (charNodo != charComp) {
                        return _node.data.compare(_comp);
                    }
                }

                return 0;

            }
        );
        this->tree.setSeachCriteria(
            [&](StringCompareNode _parameter, StringCompareNode _node) {
                std::string compElement = _parameter.data;
                std::string nodeElement = _node.data;
                if (nodeElement.size() < compElement.size())
                    return _node.data.compare(_comp);

                for (size_t i = 0; i < compElement.size(); i++)
                {
                    const auto& charNodo = nodeElement[i];
                    const auto& charComp = compElement[i];
                    if (charNodo != charComp)
                        return _node.data.compare(_comp);
                }

                return 0;

            }
        );
    }
    ~StartWithFilter() {}

    StringCompareNode searchFirst() {
        StringCompareNode nodeFind;
        nodeFind.data = comp;
        return this->tree.searchFirst(nodeFind);
    }

    std::vector<StringCompareNode> searchAll() {
        StringCompareNode nodeFind;
        nodeFind.data = comp;
        return this->tree.searchAll(nodeFind);
    }
};
class EndWithFilter : public NameFilter
{
    std::string comp;
public:
    EndWithFilter() :comp(""), NameFilter() {}
    EndWithFilter(std::string _comp) :comp(_comp), NameFilter() {
        this->name = "termina_con";
        this->tree.setInsertionCriteria(
            [&](StringCompareNode _parameter, StringCompareNode _node) {
                std::string compElement = comp;
                std::string nodeElement = _parameter.data;

                if (nodeElement.size() < compElement.size())
                    return _node.data.compare(_comp);   
                    
                for (size_t i = 0; i < compElement.size(); i++)
                {
                    const auto& charNodo = nodeElement[nodeElement.size()-compElement.size()+i];
                    const auto& charComp = compElement[i];
                    if (charNodo != charComp) {
                        return _node.data.compare(_comp);
                    }

                }
                

                return 0;

            }
        );
        this->tree.setSeachCriteria(
            [&](StringCompareNode _parameter, StringCompareNode _node) {
                std::string compElement = _parameter.data;
                std::string nodeElement = _node.data;
                if (nodeElement.size() < compElement.size())
                    return _node.data.compare(_comp);


                for (size_t i = 0; i < compElement.size(); i++)
                {
                    const auto& charNodo = nodeElement[nodeElement.size()-compElement.size()+i];
                    const auto& charComp = compElement[i];
                    if (charNodo != charComp)
                        return _node.data.compare(_comp);
                }

                return 0;

            }
        );
    }
    ~EndWithFilter() {}

    StringCompareNode searchFirst() {
        StringCompareNode nodeFind;
        nodeFind.data = comp;
        return this->tree.searchFirst(nodeFind);
    }

    std::vector<StringCompareNode> searchAll() {
        StringCompareNode nodeFind;
        nodeFind.data = comp;
        return this->tree.searchAll(nodeFind);
    }
};


class EqualsToFilter : public PublisherFilter
{
    std::string comp;
public:
    EqualsToFilter(): comp(""), PublisherFilter(){}
    EqualsToFilter(std::string _comp) : comp(_comp), PublisherFilter() {
        this->name = "Es_igual_a";
        this->tree.setInsertionCriteria(
            [&](StringCompareNode _parameter, StringCompareNode _node) {
                std::string compElement = comp;
                std::string nodeElement = _parameter.data;
                 if (nodeElement.size() < compElement.size())
                    return _node.data.compare(_comp);
               
                return _node.data.compare(_comp);
                return 0;

            }
        );
        this->tree.setSeachCriteria(
            [&](StringCompareNode _parameter, StringCompareNode _node) {
                std::string compElement = _parameter.data;
                std::string nodeElement = _node.data;
                
                 if (nodeElement.size() < compElement.size())
                    return _node.data.compare(_comp);
                
                return _node.data.compare(comp);
                return 0;

            }
        );
    }
    ~EqualsToFilter(){}

    StringCompareNode searchFirst() {
        StringCompareNode nodeFind;
        nodeFind.data = comp;
        return this->tree.searchFirst(nodeFind);
    }

    std::vector<StringCompareNode> searchAll() {
        StringCompareNode nodeFind;
        nodeFind.data = comp;
        return this->tree.searchAll(nodeFind);
    }
};


class RankFilter : public LongFilter
{
public:
    RankFilter() : LongFilter() {
        this->name = "rank";
    }

    void insert(Register* _reg, BlockNode<std::vector<Register*>>* _block) override {
        LongComapreNode _nNode;
        _nNode.block = _block;
        _nNode.data = _reg->gRank();
        this->tree.insert(_nNode);
    }
};

#endif FILTERS_HPP