/*
 * File:   hw10-Karboviak-forward.c
 * Author: Kelton Karboviak
 */

#include "./hw10-lib-Karboviak.h"


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