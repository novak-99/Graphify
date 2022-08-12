#include "Graph.hpp"
// #include "ErrorHandling/ErrorHandling.hpp"

namespace Graphify{

    template <class T>
    typename std::vector<Node<T>>& Graph<T>::operator[](Node<T> node){
        ErrorHandling<T> handler;
        handler.checkOOBUnweightedAdjList(graph, node);
        return graph[node];

    }

    template <class T>
    int Graph<T>::degree(Node<T> node){
        // vector.size() returns a size_t.. the cast is to be explicit about what we are returning
        return int(graph[node].size()); 
    }
    
    template <class T>
    int Graph<T>::maximumDegree(){ 
        int maxDegree = -1;  // Return -1 if we find some unknwon issue..
        for(auto [node, nodeList] : graph){
            maxDegree = std::max(maxDegree, int(nodeList.size()));
        }
    }

    template <class T>
    typename std::map<Node<T>, std::vector<Node<T>>>::iterator Graph<T>::find(Node<T> node){
        return graph.find(node);
    }

    template <class T>
    typename std::map<Node<T>, std::vector<Node<T>>>::iterator Graph<T>::begin(){
        return graph.begin();
    }  

    template <class T>
    typename std::map<Node<T>, std::vector<Node<T>>>::iterator Graph<T>::end(){
        return graph.end();
    }

    template <class T>
    typename std::map<Node<T>, std::vector<Node<T>>>::iterator Graph<T>::rbegin(){
        return graph.rbegin();
    }  

    template <class T>
    typename std::map<Node<T>, std::vector<Node<T>>>::iterator Graph<T>::rend(){
        return graph.rend();
    }
}