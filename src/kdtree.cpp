#include "kdtree.h"

template<size_t N, typename T>
Point<N, T>::Point(vector<T>& p): m_point(p)
{ }

template<size_t N, typename T>
KDTreeNode<N, T>::KDTreeNode(Point<N, T>& p) {
    delete m_left;
    delete m_right;
}

template<size_t N, typename T>
KDTreeNode<N, T>::~KDTreeNode() {
    delete m_left;
    delete m_right;
}
