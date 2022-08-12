#ifndef FLOWGRAPH_HPP
#define FLOWGRAPH_HPP

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Node/Node.hpp"
#include "Graph/Graph.hpp"

#include "ErrorHandling/ErrorHandling.hpp"

namespace Graphify{


    template <class T>
    class WeightedEdgeList;

    // Min Component Size 
    // Max Component Size
    // Total Number of Components 
    // Min Dist Given Start: A, End: B

    template <class T>
    class Node;

    template <class T>
    class ErrorHandling;

    template <class T>
    class Graph;

    template <class T>
    class FlowGraph{
        public:
            std::vector<std::tuple<Node<T>*, int, int>> &operator[](Node<T>* node);

            int outDegree(Node<T>* node);
            int maximumOutDegree();

            int inDegree(Node<T>* node);
            int maximumInDegree();

            void addNode(Node<T>* node, std::vector<std::tuple<Node<T>*, int, int>> nodeAdjList, std::string special="none");
            void addEdge(Node<T>* node, std::tuple<Node<T>*, int, int> nodeAdjList);

            void setMaxCapacity(Node<T>* node, Node<T>* baseNode, int newMaxCapacity);
            int getMaxCapacity(Node <T>* node, Node<T>* baseNode);

            void setCurrentCapacity(Node<T>* node, Node<T>* baseNode, int newCurrentCapacity);
            int getCurrentCapacity(Node <T>* node, Node<T>* baseNode);

            // void transpose();

            typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator find(Node<T>* node);
            typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator begin();
            typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator end();
            typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator rbegin();
            typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator rend();

            size_t size();
            void erase(Node<T>* node);

            void addBackwardEdges();

            std::vector<Node<T>*> getAllNodes();

            bool isFull();

            Node<T>* src; 
            Node<T>* sink; 

        private:
            std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>> FlowGraph;


    };

    template <class T>
    typename std::vector<std::tuple<Node<T>*, int, int>>& FlowGraph<T>::operator[](Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBFlowGraph(*this, node); // Pass current VALUE of instance of class to err handler..
        return FlowGraph[node];

    }

    template <class T>
    int FlowGraph<T>::outDegree(Node<T>* node){
        // vector.size() returns a size_t.. the cast is to be explicit about what we are returning
        return int(FlowGraph[node].size()); 
    }
    
    template <class T>
    int FlowGraph<T>::maximumOutDegree(){ 
        int maxOutDegree = 0;
        for(auto [start, nodeAdjList] : FlowGraph){
            maxOutDegree = std::max(maxOutDegree, int(nodeAdjList.size()));
        }
        return maxOutDegree;
    }

    template <class T>
    int FlowGraph<T>::inDegree(Node<T>* node){
        int nodeInDegree = 0; 
        for(auto [start, nodeAdjList] : FlowGraph){
            bool found = false; 
            for(auto [baseNode, currentCapacity, maxCapacity] : nodeAdjList){
                if(node == baseNode){
                    found = true; 
                }
            }
            if(found) nodeInDegree++;
        }
        return nodeInDegree;
    }

    template <class T>
    int FlowGraph<T>::maximumInDegree(){
        int maxInDegree = 0;
        for(auto [start, nodeAdjList] : FlowGraph) maxInDegree = std::max(maxInDegree, inDegree(start));
        return maxInDegree;
    }

    template <class T>
    void FlowGraph<T>::addNode(Node<T>* node, std::vector<std::tuple<Node<T>*, int, int>> nodeAdjList, std::string special){
        if(special == "src") src = node; 
        if(special == "sink") sink = node; 
        FlowGraph.insert(std::make_pair(node, nodeAdjList));
    }

    template <class T>
    void FlowGraph<T>::addEdge(Node<T>* node, std::tuple<Node<T>*, int, int> nodeAdjList){
        FlowGraph[node].push_back(nodeAdjList);
    }

    template <class T>
    int FlowGraph<T>::getMaxCapacity(Node <T>* node, Node<T>* baseNode){
        for(auto [iterateNode, currentCapacity, maxCapacity] : FlowGraph[node]){
            if(iterateNode == baseNode){
                return maxCapacity;
            }
        }
        // throw not found error!
    }

    template <class T>
    void FlowGraph<T>::setMaxCapacity(Node <T>* node, Node<T>* baseNode, int newMaxCapacity){
        for(auto it = FlowGraph[node].begin(); it != FlowGraph[node].end(); it++){
            if(std::get<0>(*it) == baseNode){
                std::get<2>(*it) = newMaxCapacity;
                return; // we are done here. 
            }
        }
    }

    template <class T>
    int FlowGraph<T>::getCurrentCapacity(Node <T>* node, Node<T>* baseNode){
        for(auto [iterateNode, currentCapacity, maxCapacity] : FlowGraph[node]){
            if(iterateNode == baseNode){
                return currentCapacity;
            }
        }
        // throw not found error!
    }

    template <class T>
    void FlowGraph<T>::setCurrentCapacity(Node <T>* node, Node<T>* baseNode, int newCurrentCapacity){
        for(auto it = FlowGraph[node].begin(); it != FlowGraph[node].end(); it++){
            if(std::get<0>(*it) == baseNode){
                std::get<1>(*it) = newCurrentCapacity;
                return; // we are done here. 
            }
        }
    }

    // template <class T>
    // void FlowGraph<T>::transpose(){
    //     std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>> transposedFlowGraph;
        
    //     for(auto [node, nodeAdjList] : FlowGraph){
    //         for(auto [baseNode, weight] : nodeAdjList){
    //             transposedFlowGraph[baseNode].push_back({node, weight});
    //         }
    //     }
    //     for(auto [node, nodeAdjList] : FlowGraph){
    //         if(transposedFlowGraph.find(node) == transposedFlowGraph.end()) transposedFlowGraph[node] = {};
    //     }
    //     FlowGraph = transposedFlowGraph;
    // }

    template <class T>
    typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator FlowGraph<T>::find(Node<T>* node){
        return FlowGraph.find(node);
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator FlowGraph<T>::begin(){
        return FlowGraph.begin();
    }  

    template <class T>
    typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator FlowGraph<T>::end(){
        return FlowGraph.end();
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator FlowGraph<T>::rbegin(){
        return FlowGraph.rbegin();
    }  

    template <class T>
    typename std::map<Node<T>*, std::vector<std::tuple<Node<T>*, int, int>>>::iterator FlowGraph<T>::rend(){
        return FlowGraph.rend();
    }

    template <class T>
    size_t FlowGraph<T>::size(){
        return FlowGraph.size();
    }

    template <class T>
    void FlowGraph<T>::erase(Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBFlowGraph(*this, node);

        FlowGraph.erase(node);

        for(auto [start, nodeAdjList] : FlowGraph){
            for(auto it = nodeAdjList.begin(); it != nodeAdjList.end();){
                if(it->first == node){
                    nodeAdjList.erase(it);
                }
                else{ ++it; }
            }
        }
    }

    template <class T>
    void FlowGraph<T>::addBackwardEdges(){
        for(auto [node, nodeAdjList] : FlowGraph){
            for(auto [baseNode, currentCapacity, maxCapacity] : nodeAdjList){
                addEdge(baseNode, {node, 0, 0}); // adding each backward edge
            }
        }
    }
    

    template <class T>
    std::vector<Node<T>*> FlowGraph<T>::getAllNodes(){
        std::vector<Node<T>*> nodes; 
        for(auto [node, nodeAdjList] : FlowGraph){
            nodes.push_back(node);
        }
        return nodes; 
    }

    template <class T>
    bool FlowGraph<T>::isFull(){
        bool isSrcFull = true; 

        for(auto [node, currentCapacity, maxCapacity] : FlowGraph[src]){
            if(currentCapacity == maxCapacity) isSrcFull = false;
        }

        bool isSinkFull = true; 

        for(auto [node, currentCapacity, maxCapacity] : FlowGraph[sink]){
            if(currentCapacity == maxCapacity) isSinkFull = false;
        }


        return (isSrcFull || isSinkFull);
    }
}

#endif // FLOWGRAPH_HPP