#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // Per size_t e NULL
#include <stdint.h> // Per uint8_t
#include <string.h> // Per memcpy
#include <stdalign.h> // Per alignof
#include <stdbool.h> // Per bool, true, false




// 1  Write a function that returns a pointer to the first occurrence of byte needle in [buf, buf+len), or NULL if not found.
const uint8_t* memscan8(const void* buf, size_t len, uint8_t needle) {
    // 1. Cast del Puntatore:
    // Il puntatore generico 'buf' viene convertito in 'uint8_t*'
    // (puntatore a byte) per poter eseguire l'aritmetica byte-per-byte.
    const uint8_t* ptr = (const uint8_t*)buf;

    // 2. Calcolo del Limite:
    // Calcoliamo l'indirizzo del primo byte *dopo* il buffer, che funge da limite.
    const uint8_t* end = ptr + len;

    // 3. Ciclo di Scorrimento:
    // Fintanto che il puntatore corrente è all'interno del buffer...
    while (ptr < end) {
        // 4. Dereferenziazione e Confronto:
        // Controlliamo il valore del byte a cui 'ptr' punta.
        if (*ptr == needle) {
            return ptr; // Trovato! Restituiamo il suo indirizzo.
        }
        // 5. Aritmetica del Puntatore:
        // Spostiamo il puntatore al byte successivo. (ptr++ incrementa di 1 byte, 
        // poiché ptr è di tipo uint8_t*).
        ptr++;
    }

    // 6. Non Trovato:
    return NULL;
}



// 2 Write a function that reverses a buffer in-place. Operate via two moving pointers; no indexing.
void memrev(void* buf, size_t len) {
    // 1. Gestione di Casi Limite:
    if (len == 0 || len == 1) {
        return;
    }

    // 2. Puntatori Mobili:
    // Puntatore all'inizio (char* è spesso usato come alias di uint8_t*).
    uint8_t* start = (uint8_t*)buf;
    
    // Puntatore alla FINE del buffer, poi lo si porta all'ULTIMO BYTE VALIDO.
    // L'aritmetica dei puntatori (start + len) funziona solo dopo il cast.
    uint8_t* end = (uint8_t*)buf + len - 1;

    // 3. Ciclo di Scambio:
    // Continuiamo finché i puntatori non si sono incrociati o toccati.
    while (start < end) {
        // 4. Scambio (Swap) Temporaneo:
        uint8_t temp = *start; // Salva il byte iniziale.
        *start = *end;        // Scrive il byte finale su quello iniziale.
        *end = temp;          // Scrive il byte salvato su quello finale.

        // 5. Aggiornamento dei Puntatori:
        start++; // Sposta l'inizio in avanti.
        end--;   // Sposta la fine indietro.
    }
}




//Write a function that reads an aligned 32-bit little-endian unsigned integer from memory at location `buf + offset`.
bool read_u32_le_aligned(const void* buf, size_t len, size_t offset, uint32_t* out) {
    // 1. Calcolo Indirizzo e Limiti:
    // Quanti byte deve leggere? 4 (sizeof(uint32_t)).
    const size_t size_needed = sizeof(uint32_t);
    const size_t align_req = alignof(uint32_t);
    
    // Controlliamo che la lettura non vada fuori dai limiti del buffer.
    if (offset + size_needed > len) {
        return false;
    }

    // Puntatore al punto di inizio della lettura
    const uint8_t* read_ptr = (const uint8_t*)buf + offset;

    // 2. Controllo di Allineamento:
    // 'uintptr_t' è un tipo intero abbastanza grande da contenere un indirizzo.
    // Verifichiamo se l'indirizzo di inizio lettura è un multiplo dell'allineamento richiesto (4).
    if ((uintptr_t)read_ptr % align_req != 0) {
        return false; // Misaligned: indirizzo non allineato.
    }

    // 3. Lettura Sicura (Anti Strict-Aliasing):
    // Dato che il puntatore 'read_ptr' è allineato e valido, possiamo usare memcpy
    // per copiare i 4 byte direttamente nella variabile di output.
    // Questo è il modo più sicuro e standard per trasferire dati grezzi.
    memcpy(out, read_ptr, size_needed);
    
    // Nota sulla Little-Endian: memcpy legge i byte in ordine e li scrive nella
    // variabile 'out', gestendo l'endianness automaticamente per la macchina host
    // (che è little-endian nella maggior parte dei casi). Poiché l'input è LITTLE-ENDIAN
    // e la lettura è allineata, la copia byte-per-byte è corretta.

    return true;
}



int main() {
    
}
