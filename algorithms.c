// This file contains a variety of algorithm codes from Levitan's introduction to the design of algorithms. They are a somewhat random group, thus rather than include a seperate header file, I'm keeping declarations at the top of this document, to serve as a sort of table of contents. 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "graphs.h"

//Declarations
int* getIntArray(FILE *);
int* copyArray(int *old, int length);
	
int findMaxInt(int array[], int length);
int sequentialSearch2(int array[], int length, int key);

int uniqueTF(int array[], int length);
int binaryDigits(int dec);
int bruteForceStringMatch(int intArray[], int length, int patternIntArray[], int pattenLength);

void depthFirstSearch(GRAPH *);
void breadthFirstSearch(GRAPH *);


int* lexicographicPermute(int number);
int bigIndexSmallNumber(int permutation[], int size);
int largestIndexGreaterThan(int permutation[], int size, int index);
void swap(int* a, int* b);
void reverseArray(int* firstElement, int length);




//testing code
int main(void){
	int functionNum, intAnswer, *intArray, *intPatternArray;
	int bigloop=0;//bool
	char option;	
	GRAPH *g1;
	char fileName[100];
	int intIn;
	FILE *source;

	while ( bigloop==0){
		printf("What function to test: \n\t 1: findMaxInt\n\t 2: sequentialSearch2\n\t 3: uniqueTF\n\t 6: binaryDigits\n\t 9: bruteForceStringMatch\n\t 11: depthSearch \n\t 12: breadthSearch \n\t 13: greyCode\n\t 19: Permutations\n");
		scanf(" %i",&functionNum);
		switch (functionNum){
			case 1:
				printf("Please name a file containing array information.\n");
				scanf(" %99s",fileName);

				source=fopen(fileName, "r");
				intArray=getIntArray(source);	//returns length of array in a[0], and the rest of the array in 1-length.
				intAnswer=findMaxInt(&intArray[1],intArray[0]);
				printf("Max is %i\n",intAnswer);
				break;
			case 2:
				printf("Please name a file containing array information.\n");
				scanf(" %99s",fileName);
				source=fopen(fileName, "r");
				intArray=getIntArray(source);
				
				printf("Please enter the search key\n");
				scanf(" %i",&intIn);
				
				intAnswer= sequentialSearch2(&intArray[1],intArray[0],intIn);
				
				printf("Match position is %i. (-1 represnts no match found)\n",intAnswer);
				
				break;
			case 3:
				printf("Please name a file containing array information.\n");
				scanf(" %99s",fileName);
				source=fopen(fileName, "r");
				intArray=getIntArray(source);
				if(uniqueTF(&intArray[1],intArray[0])){
					printf("There are no duplicate entries\n");
					
				}
				else {
					printf("There are duplicate entries\n");
				}
				break;
			case 6:
				printf("Please enter a decimal number\n");
				scanf(" %i",&intIn);
				intAnswer=binaryDigits(intIn);
				printf("The binary representation of %i has %i digits\n",intIn,intAnswer);
				break;
			case 9:
				printf("Please enter the name of a file containing array information\n");
				scanf(" %99s",fileName);
				source=fopen(fileName, "r");
				intArray=getIntArray(source);			
				intPatternArray=getIntArray(source);
				
				intAnswer=bruteForceStringMatch(&intArray[1],intArray[0],&intPatternArray[1],intPatternArray[0]);
				
				printf("Match position is %i. (-1 represnts no match found)\n",intAnswer);
				break;
			case 11:
				printf("\nPlease enter the name of a file containing graph information\n");
				scanf(" %99s",fileName);
				if(fileName[0]=='0'){
					return 0;
				}	
				g1=initializeGraph(fileName);
				
				printf("a. Graph name: %s\nb. No. of vertices = %i\nc. No. of edges = %i\nd. Start vertex = %i", g1->name, g1->vNum, g1->eNum, g1->start->contentsI);

				puts("\nDepth first traversal order...");
				depthFirstSearch(g1);				
				clearTraversal(g1);
				break;
			case 12:
				printf("\nPlease enter the name of a file containing graph information\n");
				scanf(" %99s",fileName);
				if(fileName[0]=='0'){
					return 0;
				}	
				g1=initializeGraph(fileName);
				
				printf("a. Graph name: %s\nb. No. of vertices = %i\nc. No. of edges = %i\nd. Start vertex = %i", g1->name, g1->vNum, g1->eNum, g1->start->contentsI);

				puts("\nBreadth first traversal order...");
				breadthFirstSearch(g1);
				clearTraversal(g1);
				break;
						
			case 13:
				puts("Sorry. Grey code is not working right now. Try something else");
				break;
			case 19:
				printf("Please enter the size of the permutations\n");
				scanf(" %i",&intIn);
				intArray=lexicographicPermute(intIn);
				break;	
			default:
				printf("Invalid Input.\n");
		}
		printf("\nWould you like to test another? Y/N \n");
		scanf(" %c",&option);
		if (option=='N'){
			bigloop=1;
			printf("quitting...\n");
			return 0;
		}
	}
}

//helper functions


int* getIntArray(FILE *source){
  int* array,*curr;
  int i, length;
	fscanf(source,"%i",&length);
	array=malloc((length+1)*sizeof(int));
	array[0]=length;
  
  for (i=1;i<=length;i++){  
	curr=array+i;
	fscanf(source," %i",curr);
  }
	
  return (array); 
}

int factorial(int input){
//ititialize total to base case value
	int total=1;
	
//base case, input is 0
	if (input==0){
		return total;	
	}
	
//recursive definition	
	else {
		total=input*factorial(input-1);
		return(total);
	}
}



//Codes
//1.
int findMaxInt(int array[], int length){
	int i,maxFound;
	
	for(i=1;i<length;i++){
		if(array[i]>maxFound){
			maxFound=array[i];
		}
	}
	return(maxFound);	
}

//2.
int sequentialSearch2(int array[], int length, int key){
		int i=0;
		array[length]=key;
		while(array[i]!=key){
			i++;
		}
		if(i<length){
			return i;
		}
		else if(i==length){
			return -1;
		}
		else{
			printf("algotithm falure\n");
			return 99;
		}
}

/*
ALGORITHM SequentialSearch(A[0..n − 1], K)
//Searches for a given value in a given array by sequential search
//Input: An array A[0..n − 1] and a search key K
//Output: The index of the first element in A that matches K
// or −1 if there are no matching elements
i ←0
while i < n and A[i] = K do
i ←i + 1
if i < n return i
else return −1
*/

//3. 
int uniqueTF(int array[], int length){
	int i,j;
	for(i=0;i<length-1;i++){
		for (j=i+1;j<length;j++){
			if (array[i]==array[j]){
				return 0;
			}
		}
	}
	return 1;
}

//6.
int binaryDigits(int dec){
	int count=1;
	for(;dec>1;count++){
		dec=(dec/2);
	}
	return count;
}


//9
int bruteForceStringMatch(int intArray[], int length, int patternIntArray[], int patternLength){
	int i,j;
		
	for (i=0;i<=(length-patternLength);i++){
		for (j=0;j<patternLength && patternIntArray[j]==intArray[i+j];j++){		}
		if (j==patternLength){
			return i;
		}
	}
	return -1;
}
//11.



/*
ALGORITHM DFS(G)
//Implements a depth-first search traversal of a given graph
//Input: Graph G = V, E
//Output: Graph G with its vertices marked with consecutive integers
// in the order they are first encountered by the DFS traversal
mark each vertex in V with 0 as a mark of being “unvisited”
count ←0
for each vertex v in V do
if v is marked with 0
dfs(v)

dfs(v)
//visits recursively all the unvisited vertices connected to vertex v
//by a path and numbers them in the order they are encountered
//via global variable count
count ←count + 1; mark v with count
for each vertex w in V adjacent to v do
if w is marked with 0
dfs(w)

*/

//13.
/*

LIST * binaryReflectedGrayCode(int order){
	LIST allBitStrings, list1, list2;
	NODE *currNode, *lastNode=NULL, *l1curr, *l2curr, *new1,*new2;
	allBitStrings=malloc(sizeof(LIST));
	
	if (order==1){
		currNode=createNode();
		currNode->contentsI=0;
		insertNode(&allBitStrings,lastNode,currNode);
		lastNode=currNode;
		
		currNode=createNode();
		currNode->contentsI=1;
		insertNode(&allBitStrings,lastNode,currNode);
		lastNode=currNode;
	}
	else{//this else statement is totally wrong. 
		
		list1=binaryReflectedGrayCode(n-1);
		list2=copyReverseList(list1);
		
		for(l1curr=list1->head && l2curr=list2->head; l1curr&&l2curr;l1curr=l1curr->next &&l2curr=l2curr->next){
			new1=createNode(void);
			new2=createNode(void);
			insertNodeBefore(list1,,new1)//BOOKMARK
		}

	}
	
}
*/
/*
ALGORITHM BRGC(n)
//Generates recursively the binary reflected Gray code of order n
//Input: A positive integer n
//Output: A list of all bit strings of length n composing the Gray code


else generate list L1 of bit strings of size n - 1 by calling BRGC(n - 1)
copy list L1 to list L2 in reversed order
add 0 in front of each bit string in list L1
add 1 in front of each bit string in list L2
append L2 to L1 to get list L
return L
*/



//19.

int* lexicographicPermute(int number){
	int** permutationList;
	int* currPermutation, *lastPermutation;
	int i, j, k=0, subsetSize, listSize;
	listSize=factorial(number);

	permutationList=malloc((sizeof(int)*(number))*listSize);
	
	currPermutation=malloc(sizeof(int)*(number));
	for (i=0;i<number;i++){
		currPermutation[i]=i+1;
	}
	permutationList[0]=currPermutation;
	lastPermutation=currPermutation;
	
	printf("Permutation %i is... \t",k);
	for (i=0;i<number;i++){
		printf("%i",currPermutation[i]);
	}
	puts("\n");

	
	for(k=1;k<listSize;k++){
		currPermutation=copyArray(lastPermutation,number);
	
		i=bigIndexSmallNumber(lastPermutation, number);
		//printf("largest index smaller than neighbor is %i\n",i);

		j=largestIndexGreaterThan(lastPermutation,number,i);
		//printf("largest index greater %i is %i\n",i,j);
		
		swap(&currPermutation[i],&currPermutation[j]);

		subsetSize=number-(i+1);
		reverseArray(&currPermutation[i+1],subsetSize);
		permutationList[k]=currPermutation;
		lastPermutation=currPermutation;
		
		printf("Permutation %i is... \t",k);
		for (i=0;i<number;i++){
			printf("%i",currPermutation[i]);
		}
		puts("\n"); 
	}
	
}

int* copyArray(int *old, int length){
	int * new, i;
	new=malloc(sizeof(int)*(length));
	for (i=0;i<length;i++){
		new[i]=old[i];
	}
	return new;
}


int bigIndexSmallNumber(int permutation[], int size){
	int i;
	for(i=(size-1);i>0;i--){
		if (permutation[i]>permutation[i-1]){
			return (i-1);
		}
	}
}

int largestIndexGreaterThan(int permutation[], int size, int index){
	int j;
	for(j=size-1;j>0;j--){
		if (permutation[index]<permutation[j]){
			return (j);
		}
	}
}
void swap(int* a, int* b){
	int temp;
	printf("swapping %i and %i...\n",*a,*b);
	temp=*a;
	*a=*b;
	*b=temp;
}

void reverseArray(int* array, int length){
	int i;
	for(i=0;i<((length/2));i++){
		swap(&array[i],&array[((length-1)-i)]); 
	}
}


/*
ALGORITHM LexicographicPermute(n)
//Generates permutations in lexicographic order
//Input: A positive integer n
//Output: A list of all permutations of {1, . . . , n} in lexicographic order

initialize the first permutation with 12 . . . n
while last permutation has two consecutive elements in increasing order do
	let i be its largest index such that ai < ai+1 //ai+1> ai+2 > . . . > an
find the largest index j such that ai < aj //j = i + 1 since ai < ai+1
swap ai with aj //ai+1ai+2 . . . an will remain in decreasing order
reverse the order of the elements from ai+1 to an inclusive
add the new permutation to the list
*/