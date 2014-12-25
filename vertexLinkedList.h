#ifndef VERTEX_LIST_H_
#define VERTEX_LIST_H_

struct graphVertex
{	
	int value;
	int visited;
	struct graphVertex* left;
	struct graphVertex* right;
	struct graphVertex* parent;
};

struct graphVertex* insertGraphVertex(struct graphVertex* inputVertex,struct graphVertex* aux);
struct graphVertex* findVertexByValue(int value,struct graphVertex* aux);
int relativeVertexes(struct graphVertex* LeafA,struct graphVertex* LeafB,struct graphVertex* graphVertexExplored);
void printVertexList(struct graphVertex* aux);
int vertexExists(struct graphVertex* inputVertex,struct graphVertex* aux);
int graphVertexSize(struct graphVertex* aux);
void setVertexVisited(struct graphVertex* inputVertex,struct graphVertex* aux);
int lastVertexVisited(struct graphVertex* aux);
struct graphVertex* vertexToBeExplored(struct graphVertex* aux);


#endif