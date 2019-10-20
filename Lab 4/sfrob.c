#include <stdio.h>
#include <stdlib.h>

char deFrob(const char a);
int frobcmp(const char* a, const char* b);

int IOError(void)
{
  if(ferror(stdin))
  {
    fprintf(stderr, "I/O Error, leaving...\n");
    return 0;
  }
  return 1;
}

int convertFrob(const void* a, const void* b)
{
  // typecasts to double pointer to match totalWords
  const char* one = *(const char**)a;
  const char* two = *(const char**)b;
  return frobcmp(one, two);
}

int main(void)
{
  char* curW; // ptr to store strings of different sizes
  char** totalWords; // double ptr to store ptrs for curW

  curW = malloc(sizeof(char)); // allocate space for 1 char
  if(curW == NULL)
  {
    fprintf(stderr, "Mem Alloc Error!");
    exit(1);
  }
  totalWords = NULL; // no words entered yet
  int letters = 0; // letters in curW
  int wordNum = 0; // # of words in totalWords
  curW[letters] = getchar(); // get first character from stdin
  if(!IOError()){
    free(curW);
    exit(1);
  }

  while(curW[letters] != EOF && IOError())
  {
    char next = getchar();
    if(!IOError())
    {
      int i;
      free(curW);
      for(i = 0; i < wordNum; i++)
        free(totalWords[i]);
      free(totalWords);
      exit(1);
    }
  
  
    if(curW[letters] == ' ') // new word
    {
      char** temp = realloc(totalWords, wordNum*sizeof(char*) + sizeof(char*));
      if(temp != NULL)
      {
        totalWords = temp; // point toalWords to new space
        totalWords[wordNum] = curW; // last element of totalWords -> curW
        wordNum++;
        letters = -1; // next letter increment returns it to 0
        curW = malloc(sizeof(char));
      }
      else
      {
        free (curW);
        int i;
        for (i = 0; i < wordNum; i++)
          free(totalWords[i]);
        free(totalWords);
        fprintf(stderr, "Mem Alloc Error!\n");
        exit(1);
      }
    
      if(next == EOF)
        break;
      while (next == ' ')
      {
        next = getchar();
        IOError();
      }
    }
    else if(next == EOF) // curW not space, but next EOF
    {
      next = ' '; // add space if none added
    }
    letters++; // for curW
    char* temp = realloc(curW, letters*sizeof(char*) + sizeof(char*));
    if(temp != NULL)
    {
      curW = temp; 
      curW[letters] = next;
    }
    else 
    {
      int i;
      free(curW);
      for(i = 0; i < wordNum; i++)
        free(totalWords[i]);
      free(totalWords);
      fprintf(stderr, "Mem Alloc Error!\n");
      exit(1);
    }
  }

  qsort(totalWords, wordNum, sizeof(char*), convertFrob);
  int i;
  int j;
  //Write to stdout
  for(i = 0; i < wordNum; i++)
  {
    for(j = 0; totalWords[i][j] != ' '; j++)
    {
      printf("%c", totalWords[i][j]);
    }
    printf(" ");
  }

  //free mem and exit
  int n;
  for(n = 0; n < wordNum; i++)
    free(totalWords[n]);
  free(totalWords);
  free(curW);
  return 0;
}

     
char deFrob(const char a){
  return (a ^ 42); // memfrob simply XOR's the item with 
                     // 00101010, which is 0x2a in hex
                     // or 42 in int
}

int frobcmp(char const* a, char const* b){
    for(;; a++, b++)
    {
      while(*a == '\0')
        a++;
      while(*b == '\0')
        b++;
      if(*a == ' ' && *b == ' '){
        return 0;  // words ended simultaneously, considered equal
      }
      if(*a == ' ' || deFrob(*a) < deFrob(*b)){
        return -1; // a < b
      }
      if(*b == ' ' || deFrob(*a) > deFrob(*b)){
	return 1; // a > b
      }
    }
    
}

