/*
 * File:   hw5-Karboviak-find.h
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST1
	typedef unsigned char uchar;
#endif

int SearchSequence(uchar *dna, uchar *fasta, int dLength, int fLength, int *start, int *end);