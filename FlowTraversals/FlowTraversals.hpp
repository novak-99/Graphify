#ifndef FLOWTRAVERSALS_HPP
#define FLOWTRAVERSALS_HPP

#include "FlowGraph/FlowGraph.hpp"
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
    class FlowTraversals{
        public:
            std::vector<std::string> validTraversalMethods(); // => ['DFS', 'BFS']

            int fordFulkersonMaximumFlow(FlowGraph<T> graph, bool edmondsKarp=false);
            int dinicMaximumFlow(FlowGraph<T> graph);

        private:
            void fordFulkersonRecurse(FlowGraph<T>& graph, Node<T>* currentNode, std::set<Node<T>*>& visited, std::vector<Node<T>*>& nodesToBacktrack, int& currentIndex, int& finalMaxFlow);

        
    };

    template <class T>
    std::vector<std::string> FlowTraversals<T>::validTraversalMethods(){
        return {"DFS", "BFS"}; 
    }

    // template <class T>
    // int FlowTraversals<T>::fordFulkersonMaximumFlow(FlowGraph<T> graph){

    //     // don't forget to add backward edges to graph as per FF.
    //     graph.addBackwardEdges();

    //     std::set<Node<T>*> visited; 

    //     NodeVisitor<T> nodesToVisit("DFS");
    //     nodesToVisit.push(graph.src);

    //     int finalMaxFlow = 0; 
    //     int minFlow = INT_MAX; 

    //     bool backtrack = true; 
    //     Node<T>* currentNode; 
    //     Node<T>* previousNode = nullptr; 

    //     std::vector<Node<T>*> currentPath(graph.size());
    //     int currentIndex = 0;

    //     // continue until no more augmented paths can be found 
    //     while(!nodesToVisit.empty() || currentPath[0] != 0){
    //         if(!backtrack || currentPath[0] == 0){
    //             currentNode = nodesToVisit.pop();
    //             backtrack = true;

    //             currentPath[currentIndex] = currentNode; 
    //             currentIndex++;
    //         }
    //         else if(backtrack){
    //             currentIndex--; 
    //             visited.erase(currentNode); 

    //             currentNode = currentPath[currentIndex]; 
    //         }

    //         visited.insert(currentNode);

    //         if(previousNode != nullptr) minFlow = std::min(minFlow, graph.getMaxCapacity(previousNode, currentNode) - graph.getCurrentCapacity(previousNode, currentNode));

    //         std::cout << currentNode->data << "\n";

    //         auto neighbors = graph[currentNode];

    //         for(auto [neighbor, currentCapacity, maxCapacity] : neighbors){
    //             if(visited.find(neighbor) == visited.end() && graph.getMaxCapacity(currentNode, neighbor) - graph.getCurrentCapacity(currentNode, neighbor) > 0) {
    //                 backtrack = false; 
    //                 nodesToVisit.push(neighbor);
    //             }
    //         }
    //         std::cout << backtrack << "\n";

    //         if(currentNode == graph.sink){ // path found
    //             auto path = currentPath;
    //             finalMaxFlow += minFlow;

    //             Node<T>* node; 
    //             Node<T>* baseNode; 

    //             for(int i = 0; !path.empty(); i++){
    //                 if(i == 0){ // this should never result in a segfault.. if the graph size is at least 2, the two nodes are the src & sink.
    //                     baseNode = path.back();
    //                     path.pop_back();

    //                     node = path.back();
    //                     path.pop_back();
    //                 } 
    //                 node = path.back();
    //                 path.pop_back();

    //                 graph.setCurrentCapacity(node, baseNode, graph.getCurrentCapacity(node, baseNode) + minFlow);
    //                 graph.setCurrentCapacity(baseNode, node, graph.getCurrentCapacity(baseNode, node) - minFlow);
    //             }
    //         }

    //         previousNode = currentNode;
    //     }
    //     return finalMaxFlow;
    // }

    template <class T>
    int FlowTraversals<T>::fordFulkersonMaximumFlow(FlowGraph<T> graph, bool edmondsKarp){
        std::vector<Node<T>*> nodesToBacktrack;
        nodesToBacktrack.resize(graph.size());

        // don't forget to add backward edges to graph as per FF.
        graph.addBackwardEdges();


        std::set<Node<T>*> visited;
        int finalMaxFlow = 0;  // we're returning this..

        bool pathFound = false; 
        do{
            pathFound = false; 
            std::set<Node<T>*> visited; 

            // Edmonds karp is essentially ford fulkerson max flow but assume BFS for path finding. 
            // If edmonds karp is uninitialized or set to false, we assume the user wants to use DFS FFA. 
            std::string method = "DFS";
            edmondsKarp ? method = "BFS" : method = "DFS"; // guaranteed initialization. 
            NodeVisitor<T> nodesToVisit(method); // Maybe pull this magic string out later.. but nevertheless BFS will be used. 
            nodesToVisit.push(graph.src);
            Node<T>* currentNode; 

            std::map<Node<T>*, Node<T>*> previousNode; 
            previousNode[graph.src] = nullptr;

            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();

                if(currentNode == graph.sink){
                    pathFound = true;
                    break; 
                }

                visited.insert(currentNode);

                auto neighbors = graph[currentNode];

                for(auto [neighbor, currentCapacity, maxCapacity] : neighbors){
                    bool isFull = graph.getMaxCapacity(currentNode, neighbor) - graph.getCurrentCapacity(currentNode, neighbor) <= 0;
                    if(!isFull && visited.find(neighbor) == visited.end()){
                        nodesToVisit.push(neighbor);
                        previousNode[neighbor] = currentNode;
                    }
                }
            }

            if(pathFound){
                int minFlow = INT_MAX;
                Node<T>* currentNode = graph.sink;
                while(previousNode[currentNode] != nullptr){
                    minFlow = std::min(minFlow, graph.getMaxCapacity(previousNode[currentNode], currentNode) - graph.getCurrentCapacity(previousNode[currentNode], currentNode));
                    currentNode = previousNode[currentNode];
                }

                // restarting variables for second loop
                currentNode = graph.sink;
                while(previousNode[currentNode] != nullptr){
                    // this should never result in a segfault.. if the graph size is at least 2, the two nodes are the src & sink.
                    auto baseNode = currentNode;
                    auto node = previousNode[currentNode];

                    graph.setCurrentCapacity(node, baseNode, graph.getCurrentCapacity(node, baseNode) + minFlow);
                    graph.setCurrentCapacity(baseNode, node, graph.getCurrentCapacity(baseNode, node) - minFlow);
                    currentNode = previousNode[currentNode];
                }
                finalMaxFlow += minFlow;
            }

            previousNode.clear();
        } while(pathFound);

        return finalMaxFlow;

    }

    template <class T>
    void FlowTraversals<T>::fordFulkersonRecurse(FlowGraph<T>& graph, Node<T>* currentNode, std::set<Node<T>*>& visited, std::vector<Node<T>*>& nodesToBacktrack, int& currentIndex, int& finalMaxFlow){

        if(visited.find(currentNode) != visited.end()) return;

        visited.insert(currentNode);
        nodesToBacktrack[currentIndex] = currentNode;
        currentIndex++;

        if(currentNode == graph.sink){
            auto path = nodesToBacktrack;
            int pathCurrentIndex = currentIndex;

            auto tempGraph = graph;

            bool stop = false; 

            int minFlow = INT_MAX;
            for(int i = pathCurrentIndex-1; i >= 1; i--){
                minFlow = std::min(minFlow, graph.getMaxCapacity(path[i-1], path[i]) - graph.getCurrentCapacity(path[i-1], path[i]));
            }
            for(int i = pathCurrentIndex-1; i >= 1; i--){
                // this should never result in a segfault.. if the graph size is at least 2, the two nodes are the src & sink.
                auto baseNode = path[i];
                auto node = path[i-1];

                tempGraph.setCurrentCapacity(node, baseNode, tempGraph.getCurrentCapacity(node, baseNode) + minFlow);
                tempGraph.setCurrentCapacity(baseNode, node, tempGraph.getCurrentCapacity(baseNode, node) - minFlow);

                if(graph.getMaxCapacity(node, baseNode) - graph.getCurrentCapacity(node, baseNode) == 0) {
                    nodesToBacktrack = path; 
                    currentIndex = i;
                }
            }
            if(!stop){
                finalMaxFlow += minFlow;
                graph = tempGraph;
            }
            std::cout  << "\n";
        }

        auto neighbors = graph[currentNode];

        // won't run if curr is sink..
        for(auto [neighbor, currentCapacity, maxCapacity] : neighbors){
            if(currentNode != graph.sink && visited.find(neighbor) == visited.end() && graph.getMaxCapacity(currentNode, neighbor) - graph.getCurrentCapacity(currentNode, neighbor) > 0) {
                fordFulkersonRecurse(graph, neighbor, visited, nodesToBacktrack, currentIndex, finalMaxFlow);
            }
        }

        currentIndex--;
        visited.erase(currentNode);
    }

    template <class T>
    int FlowTraversals<T>::dinicMaximumFlow(FlowGraph<T> graph){
        std::vector<Node<T>*> nodesToBacktrack;
        nodesToBacktrack.resize(graph.size());

        // don't forget to add backward edges to graph as per FF.
        graph.addBackwardEdges();
        int finalMaxFlow = 0;  // we're returning this..


        bool pathFound = false; 
        do{
            pathFound = false; 
            std::map<Node<T>*, int> nodeLevels; 
            std::set<Node<T>*> visited; 

            nodeLevels[graph.src] = 0; 

                NodeVisitor<T> nodesToVisit("BFS"); 
                nodesToVisit.push(graph.src);
                Node<T>* currentNode; 

                while(!nodesToVisit.empty()){
                    currentNode = nodesToVisit.pop();

                    if(currentNode == graph.sink){
                        pathFound = true;
                        break; 
                    }

                    visited.insert(currentNode);
                    
                    auto neighbors = graph[currentNode];

                    for(auto [neighbor, currentCapacity, maxCapacity] : neighbors){
                        bool isFull = graph.getMaxCapacity(currentNode, neighbor) - graph.getCurrentCapacity(currentNode, neighbor) <= 0;
                        if(visited.find(neighbor) == visited.end() && !isFull) { 
                            nodeLevels[neighbor] = nodeLevels[currentNode]+1;
                            nodesToVisit.push(neighbor);
                        }

                    }
                }

            visited.clear();

            nodesToVisit = NodeVisitor<T>("DFS"); // Maybe pull this magic string out later
            nodesToVisit.push(graph.src);
            currentNode = nullptr;

            std::map<Node<T>*, Node<T>*> previousNode; 
            previousNode[graph.src] = nullptr;

            while(!nodesToVisit.empty()){
                currentNode = nodesToVisit.pop();

                if(currentNode == graph.sink) break;

                visited.insert(currentNode);

                auto neighbors = graph[currentNode];

                for(auto [neighbor, currentCapacity, maxCapacity] : neighbors){
                    bool isFull = graph.getMaxCapacity(currentNode, neighbor) - graph.getCurrentCapacity(currentNode, neighbor) <= 0;
                    // std::cout << nodeLevels[neighbor] << " " << nodeLevels[currentNode] << "\n";
                    if(!isFull && visited.find(neighbor) == visited.end() && nodeLevels[neighbor] == nodeLevels[currentNode]+1){
                        nodesToVisit.push(neighbor);
                        previousNode[neighbor] = currentNode;
                    }
                }
            }

            if(pathFound){
                int minFlow = INT_MAX;
                Node<T>* currentNode = graph.sink;
                while(previousNode[currentNode] != nullptr){
                    minFlow = std::min(minFlow, graph.getMaxCapacity(previousNode[currentNode], currentNode) - graph.getCurrentCapacity(previousNode[currentNode], currentNode));
                    currentNode = previousNode[currentNode];
                }

                // restarting variables for second loop
                currentNode = graph.sink;
                while(previousNode[currentNode] != nullptr){
                    // this should never result in a segfault.. if the graph size is at least 2, the two nodes are the src & sink.
                    auto baseNode = currentNode;
                    auto node = previousNode[currentNode];

                    graph.setCurrentCapacity(node, baseNode, graph.getCurrentCapacity(node, baseNode) + minFlow);
                    graph.setCurrentCapacity(baseNode, node, graph.getCurrentCapacity(baseNode, node) - minFlow);
                    currentNode = previousNode[currentNode];
                }
                finalMaxFlow += minFlow;
            }

            previousNode.clear();
        } while(pathFound);

        return finalMaxFlow;

    }
}

#endif /* FLOWTRAVERSALS_HPP */