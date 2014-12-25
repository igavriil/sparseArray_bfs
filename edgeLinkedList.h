#ifndef NODE_LIST_H_
#define NODE_LIST_H_

struct graphEdge
{	
	int i;
	int j;
	int active;
	struct graphEdge* left;
	struct graphEdge* right;
};

struct graphEdge* insertGraphEdge(struct graphEdge* inputEdge,struct graphEdge* aux);
int deactivatedEdgeExists(struct graphEdge* inputEdge,struct graphEdge* aux);
int activatedEdgeExists(struct graphEdge* inputEdge,struct graphEdge* aux);
void printEdgeList(struct graphEdge* aux);


#endif