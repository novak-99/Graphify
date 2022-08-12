#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Node/Node.hpp"
#include "Graph/Graph.hpp"
#include "WeightedAdjacencyMatrix/WeightedAdjacencyMatrix.hpp"

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
    class WeightedGraph{
        public:
            std::vector<std::pair<Node<T>*, int>> &operator[](Node<T>* node);

            int outDegree(Node<T>* node);
            int maximumOutDegree();

            int inDegree(Node<T>* node);
            int maximumInDegree();

            void addNode(Node<T>* node, std::vector<std::pair<Node<T>*, int>> nodeAdjList);
            void addEdge(Node<T>* node, std::pair<Node<T>*, int> nodeAdjList);

            void setWeight(Node<T>* node, Node<T>* baseNode, int newWeight);
            int getWeight(Node <T>* node, Node<T>* baseNode);

            WeightedEdgeList<T> weightedEdgeList();
            Graph<T> unweightedGraph();
            std::tuple<WeightedAdjacencyMatrix<T>, std::map<Node<T>*, int>> weightedAdjacencyMatrix();

            void complete(std::vector<Node<T>*> nodes, std::vector<int> weights);
            void transpose();

            typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator find(Node<T>* node);
            typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator begin();
            typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator end();
            typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator rbegin();
            typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator rend();

            size_t size();
            void erase(Node<T>* node);

            std::vector<Node<T>*> getAllNodes();

            void scalarMultiply(int a);


        private:
            std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>> WeightedGraph;


    };

    template <class T>
    typename std::vector<std::pair<Node<T>*, int>>& WeightedGraph<T>::operator[](Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBWeightedAdjList(*this, node); // Pass current VALUE of instance of class to err handler..
        return WeightedGraph[node];

    }

    template <class T>
    int WeightedGraph<T>::outDegree(Node<T>* node){
        // vector.size() returns a size_t.. the cast is to be explicit about what we are returning
        return int(WeightedGraph[node].size()); 
    }
    
    template <class T>
    int WeightedGraph<T>::maximumOutDegree(){ 
        int maxOutDegree = 0;
        for(auto [start, nodeAdjList] : WeightedGraph){
            maxOutDegree = std::max(maxOutDegree, int(nodeAdjList.size()));
        }
        return maxOutDegree;
    }

    template <class T>
    int WeightedGraph<T>::inDegree(Node<T>* node){
        int nodeInDegree = 0; 
        for(auto [start, nodeAdjList] : WeightedGraph){
            bool found = false; 
            for(auto [baseNode, weight] : nodeAdjList){
                if(node == baseNode){
                    found = true; 
                }
            }
            if(found) nodeInDegree++;
        }
        return nodeInDegree;
    }

    template <class T>
    int WeightedGraph<T>::maximumInDegree(){
        int maxInDegree = 0;
        for(auto [start, nodeAdjList] : WeightedGraph) maxInDegree = std::max(maxInDegree, inDegree(start));
        return maxInDegree;
    }

    template <class T>
    void WeightedGraph<T>::addNode(Node<T>* node, std::vector<std::pair<Node<T>*, int>> nodeAdjList){
        WeightedGraph.insert(std::make_pair(node, nodeAdjList));
    }

    template <class T>
    void WeightedGraph<T>::addEdge(Node<T>* node, std::pair<Node<T>*, int> nodeAdjList){
        WeightedGraph[node].push_back(nodeAdjList);
    }

    template <class T>
    int WeightedGraph<T>::getWeight(Node <T>* node, Node<T>* baseNode){
        for(auto [iterateNode, weight] : WeightedGraph[node]){
            if(iterateNode == baseNode){
                return weight;
            }
        }
        // throw not found error!
    }

    template <class T>
    void WeightedGraph<T>::setWeight(Node <T>* node, Node<T>* baseNode, int newWeight){
        for(auto it = WeightedGraph[node].begin(); it != WeightedGraph[node].end(); it++){
            if(it->first == baseNode){
                WeightedGraph[node].erase(it);
                WeightedGraph[node].push_back({baseNode, newWeight});

                return; // we are done here. 
            }
        }
    }

    template <class T>
    WeightedEdgeList<T>  WeightedGraph<T>::weightedEdgeList(){
        WeightedEdgeList<T> edgeList; 
        for(auto [node, nodeAdjList] : WeightedGraph){
            for(auto [baseNode, weight] : nodeAdjList){
                edgeList.addEdge({node, baseNode, weight});
            }
        }
        return edgeList;
    }

    template <class T>
    Graph<T> WeightedGraph<T>::unweightedGraph(){
        Graph<T> unweightedGraph; 

        for(auto [node, nodeAdjList] : WeightedGraph){
            std::vector<Node<T>*> unweightedNodeAdjList; 
            for(auto [baseNode, weight] : nodeAdjList){
                unweightedNodeAdjList.push_back(baseNode);
            }
            unweightedGraph.addNode(node, unweightedNodeAdjList);
        }
        return unweightedGraph;
    }

    template <class T>
    std::tuple<WeightedAdjacencyMatrix<T>, std::map<Node<T>*, int>> WeightedGraph<T>::weightedAdjacencyMatrix(){
        WeightedAdjacencyMatrix<T> weightedAdjMat(WeightedGraph.size()); 
        std::map<Node<T>*, int> nodeToIndex; 

        int i = 0; 
        for(auto [node, nodeAdjList] : WeightedGraph){
            nodeToIndex.insert(std::make_pair(node, i));
            i++;
        }

        for(auto [node, nodeAdjList] : WeightedGraph){
            nodeToIndex.insert(std::make_pair(node, i));
            int j = 0; 
            for(auto [baseNode, weight] : nodeAdjList){
                weightedAdjMat[nodeToIndex[node]][nodeToIndex[baseNode]] = weight;
                j++;
            }
        }
        return {weightedAdjMat, nodeToIndex};
    }

    template <class T>
    void WeightedGraph<T>::complete(std::vector<Node<T>*> nodes, std::vector<int> weights){
        // add error handling- nodes.size() must = k!

        std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>> weightedCompleteGraph;
        
        for(auto node : nodes){
            for(int i = 0; i < nodes.size(); i++){ // O( (|V|)^2 ) algorithm.. n(n-1)/2 connections..
                if(node == nodes[i]) continue; 
                weightedCompleteGraph[node].push_back({node, weights[i]});
            }
        }

        WeightedGraph = weightedCompleteGraph;

    }

    template <class T>
    void WeightedGraph<T>::transpose(){
        std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>> transposedWeightedGraph;
        
        for(auto [node, nodeAdjList] : WeightedGraph){
            for(auto [baseNode, weight] : nodeAdjList){
                transposedWeightedGraph[baseNode].push_back({node, weight});
            }
        }
        for(auto [node, nodeAdjList] : WeightedGraph){
            if(transposedWeightedGraph.find(node) == transposedWeightedGraph.end()) transposedWeightedGraph[node] = {};
        }
        WeightedGraph = transposedWeightedGraph;
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator WeightedGraph<T>::find(Node<T>* node){
        return WeightedGraph.find(node);
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator WeightedGraph<T>::begin(){
        return WeightedGraph.begin();
    }  

    template <class T>
    typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator WeightedGraph<T>::end(){
        return WeightedGraph.end();
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator WeightedGraph<T>::rbegin(){
        return WeightedGraph.rbegin();
    }  

    template <class T>
    typename std::map<Node<T>*, std::vector<std::pair<Node<T>*, int>>>::iterator WeightedGraph<T>::rend(){
        return WeightedGraph.rend();
    }

    template <class T>
    size_t WeightedGraph<T>::size(){
        return WeightedGraph.size();
    }

    template <class T>
    void WeightedGraph<T>::erase(Node<T>* node){
        // ErrorHandling<T> handler;
        // handler.checkOOBWeightedAdjList(*this, node);

        WeightedGraph.erase(node);

        for(auto [start, nodeAdjList] : WeightedGraph){
            for(auto it = nodeAdjList.begin(); it != nodeAdjList.end();){
                if(it->first == node){
                    nodeAdjList.erase(it);
                }
                else{ ++it; }
            }
        }
    }

    template <class T>
    std::vector<Node<T>*> WeightedGraph<T>::getAllNodes(){
        std::vector<Node<T>*> nodes; 
        for(auto [node, nodeAdjList] : WeightedGraph){
            nodes.push_back(node);
        }
        return nodes; 
    }

    template <class T>
    void WeightedGraph<T>::scalarMultiply(int a){
        for(auto [node, nodeAdjList] : WeightedGraph){
            for(auto [baseNode, weight] : nodeAdjList){
                setWeight(node, baseNode, -weight);
            }
        }
    }
}

#endif // WEIGHTEDGRAPH_HPP