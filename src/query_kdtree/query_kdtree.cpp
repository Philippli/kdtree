#include "kdtree_static.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
using namespace kdtree;

int main (int argc, char** argv) {

    // build tree from csv file
    if (argc < 5) {
        cout << "please provide <origin_points_csv_file> <tree_save_file> "
             << "<test_points> <outputfile>"
             << endl;
        return 1;
    }

    // TODO remove hard code
    const size_t N = 3;
    typedef Point<N, double> MyPoint;

    // read original points file and create point-index map
    unordered_map<string, int> pointIdxMap;  
    ifstream originPointFile(argv[1]);
    string line;
    int pointIdx = 0;
    while (getline(originPointFile, line)) {
        static MyPoint tmp;
        istringstream ss(line);
        string numstr;
        for (size_t i = 0; i < N; ++i) {
            if(!getline(ss, numstr, ',')) {
                // skip corrupted line
                break;
            }
            stringstream numss(numstr);
            numss >> tmp.m_data[i]; 
        }
        pointIdxMap[tmp.toString()] = pointIdx++;
    }

    // load a StaticKDTree
    StaticKDTree<MyPoint> myTree(argv[2]);

    // query test points
    ifstream testPointFile(argv[3]);
    ofstream outfile(argv[4]);
    while (getline(testPointFile, line)) {
        static MyPoint tmp;
        istringstream ss(line);
        string numstr;
        for (size_t i = 0; i < N; ++i) {
            if(!getline(ss, numstr, ',')) {
                // skip corrupted line
                break;
            }
            stringstream numss(numstr);
            numss >> tmp.m_data[i]; 
        }
        KDTreeNode<MyPoint>* res = myTree.nearest(tmp);
        outfile << pointIdxMap[res->m_point.toString()]
                << ", "
                << res->m_point.dist(tmp)
                << endl;
    }

    return 0;
}
