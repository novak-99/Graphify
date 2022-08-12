#ifndef WEIGHTEDTRAVERSALS_HPP
#define WEIGHTEDTRAVERSALS_HPP

#include "WeightedGraph/WeightedGraph.hpp"
#include "WeightedEdgeList/WeightedEdgeList.hpp"
#include "Traversals/Traversals.hpp"
#include "NodeVisitor/NodeVisitor.hpp"
#include "Graph/Graph.hpp"
#include "Node/Node.hpp"
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <tuple>
#include <vector>
#include <iterator>

namespace Graphify{
    template <class T>
    class Node;

    template <class T>
    class WeightedTraversals{
        public:
            std::vector<std::string> validTraversalMethods(); // => ['DFS', 'BFS', 'UCS']

            bool doesPathExist(WeightedGraph<T> graph, Node<T>* start, Node<T>* end);
            std::tuple<int, std::vector<Node<T>*>> DAGShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end);
            std::tuple<int, std::vector<Node<T>*>> DAGLongestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end);
            std::tuple<int, std::vector<Node<T>*>> djikstraShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end);
            std::tuple<int, std::vector<Node<T>*>> alphaStarShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end, std::map<Node<T>*, int> h);
            std::tuple<int, std::vector<Node<T>*>> bellmanFordShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end);
            std::tuple<std::map<std::pair<Node<T>*, Node<T>*>, int>, std::map<std::pair<Node<T>*, Node<T>*>, std::vector<Node<T>*>>> floydWarshall(WeightedGraph<T> graph);
            std::tuple<std::map<std::pair<Node<T>*, Node<T>*>, int>, std::map<std::pair<Node<T>*, Node<T>*>, std::vector<Node<T>*>>> johnson(WeightedGraph<T> graph);

            int travellingSalesmanProblem(WeightedGraph<T> graph, Node<T>* start);

            // MSTs
            WeightedGraph<T> kruskalMinimumSpanningTree(WeightedGraph<T> graph);
            WeightedGraph<T> primMinimumSpanningTree(WeightedGraph<T> graph);

        private:

            int travellingSalesmanProblemRecurse(Node<T>* start, Node<T>* node, std::vector<Node<T>*>& nodesLeft, WeightedAdjacencyMatrix<T>& adjMat, std::map<Node<T>*, int>& nodeToIndex);
    };

    template <class T>
    std::vector<std::string> WeightedTraversals<T>::validTraversalMethods(){
        return {"DFS", "BFS", "UCS"}; 
    }

    /* 
        Linear time algorithm! 
        We can safely use this 
        function in path finding algorithms 
        without significant overhead cost.
    */
    template <class T>
    bool WeightedTraversals<T>::doesPathExist(WeightedGraph<T> graph, Node<T>* start, Node<T>* end){
        std::set<Node<T>*> visited; 
        // std::queue<Node<T>*> nodesToVisit;
        NodeVisitor<T> nodesToVisit("BFS"); // Maybe pull this magic string out later.. but nevertheless BFS will be used. 
        nodesToVisit.push(start);
        Node<T>* currentNode; 

        while(!nodesToVisit.empty()){
            currentNode = nodesToVisit.pop();

            if(visited.find(currentNode) != visited.end()) continue;

            if(currentNode == end){
                return true;
            }

            visited.insert(currentNode);

            auto neighbors = graph[currentNode];

            for(auto neighbor : neighbors){
                nodesToVisit.push(neighbor.first);
            }
        }
        // we haven't return yet, so we can safely assume nothing was found.. 
        return false;
    }

    template <class T>
    std::tuple<int, std::vector<Node<T>*>> WeightedTraversals<T>::DAGShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end){
        // before we create any variables or begin the search, let's make sure the path actually exists.
        if(!doesPathExist(graph, start, end)) return { -1, {}};

        // the top sort function automatically detects if the graph is a DAG.

        Traversals<T> traversals;
        auto topSort = traversals.kahnTopSort(graph.unweightedGraph()); // our top sort to iterate over

        Node<T>* currentNode = topSort.pop(); // guaranteed to not yield a segfault. 
        NodeVisitor<T> nodesToVisit("BFS");
        std::map<Node<T>*, int> nodeDistance; 
        std::map<Node<T>*, Node<T>*> previousNode; 
        previousNode[start] = nullptr; 
        std::set<Node<T>*> visited;

        std::vector<Node<T>*> path; 

        nodeDistance.insert(std::make_pair(start, 0));

        while(currentNode != end){ 
            if(visited.find(currentNode) != visited.end()) continue; 
            for(auto neighbor : graph[currentNode]){
                nodesToVisit.push(neighbor.first);
                if(nodeDistance.find(neighbor.first) == nodeDistance.end()) {
                     nodeDistance.insert(std::make_pair(neighbor.first, nodeDistance[currentNode] + neighbor.second));
                     previousNode[neighbor.first] = currentNode;
                }
                else { 
                    if(nodeDistance[currentNode] + neighbor.second <= nodeDistance[neighbor.first]){
                        nodeDistance[neighbor.first] = nodeDistance[currentNode] + neighbor.second;
                        previousNode[neighbor.first] = currentNode;
                    }
                }
            }
            currentNode = topSort.pop();
        }

        path.push_back(end);

        Node<T>* currentBackTrackedNode = previousNode[currentNode]; 

        while(currentBackTrackedNode != nullptr){
            path.push_back(currentBackTrackedNode);
            currentBackTrackedNode = previousNode[currentBackTrackedNode];
        }

        std::reverse(path.begin(), path.end());
        return {nodeDistance[end], path};
    }

    // 3 lined function
    template <class T>
    std::tuple<int, std::vector<Node<T>*>> WeightedTraversals<T>::DAGLongestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end){
        graph.scalarMultiply(-1);

        // all err handling dealt with by dag shortest path functions and other function calls within it..
        auto [length, path] = DAGShortestPath(graph, start, end);

        return {-length, path};
    }   

    /* NOTE: This is a LAZY implementation (no Binary Heaps) 
        neighbor.first = node obj, neighbor.second = integer weight
    */ 

    /*
        ->To do for Dijkstra: ensure that there actually exists a path => done
        -> return a tuple containting the path itself, too  => done 
    */
    template <class T>
    std::tuple<int, std::vector<Node<T>*>> WeightedTraversals<T>::djikstraShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end){
        // before we create any variables or begin the search, let's make sure the path actually exists.
        if(!doesPathExist(graph, start, end)) return { -1, {}}; 


        Node<T>* currentNode = start; 
        NodeVisitor<T> nodesToVisit("BFS");
        std::map<Node<T>*, int> nodeDistance; 
        std::map<Node<T>*, Node<T>*> previousNode; 
        previousNode[start] = nullptr; 
        std::set<Node<T>*> visited;

        std::vector<Node<T>*> path; 

        nodeDistance.insert(std::make_pair(start, 0));

        while(currentNode != end){ 
            if(visited.find(currentNode) != visited.end()) continue; 
            for(auto neighbor : graph[currentNode]){
                nodesToVisit.push(neighbor.first);
                if(nodeDistance.find(neighbor.first) == nodeDistance.end()) {
                     nodeDistance.insert(std::make_pair(neighbor.first, nodeDistance[currentNode] + neighbor.second));
                     previousNode[neighbor.first] = currentNode;
                }
                else { 
                    if(nodeDistance[currentNode] + neighbor.second <= nodeDistance[neighbor.first]){
                        nodeDistance[neighbor.first] = nodeDistance[currentNode] + neighbor.second;
                        previousNode[neighbor.first] = currentNode;
                    }
                }
            }
            currentNode = nodesToVisit.pop();
        }

        path.push_back(end);

        Node<T>* currentBackTrackedNode = previousNode[currentNode]; 

        while(currentBackTrackedNode != nullptr){
            path.push_back(currentBackTrackedNode);
            currentBackTrackedNode = previousNode[currentBackTrackedNode];
        }

        std::reverse(path.begin(), path.end());
        return {nodeDistance[end], path};
    }

    template <class T>
    std::tuple<int, std::vector<Node<T>*>> WeightedTraversals<T>::alphaStarShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end, std::map<Node<T>*, int> h){
        // before we create any variables or begin the search, let's make sure the path actually exists.
        if(!doesPathExist(graph, start, end)) return { -1, {}}; 


        Node<T>* currentNode = start; 
        NodeVisitor<T> nodesToVisit("BFS");
        std::map<Node<T>*, int> nodeDistance; 
        std::map<Node<T>*, Node<T>*> previousNode; 
        previousNode[start] = nullptr; 
        std::set<Node<T>*> visited;

        std::vector<Node<T>*> path; 

        nodeDistance.insert(std::make_pair(start, 0));

        while(currentNode != end){ 
            if(visited.find(currentNode) != visited.end()) continue; 
            for(auto neighbor : graph[currentNode]){
                nodesToVisit.push(neighbor.first);
                if(nodeDistance.find(neighbor.first) == nodeDistance.end()) {
                     nodeDistance.insert(std::make_pair(neighbor.first, nodeDistance[currentNode] + neighbor.second + h[neighbor.first]));
                     previousNode[neighbor.first] = currentNode;
                }
                else { 
                    if(h[currentNode] + nodeDistance[currentNode] + neighbor.second <= nodeDistance[neighbor.first] + h[neighbor.first]){
                        nodeDistance[neighbor.first] = nodeDistance[currentNode] + neighbor.second;
                        previousNode[neighbor.first] = currentNode;
                    }
                }
            }
            currentNode = nodesToVisit.pop();
        }

        path.push_back(end);

        Node<T>* currentBackTrackedNode = previousNode[currentNode]; 

        while(currentBackTrackedNode != nullptr){
            path.push_back(currentBackTrackedNode);
            currentBackTrackedNode = previousNode[currentBackTrackedNode];
        }

        std::reverse(path.begin(), path.end());
        return {nodeDistance[end], path};
    }

    template <class T>
    std::tuple<int, std::vector<Node<T>*>> WeightedTraversals<T>::bellmanFordShortestPath(WeightedGraph<T> graph, Node<T>* start, Node<T>* end){
        if(!doesPathExist(graph, start, end)) return { -1, {}}; // probably will want to change this to inf or int_max..
        auto edges = graph.weightedEdgeList();

        std::map<Node<T>*, int> nodeDistance; 
        nodeDistance.insert(std::make_pair(start, 0));

        const int NUM_ITERATIONS = graph.size() - 1;

        std::map<Node<T>*, Node<T>*> previousNode; 
        previousNode[start] = nullptr; 

        std::vector<Node<T>*> path;


        for(int i = 0; i < NUM_ITERATIONS; i++){
            for(auto edge : edges){
                if(nodeDistance.find(std::get<0>(edge)) == nodeDistance.end() && nodeDistance.find(std::get<1>(edge)) == nodeDistance.end()){
                    continue; 
                } 
                else if(nodeDistance.find(std::get<0>(edge)) != nodeDistance.end() && nodeDistance.find(std::get<1>(edge)) == nodeDistance.end()){
                    nodeDistance[std::get<1>(edge)] = nodeDistance[std::get<0>(edge)] + std::get<2>(edge);
                    previousNode[std::get<1>(edge)] = std::get<0>(edge);
                }
                else if(nodeDistance.find(std::get<0>(edge)) != nodeDistance.end() && nodeDistance.find(std::get<1>(edge)) != nodeDistance.end()){
                    if(nodeDistance[std::get<0>(edge)] + std::get<2>(edge) < nodeDistance[std::get<1>(edge)]){
                        nodeDistance[std::get<1>(edge)] = nodeDistance[std::get<0>(edge)] + std::get<2>(edge);
                        previousNode[std::get<1>(edge)] = std::get<0>(edge);
                    }
                }
            }
        }
        path.push_back(end);

        Node<T>* currentBackTrackedNode = previousNode[end]; 

        while(currentBackTrackedNode != nullptr){
            path.push_back(currentBackTrackedNode);
            currentBackTrackedNode = previousNode[currentBackTrackedNode];
        }

        std::reverse(path.begin(), path.end());

        return {nodeDistance[end], path};
    }

    // this is an all pairs algorithm.. and the loop is iterative.. 
    // due to the nature of the algorithm checking if "path from a->b exists" is not necessary

    // O((|V|)^3)! 
    template <class T>
    std::tuple<std::map<std::pair<Node<T>*, Node<T>*>, int>, std::map<std::pair<Node<T>*, Node<T>*>, std::vector<Node<T>*>>> WeightedTraversals<T>::floydWarshall(WeightedGraph<T> graph){
        std::map<std::pair<Node<T>*, Node<T>*>, int> distMat;
        std::map<std::pair<Node<T>*, Node<T>*>, std::vector<Node<T>*>> paths;

        std::map<std::pair<Node<T>*, Node<T>*>, Node<T>*> previousNodes; 

        for(auto [node, nodeAdjList] : graph){
            distMat.insert(std::make_pair(std::make_pair(node, node), 0));
            previousNodes[{node, node}] = nullptr; 
            for(auto [baseNode, weight] : nodeAdjList){
                distMat.insert(std::make_pair(std::make_pair(node, baseNode), weight));
            }

        }

        for(auto [node1, nodeAdjList] : graph){
            for(auto [node2, nodeAdjList] : graph){
                for(auto [node3, nodeAdjList] : graph){
                    // effectively traverse through node1, for all node1 : graph. 
                    if(distMat.find({node1, node3}) == distMat.end() || distMat.find({node2, node1}) == distMat.end()){
                        continue;
                    }
                    else if(distMat.find({node2, node3}) == distMat.end()){
                        distMat[{node2, node3}] = distMat[{node2, node1}] + distMat[{node1, node3}]; 
                        previousNodes[{node2, node3}] = node1; 
                    }
                    else{
                        if(distMat[{node2, node1}] + distMat[{node1, node3}] < distMat[{node2, node3}]){
                            distMat[{node2, node3}] = distMat[{node2, node1}] + distMat[{node1, node3}]; 
                            previousNodes[{node2, node3}] = node1; 
                        }
                    }
                }
            }
        }

        for(auto [node, nodeAdjList] : graph){

            for(auto [baseNode, nodeAdjList] : graph){

                paths[{node,baseNode}].push_back(baseNode);

                Node<T>* currentBackTrackedNode = previousNodes[{node, baseNode}]; 

                while(currentBackTrackedNode != nullptr){
                    paths[{node, baseNode}].push_back(currentBackTrackedNode);
                    currentBackTrackedNode = previousNodes[{node,currentBackTrackedNode}];
                }
                paths[{node,baseNode}].push_back(node);
                std::reverse(paths[{node,baseNode}].begin(), paths[{node, baseNode}].end());
            }
        }

        return {distMat, paths};
    }

    template <class T> 
    std::tuple<std::map<std::pair<Node<T>*, Node<T>*>, int>, std::map<std::pair<Node<T>*, Node<T>*>, std::vector<Node<T>*>>> WeightedTraversals<T>::johnson(WeightedGraph<T> graph){
        auto bfGraph = graph; 
        Node<T>* bfNode = new Node<T>(); 
        
        for(auto [node, nodeAdjList] : bfGraph){
            bfGraph.addEdge(bfNode, {node, 0}); // 0 weighted edge.
        }


        std::map<Node<T>*, int> newWeightMap; 

        // finding dists from every node to the new bfNode as per the algorithn
        for(auto [node, nodeAdjList] : bfGraph){
            if(node == bfNode) continue;
            auto [length, path] = bellmanFordShortestPath(bfGraph, bfNode, node);
            newWeightMap[node] = length;
        }

        // weight updation
        // W_uv_new = W_uv_old + bfWeight_u - bfWeight_v, for all edges (u, v)
        for(auto [node, nodeAdjList] : bfGraph){
            for(auto [baseNode, nodeAdjList] : bfGraph){
                int oldWeight = bfGraph.getWeight(node, baseNode);
                int newWeight = oldWeight + newWeightMap[node] - newWeightMap[baseNode];
                bfGraph.setWeight(node, baseNode, newWeight);
            }
        }

        bfGraph.erase(bfNode);

        std::map<std::pair<Node<T>*, Node<T>*>, int> distMat;
        std::map<std::pair<Node<T>*, Node<T>*>, std::vector<Node<T>*>> paths;
        // perform djikstra on all nodes.
        for(auto [node, nodeAdjList] : bfGraph){
            for(auto [baseNode, nodeAdjList] : bfGraph){
                auto [length, path] = djikstraShortestPath(bfGraph, node, baseNode);
                distMat[{node, baseNode}] = length; 
                paths[{node, baseNode}] = path;
            }
        }
        return {distMat, paths};
    }

    template <class T>
    int WeightedTraversals<T>::travellingSalesmanProblem(WeightedGraph<T> graph, Node<T>* start){
        auto [adjMat, nodeToIndex] = graph.weightedAdjacencyMatrix();

        adjMat.print();

        auto nodes = graph.getAllNodes();

        auto nodesWithoutStart = nodes;
        nodesWithoutStart.erase(std::remove(nodes.begin(), nodes.end(), start));

        return travellingSalesmanProblemRecurse(start, start, nodesWithoutStart, adjMat, nodeToIndex);
        
    }
    
    template <class T>
    WeightedGraph<T> WeightedTraversals<T>::kruskalMinimumSpanningTree(WeightedGraph<T> graph){
        auto edgeList = graph.weightedEdgeList();

        // sort by weighted (pair_element->second)
        std::sort(edgeList.begin(), edgeList.end(), [](auto &left, auto &right) { return std::get<2>(left) < std::get<2>(right); });

        typename std::vector<WeightedEdgeList<T>>::iterator emptyIt = {};

        std::vector<WeightedEdgeList<T>> unionFind; // use combine, find ops...

        for(auto edge : edgeList){ // min to max
            auto firstIt = emptyIt; 
            auto secondIt = emptyIt;
            for(auto it = unionFind.begin(); it != unionFind.end(); it++){

                auto first = it->find(std::get<0>(edge));

                if(first != it->end()){ // this can't happen more than once, by defn
                    firstIt = it;
                }

                auto second = it->find(std::get<1>(edge));

                if(second != it->end()){
                    secondIt = it; 
                }
            }

            if(firstIt == emptyIt && secondIt == emptyIt){
                WeightedEdgeList<T> group;
                group.addEdge(edge);

                unionFind.push_back(group);
            }
            else if(firstIt == secondIt){
                // just do nothing..
            }
            else if(firstIt != emptyIt && secondIt == emptyIt){
                firstIt->addEdge(edge);
            }
            else if(firstIt == emptyIt && secondIt != emptyIt){
                secondIt->addEdge(edge);
            }
            else if(firstIt != emptyIt && secondIt != emptyIt){ // arbitrarily choose the first one as a base case
                firstIt->addEdge(edge);
                firstIt->combine(*secondIt);
                unionFind.erase(secondIt);

                
            }
        }

        return unionFind[0].weightedGraph(); // Guaranteed to be of size 1..
    }

    template <class T>
    WeightedGraph<T> WeightedTraversals<T>::primMinimumSpanningTree(WeightedGraph<T> graph){
        auto currentNode = graph.begin()->first;
        auto edgeList = graph.weightedEdgeList();

        WeightedEdgeList<T> MST;

        std::set<Node<T>*> pickedNodes = {};

        while(pickedNodes.size() != graph.size()){ // all nodes are picked
            pickedNodes.insert(currentNode);


            WeightedEdgeList<T> minEdgeList;
            for(auto it = pickedNodes.begin(); it != pickedNodes.end(); it++){
                std::tuple<Node<T>*, Node<T>*, int> edge;                
                auto tempEdgeList = edgeList;
                while(MST.find(edge) != MST.end() || std::get<0>(edge) != *it || std::find(pickedNodes.begin(), pickedNodes.end(), std::get<1>(edge))  != pickedNodes.end()){
                    if(tempEdgeList.size() == 0) break;
                    edge = tempEdgeList.minEdge();
                    tempEdgeList.erase(edge); // this is an overloaded erase function
                }
                minEdgeList.addEdge(edge);
            }

            auto edge = minEdgeList.minEdge();         
            pickedNodes.insert(std::get<0>(edge));
            pickedNodes.insert(std::get<1>(edge));
            currentNode = std::get<1>(edge);
            MST.addEdge(edge);
        }   
        return MST.weightedGraph();
    }

    template <class T>
    int WeightedTraversals<T>::travellingSalesmanProblemRecurse(Node<T>* start, Node<T>* node, std::vector<Node<T>*>& nodesLeft, WeightedAdjacencyMatrix<T>& adjMat, std::map<Node<T>*, int>& nodeToIndex){
        if(nodesLeft.size() == 0){
            return adjMat[nodeToIndex[node]][nodeToIndex[start]]; // row is node, col is start. 
        }
        
        int finalVal = INT_MAX; 
        for(int i = 0; i < nodesLeft.size(); i++){
            auto currentNodesLeft = nodesLeft; 
            currentNodesLeft.erase(std::remove(currentNodesLeft.begin(), currentNodesLeft.end(), nodesLeft[i]));
            finalVal = std::min(finalVal, adjMat[nodeToIndex[node]][nodeToIndex[nodesLeft[i]]] + travellingSalesmanProblemRecurse(start, nodesLeft[i], currentNodesLeft, adjMat, nodeToIndex));
        }

        return finalVal;
    }
}

#endif /* WEIGHTEDTRAVERSALS_HPP */