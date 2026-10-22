#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strtab.h"

char currFunction[256] = "";

/* You should use a linear linklist to keep track of all parameters passed to a function. 
 * The working_list_head should point to the beginning of the linklist and working_list_end
 * should point to the end. Whenever a parameter is passed to a function, that node should 
 * also be added in this list. */
param *working_list_head = NULL;
param *working_list_end = NULL;

// A global variable that should point to the symbol table node in the scope tree as discussed in lecture 13 and 14.
table_node* current_scope = NULL;


//Helper methods:
// Make a new table node, allocate space and then create node with parent that is passed as parameter.
table_node *makeTableNode(table_node *parent){
    table_node *n = (table_node *)calloc(1, sizeof(table_node));
    n->parent = parent;
    return n;
}

int get_symbol_index(symEntry *entry) {
    if (!entry) return -1;

    table_node *scope = current_scope;

    while (scope != NULL) {
        for (int i = 0; i < MAXIDS; i++) {
            if (scope->strTable[i] == entry) {
                return i;
            }
        }
        scope = scope->parent;
    }

    return -1;
}

// Hash method taken from phase 2 and modified.
int hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash += (hash << 5) + c;
  }
  return (int)hash;
}

int hashScopeID(const char *scope, const char *id){
    char buffer[512];

    if(scope == NULL || scope[0] == '\0'){
        snprintf(buffer, sizeof(buffer), "%s", id);
    }
    else{
        snprintf(buffer, sizeof(buffer), "%s%s", scope, id);
    }
    int slot = hash((unsigned char *)buffer) % MAXIDS;
    if(slot < 0){
        slot += MAXIDS;
    }
    return slot;
}

symEntry *createSymEntry(const char *id, const char *scopeStr, int dataType, int symbolType, int valSize){
    symEntry *entry = (symEntry *)malloc(sizeof(symEntry));
    entry->id = strdup(id);
    entry->scope = strdup(scopeStr ? scopeStr : "");
    entry->data_type = dataType;
    entry->symbol_type = symbolType;
    entry->size = valSize;
    entry->params = NULL;
    return entry;
}

/* Inserts a symbol into the current symbol table tree. Please note that this function is
 * used to instead into the tree of symbol tables and NOT the AST. Start at the returned 
 * hash and probe until we find an empty slot or the id.  */
int ST_insert(char *id, int data_type, int symbol_type, int* scope){
    if(current_scope == NULL){ current_scope = makeTableNode(NULL); }

    if(!id || !scope){ return -1; }

    int isLocal = scope && *scope;
    const char *scopeStr = isLocal ? currFunction : "";
    const char *hashBuffer = isLocal ? currFunction : "";

    int h = hashScopeID(hashBuffer, id);
    int start = h;

    do{
        if(current_scope->strTable[h] == NULL){
            int initialSize = 0;
            current_scope->strTable[h] = createSymEntry(id, scopeStr, data_type, symbol_type, initialSize);
            return h;
        }
        if(current_scope->strTable[h]->id){
            if(strcmp(current_scope->strTable[h]->id, id) == 0){
                if(strcmp(current_scope->strTable[h]->scope, scopeStr) == 0){
                    return h;
                }
            }
        }
        h++;
        h %= MAXIDS;
    }while(h != start);
    
    return -1;
}

/* The function for looking up if a symbol exists in the current_scope. Always start
 * looking for the symbol from the node that is being pointed to by the current_scope variable*/
symEntry* ST_lookup(char *id){
    if(!id){ return NULL; }
    if(current_scope == NULL){ current_scope = makeTableNode(NULL); }

    table_node *currNode = current_scope;
    while(currNode != NULL){
        const char *scopeBuf = (currNode == NULL || currNode->parent == NULL) ? "" : currFunction;
        int h = hashScopeID(scopeBuf, id);
        int start = h;
        
        do
        {
            symEntry *temp = currNode->strTable[h];
            if(temp == NULL){ break; }
            if(strcmp(temp->id, id) == 0){ return temp; }
            h++;
            h %= MAXIDS;
        } while (h != start);
        
        currNode = currNode->parent;
    }

    return NULL;
    
}

/* Creates a param* whenever formalDecl in the parser.y file declares a formal parameter.
 * Please note that we are maining a separate linklist to keep track of all the formal 
 * declarations because until the function body is processed, we will not know the number
 * of parameters in advance. Link list provides a way for the formalDecl to declare as many 
 * parameters as needed.*/
void add_param(int data_type, int symbol_type){
    param *newParam = (param *)malloc(sizeof(param));
    newParam->data_type = data_type;
    newParam->symbol_type = symbol_type;
    newParam->next = NULL;

    if(working_list_head == NULL){ working_list_head = newParam; working_list_end = newParam; }
    else{ working_list_end->next = newParam; working_list_end = newParam;}
}

/*connect_params is called after the funBody is processed in parser.y. At this point, the 
 * parser has already seen all the formal parameter declaration and has built the entire 
 * list of parameters to the function. This list is pointed to by the working_list_head pointer. 
 * current_scope->parent->strTable[index]->params should point to the header of that parameter list. */
void connect_params(int i, int num_params){
    if(current_scope == NULL || current_scope->parent == NULL){ return; }
    if(i < 0 || i >= MAXIDS){ return; }

    if(current_scope->parent->strTable[i] == NULL){ return; }
    if(current_scope->parent->strTable[i]->symbol_type != FUNCTION){ return; }

    current_scope->parent->strTable[i]->params = working_list_head;
    current_scope->parent->strTable[i]->size = num_params;

    working_list_head = NULL;
    working_list_end = NULL;
}

// Creates a new scope within the current scope and sets that as the current scope.
void new_scope(){
    if(current_scope == NULL){ current_scope = makeTableNode(NULL); }

    table_node *childNode = makeTableNode(current_scope);

    if(current_scope){
        if(current_scope->last_child){
            current_scope->last_child->next = childNode;
            current_scope->last_child = childNode;
        }
        else{
            current_scope->first_child = childNode;
            current_scope->last_child = childNode;
        }
        current_scope->numChildren++;
    }
    current_scope = childNode;
}

// Moves towards the root of the sym table tree.
void up_scope(){
    //if parent scope is null, current_scope is global scope and we should not go up
    if(current_scope && current_scope->parent){
        current_scope = current_scope->parent;
    }
}

char *get_symbol_id(int val){
    if(val < 0){ return "undeclared variable"; }
    
    table_node *root = current_scope;
    
    if(root == NULL){ return "?"; }

    while(root->parent != NULL){ root = root->parent; }

    table_node *stack[2048];
    int stackPos = 0;
    stack[stackPos++] = root;

    symEntry *lastSeen = NULL;
    int hitCtr = 0;

    while(stackPos > 0){
        stackPos--;
        table_node *currNode = stack[stackPos];
        if(val < MAXIDS && currNode->strTable[val] != NULL){
            hitCtr++;
            lastSeen = currNode->strTable[val];
        }
        table_node *childNode = currNode->first_child;
        while(childNode != NULL){
            if(stackPos < 2048){ stack[stackPos++] = childNode; }
            childNode = childNode->next;
        }
    }

    if(hitCtr == 1 && lastSeen != NULL && lastSeen->id != NULL){ return lastSeen->id; }

    return "?";
}


void print_sym_tab(void){

    if(current_scope == NULL){ printf("*ERROR 404: Symbol Table Not Found*\n"); return; }

    table_node *root = current_scope;

    while(root->parent != NULL){ root = root->parent; }

    table_node *stack[2048];
    int stackPos = 0;
    stack[stackPos++] = root;

    while(stackPos > 0){
        stackPos--;
        table_node *currNode = stack[stackPos];
        
        for(int i = 0; i < MAXIDS; i++){
            symEntry *entry = currNode->strTable[i];
            if(entry == NULL){ continue; }

            char *type = "?";
            if(entry->data_type == INT_TYPE){ type = "int"; }
            else if(entry->data_type == CHAR_TYPE){ type = "char"; }
            else if(entry->data_type == VOID_TYPE){ type = "void"; }

            char *kind = "?";
            if(entry->symbol_type == SCALAR){ kind = "scalar"; }
            else if(entry->symbol_type == ARRAY){ kind = "array"; }
            else if(entry->symbol_type == FUNCTION){ kind = "function"; }

            if(strcmp(type, "void")){ printf("%s  scope=\"%s\" %s %s", entry->id, entry->scope ? entry->scope : "", kind, type); }
            else{ printf("%s  scope=\"%s\" %s", entry->id, entry->scope ? entry->scope : "", type); }

            

            if(entry->symbol_type == ARRAY || entry->symbol_type == FUNCTION){
                printf(" size=%d", entry->size);
            }

            if(entry->symbol_type == FUNCTION && entry->params != NULL){
                printf("  params=(");
                param *par = entry->params;
                int argCount = 1;

                while(par != NULL){
                    char *paramType = "?";
                    if(par->data_type == INT_TYPE){ paramType = "int"; }
                    else if(par->data_type == CHAR_TYPE){ paramType = "char"; }
                    else if(par->data_type == VOID_TYPE){ paramType = "void"; }

                    if(argCount != 1){ printf(", "); }
                    
                    if(par->next != NULL){ argCount++; }

                    printf("%s", paramType);
                    
                    if(par->symbol_type == ARRAY){ printf("[]"); }

                    par = par->next;
                }
                printf(")");
            }
            printf("\n");
        }

        table_node *childNode = currNode->first_child;
        while(childNode != NULL){
            if(stackPos < 2048){ stack[stackPos++] = childNode; }
            childNode = childNode->next;
        }
    }
}