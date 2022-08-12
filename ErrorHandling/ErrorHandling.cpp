#include "ErrorHandling.hpp"

namespace Graphify{
    template <class T>
    ErrorHandling<T>::ErrorHandling()
    : UNWEIGHTED_GRAPH_OUT_OF_BOUNDS_ERROR("Unweighted graph index out of bounds!"),
        GENERIC_ERROR("Something went wrong!")
    {}

    template <class T>
    void ErrorHandling<T>::checkOOBWeightedAdjList(Node<T> node, Graph<T> graph){
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
    std::string ErrorHandling<T>::errorDecorator(GraphifyError e){
        return "Graphify error number " + std::to_string(e) + ": ";
    }
}