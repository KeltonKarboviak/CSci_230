/*
 * File:   hw8-Karboviak.c
 * Author: Kelton Karboviak
 *
 * Version: April , 2014
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
    struct connection* connects[10];
    int count;
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

typedef struct graph gNode;
typedef struct connection link;
typedef struct index iNode;


/************************************************************/
/* FUNCTIONS                                                */
/************************************************************/
void PRINT_INDEX(iNode *head) {  //TEST TEST TEST
    iNode *current;
    current = head;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}


/*******************************************************************/
void PRINT_GRAPH(iNode *head) {  // TEST TEST TEST
    iNode *current;
    current = head;
    gNode *gPtr;
    int i;
    while (current != NULL) {
        gPtr = current->graphPtr;
        for (i = 0; i < gPtr->count; i++) {
            printf("From %s to %s is %d\n", gPtr->name, gPtr->connects[i]->dest->name, gPtr->connects[i]->weight);
        }

        current = current->next;
    }
}


/********************************************************/
/* SEARCH INDEX LINKED-LIST                             */
/********************************************************/
iNode* SEARCH_INDEX(iNode *head, char searchName[]) {
    iNode *current;
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
void CREATE_GRAPH_NODE(gNode *(*newNode), char name[]) {
    (*newNode) = (gNode*) malloc(sizeof(gNode));
    (*newNode)->name = (char*) calloc(sizeof(char), strlen(name));
    strcpy((*newNode)->name, name);
    (*newNode)->count = 0;
}


/********************************************************/
/* INSERT ARC INTO GRAPH                                */
/********************************************************/
void INSERT_ARC(iNode *head, char name1[], char name2[], int weight) {
#define gPtr1 start->graphPtr
#define gPtr2 end->graphPtr
    // Find first establishment in the index
    iNode *start = SEARCH_INDEX(head, name1);
    // Check to see if the graphPtr hasn't been created
    if (gPtr1 == NULL)  CREATE_GRAPH_NODE(&gPtr1, name1);

    // Find second establishment in the index
    iNode *end   = SEARCH_INDEX(head, name2);
    // Check to see if the graphPtr hasn't been created
    if (gPtr2 == NULL)  CREATE_GRAPH_NODE(&gPtr2, name2);


    // Create one-way link from start to end
    gPtr1->connects[gPtr1->count] = (link*) malloc(sizeof(link));
    gPtr1->connects[gPtr1->count]->dest   = gPtr2;
    gPtr1->connects[gPtr1->count]->weight = weight;
    (gPtr1->count)++;
}


/********************************************************/
/* INSERT INTO INDEX LINKED-LIST.                       */
/********************************************************/
void INSERT_INDEX(iNode *(*head), iNode *(*tail), char name[]) {
	iNode *newNode;
	newNode = (iNode*) malloc(sizeof(iNode));
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
int DRUNK_WALK(iNode *head, char start[]) {
    srand(50);
    int total = 0, random;
    // Find starting establishment's graph node
    gNode *current = SEARCH_INDEX(head, start)->graphPtr;
    printf("Starting at %s\n", current->name);

    while (strcmp(current->name, "Home")) {
        printf("Visiting %s\n", current->name);
        random = rand() % current->count;
        printf("\tcost = %d\n", current->connects[random]->weight);
        total += current->connects[random]->weight;
        current = current->connects[random]->dest;
    }

    printf("You made it Home!!!\n");
    return total;
}


/********************************************************/
/* GREEDY WALK ALGORITHM                                */
/********************************************************/
int GREEDY_WALK(iNode *head, char start[]) {
    int total = 0;
    return total;
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

    iNode *head, *tail;
    head = tail = NULL;
    char name1[100], name2[100], startLoc[100];
    int weight;

    // Read in establishments
    fscanf(data, "%s", name1);
    while (strcmp(name1, "STOP")) {
        INSERT_INDEX(&head, &tail, name1);
        fscanf(data, "%s", name1);
    }
    PRINT_INDEX(head);  // TEST TEST TEST

    // Read in connections
    fscanf(data, "%s %s %d", name1, name2, &weight);
	while (strcmp(name1, "STOP") && strcmp(name2, "STOP")) {
        INSERT_ARC(head, name1, name2, weight);
        fscanf(data, "%s %s %d", name1, name2, &weight);
	}
    PRINT_GRAPH(head);  // TEST TEST TEST

    // Read in starting location
    fscanf(data, "%s", startLoc);

    int cost;
    cost = DRUNK_WALK(head, startLoc);
    printf("Total Cost = %d\n", cost);

    return 0;
}
