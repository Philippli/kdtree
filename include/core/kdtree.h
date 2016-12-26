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

        Point(const string& line) {
            // TODO handle bad line
            istringstream ss(line);
            m_data.resize(N);
            for (size_t i = 0; i < N; ++i) {
                ss >> m_data[i];
            }
        }

        string toString() const {
            stringstream ss;
            for (size_t i = 0; i < N; ++i) {
                ss << m_data[i] << " ";
            }
            return ss.str();
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
 */
template<typename T>
struct KDTree {
    protected:
        KDTreeNode<T>*   m_root;

    public:
        KDTree() : m_root(NULL) { }

        KDTree(KDTreeNode<T>* root) : m_root(root) { }

        KDTree(const string& filename) {
            m_root = loadTree(filename);
        }

        virtual ~KDTree() { destroy(m_root); }

    public:
        virtual KDTreeNode<T>* nearest(const T& point) = 0;

    public:
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


} // close namespace kdtree
#endif
