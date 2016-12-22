#ifndef INCLUDE_KDTREE_H
#define INCLUDE_KDTREE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<size_t N, typename T>
struct Point{
        vector<T>   m_data;
    private:
        Point(const vector<T>& data) : m_data(data) { }

    public:
        virtual ~Point() { }

        size_t dimension() const {
            return N;
        }

        bool equals(const Point<N, T>& point) const {
            // TODO
            return false;
        }

    public:
        static Point<N, T>* createPoint(const vector<T>& data) {
            if (data.size() != N) {
                return NULL;
            } else {
                return new Point<N, T>(data);
            }
        }
};

template<typename T>
struct KDTreeNode {
        T*    m_point;
        KDTreeNode<T>*     m_left;
        KDTreeNode<T>*     m_right;
    public:
        KDTreeNode(T* point): m_point(point), m_left(NULL), m_right(NULL) { }
        virtual ~KDTreeNode() {
            delete m_left;
            delete m_right;
            delete m_point;
        }

};

template<typename T>
class KDTree {
        KDTreeNode<T>*   m_root;
    public:
        KDTree() : m_root(NULL) { }
        virtual ~KDTree() { delete m_root; }
    public:
        void insert(T* point) {
            // TODO
            // Need strategy
            //
            // cycle
            if (point) {
                insert(point, &m_root, 0);
            }
        }

        T query(const T& point) const {
            // TODO
            return point;
        }

        bool load(const string& file) {
            // TODO
            return false;
        }

        bool empty() const {
            return NULL == m_root;
        }

    private:
        void insert(T* point, KDTreeNode<T>** root, const size_t depth) {
            if (*root == NULL) {
                *root = new KDTreeNode<T>(point);
                return;
            }

            const size_t idx = depth % point->dimension();
            if (point->equals(*(*root)->m_point)) {
                // skip identical point insertion
            } else if (point->m_data[idx] <= (*root)->m_point->m_data[idx]) {
                insert(point, &(*root)->m_left, 1 + depth);
            } else {
                insert(point, &(*root)->m_right, 1 + depth);
            }
        }
};

#endif
