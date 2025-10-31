/*
Implement a splitter that allocates tokens and returns them via triple-pointer:

Split `s` on delimiter `delim`. On success:

- *out_tokens points to a newly allocated array of char* (N tokens)
- each token is a newly allocated NULL-terminated string
- *out_count is set to N

Caller must free each token and then the array.

Returns 0 on success, nonzero on failure.

```
int strsplit(const char* s, char delim, char*** out_tokens, size_t* out_count);
```

**Expected Behavior**

* Consecutive delimiters produce empty tokens (e.g., "a,,b" → "a", "", "b").
* Handles leading/trailing delimiters.
* s == NULL ⇒ error.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int strsplit(const char* s, char delim, char*** out_tokens, size_t* out_count){

    if(s==NULL  || out_tokens==NULL || out_count==NULL){
        return -1; // Error: NULL input pointer
    }

    size_t count = 1; // At least one token

    for (int i=0; s[i]!='\0';++i){
        if(s[i]==delim){
            count++;
        }
    }

    char **tokens = malloc(count * sizeof(char*));
    if(tokens==NULL){
        return -1; // Error: Memory allocation failed
    }

   // --- 4. Passaggio 2: Estrarre e Allocare ogni Token ---
    const char* token_start = s;
    const char* p = s;
    size_t token_index = 0;

    while (token_index < count) {
        // Troviamo la fine del token: o un delimitatore, o la fine della stringa
        if (*p == delim || *p == '\0') {
    // Calcoliamo la lunghezza del token
            size_t token_len = p - token_start;

            // Alloca memoria per il *singolo* token (+1 per il '\0')
            char* new_token = malloc(token_len + 1);
            if (new_token == NULL) {
                // Se falliamo, dobbiamo liberare TUTTO ciò che abbiamo
                // allocato finora per evitare memory leak.
                for (size_t j = 0; j < token_index; ++j) {
                    free(tokens[j]); // Libera ogni token
                }
                free(tokens); // Libera l'array contenitore
                return -2; // Errore OOM
            }
            // Copia i dati del token e aggiungi il terminatore
            memcpy(new_token, token_start, token_len);
            new_token[token_len] = '\0';

            // Inserisci il nuovo token nell'array
            tokens[token_index] = new_token;
            token_index++;

            // Aggiorna l'inizio del prossimo token
            token_start = p + 1;
        }
        // Se siamo alla fine della stringa, usciamo dal loop
        if (*p == '\0') {
            break;
        }
        p++; // Avanza al prossimo carattere
    }
    // --- 5. Restituire i risultati tramite "out-params" ---
    // Dereferenziamo i puntatori di output per scrivere i valori
    // nelle variabili del chiamante (es. nel main).
    *out_count = count;
    *out_tokens = tokens; // "Trasferiamo la proprietà" dell'array

    return 0; // Successo
}


typedef struct node {
    int value;
    struct node* next;
} node;




void list_push_front(node** head, int value){
    if(head==NULL)
        return 0;

node* newNode=  malloc(sizeof(struct node));

if(newNode== NULL)
    return 0;

newNode->value= value;
newNode->next= *head;
*head = newNode;
}


bool list_remove_first(node** head, int value){

    if(head== NULL || *head==NULL)
        return 0;

    node* curs = *head;
    node* prec = *head;

    while(curs!= NULL && curs->value!= value ){
    prec = curs;
    curs= curs->next;
    }

    if(curs==NULL && prec->value!= value ){
        return 0; /* value not in the list*/
    }

     if(curs == *head && (*head)->value == value){
        *head=curs->next;
        free(curs); /*remove first*/
        return true;
    }
    
    if(curs->next== NULL && curs->value== value){
        prec->next=NULL;
        free(curs); /*remove last*/
        return true;
    }

   
    if(curs->next!= NULL && curs->value== value){
        prec->next=curs->next;
        free(curs); /*remove in the middle*/
        return true;
    }

}


void list_free(node** head){

    if (head == NULL || *head == NULL) {
        return; // Non c'è nulla da liberare
    }

    node* curs= *head;
    node* copy= NULL;
  
    while(curs!= NULL){
        copy= curs->next;
        free(curs);
        curs=copy;
    }
      *head=NULL;

}








