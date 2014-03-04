/*
 * File:   hw5-Karboviak-load.c
 * Author: Kelton Karboviak
 */

#include "hw5-Karboviak-load.h"


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