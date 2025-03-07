#include <stdio.h>
#include <stdlib.h>

typedef struct Node *nodePointer;			//Pointer to Data Node (Sparse array)
typedef struct queueNode *queuePointer;		//Pointer to Queue using in BFS
typedef struct queue Queue;
typedef struct cycleList *cyclePointer;		//Pointer to Cycle Node (cycles)

//Colour of Nodes

typedef enum {
    WHITE,
    GREY,
    BLACK
} Colour;			

// Basic Node of Sparse Array

struct Node {
    int i, j, key, parent, distance;
    nodePointer next, prev, up, down;
    Colour colour;
};

// Auxiliary Node for BFS

struct queueNode {
	int key;
	queuePointer next;
};

struct queue {
	queuePointer first;
	queuePointer last;
};

// Cycles Node

struct cycleList {
	int x,y;
	cyclePointer next;	
	cyclePointer prev;
};

// Vertican and Horizotal arrays for Sparse Array

struct Node Vertical[30];
struct Node Horizontal[30];

void init();							// Init Sparse Array
void insert(int x, int y);				// Insert element in Sparse Array
void delete(int x, int y);				// Delete element in Sparse Array
void print();							// Print Sparse Array
void initBFS();							// Initialize nodes for Breadth First Search
void bfs(int root);						// Breadth First Search in Sparse Array
void initQueue(Queue *q);				// Init Queue using in BFS
int emptyQueue(Queue q);				// Queue is Empty
void enqueue(Queue *q, int data);		// Add elements in Queue
int dequeue(Queue *q);					// Export elements in Queue
void cycles(int a, int b);				// Find Cycles in a tree

int main(void) {
	
	int x,y,root;

    char answer = '_';

    init();
    
    // Menu
    
  	while(answer != 'Q' && answer != 'q') {
    	printf("\n\n--------------------------------------------------------------\n");
    	printf("Previous answer was: %c\nGive a new choice: (I/P/D/B/C/Q): ", answer);

    	fflush(stdin);
    	answer = getchar();
    	getchar();

    	printf("The new answer is: %c", answer);
    	printf("\n--------------------------------------------------------------\n");

        if (answer != 'I' && answer != 'i' && answer != 'P' && answer != 'p' && answer != 'D' && answer != 'd' && answer != 'Q' && answer != 'q' && answer != 'B' && answer != 'b' && answer != 'C' && answer != 'c') {
    		printf("\n\nInvalid input, please try again.\n");
    	}
    	
    	// Insert element in Sparse Array
    	
    	if(answer == 'I' || answer == 'i') {
    		printf("\n\nInsert an element of sparse array");
      
    		printf("\nGive x: ");
 	   		scanf("%d", &x);
    		getchar();

			printf("Give y: ");
    		scanf("%d", &y);
    		getchar();
      
    		while (x == y) {
				printf("x is not allowed to be equal with y. Give another input: ");
    			scanf("%d%d", &x, &y);
			}

      		insert(x,y);
      		insert(y,x);
      		printf("Element Inserted!\n");
    	}
    	
    	
    	// Print Sparse Array

    	if(answer == 'P' || answer == 'p') {
    
        	printf("\n");
        	print();
      	}
      	
      	
      	// Delete element in Sparse Array

    	if(answer == 'D' || answer == 'd') {
      		printf("\n\nDelete element (i,j)");
      		printf("\ni: ");
      		scanf("%d", &x);
      		getchar();
      
    		printf("\nj: ");
      		scanf("%d", &y);
      		getchar();

      		delete(x,y);
      		delete(y,x);
    	}
    	
    	
    	// Breadth First Search in Sparse Array
    	
    	if(answer == 'B' || answer == 'b') {
    
        	printf("\nGive root: ");
 	   		scanf("%d", &root);
    		getchar();
    		
    		bfs(root);
    		
      	}
      	
      	
      	// Find cycles in a tree
      	
      	if(answer == 'C' || answer == 'c') {
    
        	printf("\nGive edge:");
        	printf("\ni: ");
      		scanf("%d", &x);
      		getchar();
      
    		printf("\nj: ");
      		scanf("%d", &y);
      		getchar();
      		
      		cycles(x,y);
      	}
	}

  printf("\n\nThe program has halted.");
    return 0;
}


// Initialize Sparse Array

void init() {
    int index;
    for (index = 0; index < 30; index++) {
        Horizontal[index].key = index;
        Horizontal[index].next = NULL;
        Horizontal[index].prev = NULL;
        Horizontal[index].up = NULL;
        Horizontal[index].down = NULL;
        Horizontal[index].colour = WHITE;
        Horizontal[index].parent = -1;
        Horizontal[index].distance = 0;

        Vertical[index].key = index;
        Vertical[index].next = NULL;
        Vertical[index].prev = NULL;
        Vertical[index].up = NULL;
        Vertical[index].down = NULL;
        Vertical[index].colour = WHITE;
        Vertical[index].parent = -1;
        Vertical[index].distance = 0;
    }
}


// Insert element in Sparse Array

void insert(int x, int y) {
	
    nodePointer temp = (nodePointer)malloc(sizeof(struct Node));

    temp->i = x;
    temp->j = y;
    temp->next = NULL;
    temp->prev = NULL;
    temp->up = NULL;
    temp->down = NULL;
    
    
    // Insert element (x,y) and connect with Vertical array

    if (Vertical[x].next == NULL) {
        Vertical[x].next = temp;
        temp->prev = NULL;
    } else {
        nodePointer a = Vertical[x].next;
        nodePointer prev = NULL;
	
        while (a != NULL && a->j <= y) {
            prev = a;
            a = a->next;
        }

        if (prev != NULL) {
            prev->next = temp;
        } else {
            Vertical[x].next = temp;
        }

        temp->next = a;
        temp->prev = prev;

        if (a != NULL) {
            a->prev = temp;
        }
    }
    
    // Insert element (x,y) and connect with Horizontal array
    
    if (Horizontal[y].down == NULL) {
        Horizontal[y].down = temp;
        temp->up = NULL;
    } else {
        nodePointer a = Horizontal[y].down;
        nodePointer prev = NULL;

        while (a != NULL && a->i <= x) {
            prev = a;
            a = a->down;
        }

        if (prev != NULL) {
            prev->down = temp;
        } else {
            Horizontal[y].down = temp;
        }

        temp->down = a;
        temp->up = prev;

        if (a != NULL) {
            a->up = temp;
        }
    }

}

// Delete element in Sparse Array

void delete(int x, int y) {
	
	
	// Find the element and reconnect poitners with Vertical array
	
	nodePointer temp1 = Vertical[x].next;
    while (temp1 != NULL && temp1->j != y) {
        temp1 = temp1->next;
    }

    if (temp1 != NULL && temp1->j == y) {
        if (temp1->prev != NULL) {
            temp1->prev->next = temp1->next;
            if (temp1->next != NULL)
            	temp1->next->prev = temp1->prev;
        } 
		else {
            Vertical[x].next = temp1->next;
        }

    }
	else {
    	printf("\nNode at position (%d, %d) not found!", x, y);
    }
    
    
    // Find the element and reconnect poitners with Horizontal array
    
    nodePointer temp2 = Horizontal[y].down;
    while (temp2 != NULL && temp2->i != x) {
        temp2 = temp2->down;
    }

    if (temp2 != NULL && temp2->i == x) {
        if (temp2->up != NULL) {
            temp2->up->down = temp2->down;
            if (temp2->down != NULL)
            	temp2->down->up = temp2->up;
        } 
		else {
            Horizontal[y].down = temp2->down;
        }

    }
    
    // Delete element
    
    free(temp2);    
}

// Print Sparse Array

void print() {
    int i, j;
    printf("\nSparse Array:\n");
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            nodePointer temp = Vertical[i].next;
            while (temp != NULL && temp->j < j) {
                temp = temp->next;
            }

            if (temp != NULL && temp->j == j) {
                printf("(%d,%d) ", temp->i, temp->j);
                printf(" ");
            } 
        }
        printf("\n");
    }
}

// Initialize Queue

void initQueue(Queue *q) {
	q->first = NULL;
	q->last = NULL;
}

// Check if Queue is empty

int emptyQueue(Queue q){
	return q.first == NULL;	
}

// Import elements in Queue

void enqueue(Queue *q, int data) {
	
	queuePointer aux = (queuePointer)malloc(sizeof(struct queueNode));
	
	aux->next = NULL;
	aux->key = data;
	
	if(emptyQueue(*q)) {
		q->first = aux;
		q->last = aux;
	}
	else {
		q->last->next = aux;
		q->last = aux;
	}
}

// Export elements in Queue

int dequeue(Queue *q) {
	
	if(emptyQueue(*q)) {
		printf("\nEmpty queue!");
		return 0;
	}
	
	else {
		queuePointer aux = q->first;
		int data = aux->key;
		
		q->first = aux->next;
		free(aux);
		
		if (q->first == NULL) {
			q->last = NULL;
		}
		
		return data;
	}
}

// Initialize nodes for Breadth First Search

void initBFS() {
	
int index;
    for (index = 0; index < 30; index++) {

        Horizontal[index].colour = WHITE;
        Horizontal[index].parent = -1;
        Horizontal[index].distance = 0;

        Vertical[index].colour = WHITE;
        Vertical[index].parent = -1;
        Vertical[index].distance = 0;
    }
}

// Breadth First Search in a graph (Sparse Array)

void bfs(int root) {
	
	initBFS();
    Queue q;
    initQueue(&q);

    Vertical[root].colour = GREY;
    enqueue(&q, root);

    while (!emptyQueue(q)) {
        int temp = dequeue(&q);

        nodePointer aux = Vertical[temp].next;
        
        while (aux != NULL) {
            if (Vertical[aux->j].colour == WHITE) {
                Vertical[aux->j].colour = GREY;
                Vertical[aux->j].parent = temp;
                Vertical[aux->j].distance = Vertical[temp].distance + 1;
                enqueue(&q, aux->j);
                printf("\n------------\nNode %d \nDistance: %d \nParent: %d \n------------\n\n", aux->j, Vertical[aux->j].distance, Vertical[aux->j].parent);
            } 
            
            aux = aux->next;
        }

        Vertical[temp].colour = BLACK;
    }
}

// Auxiliary list for cycles - Insert

void insertCycle(cyclePointer *head, int a, double b) {
  
  cyclePointer temp = (cyclePointer)malloc(sizeof(struct cycleList));
  temp->x = a;
  temp->y = b;

  if(*head == NULL) {
    *head = temp;
    temp->next = NULL;
    temp->prev = NULL;
  }

  else if(*head != NULL) {
  	temp->next = *head;
  	(*head)->prev = temp;
  	*head = temp;  	
  }
}

// Find Cycles in a spanning tree

void cycles(int a, int b) {
	
	cyclePointer head1 = NULL;
	cyclePointer head2 = NULL;
	
	if(Vertical[a].colour != BLACK || Vertical[b].colour != BLACK)
		printf("\ninput error! Try again!");
	
	else if (Vertical[a].parent == b || Vertical[b].parent == a)
		printf("\n%d and %d is an edge of the tree! Try again!", a,b);
	
	else {
		
		head1 = NULL;
		head2 = NULL;
		int temp1 = a;
		int temp2 = b;
		
		while (Vertical[temp1].distance > 0 || Vertical[temp2].distance > 0 ) {
			
			if (Vertical[temp1].distance > 0) {
				insertCycle(&head1,temp1,Vertical[temp1].parent);
				temp1 = Vertical[temp1].parent;
			}
			
			if (Vertical[temp2].distance > 0) {
				insertCycle(&head2,temp2,Vertical[temp2].parent);
				temp2 = Vertical[temp2].parent;

			}
		}
	}
	
	cyclePointer aux1 = head1;
	cyclePointer aux2 = head2;
	
	while(aux1->x == aux2->x && aux1->y == aux2->y) {
		aux1 = aux1->next;
		aux2 = aux2->next;
	}
	
	if(aux1 != NULL && aux2 != NULL){
		printf("\n\nCycle:\n");
		
		while(aux1 != NULL) {
			printf("(%d-%d),",aux1->x, aux1->y);
			aux1 = aux1->next;
		}
		
		while(aux2 != NULL) {
			printf("(%d-%d),",aux2->x, aux2->y);
			aux2 = aux2->next;
		}
		
		printf("(%d-%d)", a,b);
	}
	
	else if (aux1 == NULL || aux2 == NULL) 
		printf("There is no cycle that connects (%d-%d)", a,b);
}