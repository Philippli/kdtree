#include "kdtree.h"
#include <assert.h>

/*
 * Test struct Point
 */
using namespace kdtree;

void TEST_constructor_0 () {
    Point<3, double> testPoint;

    assert(testPoint.m_data.size() == 3);
    assert(testPoint.m_data.size() != 0);
}

void TEST_constructor_1 () {
    const string str = "1 2 3";
    Point<3, double> testPoint(str);

    assert(testPoint.m_data.size() == 3);
    assert(testPoint.m_data[0] == 1);
    assert(testPoint.m_data[1] == 2);
    assert(testPoint.m_data[2] == 3);
}

void TEST_toString () {
    Point<3, double> testPoint;
    testPoint.m_data[0] = 1;
    testPoint.m_data[1] = 2;
    testPoint.m_data[2] = 3;

    assert(testPoint.toString() == "1 2 3 ");
}

void TEST_dist() {
    Point<3, double> testPoint1;
    testPoint1.m_data[0] = 1;
    testPoint1.m_data[1] = 2;
    testPoint1.m_data[2] = 3;

    Point<3, double> testPoint2;
    testPoint2.m_data[0] = 2;
    testPoint2.m_data[1] = 4;
    testPoint2.m_data[2] = 7;

    assert(testPoint1.dist(testPoint2) == 21);
    assert(testPoint1.dist(testPoint2) == testPoint2.dist(testPoint1));
}


int main() {

    std::cout << "===== Running tests of Point =====" << std::endl;

    TEST_constructor_0 ();
    TEST_constructor_1 ();
    TEST_toString ();
    TEST_dist ();

    std::cout << "===== Completed tests of Point =====" << std::endl;

    return 0;
}
