# Graphify

Graphs are ubiquitous sctructures in computer science, and are neccesary tools for solving problems in fields ranging from network flow to GPS systems.
However, in C++, a language of choice for many developers, a definitive data type for the graph does not exist. For this reason, this library provides
various necessary prebuilt tools for graphs and graph algorithms. 

## Usage of the Library
Graphify is a header only library, meaning compiling with SOs or compilation units is not necessary. 
To create code using the library, simply include a submodule of your choice while using the proper namespace. 
Finally, please note before proceeding that Graphify's Graph datatypes are wrappers of C++'s existing map datatype.

```cpp
#include "Graph/Graph.hpp"
#include "Node/Node.hpp"

int main(){

  Node<char>* a = new Node<char>();
  a->data = 'a'; 
  Node<char>* b = new Node<char>();
  b->data = 'b'; 
  
  Graph<int> graph; 
  graph.addNode(a, {b}); // connect a to specified list of nodes
  return 0; 
}
```

To run your program, compile the file as normal while specifying the directory of the Graphify library. Be sure to set the C++ version to 17. 

```
g++ main.cpp -O2 -Wall -o main.o -I Graphify -std=c++17
```

## Contents

# Datatypes and Main Properties
1. Graph (unweighted)
  a. Out-degree/In-degree
  b. Initialize graph as complete 
  c. Transpose 
  d. Convert to edge list
  e. Check if directed 
  f. Check if bi-partite (2-colorable)
  g. Check if Eulerian circut exists 
  h. Check if Eulerian path exists
2. Weighted Graph
  a. Out-degree/In-degree
  b. Initialize graph as complete
  c. Transpose
  d. Convert to Graph (unweighted), weighted adjacency matrix, weighted edge list
3. Flow Graph
  a. In-degree/Out-degree
  b. Transpose
  c. Is full
4. Edge List (unweighted)
  a. Combine with another edge list
5. Weighted Edge List
  a. Combine with another edge list
  b. Minimum edge weight
6. Weighted Adjacency Matrix
  a. Print 
  
# Graph Traverals
1. Traversals (Unweighted)
  1. Valid traversal methods
  2. Number of connected components
  3. Shortest path between a start & end node
  4. Maximum component
  5. Minimum component 
  6. Number of bridges 
  7. Number of articulation points
  8. Top sort (traversal pts as input)
  9. Kahn top sort
  10. Tarjan's strongly connected components
  11. Kosaraju's strongly connected components
  12. Is DAG
2. Weighted Traversals
  a. Valid traversal methods 
  b. DAG shortest path
  c. DAG longest path
  d. Djikstra's shortest path
  e. Alpha start shortest path
  f. Bellman-Ford shortest path
  g. Floyd-Warshall shortest path
  h. Johnson shortest path
  i. Travelling salesman problem
  j. Kruskal minimum spanning tree
  k. Prim minimum spanning tree
3. Flow Traversals
  a. Valid traversal methods
  b. Ford-Fulkerson maximum flow 
    - Edmonds-Karp flag
  c. Dinic maximum flow
