#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include "Node/Node.hpp" // Graph includes this anyway but this is to be explicit
#include "Graph/Graph.hpp"
#include "WeightedGraph/WeightedGraph.hpp"
#include "FlowGraph/FlowGraph.hpp"
#include "EdgeList/EdgeList.hpp"
#include "WeightedEdgeList/WeightedEdgeList.hpp"
#include "WeightedAdjacencyMatrix/WeightedAdjacencyMatrix.hpp"
#include "Traversals/Traversals.hpp"

#include <iostream>
#include <string>
#include <set>

namespace Graphify{

    // Syntax:
    // [Name of error]_..._NUM
    enum GraphifyError{
        GENERIC_ERROR_NUM,
        UNWEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR_NUM,
        UNKNOWN_UNWEIGHTED_GRAPH_TRAVERSAL_METHOD_ERROR_NUM,
        EXPECTED_DAG_GRAPH_IN_TOP_SORT_ERROR_NUM,
        WEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR_NUM,
        EDGE_LIST_OUT_OF_BOUNDS_ERROR_NUM,
        WEIGHTED_EDGE_LIST_OUT_OF_BOUNDS_ERROR_NUM,
        WEIGHTED_ADJACENCY_MATRIX_OUT_OF_BOUNDS_ERROR_NUM,
        FLOW_GRAPH_OUT_OF_BOUNDS_ERROR_NUM
    };

    template <class T>
    class Graph;


    template <class T>
    class ErrorHandling{
        public:
            ErrorHandling();
            void checkGenericErr(int x);
            void checkOOBUnweightedAdjList(Graph<T> graph, Node<T>* node);
            void checkUnknwonUnweightedTraversal(std::string traversalMethod);
            void checkGraphAsDAG(Graph<T> graph);
            void checkOOBWeightedAdjList(WeightedGraph<T> graph, Node<T>* node);
            void checkOOBEdgeList(EdgeList<T> edgeList, int i);
            void checkOOBWeightedEdgeList(WeightedEdgeList<T> edgeList, int i);
            void checkOOBWeightedAdjacencyMatrix(WeightedAdjacencyMatrix<T> adjMat, int i);
            void checkOOBFlowGraph(FlowGraph<T> graph, Node<T>* node);
            

        private:
            std::string errorDecorator(GraphifyError e);
            const std::string GENERIC_ERROR; 
            const std::string UNWEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR; 
            const std::string UNKNOWN_UNWEIGHTED_GRAPH_TRAVERSAL_METHOD_ERROR;
            const std::string EXPECTED_DAG_GRAPH_IN_TOP_SORT_ERROR;
            const std::string WEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR;
            const std::string EDGE_LIST_OUT_OF_BOUNDS_ERROR;
            const std::string WEIGHTED_EDGE_LIST_OUT_OF_BOUNDS_ERROR;
            const std::string WEIGHTED_ADJACENCY_MATRIX_OUT_OF_BOUNDS_ERROR;
            const std::string FLOW_GRAPH_OUT_OF_BOUNDS_ERROR;
    };

    template <class T>
    ErrorHandling<T>::ErrorHandling()
    :   GENERIC_ERROR("Something went wrong!"),
        UNWEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR("Unweighted graph index out of bounds!"),
        UNKNOWN_UNWEIGHTED_GRAPH_TRAVERSAL_METHOD_ERROR("Unknown unweighted graph traversal method!" 
        " Try running Graphify::Traversals::validTraversalMethods() to find a list of valid methods."),
        EXPECTED_DAG_GRAPH_IN_TOP_SORT_ERROR("Expected a directed acyclic graph as input for top sort method!"),
        WEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR("Weighted graph index out of bounds!"),
        EDGE_LIST_OUT_OF_BOUNDS_ERROR("Edge list index out of bounds!"),
        WEIGHTED_EDGE_LIST_OUT_OF_BOUNDS_ERROR("Weighted edge list index out of bounds!"),
        WEIGHTED_ADJACENCY_MATRIX_OUT_OF_BOUNDS_ERROR("Weighted adjacency matrix index out of bounds!"),
        FLOW_GRAPH_OUT_OF_BOUNDS_ERROR("Flow graph index out of bounds!")
    {}

    template <class T>
    void ErrorHandling<T>::checkOOBUnweightedAdjList(Graph<T> graph, Node<T>* node){
        try{
            if(graph.find(node) == graph.end()){
                GraphifyError e = UNWEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << UNWEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR << "\n";
        }  
    }

    template <class T>
    void ErrorHandling<T>::checkUnknwonUnweightedTraversal(std::string traversalMethod){
        try{
            Traversals<T> traversals;
            std::vector<std::string> validMethods = traversals.validTraversalMethods();

            bool found = false; 
            for(int i = 0; i < validMethods.size(); i++){
                if(traversalMethod == validMethods[i]) found = true; 
            }

            if(!found){
                GraphifyError e = UNKNOWN_UNWEIGHTED_GRAPH_TRAVERSAL_METHOD_ERROR_NUM;
                throw e;
            } 
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << UNKNOWN_UNWEIGHTED_GRAPH_TRAVERSAL_METHOD_ERROR << "\n";
        }
    }

    template <class T>
    void ErrorHandling<T>::checkGraphAsDAG(Graph<T> graph){
        Traversals<T> traversals;
        try{
            if(traversals.isDAG(graph)){ // if the graph isn't an empty set and the graph doesn't contain an independent node..
                GraphifyError e = EXPECTED_DAG_GRAPH_IN_TOP_SORT_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << EXPECTED_DAG_GRAPH_IN_TOP_SORT_ERROR << "\n";
        }
    }

    template <class T>
    void ErrorHandling<T>::checkOOBWeightedAdjList(WeightedGraph<T> graph, Node<T>* node){
        try{
            if(graph.find(node) == graph.end()){
                GraphifyError e = WEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << WEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR << "\n";
        }  
    }

    template <class T>
    void ErrorHandling<T>::checkOOBEdgeList(EdgeList<T> edgeList, int i){
        try{
            if(i > edgeList.size()-1){
                GraphifyError e = EDGE_LIST_OUT_OF_BOUNDS_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << EDGE_LIST_OUT_OF_BOUNDS_ERROR << "\n";
        }  
    }

    template <class T>
    void ErrorHandling<T>::checkOOBWeightedEdgeList(WeightedEdgeList<T> edgeList, int i){
        try{
            if(i > edgeList.size()-1){
                GraphifyError e = WEIGHTED_EDGE_LIST_OUT_OF_BOUNDS_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << WEIGHTED_EDGE_LIST_OUT_OF_BOUNDS_ERROR << "\n";
        }  
    }

    template <class T>
    void ErrorHandling<T>::checkOOBWeightedAdjacencyMatrix(WeightedAdjacencyMatrix<T> adjMat, int i){
        try{
            if(i > adjMat.size()-1){
                GraphifyError e = WEIGHTED_ADJACENCY_MATRIX_OUT_OF_BOUNDS_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << WEIGHTED_ADJACENCY_MATRIX_OUT_OF_BOUNDS_ERROR << "\n";
        }  
    }

    template <class T>
    void ErrorHandling<T>::checkOOBFlowGraph(FlowGraph<T> graph, Node<T>* node){
        try{
            if(graph.find(node) == graph.end()){
                GraphifyError e = FLOW_GRAPH_OUT_OF_BOUNDS_ERROR_NUM;
                throw e;
            }
        } catch(GraphifyError e){
            std::cerr << errorDecorator(e) << FLOW_GRAPH_OUT_OF_BOUNDS_ERROR << "\n";
        }  
    }

    template <class T>
    std::string ErrorHandling<T>::errorDecorator(GraphifyError e){
        return "Graphify error number " + std::to_string(e) + ": ";
    }
}


#endif // ERRORHANDLING_HPP