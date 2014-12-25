#ifndef PATH_LIST_H_
#define PATH_LIST_H_

struct treeEdge
{	
	int i;
	int j;
	struct treeEdge* left;
	struct treeEdge* right;
};

struct treeEdge* insertTreeEdge(struct treeEdge* inputEdge,struct treeEdge* aux);
struct treeEdge* mergePaths(struct treeEdge* pathA,struct treeEdge* pathB);
void printTreeEdgeList(struct treeEdge* aux);
struct treeEdge* createTreeEdgeCopy(struct treeEdge* inputEdge);


#endif