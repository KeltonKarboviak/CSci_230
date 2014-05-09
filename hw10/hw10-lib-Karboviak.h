/*
 * File:   hw10-lib-Karboviak.h
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TEST1
	typedef unsigned char uchar;
#endif


uchar* LoadFile(char *fileName, int *size);
int SearchSequence(uchar *dna, uchar *fasta, int dLength, int fLength, int *start, int *end);
int DisplayForwardPrimer(uchar *dna, int dnaSize, int length, int start, int count);
int DisplayReversePrimer(uchar *dna, int dnaSize, int length, int end, int count);