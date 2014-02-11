/*
 * File:   hw4-Karboviak.c
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char uchar;


int Load_File(char *fileName, uchar *sequence) {
	FILE *inFile;
	inFile = fopen(fileName, "rb");
	if (inFile == NULL) {
		printf("\nUnable to open file: %s\n\n", fileName);
		exit (0);
	}

	uchar temp;
	int count = 0;
	while (fscanf(inFile, "%c", &temp) == 1) {
		if (temp == 'A'| temp == 'T' | temp == 'G' | temp == 'C') {
			if (count % 70 == 0)  printf("\n");
			printf("%c", temp);
			count++;
		}
	}
	printf("\n\n");

	fclose(inFile);
	return 0;
}


int main(int argc, char** argv) {
	char error[] = "\n\
 ************************************************************\n\
 * HW4 ? provides help menu.                                *\n\
 ************************************************************\n\n";

	// Displays Help Menu
	if (!strcmp(argv[1], "?")) {
		printf("\n");
 		printf(" ************************************************************\n");
 		printf(" * HW4 Help Menu.                                           *\n");
 		printf(" *                                                          *\n");
		printf(" * HW4 will fail to start if no command line arguments are  *\n");
		printf(" * provided. To get this help menu start AADS as follows:   *\n");
		printf(" * ./HW4 ?                                                  *\n");
		printf(" *                                                          *\n");
		printf(" * Required command line arguments include:                 *\n");
		printf(" * ./HW4 DNA_file FASTA_file Forward_count Reverse_count    *\n");
 		printf(" *                                                          *\n");
	 	printf(" ************************************************************\n");
	 	printf("\n");
		exit (0);
	} else if (argc != 5) {
		printf("%s", error);
		exit (0);
	}

	// Validate 3rd and 4th arguments as integers
	char *ptr;
	int i, k, length;
	for (i = 3; i < 5; i++) {
		ptr = argv[i];
		length = strlen(argv[i]);
		for (k = 0; k < length; k++) {
			if (!isdigit(*ptr)) {
				printf("%s", error);
				exit (0);
			}
			ptr++;
		}
	}

	char dnaFile[strlen(argv[1])];    strcpy(dnaFile, argv[1]);    // DNA Filename
	char fastaFile[strlen(argv[2])];  strcpy(fastaFile, argv[2]);  // FASTA Filename
	int forwardSize = atoi(argv[3]);   // Size of forward primer
	int reverseSize = atoi(argv[4]);   // Size of reverse primer

	uchar *dnaArray, *fastaArray;      // Dynamic Arrays of Sequences
	Load_File(dnaFile, dnaArray);      // Store DNA Sequence
	Load_File(fastaFile, fastaArray);  // Store FASTA Sequence


	free(dnaArray);  free(fastaArray);  // Free Dynamic Arrays
	return 0;
}