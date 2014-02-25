/*
 * File:   hw4-Karboviak.c
 * Author: Kelton Karboviak
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char uchar;


/* Loads the passed in file into a dynamic array.
 * Returns the dynamic array.
 */
uchar* LoadFile(char *fileName, int *size) {
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


/* Searches the DNA Sequence for the matching FASTA Sequence.
 * start & end variables are passed in by reference and will be used later for the match indexes
 * Returns 0 if match is found, -1 if match is not found.
 */
int SearchSequence(uchar *dna, uchar *fasta, int dLength, int fLength, int *start, int *end) {
	int i, k;
	for (i = 0; i < dLength; i++) {
		k = 0;
		while (1) {
			if (i > dLength - fLength)   return -1;  // Last Point for Match
			if (fasta[k] != dna[i + k])  break;
			*start = i;
			if (k == fLength - 1) {  // A match has been found in DNA
				*end = i + k;
				return 0;
			}
			k++;
		}
	}

	return -1;
}


/* Determines and prints out the forward primer.
 * Returns 0 if the action was performed successfully, -1 if the primer went out of bounds
 */
int DisplayForwardPrimer(uchar *dna, int dnaSize, int length, int start, int count) {
	if (start - (count / 2) < 0)  return -1;  // Primer Would Be Out of Bounds

	int i, k = start - (count/2);
	printf("\n Foward Primer : ");
	for (i = k; i < k + count; i++) {
		printf("%c", dna[i]);
	}   printf("\n\n");

	return 0;
}


/* Determines and prints out the reverse primer.
 * Returns 0 if the action was performed successfully, -1 if the primer went out of bounds
 */
int DisplayReversePrimer(uchar *dna, int dnaSize, int length, int end, int count) {
	if (end + (count / 2) > dnaSize)  return -1;  // Primer Would Be Out of Bounds

	int i, k = end + (count/2);
	printf("\n Reverse Primer : ");
	for (i = k; i > k - count; i--) {
		if      (dna[i] == 'A')  printf("%c", 'T');
		else if (dna[i] == 'T')  printf("%c", 'A');
		else if (dna[i] == 'G')  printf("%c", 'C');
		else if (dna[i] == 'C')  printf("%c", 'G');
	}   printf("\n\n");

	return 0;
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
			if (!isdigit(*ptr)) {      // Print error and exit if a char is not an integer
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
	dnaArray = LoadFile(dnaFile, &dnaLength);        // Store DNA Sequence
	fastaArray = LoadFile(fastaFile, &fastaLength);  // Store FASTA Sequence

	// Find the FASTA Sequence in DNA
	int start = 0, end = 0;  // Index values of FASTA Sequence in DNA
	if (SearchSequence(dnaArray, fastaArray, dnaLength, fastaLength, &start, &end) == -1) {
		printf("\n");
		printf(" ************************************************************\n");
 		printf(" * FASTA sequence was not found in DNA sequence.            *\n");
 		printf(" ************************************************************\n");
 		printf("\n");
		free(dnaArray);  free(fastaArray);   // Free Dynamic Arrays
		dnaArray = NULL; fastaArray = NULL;  // Set pointers equal to NULL for safety
		exit (0);
	}


	// Display Forward & Reverse Primers
	if (DisplayForwardPrimer(dnaArray, dnaLength, fastaLength, start, forwardSize) == -1) {
		printf("\n");
		printf(" ************************************************************\n");
 		printf(" * Forward Primer count went out of array bounds.           *\n");
 		printf(" ************************************************************\n");
		printf("\n");
	}
	if (DisplayReversePrimer(dnaArray, dnaLength, fastaLength, end, reverseSize) == -1) {
		printf("\n");
		printf(" ************************************************************\n");
 		printf(" * Reverse Primer count went out of array bounds.           *\n");
 		printf(" ************************************************************\n");
		printf("\n");
	}


	free(dnaArray);  free(fastaArray);   // Free Dynamic Arrays
	dnaArray = NULL; fastaArray = NULL;  // Set pointers to "safe" location
	return 0;
}
