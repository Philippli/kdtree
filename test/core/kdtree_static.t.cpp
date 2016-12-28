#include "kdtree_static.h"
#include <assert.h>
#include <limits>
#include <cmath>

using namespace std;
using namespace kdtree;

typedef Point<3, double> MyPoint;

void TEST_buildtree_from_nodeVector() {
    // load test tree into a new instance
    const string savTreeFile("data/tree.test1.sav");
    const StaticKDTree<MyPoint> kdtree1(savTreeFile);

    // Build a vector of identical nodes as test tree
    vector<KDTreeNode<MyPoint>*> nodeVct;
    static MyPoint tmp;

    tmp.m_data[0] = 4.4;
    tmp.m_data[1] = 4.4;
    tmp.m_data[2] = 4.4;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 2.2;
    tmp.m_data[1] = 2.2;
    tmp.m_data[2] = 2.2;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 1.1;
    tmp.m_data[1] = 1.1;
    tmp.m_data[2] = 1.1;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 3.3;
    tmp.m_data[1] = 3.3;
    tmp.m_data[2] = 3.3;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));


    tmp.m_data[0] = 6.6;
    tmp.m_data[1] = 6.6;
    tmp.m_data[2] = 6.6;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 5.5;
    tmp.m_data[1] = 5.5;
    tmp.m_data[2] = 5.5;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 7.7;
    tmp.m_data[1] = 7.7;
    tmp.m_data[2] = 7.7;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    StaticKDTree<MyPoint> kdtree2(nodeVct);


    // diff 2 kdtree
    assert(equalTree(kdtree1.root(), kdtree2.root()));

}

void TEST_nearest() {

    // Build a vector of identical nodes as test tree
    vector<KDTreeNode<MyPoint>*> nodeVct;
    static MyPoint tmp;

    tmp.m_data[0] = 4.4;
    tmp.m_data[1] = 4.4;
    tmp.m_data[2] = 4.4;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 2.2;
    tmp.m_data[1] = 2.2;
    tmp.m_data[2] = 2.2;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 1.1;
    tmp.m_data[1] = 1.1;
    tmp.m_data[2] = 1.1;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 3.3;
    tmp.m_data[1] = 3.3;
    tmp.m_data[2] = 3.3;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));


    tmp.m_data[0] = 6.6;
    tmp.m_data[1] = 6.6;
    tmp.m_data[2] = 6.6;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 5.5;
    tmp.m_data[1] = 5.5;
    tmp.m_data[2] = 5.5;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    tmp.m_data[0] = 7.7;
    tmp.m_data[1] = 7.7;
    tmp.m_data[2] = 7.7;
    nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));

    StaticKDTree<MyPoint> kdtree(nodeVct);

    // Test point 1 equals to an internal point
    MyPoint p1;
    p1.m_data[0] = 7.7;
    p1.m_data[1] = 7.7;
    p1.m_data[2] = 7.7;
    assert( fabs(p1.dist(kdtree.nearest(p1)->m_point) - 0)
            < numeric_limits<float>::epsilon()
            );

    // Test point 2 dist is 3
    MyPoint p2;
    p2.m_data[0] = 0.1;
    p2.m_data[1] = 0.1;
    p2.m_data[2] = 0.1;
    assert( fabs(p2.dist(kdtree.nearest(p2)->m_point) - 3)
            < numeric_limits<float>::epsilon()
            );

    // Test point 3 dist is 2.27
    MyPoint p3;
    p3.m_data[0] = 4.0;
    p3.m_data[1] = 3.0;
    p3.m_data[2] = 2.0;
    assert( fabs(p3.dist(kdtree.nearest(p3)->m_point) - 2.27)
            < numeric_limits<float>::epsilon()
            );
}

int main() {

    std::cout << "===== Running tests of StaticKDTree  =====" << std::endl;

    TEST_buildtree_from_nodeVector();
    TEST_nearest();

    std::cout << "===== Completed tests of StaticKDTree  =====" << std::endl;

    return 0;
}
