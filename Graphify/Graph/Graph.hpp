#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Node/Node.hpp"
#include "EdgeList/EdgeList.hpp"

#include "ErrorHandling/ErrorHandling.hpp"

namespace Graphify{


    // Min Component Size 
    // Max Component Size
    // Total Number of Components 
    // Min Dist Given Start: A, End: B

    template <class T>
    class EdgeList;

    template <class T>
    class Graph{
        public:
            std::vector<Node<T>*> &operator[](Node<T>* node);

            int outDegree(Node<T>* node);
            int maximumOutDegree();

            int inDegree(Node<T>* node);
            int maximumInDegree();

            void addNode(Node<T>* node, std::vector<Node<T>*> adjNodeList);
            void addEdge(Node<T>* node, Node<T>* baseNode);

            // add edge list...

            EdgeList<T> edgeList();
            
            void complete(std::vector<Node<T>*> nodes);
            void transpose();

            typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator find(Node<T>* node);
            typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator begin();
            typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator end();
            typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator rbegin();
            typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator rend();

            size_t size();
            void erase(Node<T>* node);

            bool eulerianCircutExists();
            bool eulerianPathExists();

            bool isDirected();
            bool isBipartite();

        private:
            std::map<Node<T>*, std::vector<Node<T>*>> graph;


    };

    template <class T>
    typename std::vector<Node<T>*>& Graph<T>::operator[](Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBUnweightedAdjList(*this, node); // Pass current VALUE of instance of class to err handler..
        return graph[node];

    }

    template <class T>
    int Graph<T>::outDegree(Node<T>* node){
        // vector.size() returns a size_t.. the cast is to be explicit about what we are returning
        return int(graph[node].size()); 
    }
    
    template <class T>
    int Graph<T>::maximumOutDegree(){ 
        int maxOutDegree = 0;
        for(auto [start, nodeAdjList] : graph){
            maxOutDegree = std::max(maxOutDegree, int(nodeAdjList.size()));
        }
        return maxOutDegree;
    }

    template <class T>
    int Graph<T>::inDegree(Node<T>* node){
        int nodeInDegree = 0; 
        for(auto [start, nodeAdjList] : graph){
            if(std::find(nodeAdjList.begin(), nodeAdjList.end(), node) != nodeAdjList.end()){
                nodeInDegree++;
            }
        }
        return nodeInDegree;
    }

    template <class T>
    int Graph<T>::maximumInDegree(){
        int maxInDegree = 0;
        for(auto [start, nodeAdjList] : graph) maxInDegree = std::max(maxInDegree, inDegree(start));
        return maxInDegree;
    }

    template <class T>
    void Graph<T>::addNode(Node<T>* node, std::vector<Node<T>*> adjNodeList){
        graph.insert(std::make_pair(node, adjNodeList));
    }

    template <class T>
    void Graph<T>::addEdge(Node<T>* node, Node<T>* baseNode){
        graph[node].push_back(baseNode);
    }

    template <class T>
    EdgeList<T> Graph<T>::edgeList(){
        EdgeList<T> edgeList; 
        for(auto [node, nodeAdjList] : graph){
            for(auto baseNode : nodeAdjList){
                edgeList.addEdge({node, baseNode});
            }
        }
        return edgeList;
    }

    template <class T>
    void Graph<T>::complete(std::vector<Node<T>*> nodes){
        // add error handling- nodes.size() must = k!

        std::map<Node<T>*, std::vector<Node<T>*>> completeGraph;
        
        for(auto node : nodes){
            for(auto baseNode : nodes){ // (|V|)^2 algorithm.. n(n-1)/2 connections..
                if(node == baseNode) continue; 
                completeGraph[node].push_back(baseNode);
            }
        }

        graph = completeGraph;

    }

    template <class T>
    void Graph<T>::transpose(){
        std::map<Node<T>*, std::vector<Node<T>*>> transposedGraph;
        
        for(auto [node, nodeAdjList] : graph){
            for(auto baseNode : nodeAdjList){
                transposedGraph[baseNode].push_back(node);
            }
        }
        for(auto [node, nodeAdjList] : graph){
            if(transposedGraph.find(node) == transposedGraph.end()) transposedGraph[node] = {};
        }
        graph = transposedGraph;
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator Graph<T>::find(Node<T>* node){
        return graph.find(node);
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator Graph<T>::begin(){
        return graph.begin();
    }  

    template <class T>
    typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator Graph<T>::end(){
        return graph.end();
    }

    template <class T>
    typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator Graph<T>::rbegin(){
        return graph.rbegin();
    }  

    template <class T>
    typename std::map<Node<T>*, std::vector<Node<T>*>>::iterator Graph<T>::rend(){
        return graph.rend();
    }

    template <class T>
    size_t Graph<T>::size(){
        return graph.size();
    }

    template <class T>
    void Graph<T>::erase(Node<T>* node){
        ErrorHandling<T> handler;
        handler.checkOOBUnweightedAdjList(*this, node);

        graph.erase(node);

        for(auto [start, nodeAdjList] : graph){
            nodeAdjList.erase(std::remove(nodeAdjList.begin(), nodeAdjList.end(), node), nodeAdjList.end());
            graph[start] = nodeAdjList;
        }
    }

 template <class T>
    bool Graph<T>::eulerianCircutExists(){
        for(auto [node, adjNodeList] : graph){
            if(isDirected()){
                if(outDegree(node) % 2 != 0){
                    return false; 
                }
            }
            else{
                if(inDegree(node) != outDegree(node)){
                    return false; 
                }
            }
        }
        return true; 
    }

    template <class T>
    bool Graph<T>::eulerianPathExists(){
        if(isDirected()){
            bool allEvenDegree = true; 

            int numVerticiesOddDegree = 0; 

            for(auto [node, nodeAdjList] : graph){
                if(outDegree(node) % 2 != 0){
                    allEvenDegree = false;
                    numVerticiesOddDegree++;
                }
            }
            return (allEvenDegree || numVerticiesOddDegree == 2);
        }
        else{
            int numOutInDiff = 0; 
            int numInOutDiff = 0; 

            for(auto [node, nodeAdjList] : graph){
                if(inDegree(node) == outDegree(node)){
                    return false; 
                }

                if(inDegree(node) - outDegree(node) == 1){
                    numInOutDiff++;
                }
                else if(outDegree(node) - inDegree(node) == 1){
                    numOutInDiff++;
                }
            }
            return (numOutInDiff <= 1 && numInOutDiff <= 1);
        }
    }

    template <class T>
    bool Graph<T>::isDirected(){
        bool directed = true;
        for(auto [start, adjNodeList] : graph){
            for(auto node : adjNodeList){
                if(std::find(graph[node].begin(), graph[node].end(), start) == graph[node].end()){ // not an undirected connection..
                    directed = false;
                    return directed;
                }
            }
        }
        return directed;
    }

    // so this is using a traversal..
    // but I am going to keep it in graph.hpp because it is a property of a graph object
    template <class T>
    bool Graph<T>::isBipartite(){

        // as we are checking whether this graph is biaprtite, we will have just two colors.. 0, 1..
        std::map<Node<T>*, bool> color; 
        std::set<Node<T>*> visited; 

        for(auto [start, adjNodeList] : graph){

            if(visited.find(start) != visited.end()) continue; 

            color[start] = 0;

            NodeVisitor<T> nodesToVisit("DFS"); 
            nodesToVisit.push(start);
            Node<T>* currentNode; 
            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();
                if(visited.find(currentNode) != visited.end()) continue; 

                visited.insert(currentNode);
                
                auto neighbors = graph[currentNode];

                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                    if(color.find(neighbor) == color.end()) color[neighbor] = !color[currentNode];
                }
            }
        }

        visited.clear(); // reset

        for(auto [start, adjNodeList] : graph){

            color[start] = 0;

            if(visited.find(start) != visited.end()) continue; 

            NodeVisitor<T> nodesToVisit("DFS"); 
            nodesToVisit.push(start);
            Node<T>* currentNode; 
            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();
                if(visited.find(currentNode) != visited.end()) continue; 

                visited.insert(currentNode);
                
                auto neighbors = graph[currentNode];

                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                    if(color[neighbor] != !color[currentNode]){
                        return false; 
                    }
                }
            }
        }
        return true; 
    }
}

#endif // GRAPH_HPP