/*
 * File:   hw5-Karboviak-load.h
 * Author: Kelton Karboviak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST1
	typedef unsigned char uchar;
#endif

uchar* LoadFile(char *fileName, int *size);