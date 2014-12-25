#ifndef SPARSE_ARRAY_H_
#define SPARSE_ARRAY_H_

/**
 * datatype graphNode
 *	fields
 *	name    type
 *      _____________
 *	i       int    -> store graphNode's horizontal position
 *	j       int    -> store graphNode's vertical position
 *	data    int    -> store the data of the graphNode 
 *	left    graphNode*  -> store the address of the left graphNode (pointer to graphNode)	
 *	right   graphNode*  -> store the address of the right graphNode (pointer to graphNode)
 *	up      graphNode*  -> store the address of the up graphNode (pointer to graphNode)
 *	down    graphNode*  -> store the address of the down graphNode (pointer to graphNode)
 */
struct graphNode
{
	int i;
	int j;
	int data;
	struct graphNode* left;
	struct graphNode* right;
	struct graphNode* up;
	struct graphNode* down;
};

/**
 * datatype sparseArray
 *	fields
 *	    name              type
 *      ______________________
 *	    horizontalArray   graphNode**   -> Array of pointer to graphNode 
 *      verticalArray     graphNode**   -> Array of pointer to graphNode 
 *      size              int           -> size of the Array (both horizontal and vertical)
 */
struct matrix
{
	struct graphNode** horizontalArray;
	struct graphNode** verticalArray;
	int size;
};

struct matrix* sparseMenu();
struct matrix* headConstruct(int size);

void insert(struct matrix* sparseArray,struct graphNode* input);
void insertByHand(struct matrix* sparseArray);
void horizontalInsert(struct graphNode* aux, struct graphNode* inputgraphNode);
void verticalInsert(struct graphNode* aux, struct graphNode* inputgraphNode);

void delete(struct matrix* sparseArray);
void horizontalDelete(struct graphNode* horizontalAux, struct graphNode* inputgraphNode);
void verticalDelete(struct graphNode* verticalAux, struct graphNode* inputgraphNode);

void printGraph(struct matrix* sparseArray);

int graphNodeExists(struct matrix* sparseArray,struct graphNode* inputgraphNode);


struct graphVertex* findGraphVertexes(struct graphVertex* vertexesGroup,struct matrix* sparseArray);
void readFromFile(struct matrix* sparseArray);
//moved to BFS main
//void findVertexNeighboors(struct graphVertex* vertexesGroup,struct matrix* sparseArray);
//void checkExists(struct matrix* sparseArray);
//void graphNodeUpdate(struct matrix* sparseArray,struct graphNode* inputgraphNode);
//void findgraphNodesByValue(struct matrix* sparseArray,int data);

#endif