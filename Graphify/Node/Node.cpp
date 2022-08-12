#include "Node.hpp"

namespace Graphify {
    template <class T>
     Node<T>::Node(T data)
     : data(data)
     { }

    template <class T>
     Node<T>::Node()
     { }
}