/***********************************/
/* File:   hw6-Karboviak.c         */
/* Author: Kelton Karboviak        */
/***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
	char fname[20];
	char lname[20];
	int startBlock;
};

struct phoneNumber {
	char number[10];
	int nextBlock;
};


int Search_Contacts() {


	return 0;
}

/*  Removes the specified contact from the directory if it is in the list.
 *  returns 0 if successful, -1 if unsuccessful.
 */
int Remove_Contact() {


	return 0;
}

/*  Adds the specified contact to the directory if it is not in the list.
 *  returns 0 if successful, -1 if unsuccessful.
 */
int Add_Contact(char *fname, char *lname, int N, char **numbers) {


	return 0;
}


int main(void) {
	// Open file for reading
	char fileName[] = "./hw6data.txt";
	FILE *inFile;
	inFile = fopen(fileName, "r");
	if (inFile == NULL) {
		printf("\nUnable to open file: %s\n\n", fileName);
		exit (0);
	}

	// Create struct arrays
	struct contact     DIRECTORY[10];    // Array of contact structs
	struct phoneNumber NUMBER_LIST[50];  // Array of phoneNumber structs


	int i;
	// Initialize DIRECTORY with -1 (indicates free block)
	for (i = 0; i < 10; i++) {
		DIRECTORY[i].startBlock = -1;
	}

	// Initialize NUMBER_LIST with -1 (indicates free block)
	for (i = 0; i < 50; i++) {
		NUMBER_LIST[i].nextBlock = -1;
	}

	// Check inFile contents
	char status, fname[20], lname[20];
	char **temp;  // Temporary dynamic array to hold multiple numbers
	int N;        // number of phone numbers for 1 contact
	do {
		fscanf(inFile, "%c", &status);

		if (status == 'I') {        // Add a contact
			fscanf(inFile, "%s %s %d", fname, lname, &N);
			// Create 2D dynamic char array for phone numbers
			temp = (char**) calloc(N, sizeof(*temp));  // Creates a column of pointers
			for (i = 0; i < N; i++) {
				temp[i] = (char*) calloc(10, sizeof(char));  // Create a row of chars
			}

			// Store N numbers in dynamic array
			for (i = 0; i < N; i++) {
				fscanf(inFile, "%s", temp[i]);
			}
			for (i = 0; i < N; i++) {
				printf("%s\n", temp[i]);
			}

			Add_Contact(fname, lname, N, temp);
		}
		else if (status == 'R') {  // Remove a contact

		}

	} while (status != 'Q');

	printf("\nDONE !!!\n");

	fclose(inFile);
	return 0;
}