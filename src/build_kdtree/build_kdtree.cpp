#include "kdtree.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace kdtree;

int main () {
    typedef Point<3, double> MyPoint;

    double a[] = { 1, 2, 3, 4, 5, 6};
    vector<double> vct1(a, a + 3);
    vector<double> vct2(a + 1, a + 4);
    vector<double> vct3(a + 2, a + 5);

    MyPoint* p1 = MyPoint::createPoint(vct1);
    MyPoint* p2 = MyPoint::createPoint(vct2);
    MyPoint* p3 = MyPoint::createPoint(vct3);

    KDTree<MyPoint> mytree;
    mytree.insert(*p1);
    mytree.insert(*p2);
    mytree.insert(*p3);

    mytree.print();

    KDTree<MyPoint> mytree2(buildTree<MyPoint>("data/test"));
    mytree2.print();
    

    delete p1;
    delete p2;
    delete p3;

    return 0;
}
