#ifndef INCLUDE_KDTREE_H
#define INCLUDE_KDTREE_H

#include <vector>

using namespace std;

template<size_t N, typename T>
class Point{
    private:
        vector<T> m_point;
    public:
        Point(vector<T>& p);
        virtual ~Point();
};

template<size_t N, typename T>
class KDTreeNode {
    private:
        Point<N, T> m_point;
        KDTreeNode* m_left;
        KDTreeNode* m_right;
    public:
        KDTreeNode(Point<N, T>& p);
        virtual ~KDTreeNode();

};

#endif
