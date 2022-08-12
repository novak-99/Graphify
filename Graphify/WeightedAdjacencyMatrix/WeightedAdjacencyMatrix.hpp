#ifndef WEIGHTEDADJACENCYMATRIX_HPP
#define WEIGHTEDADJACENCYMATRIX_HPP

#include "WeightedAdjacencyMatrix/WeightedAdjacencyMatrix.hpp"

#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

namespace Graphify{


    template <class T>
    class WeightedEdgeList;

    template <class T>
    class ErrorHandling;

    // Min Component Size 
    // Max Component Size
    // Total Number of Components 
    // Min Dist Given Start: A, End: B

    template <class T>
    class WeightedAdjacencyMatrix{
        public:
            WeightedAdjacencyMatrix(int V);
            typename std::vector<int>& operator[](int i);
            int size();

            void print();


        private:
            std::vector<std::vector<int>> WeightedAdjMat;
            int V; 


    };

    template <class T>
    WeightedAdjacencyMatrix<T>::WeightedAdjacencyMatrix(int V)
    : V(V)
    {
        for(int i = 0; i < V; i++){
            WeightedAdjMat.resize(V);
            for(int j = 0; j < V; j++){
                WeightedAdjMat[i].resize(V);
            }
        }
    }

    template <class T>
    typename std::vector<int>& WeightedAdjacencyMatrix<T>::operator[](int i){
        ErrorHandling<T> handler;
        handler.checkOOBWeightedAdjacencyMatrix(*this, i); // Pass current VALUE of instance of class to err handler..
        return WeightedAdjMat[i];

    }

    template <class T>
    int WeightedAdjacencyMatrix<T>::size(){
        return V;
    }

    template <class T>
    void WeightedAdjacencyMatrix<T>::print(){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                std::cout << WeightedAdjMat[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
}

#endif // WEIGHTEDADJACENCYMATRIX_HPP