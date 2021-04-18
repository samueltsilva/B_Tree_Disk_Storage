# B_Tree_Disk_Storage

A C ++ program that stores a complex set of ADT objects (abstract data type) in a B tree, with the storage of each page of the tree in a register file. The implementation keeps as few pages as possible in memory. Each page in the tree will be stored in a single file record. The complex ADT is an object that represents a complex number in the form a + bi, where a and b are real numbers that represent the real and the imaginary parts, respectively. There is a class that represents this type of data, as well as basic operations (addition, subtraction, multiplication, division, relational comparisons and the << operator for writing to standard output). The writing on the screen will always be in the form a + bi, omitting the part that is null, when it occurs. The values ​​will always be read in pairs (real and imaginary part), whenever data entry in the program occurs.
The program presents the following options to the user:
• insert a value in the tree;
• remove a value from the tree;
• print the page of the tree where a key is;
• search for a value in a tree;