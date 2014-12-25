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
void printVertexList(struct graphVertex* aux);
int vertexExists(struct graphVertex* inputVertex,struct graphVertex* aux);
int graphVertexSize(struct graphVertex* aux);
void setVertexVisited(struct graphVertex* inputVertex,struct graphVertex* aux);

#endif