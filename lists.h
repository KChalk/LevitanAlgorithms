#include <string.h>
#include <stdlib.h>

typedef struct NODE{
	string contentsS;
	int contentsI;
//	TYPE *contentsP;
	NODE *next;
	NODE *prev;

}NODE;
	
NODE* createNode(void){
		NODE* this;
		this=malloc(sizeof(NODE));
		this->next=NULL;
		this->prev=NULL;
		this->contentsI=-1;
		this->contentsS="\0";
		this->contentsP=NULL;
		return this;
}

	
void clearNode(NODE* this){
		this->next=NULL;
		this->prev=NULL;
		this->contentsI=-1;
		this->contentsS="\0";
		this->contentsP=NULL;	
}

int copyNode(NODE* this, NODE *original){
		this->contentsI=original->contentsI;
		this->contentsS=original->contentsS;
		this->contentsP=original->contentsP;
		return 0;
}
	

int insertnext(NODE* this, NODE *node1){
		if(this->next!=NULL){
			node1->next=this->next;
			this->next->prev=node1;
		}
		this->next=node1;
		node1->prev=this;
		return 0;
}
	

typedef struct LIST{
	NODE *head;
	NODE *tail;
	int length;
}LIST;

void clearList(LIST* this){
		this->head=NULL;
		this->tail=NULL;
		this->length=0;
	}
}

LIST* copyReverseList(LIST *original){
	LIST* new;
	NODE* currNew, lastNew, currOrig;

	new=malloc(sizeof(LIST));
	currNew=malloc(sizeof(NODE));
	
	currOrig=original->tail;
	copyNode(currNew, currOrig);
	new->head=currNew;
	currOrig=currOrig->prev;
	
	while(currOrig){
		lastNew=currNew;
		currNew=malloc(sizeof(NODE));
		copyNode(currNew, currOrig);
		insertNode(new,lastNew,currNew)
		currOrig=currOrig->prev;
	}
	
	return new;
}

int insertSortedI (LIST* this, NODE *start, NODE *addend){
	//empty list 
	if (start==NULL){
		this->head=addend;
		this->tail=addend;
		this->head->next=NULL;
		this->length++;
	}
	//less than start
	else if(addend->contentsI < start.contentsI){
		this->head=addend;
		addend->next=start;
		this->length++;
	}
	//next is EOL, add to end		
	else if (start->next==NULL){
		start->next=addend;
		this->tail=addend;
		this->length++;
	}
	//less than next
	else if(addend->contentsI < start->next->contentsI){
		addend->next=start->next;
		start->next=addend;
		this->length++;
	}
	//greater than next
	else {
		insertSortedI(this, start->next, addend);
	}
	return (this->length);
}

	
	int insertSortedA (LIST* this, NODE *start, NODE *addend){
		//empty list 
		if (start==NULL){
			head=addend;
			this->tail=addend;
			head->next=NULL;
			this->length++;
		}
		//less than start
		else if(addend->contentsS < start->contentsS){
			head=addend;
			addend->next=start;
			this->length++;
		}
		//next is EOL, add to end		
		else if (start->next==NULL){
			start->next=addend;
			this->tail=addend;
			this->length++;
		}
		//less than next
		else if(addend->contentsS < start->next->contentsS){
			addend->next=start->next;
			start->next=addend;
			this->length++;
		}
		//greater than next
		else {
			insertSortedA(start->next, addend);
		}
		return (this->length);
	}
	
	int insertSorted (LIST* this, NODE *start, NODE *addend){
		//empty list 
		if (start==NULL){
			this->head=addend;
			this->tail=addend;
			this->length++;
		}
		//less than start
		else if(addend->contentsI < start->contentsI || addend->contentsS < start->contentsS){
			this->head=addend;
			addend->next=start;
			this->length++;
		}
		//next is EOL, add to end		
		else if (start->next==NULL){
			this->tail=addend;
			start->next=addend;
			this->length++;
		}
		//less than next
		else if(addend->contentsI < start->next->contentsI || addend->contentsS < start->next->contentsS){
			addend->next=start->next;
			start->next=addend;
			this->length++;
		}
		//greater than next
		else {
			insertSorted(start->next, addend);
		}
		return (this->length);
	}

	
	int insertNode(LIST* this, NODE *before, NODE *addend){
		if (this->head==NULL){
			this->head=addend;
			this->tail=addend;
			this->length=1;
		}
		else {		
			insertnext(before,addend);
			if(before==NULL){
				this->head=addend;
			}
			if(addend->next==NULL){
				this->tail=addend;
			}
			this->length++;
		}
		return (this->length);
	}
	
	int insertNodeBefore(LIST* this, NODE *after, NODE *addend){//BOOKMARK
		if (this->head==NULL){
			this->head=addend;
			this->tail=addend;
			this->length=1;
		}
		else {		
			insertnext(before,addend);
			if(before==NULL){
				this->head=addend;
			}
			if(addend->next==NULL){
				this->tail=addend;
			}
			this->length++;
		}
		return (this->length);
	}

	int printList(LIST* this){
		int listLength=0;
		NODE *curr=this->head;
		while (curr!=NULL){
			listLength++;
			curr->contentsI;
			curr->contentsS;
			curr=curr->next;
		}
		return (listLength);
	}
};

