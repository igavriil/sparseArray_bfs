sparseArray_bfs
===============

bfs c implementation with graph representation as sparse array

Graph representation: 
A graph can be represented as a two-dimensional sparse array. Rows and columns represent a vertice in the graph and 
each entry repsent a neighboor to the indicated vertice, forming thus corresponding edge. In this way a bidirectional graph
is represented by a symmetric array. 
The graph array is constructed using link lists in two "directions": vertical and horizontal. An insertion on the array is
being processed first on the horizontal and then in the vertical linked list.


Breadth First Search:
The algorithm is simple but we need to implement some basic functionallity:
A Queue which is implemented with a linked list
Find next edge to process (basically a dequeue functionality applied to the previous linked list datatype).
Each edge's neighboor is easy to be found as we have implemented the graph as a sparce array.
Terminate execution when all vetices are proccessed.
+ An algorithm to find after the construction of the acyclic graph the cycles that needed to be destructed in the initial graph.

