#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strtab.h"

const char *dataTypeStr[3] = {"int", "char", "void"};
const char *symbolTypeStr[3] = {"", "[]", "()"};

/* The symbolTable, which will be implemented as a hash table
  */
struct strEntry strTable[MAXIDS];

/* Provided is a hash function that you may call to get an integer back. */
int hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash += (hash << 5) + c;
  }
  return hash % MAXIDS; // MAXIDS defined in strtab.h
}

int ST_insert(char *id, char *scope, int data_type, int symbol_type){
  // TODO: Concatenate the scope and id and use that to create the hash key

  /* TODO: Use ST_lookup to check if the id is already in the symbol table.
    If yes, ST_lookup will return an index that is not -1.
    if index != -1, that means the variable is already in the hashtable.
    Hence, no need to insert that variable again.
    However, if index == -1,
      then use linear probing to find an empty spot and insert there.
    Then return that index.
    */

  // If id and scope match a preexisting id then we should not add another one
  int existing = ST_lookup(id, scope);
  if (existing != -1){
    return existing;
  }

  int hashInputlen = (strlen(scope) + strlen(id));
  int keylength = (hashInputlen + 1);
  char *key = (char *)malloc(keylength);

  if(!key){
    return -1;
  }
  
  // concatenate scope and id and create hashID
  strcpy(key, scope);
  strcat(key, id);
  int hashID = hash((unsigned char*)key);
  free(key);

  // creat target index according to hashID
  int index = hashID;

  for (int ctr = 0; ctr < MAXIDS; ctr++){
    // if target index is empty
    if (strTable[index].id == NULL){ 

      // allocate space
      int idLength = strlen(id) + 1;
      int scopeLength = strlen(scope) + 1;
      strTable[index].id = (char *)malloc(idLength);
      strTable[index].scope = (char *)malloc(scopeLength);

      // if id or scope is wrong, return.
      if (!strTable[index].id || !strTable[index].scope){ return -1; }

      // assign everything
      strcpy(strTable[index].id, id);
      strcpy(strTable[index].scope, scope);
      strTable[index].data_type = data_type;
      strTable[index].symbol_type = symbol_type;
    }
    // compare id and scope to verify they are correct in the table, then return index
    if (strcmp(strTable[index].id, id) == 0 && strcmp(strTable[index].scope, scope) == 0){
      return index;
    }
    index = (index + 1) % MAXIDS;
  }

  return -1;
}

int ST_lookup(char *id, char *scope) {
  // TODO: Concatenate the scope and id and use that to create the hash key

  /* TODO: Use the hash value to check if the index position has the "id".
    If not, keep looking for id until you find an empty spot.
    If you find "id", return that index.
    If you arrive at an empty spot, that means "id" is not there.
    Then return -1. 
    */
  int hashInputlen = (strlen(scope) + strlen(id));
  int keylength = (hashInputlen + 1);
  char *key = (char *)malloc(keylength);

  if(!key){
    return -1;
  }
  
  // concatenate scope and id and create hashID
  strcpy(key, scope);
  strcat(key, id);
  int hashID = hash((unsigned char*)key);
  free(key);

  int index = hashID;
  for (int ctr = 0; ctr < MAXIDS; ctr++){
    if (strTable[index].id == NULL){ return -1; }
    if (strcmp(strTable[index].id, id) == 0 && strcmp(strTable[index].scope, scope) == 0){
      return index;
    }
    index = (index + 1) % MAXIDS;
  }

  return -1;
}

void output_entry(int i){
  printf("%d: %s ", i, dataTypeStr[strTable[i].data_type]);
  printf("%s:%s%s\n",
    strTable[i].scope, strTable[i].id, symbolTypeStr[strTable[i].symbol_type]);
}
