#ifndef TRAVERSALS_HPP
#define TRAVERSALS_HPP

#include "Graph/Graph.hpp"
#include "Node/Node.hpp"
#include "NodeVisitor/NodeVisitor.hpp"
#include "EdgeList/EdgeList.hpp"
#include <map>
#include <set>
#include <tuple>

#include <vector>
#include <string>

namespace Graphify{

    template <class T>
    class Graph;

    template <class T>
    class EdgeList;

    template <class T>
    class Traversals{
        public:
            std::vector<std::string> validTraversalMethods(); // => ['DFS', 'BFS']

            int numConnectedComponents(Graph<T> graph, std::string traversalMethod="DFS");
            std::tuple<int, std::vector<Node<T>*>> shortestPath(Graph<T> graph, Node<T>* start, Node<T>* end);

            std::tuple<int, std::vector<Graph<T>>> maxComponent(Graph<T> graph, std::string traversalMethod="DFS");
            std::tuple<int, std::vector<Graph<T>>> minComponent(Graph<T> graph, std::string traversalMethod="DFS");

            // change both of these to use low link values for efficiency.. this is a naive approach
            std::tuple<int, EdgeList<T>> numBridges(Graph<T> graph, std::string traversalMethod="DFS");
            std::tuple<int, std::vector<Node<T>*>> numArticulationPoints(Graph<T> graph, std::string traversalMethod="DFS");

            NodeVisitor<T> topologicalSort(Graph<T> graph, std::vector<Node<T>*> traversalPts);
            NodeVisitor<T> kahnTopSort(Graph<T> graph);


            std::tuple<int, std::vector<std::vector<Node<T>*>>> tarjanStronglyConnectedComponenets(Graph<T> graph);
            std::tuple<int, std::vector<std::vector<Node<T>*>>> kosarajuStronglyConnectedComponents(Graph<T> graph);

            bool isDAG(Graph<T> graph);

        private:
            void tarjanRecurse(Graph<T> graph, Node<T>* currentNode, std::set<int>& ids, std::map<Node<T>*, int>& nodeIds, std::map<Node<T>*, int>& nodeLowLinks, std::map<Node<T>*, bool>& pushedToStack, NodeVisitor<T>& currentOstensibleComponent, std::set<Node<T>*>& visited);

        
    };

    template <class T>
    std::vector<std::string> Traversals<T>::validTraversalMethods(){
        return {"DFS", "BFS"}; 
    }

    template <class T>
    int Traversals<T>::numConnectedComponents(Graph<T> graph, std::string traversalMethod){
        int numConnectedComponents = 0;
        std::set<Node<T>*> visited; 

        for(auto [start, adjNodeList] : graph){

            if(visited.find(start) != visited.end()) continue; 

            NodeVisitor<T> nodesToVisit(traversalMethod); 
            nodesToVisit.push(start);
            Node<T>* currentNode; 
            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();
                if(visited.find(currentNode) != visited.end()) continue; 

                visited.insert(currentNode);
                
                auto neighbors = graph[currentNode];

                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                }
            }
            numConnectedComponents++;
        }
        return numConnectedComponents;
    }

    /* For unweighted graphs, we will always utilize the BFS method, since it guarantees 
    an optimal path. We return an int (path length) and a vector of nodes (path of nodes).
    */
    template <class T>
    std::tuple<int, std::vector<Node<T>*>> Traversals<T>::shortestPath(Graph<T> graph, Node<T>* start, Node<T>* end){
        std::map<Node<T>*, Node<T>*> previousNode; 
        std::vector<Node<T>*> emptySet = {};
        int notFoundDist = -1;

        std::set<Node<T>*> visited; 
        // std::queue<Node<T>*> nodesToVisit;
        NodeVisitor<T> nodesToVisit("BFS"); // Maybe pull this magic string out later.. but nevertheless BFS will be used. 
        nodesToVisit.push(start);
        Node<T>* currentNode; 

        std::map<Node<T>*, int> distFromStart; 
        distFromStart.insert(std::make_pair(start, 0));

        while(!nodesToVisit.empty()){
            currentNode = nodesToVisit.pop();

            if(currentNode == end){
                Node<T>* currentNode = end; 

                std::vector<Node<T>*> nodePath; 
                while(currentNode != nullptr){
                    nodePath.push_back(currentNode);
                    currentNode = previousNode[currentNode];
                }
                std::reverse(nodePath.begin(), nodePath.end());
                return {distFromStart[currentNode], nodePath};
            }

            visited.insert(currentNode);

            auto neighbors = graph[currentNode];

            for(auto neighbor : neighbors){
                if(visited.find(currentNode) != visited.end()){
                    nodesToVisit.push(neighbor);
                    distFromStart.insert(std::make_pair(neighbor, distFromStart[currentNode]+1));
                    previousNode[neighbor] = currentNode;
                }
            }
        }
        // we haven't return yet, so we can safely assume nothing was found.. 
        // we return -1, and the empty set.
        return {notFoundDist, emptySet};
    }

    template <class T>
    std::tuple<int, std::vector<Graph<T>>> Traversals<T>::maxComponent(Graph<T> graph, std::string traversalMethod){
        std::set<Node<T>*> visited; 
        std::vector<Graph<T>> maxComponents = {};

        for(auto [start, adjNodeList] : graph){

            if(visited.find(start) != visited.end()) continue; 

            // std::queue<Node<T>*> nodesToVisit;
            NodeVisitor<T> nodesToVisit("BFS"); // Maybe pull this magic string out later.. but nevertheless BFS will be used. 
            nodesToVisit.push(start);
            Node<T>* currentNode; 
            Graph<T> currentComponent; 

            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();

                if(visited.find(currentNode) != visited.end()) continue;

                visited.insert(currentNode);

                auto neighbors = graph[currentNode];

                currentComponent.addNode(currentNode, neighbors);
            
                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                }
            }
            if(maxComponents.empty()) maxComponents.push_back(currentComponent);
            else if(currentComponent.size() > maxComponents[0].size()) { // maxComponent_i will have the same size for all i
                maxComponents.clear();
                maxComponents.push_back(currentComponent);
            }
            else if(currentComponent.size() == maxComponents[0].size()){
                maxComponents.push_back(currentComponent);
            }
        }

        if(maxComponents.empty()) return {0, maxComponents}; // empty set
        return {maxComponents[0].size(), maxComponents};
    }

    template <class T>
    std::tuple<int, std::vector<Graph<T>>> Traversals<T>::minComponent(Graph<T> graph, std::string traversalMethod){
        std::set<Node<T>*> visited; 
        std::vector<Graph<T>> minComponents = {};

        for(auto [start, adjNodeList] : graph){
            
            if(visited.find(start) != visited.end()) continue; 

            // std::queue<Node<T>*> nodesToVisit;
            NodeVisitor<T> nodesToVisit("BFS"); // Maybe pull this magic string out later.. but nevertheless BFS will be used. 
            nodesToVisit.push(start);
            Node<T>* currentNode; 
            Graph<T> currentComponent; 

            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();

                if(visited.find(currentNode) != visited.end()) continue;

                visited.insert(currentNode);

                auto neighbors = graph[currentNode];

                currentComponent.addNode(currentNode, neighbors);
            
                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                }
            }
            if(minComponents.empty()) minComponents.push_back(currentComponent);
            else if(currentComponent.size() < minComponents[0].size()) { // maxComponent_i will have the same size for all i
                minComponents.clear();
                minComponents.push_back(currentComponent);
            }
            else if(currentComponent.size() == minComponents[0].size()){
                minComponents.push_back(currentComponent);
            }
        }
        if(minComponents.empty()) return {0, minComponents}; // empty set
        return {minComponents[0].size(), minComponents};
    }

    template <class T>
    std::tuple<int, EdgeList<T>> Traversals<T>::numBridges(Graph<T> graph, std::string traversalMethod){
        EdgeList<T> bridgeEdges = {};
        int baseConnectedComponents = numConnectedComponents(graph, traversalMethod); 

        auto edgeList = graph.edgeList();
        for(auto edge : edgeList){
            auto currentEdgeList = edgeList;
            currentEdgeList.erase(edge);

            auto currentGraph = currentEdgeList.graph();

            for(auto [node, nodeAdjList] : graph) { 
                if(currentGraph.find(node) == currentGraph.end())
                    currentGraph.addNode(node, {});
            }

            int currentConnectedComponents = numConnectedComponents(currentGraph, traversalMethod);

            if(currentConnectedComponents > baseConnectedComponents) bridgeEdges.addEdge(edge);
        }

        return {bridgeEdges.size(), bridgeEdges};
    }

    template <class T>
    std::tuple<int, std::vector<Node<T>*>> Traversals<T>::numArticulationPoints(Graph<T> graph, std::string traversalMethod){ 
        std::vector<Node<T>*> articulationNodes = {};
        int baseConnectedComponents = numConnectedComponents(graph, traversalMethod); 
        for(auto [start, adjNodeList] : graph){
            auto currentGraph = graph;
            currentGraph.erase(start);

            int currentConnectedComponents = numConnectedComponents(currentGraph, traversalMethod);

            if(currentConnectedComponents > baseConnectedComponents) articulationNodes.push_back(start);
        }

        return {articulationNodes.size(), articulationNodes};
    }

    // NUMBER OF CYCLES FUNCTION TOO


    template <class T>
    NodeVisitor<T> Traversals<T>::topologicalSort(Graph<T> graph, std::vector<Node<T>*> traversalPts){
        // CHECK FOR CYCLES
        NodeVisitor<T> topSort("BFS"); // this is a queue..

        std::set<Node<T>*> visited; 

        ErrorHandling<T> handler;
        handler.checkGraphAsDAG(graph);

        for(auto start : traversalPts){

            NodeVisitor<T> nodesToVisit("DFS"); // uses DFS.. (stack)
            nodesToVisit.push(start);
            Node<T>* currentNode; 

            if(visited.find(start) != visited.end()) continue;

            NodeVisitor<T> currentTopSort("BFS");
            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();

                if(visited.find(currentNode) != visited.end()) continue;

                currentTopSort.push(currentNode);

                visited.insert(currentNode);

                auto neighbors = graph[currentNode];

                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                }
            }
            NodeVisitor<T> newTopSort("BFS");
            while(!currentTopSort.empty()){
                newTopSort.push(currentTopSort.pop());
            }

            while(!topSort.empty()){
                newTopSort.push(topSort.pop());
            }

            topSort = newTopSort;
        }
        return topSort;
    }

    template <class T>
    NodeVisitor<T> Traversals<T>::kahnTopSort(Graph<T> graph){
        NodeVisitor<T> nodesToVisit("BFS"); // uses queue..
        NodeVisitor<T> topSort("BFS"); // this is a queue..

        std::set<Node<T>*> visited;

        // std::set<Node<T>*> visited; => graph is directed- and has no cycles- so this isn't necessary.
        std::map<Node<T>*, int> nodeInDegrees; 
        std::set<int> uniqueInDegrees; 
        for(auto [start, adjNodeList] : graph){
            nodeInDegrees.insert(std::make_pair(start, graph.inDegree(start))); // in degree map for every node "start" in graph.
            uniqueInDegrees.insert(graph.inDegree(start));

            if(nodeInDegrees[start] == 0) { 
                nodesToVisit.push(start);
                visited.insert(start);
            }
        }

        ErrorHandling<T> handler;
        handler.checkGraphAsDAG(graph);

        Node<T>* currentNode; 

        while(!nodesToVisit.empty()){
            currentNode = nodesToVisit.pop();

            auto neighbors = graph[currentNode];

            graph.erase(currentNode);
            nodeInDegrees.erase(currentNode);
            for(auto neighbor : neighbors){
                nodeInDegrees[neighbor]--; // subtract the affected degree..
            }

            topSort.push(currentNode);
            // add 0 degrees to visiting queue..
            for(auto [start, adjNodeList] : graph){
                if(nodeInDegrees[start] == 0 && visited.find(start) == visited.end()) { 

                    nodesToVisit.push(start);
                    visited.insert(start);
                }
            }
        }

        return topSort;
    }
    

    // This iterative implementation of Tarjan's algorithm is REALLY messy 
    // Be sure to fix at a later time
    template <class T>
    std::tuple<int, std::vector<std::vector<Node<T>*>>> Traversals<T>::tarjanStronglyConnectedComponenets(Graph<T> graph){
        std::set<int> ids; 
        std::map<Node<T>*, int> nodeIds; 
        std::map<Node<T>*, int> nodeLowLinks; 

        std::set<Node<T>*> visited; 

        std::vector<std::vector<Node<T>*>> stronglyConnectedComponenets; 

        std::map<int, std::vector<Node<T>*>> stronglyConnectedComponenetIds; // id to strongly connected componenet

        std::map<Node<T>*, bool> pushedToStack; 

        NodeVisitor<T> currentOstensibleComponent("DFS");  // stack

        for(auto [start, nodeAdjList] : graph){
            if(visited.find(start) == visited.end()) tarjanRecurse(graph, start, ids, nodeIds, nodeLowLinks, pushedToStack, currentOstensibleComponent, visited);   
        }

        for (auto [m,v] : nodeLowLinks){
            stronglyConnectedComponenetIds[v].push_back(m);
        }

        for (auto [m, v] : stronglyConnectedComponenetIds){
            stronglyConnectedComponenets.push_back(v);
        }

        // for(auto it = stronglyConnectedComponenets.begin(); it != stronglyConnectedComponenets.end();){
        //     if(it->size() == 1){
        //         std::vector<Node<T>*> nodeScalar = {it->at(0)};
        //         if(graph[it->at(0)] != nodeScalar){ // not a reflexive connection

        //             stronglyConnectedComponenets.erase(it);
        //         }
        //         else {
        //             ++it;
        //         }
        //     }
        //     else {
        //         ++it;
        //     }
        // }
        return {stronglyConnectedComponenets.size(), stronglyConnectedComponenets};
    }

    template <class T>
    bool Traversals<T>::isDAG(Graph<T> graph){
        auto [componentsSize, componenets] = tarjanStronglyConnectedComponenets(graph);
        return (componentsSize != graph.size() || graph.isDirected());
    }

    template <class T>
    void Traversals<T>::tarjanRecurse(Graph<T> graph, Node<T>* currentNode, std::set<int>& ids, std::map<Node<T>*, int>& nodeIds, std::map<Node<T>*, int>& nodeLowLinks, std::map<Node<T>*, bool>& pushedToStack, NodeVisitor<T>& currentOstensibleComponent, std::set<Node<T>*>& visited){
        currentOstensibleComponent.push(currentNode);
        pushedToStack[currentNode] = true; 

        nodeLowLinks[currentNode] = ids.size()+1;
        nodeIds[currentNode] = ids.size()+1;

        ids.insert(ids.size()+1);

        visited.insert(currentNode);

        for(auto neighbor : graph[currentNode]){
            if(visited.find(neighbor) == visited.end()) { 
                tarjanRecurse(graph, neighbor, ids, nodeIds, nodeLowLinks, pushedToStack, currentOstensibleComponent, visited);  
            }
            if(pushedToStack[neighbor]){
                nodeLowLinks[currentNode] = std::min(nodeLowLinks[neighbor], nodeLowLinks[currentNode]);
            }
        }

        if(nodeLowLinks[currentNode] == nodeIds[currentNode]){
            while(!currentOstensibleComponent.empty()){
                auto baseNode = currentOstensibleComponent.pop();
                pushedToStack[baseNode] = false; 
                nodeLowLinks[baseNode] = nodeIds[currentNode];

                if(baseNode == currentNode) break;
            }
        }
    }

    template <class T>
    std::tuple<int, std::vector<std::vector<Node<T>*>>> Traversals<T>::kosarajuStronglyConnectedComponents(Graph<T> graph){
        std::vector<std::vector<Node<T>*>> stronglyConnectedComponenets;
        
        std::set<Node<T>*> visited; 
        NodeVisitor<T> orderedNodes("DFS");

        for(auto [start, adjNodeList] : graph){

            if(visited.find(start) != visited.end()) continue; 

            NodeVisitor<T> nodesToVisit("DFS"); 
            NodeVisitor<T> nodesToBacktrack("DFS"); 

            nodesToVisit.push(start);
           
            bool backtrack = true; 
            Node<T>* currentNode;

            while(!nodesToVisit.empty() || !nodesToBacktrack.empty()){
                if(!backtrack || nodesToBacktrack.empty()){
                    currentNode = nodesToVisit.pop();
                    backtrack = true;
                }
                else if(backtrack){
                    orderedNodes.push(currentNode);
                    currentNode = nodesToBacktrack.pop();
                }
                if(visited.find(currentNode) != visited.end()) continue; 

                visited.insert(currentNode);
                
                auto neighbors = graph[currentNode];

                for(auto neighbor : neighbors){
                    if(visited.find(neighbor) == visited.end()) {
                        backtrack = false; 
                    }
                    nodesToVisit.push(neighbor);
                    
                }
                nodesToBacktrack.push(currentNode);
            } 
        }

        graph.transpose();

        visited.clear();

        while(!orderedNodes.empty()){

            auto start = orderedNodes.pop();

            if(visited.find(start) != visited.end()) continue; 

            NodeVisitor<T> nodesToVisit("DFS"); 
            NodeVisitor<T> nodesToBacktrack("DFS"); 

            nodesToVisit.push(start);
           
            bool backtrack = true; 
            Node<T>* currentNode;

            std::vector<Node<T>*> currentComponent;
            while(!nodesToVisit.empty() || !nodesToBacktrack.empty()){
                if(!backtrack || nodesToBacktrack.empty()){
                    currentNode = nodesToVisit.pop();
                    backtrack = true;
                }
                // else if(backtrack){
                //     while(!nodesToBacktrack.empty()){
                //         currentComponent.push_back(nodesToBacktrack.pop());
                //     }
                //     stronglyConnectedComponenets.push_back(currentComponent);
                // }

                if(visited.find(currentNode) != visited.end()) continue; 

                visited.insert(currentNode);
                
                auto neighbors = graph[currentNode];

                for(auto neighbor : neighbors){
                    nodesToVisit.push(neighbor);
                    
                }
                currentComponent.push_back(currentNode);
            } 
            stronglyConnectedComponenets.push_back(currentComponent);
        }
        return {stronglyConnectedComponenets.size(), stronglyConnectedComponenets};
    }
}

#endif /* TRAVERSALS_HPP */