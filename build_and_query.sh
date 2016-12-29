#!/bin/bash

./bin/build_kdtree.out data/sample_data.csv sample_data_kdtree.sav
./bin/query_kdtree.out data/sample_data.csv sample_data_kdtree.sav data/query_data.csv query_output
