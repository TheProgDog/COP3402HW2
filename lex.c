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
bool EndOfWord(char);
bool IsReserved(char*);
bool IsVar(char*);

bool currentlyVar = false;

char *reservedWords[] = {
  "const",
  "var",
  "procedure",
  "call",
  "if",
  "then",
  "else",
  "while",
  "do",
  "read",
  "write",
  "odd",
  "return",
  "begin",
  "end"
};

char *varWords[11];

int main(int argc, char *args[])
{
  // initialize varWords
  for (int i = 0; i < 15; i++)
  {
    varWords[i] = malloc(11 * sizeof(char));
  }


  char character;
  char futureChar;

  char *tokenList = "";
  char word[50];

  int wordCounter = 0, varCount = 0;

  bool isComment = false;
  bool wordFound = false;

  FILE *input = fopen(args[1], "r");

  memset(word, 0, sizeof(word));

  printf("\n\nLexeme Table:\n\tLexeme\t\ttoken type\n");

  while (!feof(input))
  {
    fscanf(input, "%c", &character);

    if((iscntrl(character) || EndOfWord(character)) && wordCounter > 0)
    {
      wordCounter = 0;

      if (!isComment)
      {
        // This is a reserved word
        if (IsReserved(word))
        {
          //printf("Reserved word: %s\n", word);
        }
        else if (!isdigit(character))
        {
          // This is a reserved variable already
          if (varCount > 0 && IsVar(word))
          {
            //printf("Reserved var: %s\n", word);
          }
          else if (!(strcmp(word, " ") == 0))
          {
            // This is a new variable
            //printf("New var: %s\n", word);
            strcpy(varWords[varCount], word);
            varCount++;
          }
        }

        // Recognize special character
        if (EndOfWord(character) && character != ' ')
        {
          //printf("Special character: %c\n", character);
        }

        wordFound = true;
      }
    }
    else if (wordCounter == 0 && EndOfWord(character) && character != ' ')
    {
      // Handle special, SPECIAL characters here
      // like /*, */, >=, := etc.

      if (character == '/')
      {
        fscanf(input, "%c", &futureChar);
        if (futureChar == '*')
          isComment = true;
        else
          fseek(input, -1, SEEK_CUR);
      }
      else if (character == '*')
      {
        fscanf(input, "%c", &futureChar);
        if (futureChar == '/')
          isComment = false;
        else
        {
          //printf("Special character: %c\n", character);
          fseek(input, -1, SEEK_CUR);
        }
      }
      else if (character == ':')
      {
        fscanf(input, "%c", &futureChar);
        if (futureChar == '=')
        {
          token = CheckTokenNum(futureChar);

          printf("\t%s\t\t%d\n", futureChar, token);
        }
        else
          fseek(input, -1, SEEK_CUR);
      }
      else if (character == '<')
      {
        fscanf(input, "%c", &futureChar);
        if (futureChar == '>' || futureChar == '=')
        {
          token = CheckTokenNum(futureChar);

          printf("\t%s\t\t%d\n", futureChar, token);
        }
        else
          fseek(input, -1, SEEK_CUR);
      }
      else if (character == '>')
      {
        fscanf(input, "%c", &futureChar);
        if (futureChar == '=')
        {
          token = CheckTokenNum(futureChar);

          printf("\t%s\t\t%d\n", futureChar, token);
        }
        else
          fseek(input, -1, SEEK_CUR);
      }
      else
      {
        printf("Special character AAAAAAAAA: %c\n", character);
      }

    }
    else
    {
      // Add to the word here
      if (isalpha(character))
      {
        word[wordCounter] = character;
        wordCounter++;
      }
      else if (!iscntrl(character) && character != ' ')
      {
        printf("Number: %c\n", character);
      }
    }

    int stringLength = 0, token = 0;

    // ERROR HANDLING HERE

    if (wordFound)
    {
      // Here comes the big ladder
      token = CheckTokenNum(word);

      printf("\t%s\t\t%d\n", word, token);

      if (strcmp(word, "end") == 0)
      {
        break;
      }

      // Reset word
      memset(word, 0, sizeof(word));
      wordFound = false;
    }


  }

  fclose(input);

  return 0;
}

bool EndOfWord(char character)
{
  char specialCharacters[] = {
    ' ',
    '+',
    '-',
    '*',
    '/',
    '(',
    ')',
    '=',
    ',',
    '.',
    '<',
    '>',
    ';',
    ':',
    '%'
  };

  for (int i = 0; i < strlen(specialCharacters); i++)
  {
    if (character == specialCharacters[i])
      return true;
  }

  return false;
}

bool IsReserved(char *word)
{
  for (int i = 0; i < 15; i++)
  {
    if (strcmp(word, reservedWords[i]) == 0)
      return true;
  }

  return false;
}

bool IsVar(char *word)
{
  for (int i = 0; i < 15; i++)
  {
    //printf("\t\t%d. %s\n", i+1, varWords[i]);
    if (strcmp(word, varWords[i]) == 0)
      return true;
  }

  return false;
}

int CheckTokenNum(char *word)
{
  // this is really ugly I'm not a fan of this but idk what else to do don't sue me
  if (strcmp(word, "%") == 0)
    return 1;
  else if (strcmp(word, "+") == 0)
    return 4;
  else if (strcmp(word, "-") == 0)
    return 5;
  else if (strcmp(word, "*") == 0)
    return 6;
  else if (strcmp(word, "/") == 0)
    return 7;
  else if (strcmp(word, "odd") == 0)
    return 8;
  else if (strcmp(word, "=") == 0)
    return 9;
  else if (strcmp(word, "<>") == 0)
    return 10;
  else if (strcmp(word, "<") == 0)
    return 11;
  else if (strcmp(word, "<=") == 0)
    return 12;
  else if (strcmp(word, ">") == 0)
    return 13;
  else if (strcmp(word, ">=") == 0)
    return 14;
  else if (strcmp(word, "(") == 0)
    return 15;
  else if (strcmp(word, ")") == 0)
    return 16;
  else if (strcmp(word, ",") == 0)
    return 17;
  else if (strcmp(word, ";") == 0)
  {
    currentlyVar = false;
    return 18;
  }
  else if (strcmp(word, ".") == 0)
    return 19;
  else if (strcmp(word, ":=") == 0)
    return 20;
  else if (strcmp(word, "begin") == 0)
    return 21;
  else if (strcmp(word, "end") == 0)
    return 22;
  else if (strcmp(word, "if") == 0)
    return 23;
  else if (strcmp(word, "then") == 0)
    return 24;
  else if (strcmp(word, "while") == 0)
    return 25;
  else if (strcmp(word, "do") == 0)
    return 26;
  else if (strcmp(word, "call") == 0)
    return 27;
  else if (strcmp(word, "const") == 0)
    return 28;
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
