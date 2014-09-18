/*
 * File:   hw8-Karboviak.c
 * Author: Kelton Karboviak
 *
 * Version: April 14, 2014
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/************************************************************/
/* STRUCTS                                                  */
/************************************************************/
/* struct graph is used to represent a node in the graph of locations */
struct graph {
    char *name;
    struct connection* arcs[10];
    int count, traversed;  // traverse is used as a boolean
};

/* struct connection is used to represent the one-way link between establishments */
struct connection {
    struct graph *dest;
    int weight;
};

/* struct index is used to represent a node in the index of all establishments */
struct index {
    char *name;
    struct graph *graphPtr;
    struct index *next;
};

typedef struct graph _gNode;
typedef struct connection _link;
typedef struct index _iNode;


/************************************************************/
/* FUNCTIONS                                                */
/************************************************************/
/********************************************************/
/* SEARCH INDEX LINKED-LIST                             */
/********************************************************/
_iNode* SEARCH_INDEX(_iNode *head, char searchName[]) {
    _iNode *current;
    current = head;
    while (current != NULL) {
        if (!strcmp(current->name, searchName))  return current;
        current = current->next;
    }

    return NULL;
}


/********************************************************/
/* CREATE A NEW GRAPH NODE                              */
/********************************************************/
void CREATE_GRAPH_NODE(_gNode *(*newNode), char name[]) {
    (*newNode) = (_gNode*) malloc(sizeof(_gNode));
    (*newNode)->name = (char*) calloc(sizeof(char), strlen(name));
    strcpy((*newNode)->name, name);
    (*newNode)->count     = 0;
    (*newNode)->traversed = 0;
}


/********************************************************/
/* INSERT ARC INTO GRAPH                                */
/********************************************************/
void INSERT_ARC(_iNode *head, char name1[], char name2[], int weight) {
#define gPtr1 start->graphPtr
#define gPtr2 end  ->graphPtr
    // Find first establishment in the index
    _iNode *start = SEARCH_INDEX(head, name1);
    // Check to see if the graphPtr hasn't been created
    if (gPtr1 == NULL)  CREATE_GRAPH_NODE(&gPtr1, name1);

    // Find second establishment in the index
    _iNode *end   = SEARCH_INDEX(head, name2);
    // Check to see if the graphPtr hasn't been created
    if (gPtr2 == NULL)  CREATE_GRAPH_NODE(&gPtr2, name2);


    // Create one-way link from start to end
    gPtr1->arcs[gPtr1->count] = (_link*) malloc(sizeof(_link));
    gPtr1->arcs[gPtr1->count]->dest   = gPtr2;
    gPtr1->arcs[gPtr1->count]->weight = weight;
    (gPtr1->count)++;
}


/********************************************************/
/* INSERT INTO INDEX LINKED-LIST.                       */
/********************************************************/
void INSERT_INDEX(_iNode *(*head), _iNode *(*tail), char name[]) {
	_iNode *newNode;
	newNode = (_iNode*) malloc(sizeof(_iNode));
	newNode->name = (char*) calloc(sizeof(char), strlen(name));
	strcpy(newNode->name, name);
    newNode->graphPtr = NULL;

	if ((*head) == NULL)  (*head) = (*tail) = newNode;

    (*tail)->next = newNode;
    (*tail) = newNode;
    newNode->next = NULL;
}


/********************************************************/
/* DRUNKARD'S WALK ALGORITHM                            */
/********************************************************/
int DRUNK_WALK(_iNode *head, char start[], char end[]) {
    srand(100);
    int total = 0, random;

    // Find starting establishment's graph node
    _gNode *current = SEARCH_INDEX(head, start)->graphPtr;

    printf("\nDRUNKARD'S WALK\n----------------\n");
    printf("Started at %s\n", current->name);
    while (strcmp(current->name, end)) {
        random = rand() % current->count;
        total += current->arcs[random]->weight;
        current = current->arcs[random]->dest;
    }

    printf("Ended at %s\n", current->name);
    return total;
}


/********************************************************/
/* GREEDY WALK ALGORITHM                                */
/********************************************************/
int GREEDY_WALK(_iNode *head, char start[], char end[], int N) {
    int total = 0, shortest, i;

    // Find starting establishment's graph node
    _gNode *current = SEARCH_INDEX(head, start)->graphPtr;

    printf("\nGREEDY WALK\n----------------\n");
    printf("Started at %s\n", current->name);
    while (strcmp(current->name, end)) {
        // Check to see if the graph node has already been traversed
        if (current->traversed) {
            printf("\nStuck in an infinite greedy loop.\n");
            printf("You will never make it to your destination.\n\n");
            return -1;
        }

        // Iterate through connections to find the shortest path
        shortest = 0;
        for (i = 1; i < current->count; i++) {
            if (current->arcs[i]->weight < current->arcs[shortest]->weight)
                shortest = i;
        }

        (current->traversed)++;
        total += current->arcs[shortest]->weight;
        current = current->arcs[shortest]->dest;
    }

    printf("Ended at %s\n", current->name);
    return total;
}


/********************************************************/
/* DESTROY THE GRAPH                                    */
/********************************************************/
void DESTROY_GRAPH(_iNode *(*head)) {
    _iNode *current;
    int i;

    current = (*head);
    while (current != NULL) {
        for (i = 0; i < current->graphPtr->count; i++) {
            free(current->graphPtr->arcs[i]);
            current->graphPtr->arcs[i] = NULL;
        }

        free(current->graphPtr->name);  current->graphPtr->name = NULL; // Free the graphPtr's name
        free(current->graphPtr);        current->graphPtr       = NULL; // Free the index's graphPtr
        current = current->next;
    }
}


/********************************************************/
/* DESTROY THE INDEX LINKED-LIST                        */
/********************************************************/
void DESTROY_INDEX(_iNode *(*head), _iNode *(*tail)) {
    _iNode *current = NULL;

	while ((*head) != NULL) {
		current = (*head);
		(*head) = (*head)->next;
		free(current->name);  current->name = NULL;   // Free the index node's name
		free(current);        current       = NULL;   // Free the index node
	}

	// Free head & tail pointers
	(*head) = (*tail) = NULL;
	free((*head));  free((*tail));
}



/************************************************************/
/* MAIN                                                     */
/************************************************************/
int main(void) {
    // Open data file
    FILE *data;
    if ((data = fopen("./hw8data.txt", "r")) == NULL) {
        printf("ERROR - hw8data.txt could not be opened.\n");
        exit (0);
    }

    _iNode *head, *tail;
    head = tail = NULL;
    char name1[100], name2[100], startLoc[100];
    int weight, numOfNodes = 0;

    // Read in establishments
    fscanf(data, "%s", name1);
    while (strcmp(name1, "STOP")) {
        INSERT_INDEX(&head, &tail, name1);
        numOfNodes++;
        fscanf(data, "%s", name1);
    }


    // Read in connections
    fscanf(data, "%s %s %d", name1, name2, &weight);
	while (strcmp(name1, "STOP") && strcmp(name2, "STOP")) {
        INSERT_ARC(head, name1, name2, weight);
        fscanf(data, "%s %s %d", name1, name2, &weight);
	}


    // Read in starting location
    fscanf(data, "%s", startLoc);
    fclose(data);

    int cost;
    cost = DRUNK_WALK(head, startLoc, tail->name);
    printf("Total Random Cost = %d\n\n", cost);

    cost = GREEDY_WALK(head, startLoc, tail->name, numOfNodes);
    if (cost != -1)  printf("Total Greedy Cost = %d\n\n", cost);

    DESTROY_GRAPH(&head);
    DESTROY_INDEX(&head, &tail);

    return 0;
}