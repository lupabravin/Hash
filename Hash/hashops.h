
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define TAM 11
#define NIL -1

typedef struct hash {
	int hashCode;
	int code[2];
	int fileRRN[2];

} Hash;


int insertHash(int key, int fileRRN);
void initHash();