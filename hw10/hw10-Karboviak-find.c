/*
 * File:   hw10-Karboviak-find.c
 * Author: Kelton Karboviak
 */

#include "./hw10-lib-Karboviak.h"


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