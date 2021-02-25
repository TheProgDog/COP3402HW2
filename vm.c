#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


typedef enum { 
modsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
multsym = 6, slashsym = 7, oddsym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18,
periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, 
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym = 25, elsesym = 26, returnsym = 27} token_type;

void main()
{
	FILE *input = fopen("input.txt", "r");


}