#include "kdtree.h"

#include <iostream>

using namespace std;

int main () {
    typedef Point<3, double> MyPoint;
    vector<double> vct;
    MyPoint* p = MyPoint::createPoint(vct);
    //Point<3, double>* p = Point<3, double>::createPoint(vct);

    KDTree<MyPoint> mytree;
    mytree.insert(p);

    cout << mytree.empty() << endl;

    return 0;
}
