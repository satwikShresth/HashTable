#include "interface.h"

struct OpenHash* newOpenHash(int size){
  struct OpenHash* hashTable = calloc(1,sizeof(*hashTable));
  hashTable->bins = malloc(size*sizeof(*hashTable->bins));
  hashTable->numberBins = size;
  for(int i =0;i<hashTable->numberBins;i++)
    hashTable->bins[i]=NULL;
  return hashTable;
}

int hash (char* string ,int N){
  int total = 0;
  for(int i =0;string[i]!=0;i++)
    {
      char c = string[i];
      int m = (int) c;
      total += m;
      total *= 101;
      total = total % N;
    }
  return total;
}

char member (char* string , struct OpenHash* H){
  struct list *item = H->bins[hash(string,H->numberBins)];
  if(item){
    for(;item;item = item->next)
      if(strcmp(item->key,string) == 0)
        return 1;
  }
  return 0;
}

void insert (char *string , struct OpenHash *H){
  struct list *item = malloc(sizeof(*item));
  item->key = malloc(strlen(string)+1);
  strcpy(item->key,string);
  int bin = hash(string,H->numberBins);
  item->length++;
  item->next = H->bins[bin];
  H->bins[bin] = item;  
}

void hashStats (struct OpenHash* H){
  double total = 0;
  for(int bin = 0;bin<H->numberBins;bin++)
  {
    int count;
    struct list *item = H->bins[bin];
    for(count=0;item;item = item->next,++count);
    printf("Row %d contains %d values.\n",bin,count);
    total += count;
  }
  printf("Average Length: %.2f\n",total/H->numberBins);
}

void freeTable (struct OpenHash* H){
  for(int bin = 0;bin<H->numberBins;bin++)
  {
    for(struct list *item = H->bins[bin],*head=item;head;){
      free(head->key);
      head = head->next;
      H->bins[bin] = head;
      free(item);
      item = NULL;
    }
  }
  free(H->bins);
  free(H);
}
