/*
 * File:   hw10-Karboviak-main.c
 * Author: Kelton Karboviak
 */

#define TEST1


#include "./hw10-Karboviak-main.h"
#include "./hw10-lib-Karboviak.h"


int main(int argc, char** argv) {
	char error[] = "\n\
 ************************************************************\n\
 * hw10 ? provides help menu.                               *\n\
 ************************************************************\n\n";

	// Displays Help Menu
	if (argc != 5 && argc != 2) {
		printf("%s", error);
		exit (0);
	} else if (!strcmp(argv[1], "?")) {
		printf("\n");
 		printf(" ************************************************************\n");
 		printf(" * hw10 Help Menu.                                          *\n");
 		printf(" *                                                          *\n");
		printf(" * hw10 will fail to start if no command line arguments are *\n");
		printf(" * provided. To get this help menu start AADS as follows:   *\n");
		printf(" * ./hw10 ?                                                 *\n");
		printf(" *                                                          *\n");
		printf(" * Required command line arguments include:                 *\n");
		printf(" * ./hw10 DNA_file FASTA_file Forward_count Reverse_count   *\n");
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