#ifndef INCLUDE_KDTREE_H
#define INCLUDE_KDTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

namespace kdtree {

template<size_t N, typename T>
struct Point{
        vector<T>   m_data;

        Point(const Point<N, T>& p) : m_data(p.m_data) { }

        Point(const string& line) {
            // TODO
            // bad line
            istringstream ss(line);
            m_data.resize(N);
            for (size_t i = 0; i < N; ++i) {
                ss >> m_data[i];
            }
        }

        static Point<N, T>* createPoint(const vector<T>& data) {
            if (data.size() != N) {
                return NULL;
            } else {
                return new Point<N, T>(data);
            }
        }

        size_t dimension() const { return N; }

        bool equals(const Point<N, T>& point) const {
            // TODO
            return false;
        }

    private:
        Point(const vector<T>& data) : m_data(data) { }

};

template<typename T>
struct KDTreeNode {
        T    m_point;
        KDTreeNode<T>*     m_left;
        KDTreeNode<T>*     m_right;
        KDTreeNode(const T& point): m_point(point), m_left(NULL), m_right(NULL)
        { }
};

template<typename T>
struct KDTree {
        KDTreeNode<T>*   m_root;
    public:
        KDTree() : m_root(NULL) { }
        KDTree(KDTreeNode<T>* root) : m_root(root) { }
        virtual ~KDTree() { destroy(m_root); }

        void insert(const T& point) {
            // TODO
            // Need strategy
            //
            // cycle
            insert(point, &m_root, 0);
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

        void print() const {
            print(m_root);
        }

        void print(const KDTreeNode<T>* root) const {
            if (root != NULL) {
                for (auto e: root->m_point.m_data) {
                    cout << e << ", ";
                }
                cout << endl;
                print(root->m_left);
                print(root->m_right);
            }
        }

    private:
        void destroy(KDTreeNode<T>* root) {
            if (root != NULL) {
                destroy(root->m_left);
                destroy(root->m_right);
                delete root;
            }
        }

        void insert(const T& point, KDTreeNode<T>** root, const size_t depth) {
            if (*root == NULL) {
                *root = new KDTreeNode<T>(point);
                return;
            }

            const size_t idx = depth % point.dimension();
            if (point.equals((*root)->m_point)) {
                // skip identical point insertion
            } else if (point.m_data[idx] <= (*root)->m_point.m_data[idx]) {
                insert(point, &(*root)->m_left, 1 + depth);
            } else {
                insert(point, &(*root)->m_right, 1 + depth);
            }
        }
};

template <typename T>
KDTreeNode<T>* buildTree(const string& filename) {
    KDTreeNode<T>* root;
    ifstream infile(filename);
    buildTree<T>(&root, infile);
    return root;
}

template <typename T>
void buildTree(KDTreeNode<T>** root, ifstream& infile) {
    string line;
    if (getline(infile, line)) {
        if (line.empty()) {
            *root = NULL;
            return;
        } else {
            *root = new KDTreeNode<T>(T(line));
            buildTree(&((*root)->m_left), infile);
            buildTree(&((*root)->m_right), infile);
        }
    }
}

} // close namespace kdtree
#endif
