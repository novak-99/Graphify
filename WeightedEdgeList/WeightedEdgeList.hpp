#ifndef WEIGHTEDEDGELIST_HPP
#define WEIGHTEDEDGELIST_HPP

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "WeightedGraph/WeightedGraph.hpp"
#include "Node/Node.hpp"

#include "ErrorHandling/ErrorHandling.hpp"

namespace Graphify{

   template <class T>
    class ErrorHandling;

    template <class T>
    class WeightedEdgeList{
        public:
            WeightedEdgeList();
            WeightedEdgeList(bool directed);
            std::tuple<Node<T>*, Node<T>*, int> &operator[](int i);

            void addEdge(Node<T>* node, Node<T>* baseNode, int weight);
            void addEdge(std::tuple<Node<T>*, Node<T>*, int> edge); 

            WeightedGraph<T> weightedGraph();

            typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator find(Node<T>* node);
            typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator find(std::tuple<Node<T>*, Node<T>*, int> edge);
            typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator begin();
            typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator end();
            typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator rbegin();
            typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator rend();

            void combine(WeightedEdgeList<T> edgeList);

            size_t size();
            void erase(Node<T>* node);
            void erase(std::tuple<Node<T>*, Node<T>*, int> edge);

            std::tuple<Node<T>*, Node<T>*, int> minEdge(); 


        private:
            std::vector<std::tuple<Node<T>*, Node<T>*, int>> edgeList;
            bool directed; 


    };

    template <class T>
    WeightedEdgeList<T>::WeightedEdgeList()
    { }

    template <class T>
    WeightedEdgeList<T>::WeightedEdgeList(bool directed)
    : directed(directed)
    { }

    template <class T>
    typename std::tuple<Node<T>*, Node<T>*, int>& WeightedEdgeList<T>::operator[](int i){
        ErrorHandling<T> handler;
        handler.checkOOBWeightedEdgeList(*this, i); // Pass current VALUE of instance of class to err handler..
        return edgeList[i];

    }

    template <class T>
    void WeightedEdgeList<T>::addEdge(Node<T>* node, Node<T>* baseNode, int weight){
        edgeList.push_back({node, baseNode, weight});
        if(directed) edgeList.push_back({baseNode, node, weight});
    }

    template <class T>
    void WeightedEdgeList<T>::addEdge(std::tuple<Node<T>*, Node<T>*, int> edge){
        edgeList.push_back(edge);
        if(directed){
            std::swap(std::get<0>(edge), std::get<1>(edge));
            edgeList.push_back(edge);
        }
    }

    template <class T> 
    WeightedGraph<T> WeightedEdgeList<T>::weightedGraph(){
        // we could add a directed flag too.. 
        WeightedGraph<T> graph; 
        for(auto edge : edgeList){
            graph.addEdge(std::get<0>(edge), {std::get<1>(edge), std::get<2>(edge)});
        }

        return graph; 
    }

    template <class T>
    typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator WeightedEdgeList<T>::find(Node<T>* node){
        for(auto it = this->begin(); it != this->end(); it++){
            if(std::get<0>(*it) == node || std::get<1>(*it) == node) return it; 
        }
        return this->end(); // return end iterator if nothing was found 
    }

    template <class T>
    typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator WeightedEdgeList<T>::find(std::tuple<Node<T>*, Node<T>*, int> edge){
        return std::find(edgeList.begin(), edgeList.end(), edge);
    }

    template <class T>
    typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator WeightedEdgeList<T>::begin(){
        return edgeList.begin();
    }  

    template <class T>
    typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator WeightedEdgeList<T>::end(){
        return edgeList.end();
    }

    template <class T>
    typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator WeightedEdgeList<T>::rbegin(){
        return edgeList.rbegin();
    }  

    template <class T>
    typename std::vector<std::tuple<Node<T>*, Node<T>*, int>>::iterator WeightedEdgeList<T>::rend(){
        return edgeList.rend();
    }

    template <class T>
    size_t WeightedEdgeList<T>::size(){
        return edgeList.size();
    }

    template <class T>
    void WeightedEdgeList<T>::combine(WeightedEdgeList<T> edgeList){
         this->edgeList.insert(this->end(), edgeList.begin(), edgeList.end());
    }

    template <class T>
    void WeightedEdgeList<T>::erase(Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBWeightedEdgeList(*this, node);


        for(auto it = this->begin(); it != this->end();){
            if(std::get<0>(*it) == node || std::get<1>(*it) == node){
                edgeList.erase(it);
            }
            else{ ++it; }
        }
    }

    template <class T>
    void WeightedEdgeList<T>::erase(std::tuple<Node<T>*, Node<T>*, int> edge){
        edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), edge));
    }

    template <class T>
    std::tuple<Node<T>*, Node<T>*, int> WeightedEdgeList<T>::minEdge(){
        return *std::min_element(edgeList.begin(), edgeList.end(), [](auto &left, auto &right) { return std::get<2>(left) < std::get<2>(right); });
    }
}

#endif // WEIGHTEDEDGELIST_HPP