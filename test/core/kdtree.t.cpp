#include "kdtree.h"
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <fstream>

/*
 * test abstract class through derived phony class
 */
using namespace kdtree;

template <typename T>
class PhonyKDTree : public KDTree<T> {
    public:
        PhonyKDTree(KDTreeNode<T>* root) : KDTree<T>(root) { }
        
        PhonyKDTree(const std::string& filename) : KDTree<T>(filename) { }

        // PHONY
        virtual KDTreeNode<T>* nearest(const T& testPoint) const {
            return NULL;
        }
};

void TEST_loadTree() {

    // construct a tree in memory
    typedef Point<3, double> MyPoint;
    static MyPoint tmp;

    tmp.m_data[0] = 1.1;
    tmp.m_data[1] = 1.2;
    tmp.m_data[2] = 1.3;
    KDTreeNode<MyPoint>* p1 = new KDTreeNode<MyPoint>(tmp);

    tmp.m_data[0] = 2.1;
    tmp.m_data[1] = 2.2;
    tmp.m_data[2] = 2.3;
    KDTreeNode<MyPoint>* p2 = new KDTreeNode<MyPoint>(tmp);

    tmp.m_data[0] = 3.1;
    tmp.m_data[1] = 3.2;
    tmp.m_data[2] = 3.3;
    KDTreeNode<MyPoint>* p3 = new KDTreeNode<MyPoint>(tmp);

    p1->m_left = p2;
    p1->m_right = p3;

    // load an identical tree from file
    const std::string loadFilename("data/tree.test0.sav");
    PhonyKDTree<MyPoint> phonyTree(loadFilename);

    // diff
    assert(equalTree(p1, phonyTree.root()));

    delete p1;
    delete p2;
    delete p3;
}

void TEST_saveTree() {

    // construct a tree in memory
    typedef Point<3, double> MyPoint;
    static MyPoint tmp;

    tmp.m_data[0] = 1.1;
    tmp.m_data[1] = 1.2;
    tmp.m_data[2] = 1.3;
    KDTreeNode<MyPoint>* p1 = new KDTreeNode<MyPoint>(tmp);

    tmp.m_data[0] = 2.1;
    tmp.m_data[1] = 2.2;
    tmp.m_data[2] = 2.3;
    KDTreeNode<MyPoint>* p2 = new KDTreeNode<MyPoint>(tmp);

    tmp.m_data[0] = 3.1;
    tmp.m_data[1] = 3.2;
    tmp.m_data[2] = 3.3;
    KDTreeNode<MyPoint>* p3 = new KDTreeNode<MyPoint>(tmp);

    p1->m_left = p2;
    p1->m_right = p3;

    PhonyKDTree<MyPoint> phonyTree(p1);

    // save constructed tree
    const std::string savFilename("data/tree.test0.0.sav");
    phonyTree.saveTree(savFilename);

    // diff savFile and test file
    const std::string loadFilename("data/tree.test0.sav");
    std::ifstream loadIfs(loadFilename);
    std::stringstream loadSs;
    loadSs << loadIfs.rdbuf();
    const std::string str1 = loadSs.str();
    
    std::ifstream savIfs(savFilename);
    std::stringstream savSs;
    savSs << savIfs.rdbuf();
    const std::string str2 = savSs.str();

    assert (str1 == str2);
}

int main() {

    std::cout << "===== Running tests of KDTree  =====" << std::endl;

    TEST_loadTree();
    TEST_saveTree();

    std::cout << "===== Completed tests of KDTree  =====" << std::endl;

    return 0;
}
