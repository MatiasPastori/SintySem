/*
 ============================================================================
 Name        : TP1.c
 Author      : Matias Pastori
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/automata.h"

int main(void) {

	FILE* ent = fopen("Entry.txt", "r");
	FILE* out = fopen("Results.txt", "w");

	automata(ent, out);

	fclose(ent);
	fclose(out);
	printf(
			"Felicidades, su archivo se encuentra en el directorio del proyecto\n");

	return 0;
}
