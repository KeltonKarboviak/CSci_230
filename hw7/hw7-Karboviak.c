/***********************************/
/* CSci 230 HW #7                  */
/*                                 */
/* File:   hw7-Karboviak.c         */
/* Author: Kelton Karboviak        */
/***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************/
/* STRUCTS                                                  */
/************************************************************/
/* struct dNode is used to store the hw7data.txt file */
struct dNode {
    char *word;
    struct dNode *next;
};

/* struct cNode is used to store the hw7codex.txt file */
struct cNode {
    char *original, *new;
    struct cNode *next;
};

typedef struct dNode _dNode;
typedef struct cNode _cNode;

/************************************************************/
/* FUNCTIONS                                                */
/************************************************************/
void dInsert(_dNode *(*head), _dNode *(*tail), _dNode *(*newNode)) {
    if (*head == NULL)  (*head) = (*tail) = (*newNode);

    (*tail)->next = (*newNode);
    (*tail) = (*newNode);
    (*newNode)->next = NULL;
}


void cInsert(_cNode **head, _cNode **tail, _cNode **newNode) {
    if (*head == NULL)  (*head) = (*tail) = (*newNode);

    (*tail)->next = (*newNode);
    (*tail) = (*newNode);
    (*newNode)->next = NULL;
}


void dSearch() {

}


void cSearch() {

}


void removeNode(_dNode *(*node)) {
	_dNode *obsoleteNode = (_dNode*) malloc(sizeof(_dNode));
	obsoleteNode = (*node)->next;
	(*node)->next = (*node)->next->next;
	free(obsoleteNode->word);
	free(obsoleteNode);
	obsoleteNode = NULL;
}


void updateNode(_dNode *(*dNode), _cNode *(*cNode)) {
	(*dNode)->word = (char*) malloc( (strlen( (*cNode)->new ) + 1) * sizeof(char));
	strcpy((*dNode)->word, (*cNode)->new);
}


void correctPoem(_dNode *(*dHead), _dNode *(*dTail), _cNode *(*cHead), _cNode *(*cTail)) {
	_dNode *dCurrent = (_dNode*) malloc(sizeof(_dNode));
	_cNode *cCurrent = (_cNode*) malloc(sizeof(_cNode));

	dCurrent = (*dHead);
	cCurrent = (*cHead);
	while (dCurrent != NULL && cCurrent != NULL) {
		if (strcmp(cCurrent->original, cCurrent->new))  updateNode(&dCurrent, &cCurrent);
		if (cCurrent->next != NULL && !strcmp(cCurrent->next->new, "!")) {
			removeNode(&dCurrent);
			cCurrent = cCurrent->next;
		}


		dCurrent = dCurrent->next;
		cCurrent = cCurrent->next;
	}
}


void printPoem(_dNode **head) {
	_dNode *current = (_dNode*) malloc(sizeof(_dNode));
	current = (*head);
	while (current != NULL) {
		if (strstr(current->word, ",") != NULL || strstr(current->word, ".") != NULL)
			printf("%s\n", current->word);
		else
			printf("%s ", current->word);

		current = current->next;
	}
}


void destroyDataList(_dNode *(*head), _dNode *(*tail), _dNode *(*current)) {

}


void destroyCodexList(_cNode *(*head), _cNode *(*tail), _cNode *(*current)) {

}


/************************************************************/
/* MAIN                                                     */
/************************************************************/
int main(void) {
    // Open dataFile for reading
    FILE *dataFile;
    dataFile = fopen("./hw7data.txt", "r");
    // Trap file open error
    if (dataFile == NULL) {
		printf("\nUnable to open file!\n\n");
		exit (0);
	}

    // Store dataFile contents
    char *temp;
    temp = (char*) malloc(15 * sizeof(char));
    _dNode *dCurrent, *dHead, *dTail;
    dHead = dTail = NULL;
    while (1) {
        dCurrent = (_dNode*) malloc(sizeof(_dNode));
        fscanf(dataFile, "%s", temp);

        dCurrent->word = (char*) malloc( (strlen(temp) + 1) * sizeof(char) );
        strcpy(dCurrent->word, temp);
        dInsert(&dHead, &dTail, &dCurrent);

        if (feof(dataFile)) break;
    }

	// Free pointer
	free(dCurrent);  dCurrent = NULL;
    fclose(dataFile);


    // Open codexFile for reading
    FILE *codexFile;
    codexFile = fopen("./hw7codex.txt", "r");
    // Trap file open error
    if (dataFile == NULL) {
		printf("\nUnable to open file!\n\n");
		exit (0);
	}

    // Store codexFile contents
    int i;
    char *tempOld, *tempNew;
    tempOld = (char*) malloc(15 * sizeof(char));
    tempNew = (char*) malloc(15 * sizeof(char));
    _cNode *cCurrent, *cHead, *cTail;
    cHead = cTail = NULL;
    while (1) {
        temp = (char*) malloc(25 * sizeof(char));
        cCurrent = (_cNode*) malloc(sizeof(_cNode));
        fscanf(codexFile, "%s", temp);

        // Parse paired words by '|'
        for (i = 0; i < 2; i++) {
            if (i == 0) tempOld = strsep(&temp, "|");
            else        tempNew = strsep(&temp, "|");
        }

        cCurrent->original = (char*) malloc( (strlen(tempOld) + 1) * sizeof(char) );
        cCurrent->new      = (char*) malloc( (strlen(tempNew) + 1) * sizeof(char) );
        strcpy(cCurrent->original, tempOld);
        strcpy(cCurrent->new,      tempNew);
        cInsert(&cHead, &cTail, &cCurrent);

        if (feof(codexFile)) break;
    }

	// Free pointers
	free(temp);  free(tempOld);  //free(tempNew);  // ERROR ERROR ERROR ERROR ERROR ERROR
	free(cCurrent); cCurrent = NULL;
    fclose(codexFile);

	printPoem(&dHead);
	printf("*******************************************\n");
	// Correct the poem
	correctPoem(&dHead, &dTail, &cHead, &cTail);

	// Print the poem
	printPoem(&dHead);



    destroyDataList(&dHead, &dTail, &dCurrent);
    destroyCodexList(&cHead, &cTail, &cCurrent);
    return 0;
}