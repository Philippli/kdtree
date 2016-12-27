#ifndef INCLUDE_KDTREE_H
#define INCLUDE_KDTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

namespace kdtree {

/*
 * class Point
 *
 * N: dimension
 * T: value type
 */
template<size_t N, typename T>
struct Point{
        vector<T>   m_data;

        Point() { m_data.resize(N); }

        Point(const vector<T>& data) : m_data(data) { }

        Point(const Point<N, T>& p) : m_data(p.m_data) { }

        /*
         * construct a point from a string of space seperated values.
         */
        Point(const string& line) {
            // TODO handle bad line
            m_data.resize(N);
            istringstream ss(line);
            for (size_t i = 0; i < N; ++i) {
                ss >> m_data[i];
            }
        }

        /*
         * create a string with each value sperated by space.
         */
        string toString() const {
            stringstream ss;
            for (size_t i = 0; i < N; ++i) {
                ss << m_data[i] << " ";
            }
            return ss.str();
        }

        size_t dimension() const { return N; }

        bool equals(const Point<N, T>& point) const {
            for (size_t i = 0; i < N; ++i) {
                if (this->m_data[i] != point.m_data[i]) {
                    return false;
                }
            }
            return true;
        }

        T dist(const Point<N, T>& point) const {
            // TODO support other types
            T res = 0;
            for (size_t i = 0; i < N; ++i) {
                res += (this->m_data[i] - point.m_data[i])
                        * (this->m_data[i] - point.m_data[i]);
            }
            return res;
        }

};

/*
 * class KDTreeNode
 *
 * T: point type
 */
template<typename T>
struct KDTreeNode {
        T    m_point;
        KDTreeNode<T>*     m_left;
        KDTreeNode<T>*     m_right;
        KDTreeNode(const T& point): m_point(point), m_left(NULL), m_right(NULL)
        { }
};

/*
 * class KDTree
 *
 * T: point type
 *
 *
 * This is an abstract class. It impletes basic constructors of a KDTree,
 * save & load functions.
 *
 * All its derived classes are required to explicitly implement function
 *      virtual KDTreeNode<T>* nearest(const T& point);
 */
template<typename T>
struct KDTree {
    protected:
        KDTreeNode<T>*   m_root;

    public:
        KDTree() : m_root(NULL) { }

        KDTree(KDTreeNode<T>* root) : m_root(root) { }

        /*
         * create an instance from saved tree.
         */
        KDTree(const string& filename) {
            m_root = loadTree(filename);
        }

        virtual ~KDTree() { destroy(m_root); }

    public:

        /*
         * return nearest node from test point.
         */
        virtual KDTreeNode<T>* nearest(const T& point) const = 0;

    public:
        bool empty() const {
            return NULL == m_root;
        }

        const KDTreeNode<T>* root() const {
            return m_root;
        }

    public:
        /*
         * save this KDTree into a file
         * each line stores a single node's point's values, seperated by space
         * a null node is an empty ine
         * nodes are stored as in-order
         */
        void saveTree(const string& filename) {
            ofstream ofile(filename);
            saveTree(m_root, ofile);
        }

    private:
        void saveTree(KDTreeNode<T>* node, ofstream& ofile) {
            if (node == NULL) {
                ofile << "\n";
            } else {
                ofile << node->m_point.toString() << "\n";
                saveTree(node->m_left, ofile);
                saveTree(node->m_right, ofile);
            }
        }

        /*
         * load a KDTree from file
         * each line stores a single node's point's values, seperated by space
         * a null node is an empty ine
         * nodes are stored as in-order
         */
        KDTreeNode<T>* loadTree(const string& filename) {
            KDTreeNode<T>* root = NULL;
            ifstream infile(filename);
            loadTree(root, infile);
            return root;
        }

        void loadTree(KDTreeNode<T>*& node, ifstream& infile) {
            string line;
            if (getline(infile, line)) {
                if (line.empty()) {
                    node = NULL;
                    return;
                } else {
                    node = new KDTreeNode<T>(T(line));
                    loadTree(node->m_left, infile);
                    loadTree(node->m_right, infile);
                }
            }
        }

        void destroy(KDTreeNode<T>* node) {
            if (node != NULL) {
                destroy(node->m_left);
                destroy(node->m_right);
                delete node;
            }
        }
};

template <typename T>
void printTree(const KDTreeNode<T>* root) {
    if (root != NULL) {
        for (auto e: root->m_point.m_data) {
            cout << e << ", ";
        }
        cout << endl;
        print(root->m_left);
        print(root->m_right);
    }
}

template <typename T>
bool equalTree(const KDTreeNode<T>* root1, const KDTreeNode<T>* root2) {
    if (root1 == NULL || root2 == NULL) {
        return root1 == root2;
    }

    return root1->m_point.equals(root2->m_point)
            && equalTree(root1->m_left, root2->m_left)
            && equalTree(root1->m_right, root2->m_right)
            ;
}

} // close namespace kdtree
#endif
