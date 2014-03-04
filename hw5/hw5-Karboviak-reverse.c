/*
 * File:   hw5-Karboviak-reverse.c
 * Author: Kelton Karboviak
 */

 #include "./hw5-Karboviak-reverse.h"


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