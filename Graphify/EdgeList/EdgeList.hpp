#ifndef EDGELIST_HPP
#define EDGELIST_HPP

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Graph/Graph.hpp"
#include "Node/Node.hpp"

#include "ErrorHandling/ErrorHandling.hpp"

namespace Graphify{

   template <class T>
    class ErrorHandling;

    template <class T>
    class EdgeList{
        public:
            EdgeList();
            EdgeList(bool directed);
            std::pair<Node<T>*, Node<T>*> &operator[](int i);

            void addEdge(Node<T>* node, Node<T>* baseNode);
            void addEdge(std::pair<Node<T>*, Node<T>*> edge); 

            Graph<T> graph();

            typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator find(Node<T>* node);
            typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator find(std::pair<Node<T>*, Node<T>*> edge);
            typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator begin();
            typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator end();
            typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator rbegin();
            typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator rend();

            void combine(EdgeList<T> edgeList);

            size_t size();
            void erase(Node<T>* node);
            void erase(std::pair<Node<T>*, Node<T>*> edge);


        private:
            std::vector<std::pair<Node<T>*, Node<T>*>> edgeList;
            bool directed; 


    };

    template <class T>
    EdgeList<T>::EdgeList()
    : directed(false)
    { }

    template <class T>
    EdgeList<T>::EdgeList(bool directed)
    : directed(directed)
    { }

    template <class T>
    typename std::pair<Node<T>*, Node<T>*>& EdgeList<T>::operator[](int i){
        ErrorHandling<T> handler;
        handler.checkOOBEdgeList(*this, i); // Pass current VALUE of instance of class to err handler..
        return edgeList[i];

    }

    template <class T>
    void EdgeList<T>::addEdge(Node<T>* node, Node<T>* baseNode){
        edgeList.push_back({node, baseNode});
        if(directed) edgeList.push_back({baseNode, node});
    }

    template <class T>
    void EdgeList<T>::addEdge(std::pair<Node<T>*, Node<T>*> edge){
        edgeList.push_back(edge);
        if(directed){
            std::swap(edge.first, edge.second);
            edgeList.push_back(edge);
        }
    }

    template <class T> 
    Graph<T> EdgeList<T>::graph(){
        // we could add a directed flag too.. 
        Graph<T> graph; 
        for(auto edge : edgeList){
            graph.addEdge(edge.first, edge.second);
        }

        return graph; 
    }

    template <class T>
    typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator EdgeList<T>::find(Node<T>* node){
        for(auto it = this->begin(); it != this->end(); it++){
            if(*it.first == node || *it.second == node) return it; 
        }
        return this->end(); // return end iterator if nothing was found 
    }

    template <class T>
    typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator EdgeList<T>::find(std::pair<Node<T>*, Node<T>*> edge){
        return std::find(edgeList.begin(), edgeList.end(), edge);
    }

    template <class T>
    typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator EdgeList<T>::begin(){
        return edgeList.begin();
    }  

    template <class T>
    typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator EdgeList<T>::end(){
        return edgeList.end();
    }

    template <class T>
    typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator EdgeList<T>::rbegin(){
        return edgeList.rbegin();
    }  

    template <class T>
    typename std::vector<std::pair<Node<T>*, Node<T>*>>::iterator EdgeList<T>::rend(){
        return edgeList.rend();
    }

    template <class T>
    size_t EdgeList<T>::size(){
        return edgeList.size();
    }

    template <class T>
    void EdgeList<T>::combine(EdgeList<T> edgeList){
         this->edgeList.insert(this->end(), edgeList.begin(), edgeList.end());
    }

    template <class T>
    void EdgeList<T>::erase(Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBEdgeList(*this, node);


        for(auto it = this->begin(); it != this->end();){
            if(*it.first == node || *it.second == node){
                edgeList.erase(it);
            }
            else{ ++it; }
        }
    }

    template <class T>
    void EdgeList<T>::erase(std::pair<Node<T>*, Node<T>*> edge){
        edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), edge));
    }
}

#endif // EdgeList_HPP