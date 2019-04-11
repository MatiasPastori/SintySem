/*
 * automata.h
 *
 *  Created on: 28 mar. 2019
 *      Author: matup
 */

#ifndef LIB_AUTOMATA_H_
#define LIB_AUTOMATA_H_

#define col 7
#define row 7

#include <stdio.h>
#include <stdlib.h>

int readnwriteFile(FILE* ent, FILE* out, int sInfo[row][col]) {
	char c = '0';
	int state = 0;
	while ((c = fgetc(ent)) != EOF) {

		switch (c) {
		case '0': {
			state = sInfo[state][0];
			fprintf(out, "%c", c);
			break;
		}
		case '1' ... '7': {
			state = sInfo[state][1];
			fprintf(out, "%c", c);
			break;
		}
		case '8' ... '9': {
			state = sInfo[state][2];
			fprintf(out, "%c", c);
			break;
		}
		case 'a' ... 'f': {
			state = sInfo[state][3];
			fprintf(out, "%c", c);
			break;
		}
		case 'A' ... 'F': {
			state = sInfo[state][4];
			fprintf(out, "%c", c);
			break;
		}
		case 'x': {
			state = sInfo[state][5];
			fprintf(out, "%c", c);
			break;
		}
		case 'X': {
			state = sInfo[state][5];
			fprintf(out, "%c", c);
			break;
		}
		case ',': {
			switch (state) {
			case 1: {
				fprintf(out, "%s", "\tOctal\n");
				break;
			}
			case 2: {
				fprintf(out, "%s", "\tDecimal\n");
				break;
			}
			case 4: {
				fprintf(out, "%s", "\tHexadecimal\n");
				break;
			}
			case 5: {
				fprintf(out, "%s", "\tOctal\n");
				break;
			}
			case 6: {
				fprintf(out, "%s", "\tNo Reconocido\n");
				break;
			}
			}

			state = 0;
			break;

		}
		default: {
			state = sInfo[state][6];
			fprintf(out, "%c", c);
			break;
		}
		}
	}
	return state;
}

void finalState(int finalState, FILE* out) {
	switch (finalState) {
	case 1:
	case 4:
		fprintf(out, "%s", "\tHexadecimal\n");
		break;
	case 5:
		fprintf(out, "%s", "\tOctal\n");
		break;
	case 2:
		fprintf(out, "%s", "\tDecimal\n");
		break;
	case 0:
		break;
	default:
		fprintf(out, "%s", "\tNo Reconocido\n");
		break;
	}
}

void automata(FILE* ent, FILE* out) {

	int sInfo[row][col] = { { 1, 2, 2, 6, 6, 6, 6 }, { 5, 5, 6, 6, 6, 3, 6 }, {
			2, 2, 2, 6, 6, 6, 6 }, { 4, 4, 4, 4, 4, 6, 6 }, { 4, 4, 4, 4, 4, 6,
			6 }, { 5, 5, 6, 6, 6, 6, 6 }, { 6, 6, 6, 6, 6, 6, 6 }

	};

	int fs = readnwriteFile(ent, out, sInfo);
	finalState(fs, out);

}

#endif /* LIB_AUTOMATA_H_ */
