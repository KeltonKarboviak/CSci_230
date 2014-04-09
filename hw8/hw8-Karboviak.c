/*
 * File:   hw8-Karboviak.c
 * Author: Kelton Karboviak
 *
 * Version: April , 2014
 */


#include <stdio.h>
#include <stdlib.h>


struct graph {
    char *name;
    struct graph connections[10];
    int count;
};

struct index {
    char *name;
    struct graph *graphPtr;
    struct index *next;
};

typedef struct graph gNode;
typedef struct graph iNode;


void INSERT_INDEX(iNode *(*head), iNode *(*tail), char name[]) {
	iNode *newNode;
	newNode = (iNode*) malloc(sizeof(iNode));
	newNode->name = (char*) calloc(sizeof(char), strlen(name));
	strcpy(newNode->name, name);

	if ((*head) == NULL)  (*head) = (*tail) = (*newNode);

    (*tail)->next = (*newNode);
    (*tail) = (*newNode);
    (*newNode)->next = NULL;
}



int main(void) {
    // Open data file
    FILE *data;
    if ((data = fopen("./hw8data.txt", "r")) == NULL) {
        printf("ERROR - hw8data.txt could not be opened.\n");
        exit (0);
    }

    iNode *head, *tail;
    head = tail = NULL;
    char name1[100], name2[100];

    // Read in establishments
    while (strcmp(name1, "STOP")) {
        fscanf(data, "%s", name1);
        INSERT_INDEX(&head, &tail, name1);
    }

    // Read in connections
	while (strcmp(name1, "STOP") && strcmp(name2, "STOP")) {



	}

    return 0;
}
