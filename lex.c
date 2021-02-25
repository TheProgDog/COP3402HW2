#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

typedef enum token_type{
modsym = 1,
identsym,
numbersym,
plussym,
minussym,
multsym,
slashsym,
oddsym,
eqsym,
neqsym,
lessym,
leqsym,
gtrsym,
geqsym,
lparentsym,
rparentsym,
commasym,
semicolonsym,
periodsym,
becomessym,
beginsym,
endsym,
ifsym,
thensym,
whilesym,
dosym,
callsym,
constsym,
varsym,
procsym,
writesym,
readsym,
elsesym,
returnsym
} token_type;

int CheckTokenNum(char*);

bool currentlyVar = false;

int main(int argc, char *args[])
{
  char word[100];

  char *tokenList = "";

  FILE *input = fopen(args[1], "r");

  bool isComment = false;

  printf("\n\nLexeme Table:\n\tLexeme\t\ttoken type\n");

  while (!feof(input))
  {
    fscanf(input, "%s", word);

    int stringLength = (int)strlen(word), token = 0;


    // ERROR HANDLING HERE
    if (stringLength > 11)
      printf("Error : Identifier names cannot exceed 11 characters");


    // end error handling

    // Push the pointer back by one if "var" name ends with , or ; or something similar
    if (stringLength >= 2)
    {
      switch (word[stringLength - 1])
      {
        case ',':
        case ';':
        case '.':
          word[stringLength - 1] = 0;
          fseek(input, -1, SEEK_CUR);
          stringLength = (int)strlen(word);
          break;
        default:
          break;
      }
    }

    if (strcmp(word, "/*") == 0)
      isComment = true;

    if (!isComment)
    {
      // oh no here comes the big ladder
      token = CheckTokenNum(word);
      printf("\t%s\t\t%d\n", word, token);

      strcat(tokenList, (char)token);
    }

    else if (strcmp(word, "*/") == 0)
      isComment = false;

  }

  fclose(input);

  return 0;
}

int CheckTokenNum(char *word)
{
  // this is really ugly I'm not a fan of this but idk what else to do don't sue me
    if (strcmp(word, "%") == 0)
    {
      return 1;
    }
    else if (strcmp(word, "+") == 0)
    {
      return 4;
    }
    else if (strcmp(word, "-") == 0)
    {
      return 5;
    }
    else if (strcmp(word, "*") == 0)
    {
      return 6;
    }
    else if (strcmp(word, "/") == 0)
    {
      return 7;
    }
    else if (strcmp(word, "odd") == 0)
    {
      return 8;
    }
    else if (strcmp(word, "=") == 0)
    {
      return 9;
    }
    else if (strcmp(word, "<>") == 0)
    {
      return 10;
    }
    else if (strcmp(word, "<") == 0)
    {
      return 11;
    }
    else if (strcmp(word, "<=") == 0)
    {
      return 12;
    }
    else if (strcmp(word, ">") == 0)
    {
      return 13;
    }
    else if (strcmp(word, ">=") == 0)
    {
      return 14;
    }
    else if (strcmp(word, "(") == 0)
    {
      return 15;
    }
    else if (strcmp(word, ")") == 0)
    {
      return 16;
    }
    else if (strcmp(word, ",") == 0)
    {
      return 17;
    }
    else if (strcmp(word, ";") == 0)
    {
      currentlyVar = false;
      return 18;
    }
    else if (strcmp(word, ".") == 0)
    {
      return 19;
    }
    else if (strcmp(word, ":=") == 0)
    {
      return 20;
    }
    else if (strcmp(word, "begin") == 0)
    {
      return 21;
    }
    else if (strcmp(word, "end") == 0)
    {
      return 22;
    }
    else if (strcmp(word, "if") == 0)
    {
      return 23;
    }
    else if (strcmp(word, "then") == 0)
    {
      return 24;
    }
    else if (strcmp(word, "while") == 0)
    {
      return 25;
    }
    else if (strcmp(word, "do") == 0)
    {
      return 26;
    }
    else if (strcmp(word, "call") == 0)
    {
      return 27;
    }
    else if (strcmp(word, "const") == 0)
    {
      return 28;
    }
    else if (strcmp(word, "var") == 0)
    {
      currentlyVar = true;
      return 29;
    }
    else
    {
      if (currentlyVar)
        return 2;

      if (isdigit(word[(int)strlen(word) - 1]))
        return 3;

    }
}
