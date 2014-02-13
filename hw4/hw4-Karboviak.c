/*
 * File:   hw4-Karboviak.c
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char uchar;


uchar* Load_File(char *fileName, int *size) {
	FILE *inFile;
	inFile = fopen(fileName, "rb");
	if (inFile == NULL) {
		printf("\nUnable to open file: %s\n\n", fileName);
		exit (0);
	}

	// Determine File Size
	uchar temp;
	*size = 0;
	while (fscanf(inFile, "%c", &temp) == 1) {
		if (temp == 'A'| temp == 'T' | temp == 'G' | temp == 'C')  (*size)++;
	}

	rewind(inFile);

	// Create Dynamic uchar Array
	uchar *sequence;
	sequence = (uchar*) calloc(*size, sizeof(uchar));

	// Fill Array With Sequence
	*size = 0;
	while (fscanf(inFile, "%c", &temp) == 1) {
		if (temp == 'A'| temp == 'T' | temp == 'G' | temp == 'C') {
			sequence[*size] = temp;
			(*size)++;
		}
	}

	fclose(inFile);

	return sequence;
}


int Search_Sequence(uchar *dna, uchar *fasta, int dLength, int fLength, int *start, int *end) {
	int i, k;
	for (i = 0; i < dLength; i++) {
		k = 0;
		while (1) {
			if (i > dLength - fLength)   return -1;  // Last Point for Match
			if (fasta[k] != dna[i + k])  break;
			*start = i;
			if (k == fLength - 1) {
				*end = i + k;
				return 0;
			}
			k++;
		}
	}

	return -1;
}


int main(int argc, char** argv) {
	char error[] = "\n\
 ************************************************************\n\
 * HW4 ? provides help menu.                                *\n\
 ************************************************************\n\n";

	// Displays Help Menu
	if (argc != 5 && argc != 2) {
		printf("%s", error);
		exit (0);
	} else if (!strcmp(argv[1], "?")) {
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
	int forwardSize = atoi(argv[3]);    // Size of forward primer
	int reverseSize = atoi(argv[4]);    // Size of reverse primer

	uchar *dnaArray, *fastaArray;       // Dynamic Arrays of uchars
	int dnaLength, fastaLength;         // Length of Files
	dnaArray = Load_File(dnaFile, &dnaLength);        // Store DNA Sequence
	fastaArray = Load_File(fastaFile, &fastaLength);  // Store FASTA Sequence

	// Find the FASTA Sequence in DNA
	int start, end;  // Index values of FASTA Sequence in DNA
	if (Search_Sequence(dnaArray, fastaArray, dnaLength, fastaLength, &start, &end) == -1) {
		printf("\nFASTA sequence was not found in DNA sequence.\n\n");
		free(dnaArray);  free(fastaArray);
		printf("%d %d\n", dnaLength, fastaLength);
		printf("%d %d\n", start, end);
		exit (0);
	}
	printf("%d %d\n", start, end);

	free(dnaArray);  free(fastaArray);  // Free Dynamic Arrays
	return 0;
}