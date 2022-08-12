#ifndef NODEVISITOR_HPP
#define NODEVISITOR_HPP

#include "Node/Node.hpp"
#include "ErrorHandling/ErrorHandling.hpp"
#include <stack>
#include <queue>

#include <vector>
#include <string>
#include <stack>
#include <queue>

namespace Graphify{

    template <class T>
    class ErrorHandling;

    template <class T>
    class NodeVisitor{
        public:
            NodeVisitor(std::string traversalMethod);
            
            bool empty();

            void push(Node<T>* node);
            Node<T>* pop(); // Fixing the pop methods of std::stack and std::queue..

            bool operator== (const NodeVisitor<T>& visitor) const;

            int len();
            int len() const;

        private:
            int size;

            std::string traversalMethod;

            std::stack<Node<T>*> visitorDFS; 
            std::queue<Node<T>*> visitorBFS;
    };

    template <class T>
    NodeVisitor<T>::NodeVisitor(std::string traversalMethod) 
    : size(0)
    { 
        ErrorHandling<T> handler;
        handler.checkUnknwonUnweightedTraversal(traversalMethod);
        this->traversalMethod = traversalMethod;
    }

    template <class T>
    bool NodeVisitor<T>::empty(){
        if(traversalMethod == "BFS"){
            return visitorBFS.empty();
        } 
        else if(traversalMethod == "DFS"){
            return visitorDFS.empty();
        }
        else{ // GIVE ERROR HERE. 
            ErrorHandling<T> handler;
            handler.checkUnknwonUnweightedTraversal(traversalMethod);

            return true; // default 
        }   
    }

    template <class T>
    void NodeVisitor<T>::push(Node<T>* node){
        if(traversalMethod == "BFS"){
            size++;
            visitorBFS.push(node);
        } 
        else if(traversalMethod == "DFS"){
            size++;
            visitorDFS.push(node);
        }
        else{ // GIVE ERROR HERE. 
            ErrorHandling<T> handler;
            handler.checkUnknwonUnweightedTraversal(traversalMethod);
        }

    }

    template <class T>
    Node<T>* NodeVisitor<T>::pop(){
        if(traversalMethod == "BFS"){
            auto lastNode = visitorBFS.front();
            visitorBFS.pop();
            size--;
            return lastNode;
        } 
        else if(traversalMethod == "DFS"){
            auto lastNode = visitorDFS.top();
            visitorDFS.pop();
            size--;
            return lastNode;
        }
        else{ // GIVE ERROR HERE. 
            ErrorHandling<T> handler;
            handler.checkUnknwonUnweightedTraversal(traversalMethod);

            return nullptr; // default
        }
    }

    template <class T>
    int NodeVisitor<T>::len() const {
        return size;
    }

    template <class T>
    int NodeVisitor<T>::len() {
        return size;
    }

    template <class T>
    bool NodeVisitor<T>::operator== (const NodeVisitor<T>& visitor) const {
        if(this->len() != visitor.len()) return false; 
        auto tempVisitor1 = *this;
        auto tempVisitor2 = visitor; 

        while(!tempVisitor1.empty() && !tempVisitor2.empty()){
            auto node1 = tempVisitor1.pop();
            auto node2 = tempVisitor2.pop();

            if(node1 != node2) return false; 
        }

        return true; 

        // check sizes here too
    }
}

#endif // NODEVISITOR_HPP