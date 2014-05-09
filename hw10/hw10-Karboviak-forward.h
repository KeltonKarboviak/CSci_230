/*
 * File:   hw10-Karboviak-forward.h
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TEST1
	typedef unsigned char uchar;
#endif

int DisplayForwardPrimer(uchar *dna, int dnaSize, int length, int start, int count);