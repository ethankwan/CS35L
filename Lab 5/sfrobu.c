#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char deFrob(const char a);
int frobcmp(const char* a, const char* b);

int IOError(size_t status)
{
  if(status < 0)
  {
    fprintf(stderr, "r/w sys call error\n");
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

int flag = 0;

int main(int argc, char** argv)
{
  if(argc > 2) // only one option is allowed
  {
    fprintf(stderr, "Too many arguments!\n");
    exit(1);
  }
     
  char* curW; // ptr to store strings of different sizes
  char** totalWords; // double ptr to store ptrs for curW
  char** temp;
  const char* toggle = argv[1];
  const char* flagKey = "-f";
  
  if(argc == 2 && strcmp(toggle, flagKey) != 0)
  {
    fprintf(stderr, "only -f shall pass\n");
    exit(1);
  }
  else if(argc == 2 && strcmp(toggle, flagKey) == 0)  
  {
    flag = 1; // turn on -f
  }

  struct stat inputFile;
  if(fstat(0, &inputFile) < 0)
  {
    fprintf(stderr, "fstat error.\n");
    exit(1);
  }

  char* buffer;
  int buffbytes = 0;
  int maxbytes = 0;
  if (S_ISREG(inputFile.st_mode))
  {
    buffer = malloc((inputFile.st_size + 1)*sizeof(char)); // allocating mem
                                                     // for entire input
    if(buffer == NULL)
    {
      fprintf(stderr, "Mem Alloc Error\n");
      exit(1);
    }
    if(read(0, buffer, inputFile.st_size) < 0)
    {
      fprintf(stderr, "Illiterate..\n");
      exit(1);
    }
    
    maxbytes = inputFile.st_size;
  }
  
  curW = malloc(sizeof(char));
  if(curW == NULL)
  {
    fprintf(stderr, "Mem Alloc Error..\n");
    exit(1);
  }
  
  totalWords = NULL; // no words added yet
 
  int letters = 0; 
  int wordNum = 0;
  
  size_t status;
  if (buffbytes >= maxbytes)
  {
    status = read(0, curW, 1);
    if(!IOError(status))
    {
      free(curW);
      exit(1);
    }
  }
  else 
  {
    curW[letters] = buffer[buffbytes++];
    status = 1;
  }
  
  while (status > 0) // not EOF, no IOError
  {
    char next;
    if(buffbytes >= maxbytes)
    {
      status = read(0, &(next), 1);
      if(!IOError(status))
      {
        free(curW);
        int i;
        for(i = 0; i < wordNum; i++)
	{
          free(totalWords[i]);
        }
        free(totalWords);
        exit(1);
      }
      else
      {
        next = buffer[buffbytes++];
      }
    }
    
    if(curW[letters] == ' ') // new word
    {
     temp = (char**)realloc(totalWords, wordNum*sizeof(char*) + sizeof(char*));
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
    
      if(status == 0)
        break;
      while (next == ' ')
      {
        if(buffbytes >= maxbytes)
	{
          status = read(0, &(next), 1);
	  if(!IOError(status))
	  {
	    free(curW);
	    int i;
	    for(i = 0; i < wordNum; i++)
	    {
	      free(totalWords[i]);
	    }
	    free(totalWords);
	    exit(1);
	  }
        }
	else
	{
	  next = buffer[buffbytes++];
	}
      }
    }
    else if(status == 0) // curW not space, but next EOF
    {
      next = ' '; // add space if none added
      status = 1;
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
  size_t i;
  size_t j;
  //Write to stdout
  for(i = 0; i < wordNum; i++)
  {
    for(j = 0; totalWords[i][j] != ' '; j++)
    {
      write(1, &totalWords[i][j], 1);
    }
    write(1, " ", 1);
  }

  //free mem and exit
  size_t n;
  for(n = 0; n < wordNum; n++)
  {
    free(totalWords[n]);
  }
  free(totalWords);
  free(curW);
  return 0;
    
}
  
     
char deFrob(const char a)
{
  
  
    return toupper(a ^ 42); // memfrob simply XOR's the item with 
                             // 00101010, which is 0x2a in hex 
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

