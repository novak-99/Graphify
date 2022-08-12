#include <iostream>
#include <vector>
#include "Graph/Graph.hpp"
#include "WeightedGraph/WeightedGraph.hpp"
#include "Node/Node.hpp"
#include "Traversals/Traversals.hpp"
#include "WeightedTraversals/WeightedTraversals.hpp"
#include "NodeVisitor/NodeVisitor.hpp"
#include "FlowTraversals/FlowTraversals.hpp"
#include "FlowGraph/FlowGraph.hpp"

using namespace Graphify;

int main(){

    // don't forget to add:
    // test cases
    // typedef NodeList, or create custom class
    // error handling for and flow graph
    // rename WeightedGraph => graph
    // switch -1 to INF
    // union cost search
    // check for undirected in weighted traversals MSTs...
    // add return vector path in TSMP
    // add network graph in returning in flow traversals 
    // also don't forget to return vals when necessary and to remove all warnings

    // Graph<int> graph; 


    // // Node<char>* a = new Node<char>();
    // // a->data = 'a'; 
    // // Node<char>* b = new Node<char>();
    // // b->data = 'b'; 
    // // Node<char>* c = new Node<char>();
    // // c->data = 'c'; 
    // // Node<char>* d = new Node<char>();
    // // d->data = 'd'; 
    // // Node<char>* e = new Node<char>();
    // // e->data = 'e'; 
    // // Node<char>* f = new Node<char>();
    // // f->data = 'f'; 
    // // Node<char>* g = new Node<char>();
    // // g->data = 'g'; 
    // // Node<char>* h = new Node<char>();
    // // h->data = 'h'; 
    // // Node<char>* i = new Node<char>();
    // // i->data = 'i'; 
    // // Node<char>* j = new Node<char>();
    // // j->data = 'j'; 
    // // Node<char>* k = new Node<char>();
    // // k->data = 'k'; 
    // // Node<char>* l = new Node<char>();
    // // l->data = 'l'; 
    // // Node<char>* m = new Node<char>();
    // // m->data = 'm'; 

    // // // graph.addNode(a, {b});
    // // // graph.addNode(b, {c,e,f});
    // // // graph.addNode(c, {d,g});
    // // // graph.addNode(d, {c, h});
    // // // graph.addNode(e, {a,f});
    // // // graph.addNode(f, {g});
    // // // graph.addNode(g, {f});
    // // // graph.addNode(h, {d,g});

    // // graph.addNode(a, {b,c,d,e});
    // // graph.addNode(b, {d});
    // // graph.addNode(c, {d,e});
    // // graph.addNode(d, {e});
    // // graph.addNode(e, {});

    // std::cout << graph.maximumOutDegree() << "\n";

    // Traversals<char> traversals; 

    // // std::cout << traversals.numConnectedComponents(graph, "Djikstra") << "\n" << "\n"; // maybe remove repition..

    // // auto [maxCompSize, maxComponents] = traversals.maxComponent(graph);

    // // std::cout << maxCompSize << "\n" << "\n";

    // auto TOPSORT = traversals.topologicalSort(graph, {b,a});

    // while(!TOPSORT.empty()){
    //     std::cout << TOPSORT.pop()->data << "\n";
    // }

    // Graph<char> graph;

    // Node<char>* a = new Node<char>();
    // a->data = 'a'; 
    // Node<char>* b = new Node<char>();
    // b->data = 'b'; 
    // Node<char>* c = new Node<char>();
    // c->data = 'c'; 
    // Node<char>* d = new Node<char>();
    // d->data = 'd'; 
    // Node<char>* e = new Node<char>();
    // e->data = 'e'; 
    // Node<char>* f = new Node<char>();
    // f->data = 'f'; 
    // Node<char>* g = new Node<char>();
    // g->data = 'g'; 
    // Node<char>* h = new Node<char>();
    // h->data = 'h'; 

    // graph.addNode(a, {c});
    // graph.addNode(b, {a,d});
    // graph.addNode(c, {b,d,e});
    // graph.addNode(d, {f});
    // graph.addNode(e, {f,g});
    // graph.addNode(f, {d});
    // graph.addNode(g, {e,h});
    // graph.addNode(h, {g,f});


    // Traversals<char> traversals;
    // auto [has_cycles, _] = traversals.kosarajuStronglyConnectedComponents(graph);
    // std::cout << has_cycles << " " << _.size() << "\n";


    // graph.addNode(a, {d,e});
    // graph.addNode(b, {d});
    // graph.addNode(c, {d,e});
    // graph.addNode(d, {a,b,c});
    // graph.addNode(e, {a,c});

    // std::cout << std::boolalpha << graph.isBipartite() << "\n";


    // WeightedGraph<char> graph;
    // graph.addNode(a, {{b, 2}, {c,4}});
    // graph.addNode(b, {{a,2}, {d, 4}, {e,2}, {c,1}});
    // graph.addNode(c, {{a, 4}, {b,1}, {e,3}});
    // graph.addNode(d, {{b, 4}, {e,2}, {f,2}});
    // graph.addNode(e, {{b, 2}, {d,3}, {f,2}});
    // graph.addNode(f, {{d, 2}, {e,2}});

    // Node<int>* a = new Node<int>();
    // a->data = 1; 
    // Node<int>* b = new Node<int>();
    // b->data = 2; 
    // Node<int>* c = new Node<int>();
    // c->data = 3; 
    // Node<int>* d = new Node<int>();
    // d->data = 4; 
    // Node<int>* e = new Node<int>();
    // e->data = 5; 
    // Node<int>* f = new Node<int>();
    // f->data = 6; 
    // Node<int>* g = new Node<int>();
    // g->data = 7; 

    // WeightedGraph<int> graph;
    // graph.addNode(a, {{b, 6}, {c,5}, {d, 5}});
    // graph.addNode(b, {{e,-1}});
    // graph.addNode(c, {{e, 1}, {b, -2}});
    // graph.addNode(d, {{c, -2}, {f, -1}});
    // graph.addNode(e, {{g, 3}});
    // graph.addNode(f, {{g, 3}});
    // graph.addNode(g, {});

    // WeightedTraversals<int> wt;
    // auto [length, path] = wt.bellmanFordShortestPath(graph, a, g);

    // for(int i = 0; i < path.size(); i++){
    //     std::cout << path[i]->data << "\n";
    // }

    // std::cout << length << "\n";



    // Node<char>* s = new Node<char>();
    // s->data = 's'; 
    // Node<char>* a = new Node<char>();
    // a->data = 'a'; 
    // Node<char>* b = new Node<char>();
    // b->data = 'b'; 
    // Node<char>* c = new Node<char>();
    // c->data = 'c'; 
    // Node<char>* d = new Node<char>();
    // d->data = 'd'; 
    // Node<char>* e = new Node<char>();
    // e->data = 'e'; 
    // Node<char>* f = new Node<char>();
    // f->data = 'f'; 
    // Node<char>* g = new Node<char>();
    // g->data = 'g'; 
    // Node<char>* h = new Node<char>();
    // h->data = 'h'; 
    // Node<char>* i = new Node<char>();
    // i->data = 'i'; 
    // Node<char>* j = new Node<char>();
    // j->data = 'j'; 
    // Node<char>* k = new Node<char>();
    // k->data = 'k'; 
    // Node<char>* l = new Node<char>();
    // l->data = 'l'; 


    // WeightedEdgeList<char> edges(true); 
    // edges.addEdge({s,c,3});
    // edges.addEdge({c,l,2});
    // edges.addEdge({l,j,4});
    // edges.addEdge({l,i,4});
    // edges.addEdge({i,j,6});
    // edges.addEdge({k,e,5});
    // edges.addEdge({j,k,4});
    // edges.addEdge({i,k,4});
    // edges.addEdge({g,e,2});
    // edges.addEdge({h,g,2});
    // edges.addEdge({h,f,3});
    // edges.addEdge({b,h,1});
    // edges.addEdge({b,d,4});
    // edges.addEdge({s,a,7});
    // edges.addEdge({s,b,2});
    // edges.addEdge({a,d,4});
    // edges.addEdge({a,b,3});

    // std::map<Node<char>*, int> heuristic; 
    // heuristic[s] = 10; 
    // heuristic[c] = 8; 
    // heuristic[l] = 6; 
    // heuristic[j] = 4; 
    // heuristic[i] = 4; 
    // heuristic[j] = 3; 
    // heuristic[e] = 0; 
    // heuristic[g] = 3; 
    // heuristic[h] = 6; 
    // heuristic[f] = 6; 
    // heuristic[b] = 1000; 
    // heuristic[a] = 9; 
    // heuristic[d] = 8; 
    // heuristic[k] = 3;



    // WeightedTraversals<char> traversals;

    // auto [length, path] = traversals.alphaStarShortestPath(edges.weightedGraph(), s, e, heuristic);

    // for(int i = 0; i < path.size(); i++){
    //     std::cout << path[i]->data << "\n";
    // }

    // std::cout << length << "\n";

    // auto [_,  paths] =traversals.floydWarshall(graph);

    // for(int i = 0; i < paths[{d,c}].size(); i++){
    //     std::cout << paths[{d,c}][i]->data << "\n";
    // }

    // auto [_,  paths] = traversals.johnson(graph);

    // for(int i = 0; i < paths[{a,b}].size(); i++){
    //     std::cout << paths[{a,b}][i]->data << "\n";
    // }

    // auto graph = traversals.kruskalMinimumSpanningTree(edges.weightedGraph());

    // int val = 0; 
    // for(auto edge : graph.weightedEdgeList()){
    //     std::cout << std::get<0>(edge)->data << " " << std::get<1>(edge)->data << "\n";
    //     val += std::get<2>(edge);
    // }
    // std::cout << val / 2 << "\n";

    // auto graph = traversals.primMinimumSpanningTree(edges.weightedGraph());

    // int val = 0; 
    // for(auto edge : graph.weightedEdgeList()){
    //     std::cout << std::get<0>(edge)->data << " " << std::get<1>(edge)->data << "\n";
    //     val += std::get<2>(edge);
    // }
    // std::cout << val/2 << "\n";




    // std::cout << graph.inDegree(b) << "\n";
    // std::cout << graph.maximumInDegree() << "\n";

    // Node<char>* a = new Node<char>();
    // a->data = 'a'; 
    // Node<char>* b = new Node<char>();
    // b->data = 'b'; 
    // Node<char>* c = new Node<char>();
    // c->data = 'c'; 
    // Node<char>* d = new Node<char>();
    // d->data = 'd'; 
    // Node<char>* e = new Node<char>();
    // e->data = 'e'; 
    // Node<char>* f = new Node<char>();
    // f->data = 'f'; 
    // Node<char>* g = new Node<char>();
    // g->data = 'g'; 
    // Node<char>* h = new Node<char>();
    // h->data = 'h'; 

    // Graph<char> graph; 
    // Traversals<char> t; 

    // graph.addNode(a, {b});
    // graph.addNode(b, {c});
    // graph.addNode(c, {d});
    // graph.addNode(d, {});

    // auto [num, bridges] = t.numBridges(graph);
    // std::cout << num << "\n";

    // graph.addNode(a, {{b, 3}, {c, 6}});
    // graph.addNode(b, {{c, 4}, {d, 4}, {e, 11}});
    // graph.addNode(c, {{d, 8}, {g, 11}});
    // graph.addNode(d, {{e, -4}, {f, 5}, {g, 2}});
    // graph.addNode(e, {{h, 9}});
    // graph.addNode(f, {{h, 1}});
    // graph.addNode(g, {{h, 2}});
    // graph.addNode(h, {});

    

    // WeightedTraversals<char> wt;
    // auto [length, path] = wt.DAGLongestPath(graph, a, h);
    // for(auto node : path){
    //     std::cout << node->data << "\n";
    // }
    // std::cout << length << "\n";


    // TSP

    // Node<char>* a = new Node<char>();
    // a->data = 'a'; 
    // Node<char>* b = new Node<char>();
    // b->data = 'b'; 
    // Node<char>* c = new Node<char>();
    // c->data = 'c'; 
    // Node<char>* d = new Node<char>();
    // d->data = 'd'; 
    // Node<char>* e = new Node<char>();
    // e->data = 'e'; 
    // Node<char>* f = new Node<char>();
    // f->data = 'f'; 
    // Node<char>* g = new Node<char>();
    // g->data = 'g'; 

    // WeightedGraph<char> graph;
    // graph.addNode(a, {{b, 10},{c, 15},{d,20}});
    // graph.addNode(b, {{a,5},{c,9},{d,10}});
    // graph.addNode(c, {{a,6},{b,13},{d,12}});
    // graph.addNode(d, {{a,8},{b,8},{c,9}});

    // WeightedTraversals<char> wt; 

    // std::cout << wt.travellingSalesmanProblem(graph, a) << "\n";

    // Node<char>* a = new Node<char>();
    // a->data = 'a'; 
    // Node<char>* b = new Node<char>();
    // b->data = 'b'; 
    // Node<char>* c = new Node<char>();
    // c->data = 'c'; 
    // Node<char>* d = new Node<char>();
    // d->data = 'd'; 
    // Node<char>* e = new Node<char>();
    // e->data = 'e'; 
    // Node<char>* f = new Node<char>();
    // f->data = 'f'; 
    // Node<char>* g = new Node<char>();
    // g->data = 'g'; 
    // Node<char>* h = new Node<char>();
    // h->data = 'h'; 


    // Node<char>* s = new Node<char>();
    // s->data = 's'; 
    // Node<char>* t = new Node<char>();
    // t->data = 't'; 

    // FlowGraph<char> graph; 
    // graph.addNode(s, {{a, 0, 10}, {c,0,10}}, "src");
    // graph.addNode(a, {{b, 0, 4}, {d,0,8}});
    // graph.addNode(b, {{t, 0, 10}});
    // graph.addNode(c, {{d, 0, 9}});
    // graph.addNode(d, {{b, 0, 6}, {t, 0, 10}});
    // graph.addNode(t, {}, "sink");

    // FlowTraversals<char> ft;


    // std::cout << ft.dinicMaximumFlow(graph) << "\n";


    Node<char>* s = new Node<char>();
    s->data = 's'; 
    Node<char>* a = new Node<char>();
    a->data = 'a'; 
    Node<char>* b = new Node<char>();
    b->data = 'b'; 
    Node<char>* c = new Node<char>();
    c->data = 'c'; 
    Node<char>* d = new Node<char>();
    d->data = 'd'; 
    Node<char>* e = new Node<char>();
    e->data = 'e'; 
    Node<char>* f = new Node<char>();
    f->data = 'f'; 
    Node<char>* g = new Node<char>();
    g->data = 'g'; 
    Node<char>* h = new Node<char>();
    h->data = 'h'; 
    Node<char>* t = new Node<char>();
    t->data = 't'; 

    FlowGraph<char> graph; 
    graph.addNode(s, {{a, 0, 10}, {c,0,10}}, "src");
    graph.addNode(a, {{b, 0, 4}, {d,0,8}});
    graph.addNode(b, {{t, 0, 10}});
    graph.addNode(c, {{d, 0, 9}});
    graph.addNode(d, {{b, 0, 6}, {t, 0, 10}});
    graph.addNode(t, {}, "sink");

    graph[h];



}