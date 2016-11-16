#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct GNODE{
//	char contentsS[20];
	int contentsI;
	struct GNODE *forward;
	struct GNODE *backward;
	unsigned char * adjacency;
	int transversalOrder;

}GNODE;

typedef struct QUEUE{
	GNODE * front;
	GNODE * end;
}QUEUE;

typedef struct GRAPH{
	char name[20];
	int vNum;
	int eNum;
	GNODE *origin;
	GNODE *start;
}GRAPH;


GRAPH * createGraph(int);
void createEdge(GNODE *, GNODE *);
void clearTraversal(GRAPH*);

GRAPH *initializeGraph(char *);

int dfs(GRAPH *, GNODE *, int );
int bfs(GRAPH *, GNODE *, int);


GRAPH * createGraph(int vNum){ 
	int i;
	GRAPH * this;
	this=malloc(sizeof(GRAPH));
	this->origin=malloc(sizeof(GNODE)*(1 + vNum));

	this->vNum=vNum;

	for (i=1;i<=vNum;i++){
		this->origin[i].contentsI=i;
//		printf("contents at origin %i are %i\n",i,this->origin[i].contentsI);
		this->origin[i].transversalOrder=0;
		
		this->origin[i].adjacency=calloc(vNum+1,sizeof(unsigned char));

	}
	return this; 
}
  
void createEdge(GNODE *vFrom, GNODE *vTo){
//	printf("creating edge from %i to %i\n",vFrom->contentsI,vTo->contentsI);
	vFrom->adjacency[vTo->contentsI]=1;
//	printf("adjacency at %i is %i\n",vTo->contentsI,vFrom->adjacency[vTo->contentsI]);
}	

void clearTraversal(GRAPH *this){
	int i, vNum;
	vNum=this->vNum;
	
	for (i=1;i<=vNum;i++){
		this->origin[i].transversalOrder=0;
	}
}

GRAPH *initializeGraph(char fileName[]){
	int vNum,eNum,e,v1,v2,startPos;
	char graphName[21]; 
	FILE *source;
	GRAPH *g1;
	GNODE *vFrom, *vTo;
	
		source=fopen(fileName, "r");
		
		fscanf(source," %20s",graphName);
		fscanf(source,"%i",&vNum);
		
		g1=createGraph(vNum);
		strcpy(g1->name,graphName);
		fscanf(source,"%i",&eNum);
		g1->eNum=eNum;
		
		for(e=0;e<eNum;e++){
			fscanf(source,"%i,",&v1);
			fscanf(source,"%i,",&v2);
			vFrom=&(g1->origin[v1]);
			vTo=&(g1->origin[v2]);

			createEdge(vFrom,vTo);
		}
		fscanf(source,"%i",&startPos);
		g1->start=&(g1->origin[startPos]);
		fclose(source);
		return(g1);
}



void depthFirstSearch(GRAPH * this){
	int count=0;
	int v, vNum=this->vNum;
	GNODE * currNode;
	currNode=this->start;
	
	for(v=1;v<=vNum;v++){

		if(currNode->transversalOrder==0){
			count=dfs(this, currNode,count);
		}
	}
}
int dfs(GRAPH * graph, GNODE * currNode, int count){
	int i;
	count++;
	currNode->transversalOrder=count; 
	printf("%i ", currNode->contentsI);
	
	i=graph->vNum;
	int vNum=graph->vNum;
	
	for(i=1;i<=vNum;i++){
//			printf("thisfar.%i is %i\n", i, currNode->adjacency[i]); 
		if(currNode->adjacency[i]){
			if(graph->origin[i].transversalOrder==0){
				count=dfs(graph, &graph->origin[i], count);
			}
		}
	}
	return count;
}

/*
ALGORITHM BFS(G)
//Implements a breadth-first search traversal of a given graph

count ?0
for each vertex v in V do
if v is marked with 0
bfs(v)
bfs(v)
//visits all the unvisited vertices connected to vertex v
//by a path and numbers them in the order they are visited
//via global variable count
count ?count + 1; mark v with count */

void breadthFirstSearch(GRAPH * this){
	int count=1;
	int v, vNum=this->vNum;
	GNODE * currNode;
	currNode=this->start;
	
	for(v=1;v<=vNum;v++){

		if(currNode->transversalOrder==0){
			count=bfs(this, currNode,count);
		}
	}
}
int bfs(GRAPH * graph, GNODE * currNode, int count){
	int i, vNum;
	QUEUE queue;
	GNODE *adjNode;
	
	if(currNode->transversalOrder==0){
		currNode->transversalOrder=count++; 
		printf("%i ", currNode->contentsI);
		queue.front=queue.end=currNode;

		i=graph->vNum;
		vNum=graph->vNum;
		
		while(queue.front!=NULL){
			for(i=1;i<=vNum;i++){
				if(queue.front->adjacency[i]){
					adjNode=&graph->origin[i];
					if(adjNode->transversalOrder==0){
						adjNode->transversalOrder=count++;
						printf("%i ", adjNode->contentsI);
						adjNode->forward=queue.end;
						adjNode->backward=NULL;
						queue.end->backward=adjNode;
						queue.end=adjNode;
					}
				}
			}
			queue.front=queue.front->backward;
		}
	}

	return count;
}

