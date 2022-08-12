#ifndef NODE_HPP
#define NODE_HPP

namespace Graphify{

    template <class T>
    class Node{
        public:
            Node(T data);
            Node();
            T data; 
            bool operator< (const Node& node) const;
        private:

    };

    template <class T>
     Node<T>::Node(T data)
     : data(data)
     { }

    template <class T>
     Node<T>::Node()
     { }

    template <class T>
    bool Node<T>::operator< (const Node<T>& node) const {
        if(node->data < this->data)
            return true;
    }
}

#endif // NODE_HPP