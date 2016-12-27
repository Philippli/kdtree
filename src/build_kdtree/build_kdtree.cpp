#include "kdtree_static.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace kdtree;

int main (int argc, char** argv) {

    // build tree from csv file
    if (argc < 3) {
        cout << "please provide <points_csv_file> <tree_save_file>\n"
             << endl;
        return 1;
    }

    // TODO remove hard code
    const size_t N = 3;
    typedef Point<N, double> MyPoint;

    // read file and create KDTreeNode line by line
    vector<KDTreeNode<MyPoint>* > nodeVct;
    ifstream infile(argv[1]);
    string line;
    while (getline(infile, line)) {
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
        nodeVct.emplace_back(new KDTreeNode<MyPoint>(tmp));
    }


    // create a StaticKDTree instance
    StaticKDTree<MyPoint> myTree(nodeVct);

    // save tree to file
    myTree.saveTree(argv[2]);
    return 0;
}
