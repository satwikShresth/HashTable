#ifndef _interface_h_
#define _interface_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct list{
char* key;
int length;
struct list *next;
};

struct OpenHash{
struct list **bins;
int numberBins;
int totalWords;
int uniqueWords;

};

struct OpenHash* newOpenHash (int size);
int hash (char* string ,int N);
char member (char* string , struct OpenHash* H);
void insert (char *string , struct OpenHash *H);
void hashStats (struct OpenHash* H);
void freeTable (struct OpenHash* H);
void printTable (int size, int uniqueWords, int totalWords);
int loadDatabase(struct OpenHash *hashTable, const char *filename);

#endif  