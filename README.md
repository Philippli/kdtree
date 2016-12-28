Pei Li  
Dec 28, 2016  
pei.li.philip@gmail.com  

# Build  
```make all```

This command will generate following binaries under ```bin/```  
```
[apps]
build_kdtree.out  
query_kdtree.out  

[tests]
point.t.out  
kdtree.t.out  
kdtree_static.t.out  
```

# Run

1. buid_kdtree  
``` ./bin/build_kdtree.out data/sample_data.csv sample_data_kdtree.sav ```  
This command will build a kdtree and save it into file *sample_data_kdtree.sav*

2. query_kdtree  
``` ./bin/query_kdtree.out data/sample_data.csv sample_data_kdtree.sav data/query_data.csv query_output ```  
This command will load *sample_data_kdtree.sav* into memory and query test points. Output will be saved in *query_output*

3. tests  
``` ./run_tests ```  
This command will run 3 test binaries generated in **Build**

# Dev/Test Environment
```sh
$ g++ --version
g++ (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4

$ cat  /etc/os-release
NAME="Ubuntu"
VERSION="14.04.3 LTS, Trusty Tahr"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 14.04.3 LTS"
VERSION_ID="14.04"
```

# References
Wikipedia K-d Tree  https://en.wikipedia.org/wiki/K-d_tree  
Standord cs106  https://web.stanford.edu/class/cs106l/handouts/assignment-3-kdtree.pdf  
Build a balanced K-d Tree   http://jcgt.org/published/0004/01/03/paper.pdf  
