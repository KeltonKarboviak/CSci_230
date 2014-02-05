/*
 * File:   hw3-Karboviak.c
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>


/*  Simple Bubble Sort */
void bubbleSort(int *data, int size)  {
	int i, k, temp;

	for (i = size - 1; i >= 0; i--) {
		for (k = 0; k <= i - 1; k++) {
			if (data[k] > data[k+1]) {
				temp = data[k];
				data[k] = data[k+1];
				data[k+1] = temp;
			}
		}
	}
}


int main(void) {
	// Determine File Sizes
	int size, num, i;
	FILE *inFile;

	size = 0;
	for (i = 0; i < 3; i++) {
		if (i == 0)       inFile = fopen("list0.txt", "r");
		else if (i == 1)  inFile = fopen("list1.txt", "r");
		else              inFile = fopen("list2.txt", "r");

		while (fscanf(inFile, "%d", &num) == 1) {
			size++;
		}

		fclose(inFile);
	}


	// Create Dynamic Int Array
	int *numberSet;
	numberSet = calloc(size, sizeof(int));
	if (numberSet == NULL) return 0;  // Return if memory was not successfully allocated


	// Fill Array With Numbers
	size = 0;
	for (i = 0; i < 3; i++) {
		if (i == 0)       inFile = fopen("list0.txt", "r");
		else if (i == 1)  inFile = fopen("list1.txt", "r");
		else              inFile = fopen("list2.txt", "r");

		while (fscanf(inFile, "%d", &numberSet[size]) == 1) {
			size++;
		}

		fclose(inFile);
	}


	// Sort The Numbers
	bubbleSort(numberSet, size);


	// Write Numbers To Output File
	FILE *outFile;
	outFile = fopen("hw3.out", "w");

	for (i = 0; i < size; i++) {
		fprintf(outFile, "%d\n", numberSet[i]);
	}

	fclose(outFile);
	free(numberSet);

	return 0;
}