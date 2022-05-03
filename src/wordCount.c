#include "interface.h"


int main(int argc, char**argv) {

  int ret;
  struct OpenHash* hashTable = newOpenHash(atoi(argv[1]));
  
  ret = loadDatabase(hashTable, argv[2]);

  if (!ret) {
        fprintf(stderr, "Failed to open database.\n");
        return EXIT_FAILURE;
    }
  printTable (hashTable->numberBins, hashTable->uniqueWords, hashTable->totalWords);
  hashStats(hashTable);
  freeTable(hashTable);
  return 0;
}

int loadDatabase(struct OpenHash *hashTable, const char *filename)
{
  FILE *fp;
  int ret;
  int uniqueWords = 0;
  int totalWords;
  
  if ( !(fp = fopen(filename, "r")) )
        return 0;
  
  for(totalWords=0;;totalWords++)
  {
    char* buffer = malloc(45*sizeof(*buffer));
    if (fscanf(fp,"%s",buffer) == EOF)
      break;
    
    int length = 0;
    for(int count =0;(*(buffer+count)!= '\0');count++)
      {
        if (isalpha(*(buffer+count)))
        {
          *(buffer+length) = tolower(*(buffer+count));
          length++;
        }
      }
    *(buffer+length)='\0';
    if (isalpha(*buffer) != 0)
    {
      if(member(buffer,hashTable) != 1)
      {
        uniqueWords++;
        insert(buffer,hashTable);
      }
    }
    else{
      totalWords--;
    }
    free(buffer);
    buffer = NULL;
  }
  
  fp = fopen(filename, "r");
  fclose(fp);
  
  hashTable->uniqueWords = uniqueWords;
  hashTable->totalWords = totalWords;
  
  return 1;
}

void printTable (int size, int uniqueWords, int totalWords)
{
  printf("Total Words: %d\n",totalWords);
  printf("Unique Words: %d\n",uniqueWords);
  printf("Hash Size: %d\n",size);
}