# Graphify

Graphs are ubiquitous sctructures in computer science, and are neccesary tools for solving problems in fields ranging from network flow to GPS systems.
However, in C++, a language of choice for many developers, a definitive data type for the graph does not exist. For this reason, this library provides
various necessary prebuilt tools for graphs and graph algorithms. 

## Usage of the Library
Graphify is a header only library, meaning compiling with SOs or compilation units is not necessary. 
To create code using the library, simply include a submodule of your choice while using the proper namespace. 

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
