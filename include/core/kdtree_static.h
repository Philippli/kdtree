#ifndef INCLUDE_KDTREE_STATIC_H
#define INCLUDE_KDTREE_STATIC_H

#include "kdtree.h"

namespace kdtree {

/*
 * class StaticKDTree
 *
 * This is a type of KDTree that
 * does not expect modification after construction
 */
template<typename T>
class StaticKDTree : public KDTree<T> {
    public:
        StaticKDTree(KDTreeNode<T>* root) : KDTree<T>(root) { }

        StaticKDTree(const string& filename) : KDTree<T>(filename) { }

        /*
         * construct an instance from a vector of KDTreeNode
         */
        StaticKDTree(vector<KDTreeNode<T>*>& nodes) {
            this->m_root = NULL;
            buildTree(this->m_root, nodes, 0, nodes.size() - 1, 0);
        }

        /*
         * return nearest KDTreeNode from input point
         */
        virtual KDTreeNode<T>* nearest(const T& point) const {
            if (this->m_root == NULL) {
                return this->m_root;
            }

            KDTreeNode<T>* nearestNode = this->m_root;
            nearest(point, this->m_root->m_left, nearestNode, 1 % point.dimension());
            nearest(point, this->m_root->m_right, nearestNode, 1 % point.dimension());
            return nearestNode;
        }

    private:
        /*
         * recursively build tree
         */
        void buildTree(KDTreeNode<T>*& root, vector<KDTreeNode<T>*>& nodes,
                const int left, const int right, const int depth
                ) {
            if (right < left
                || left < 0
                || right < 0
                || left >= nodes.size()
                || right >= nodes.size()
                ) {
                return;
            }

            const int mid = selectMedian( nodes, left ,right,
                                depth % nodes[left]->m_point.dimension());
            root = nodes[mid];
            buildTree(root->m_left, nodes, left, mid - 1, depth + 1);
            buildTree(root->m_right, nodes, mid + 1, right, depth + 1);
        }

        /*
         * this function sorts nodes range based on dimension,
         * and return median position of nodes after sort
         */
        int selectMedian(vector<KDTreeNode<T>* >& nodes, const int left,
                            const int right, const int idx
                            ) {
            if (left + 1 >= right) {
                return left;
            }
            quickSort(nodes, left, right, idx);
            return left + (right - left) / 2;
        }

        /*
         * sort nodes based on dimension
         */
        void quickSort(vector<KDTreeNode<T>*>& nodes, const int left, const int right,
                        const int idx) {
            if (left >= right) {
                return;
            }
            const int p = partition(nodes, left, right, idx);
            quickSort(nodes, left, p - 1, idx);
            quickSort(nodes, p + 1, right, idx);
        }

        int partition(vector<KDTreeNode<T>*>& nodes, const int left, const int right,
                        const int idx) {
            const int mid = left + (right - left) / 2;
            swap(nodes[mid], nodes[right]);
            int i, j;
            for (i = j = left; i < right; ++i) {
                if (nodes[i]->m_point.m_data[idx] < nodes[right]->m_point.m_data[idx])
                {
                    if (i != j) {
                        swap(nodes[j], nodes[i]);
                    }
                    ++j;
                }
            }
            swap(nodes[j], nodes[right]);
            return j;
        }

        void nearest(const T& point, KDTreeNode<T>* node,
                    KDTreeNode<T>*& nearestNode, const size_t idx
                    ) const {
            if (node == NULL) {
                return;
            }

            if (point.dist(node->m_point) < point.dist(nearestNode->m_point)) {
                nearestNode = node;
            }

            const bool searchLeft =
                        point.m_data[idx] < node->m_point.m_data[idx];
            if (searchLeft) {
                nearest(point, node->m_left, nearestNode,
                        (idx + 1) % point.dimension());
            } else {
                nearest(point, node->m_right, nearestNode,
                        (idx + 1) % point.dimension());
            }

            if ((node->m_point.m_data[idx] - point.m_data[idx])
                * (node->m_point.m_data[idx] - point.m_data[idx])
                 < point.dist(nearestNode->m_point)
                 ) {
                // search other side
                if (searchLeft) {
                    nearest(point, node->m_right, nearestNode,
                            (idx + 1) % point.dimension());
                } else {
                    nearest(point, node->m_left, nearestNode,
                            (idx + 1) % point.dimension());
                }
            }

        }
};

} // close namespace kdtree

#endif
