/*
 * File:   midterm-Karboviak.c
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* LoadFile(char *fileName, int *size) {
	FILE *inFile;
	inFile = fopen(fileName, "r");
	if (inFile == NULL) {
		printf("\nUnable to open file: %s\n\n", fileName);
		exit (0);
	}

	// Determine File Size
	char temp;
	*size = 0;
	while (fscanf(inFile, "%c", &temp) == 1) {
		(*size)++;
	}

	rewind(inFile);

	// Create Dynamic char Array
	char *sequence;
	sequence = (char*) calloc(*size, sizeof(char));

	// Fill Array With Sequence
	*size = 0;
	while (fscanf(inFile, "%c", &temp) == 1) {
		sequence[*size] = temp;
		(*size)++;
	}

	fclose(inFile);

	return sequence;
}


int SearchFile(char *text, int length, char *searchWord, char *flag) {
	int i, j, start, index = -1;
	for (i = 0; i < length; i++) {
		for (j = 0; j < strlen(searchWord); j++) {
			if (searchWord[j] != text[i + j])  break;
			start = i;

			if (j == strlen(searchWord) - 1) {
				if (!strcmp("first", flag))  return start;
				else                         index = start;
			}
		}
	}

	return index;
}


int main(int argc, char** argv) {
	char error[] = "\n\
 ************************************************************\n\
 * MIDTERM ? provides help menu.                            *\n\
 ************************************************************\n\n";

	// Displays Help Menu
	if (argc != 4 && argc != 2) {
		printf("%s", error);
		exit (0);
	} else if (argc == 2) {
		if (!strcmp(argv[1], "?")) {
			printf("\n");
 			printf(" ************************************************************\n");
	 		printf(" * MIDTERM Help Menu.                                       *\n");
 			printf(" *                                                          *\n");
			printf(" * MIDTERM will fail to start if no command line arguments  *\n");
			printf(" * are provided. To get this help menu start MIDTERM as     *\n");
			printf(" * follows: ./MIDTERM ?                                     *\n");
			printf(" *                                                          *\n");
			printf(" * Required command line arguments include:                 *\n");
			printf(" * ./MIDTERM TEXT_file string_to_search_for search_flag     *\n");
 			printf(" *                                                          *\n");
		 	printf(" ************************************************************\n");
		 	printf("\n");
			exit (0);
		} else {
			printf("%s", error);
			exit(0);
		}
	}

	if (strcmp(argv[3], "first") && strcmp(argv[3], "last")) {
		printf("%s", error);
		exit(0);
	}

	char *text;                         // Dynamic Array of chars
	int length;                         // Length of File
	text = LoadFile(argv[1], &length);  // Store text file

	int index = SearchFile(text, length, argv[2], argv[3]);

	if (index != -1)  printf("\nSUCCESS - String found in file starting at character: %d\n\n", index);
	else              printf("\nERROR - String not found in file.\n\n");


	free(text);  text = NULL;
	return 0;
}
