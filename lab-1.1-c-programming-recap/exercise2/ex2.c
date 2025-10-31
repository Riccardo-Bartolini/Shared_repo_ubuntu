#include <stdio.h>
#include <stddef.h>  // Per size_t e NULL
#include <stdint.h>  // Per int32_t
#include <stdbool.h> // Per bool

/*
 * ============================================================================
 * Esercizio 1: vswap (versione con puntatori)
 * ============================================================================
 */
void vswap(void* a, void* b, size_t size) {
    if (a == b || size == 0) {
        return;
    }

    unsigned char* pa = (unsigned char*)a;
    unsigned char* pb = (unsigned char*)b;
    unsigned char temp;

    // Puntatore alla fine del blocco 'a'
    unsigned char* const end_a = pa + size;

    // Iteriamo incrementando i puntatori stessi
    while (pa < end_a) {
        // Scambiamo i byte correnti
        temp = *pa;
        *pa = *pb;
        *pb = temp;

        // Passiamo al prossimo byte
        pa++;
        pb++;
    }
}


/*
 * ============================================================================
 * Esercizio 2: vcopy_n (versione con puntatori)
 * ============================================================================
 */
void vcopy_n(void* dst, const void* src, size_t count, size_t elem_size) {
    size_t total_bytes = count * elem_size;

    if (dst == src || total_bytes == 0) {
        return;
    }

    unsigned char* pdst = (unsigned char*)dst;
    const unsigned char* psrc = (const unsigned char*)src;

    // Dobbiamo gestire la sovrapposizione (memmove)
    if (pdst > psrc && pdst < psrc + total_bytes) {
        
        // Copia all'indietro
        // Puntiamo *oltre* l'ultimo byte
        unsigned char* dst_ptr = pdst + total_bytes;
        const unsigned char* src_ptr = psrc + total_bytes;

        size_t n = total_bytes;
        while (n > 0) {
            // Decrementiamo *prima* di dereferenziare
            --dst_ptr;
            --src_ptr;
            *dst_ptr = *src_ptr;
            --n;
        }

    } else {
        
        // Copia in avanti
        size_t n = total_bytes;
        while (n > 0) {
            *pdst = *psrc;
            pdst++;
            psrc++;
            --n;
        }
    }
}


/*
 * ============================================================================
 * Esercizio 3: vminmax e Comparatori (Invariato)
 * ============================================================================
 * Questa funzione usava già l'aritmetica dei puntatori (base + offset)
 * e non l'operatore [].
 */

int cmp_int32(const void* a, const void* b) {
    const int32_t* pa = (const int32_t*)a;
    const int32_t* pb = (const int32_t*)b;
    if (*pa < *pb) return -1;
    if (*pa > *pb) return 1;
    return 0;
}

int cmp_double(const void* a, const void* b) {
    const double* pa = (const double*)a;
    const double* pb = (const double*)b;
    if (*pa < *pb) return -1;
    if (*pa > *pb) return 1;
    return 0;
}

bool vminmax(const void* base, size_t count, size_t elem_size,
             int (*comparator)(const void*, const void*),
             const void** out_min, const void** out_max) {

    if (count == 0 || base == NULL || comparator == NULL || 
        out_min == NULL || out_max == NULL) 
    {
        if (out_min) *out_min = NULL;
        if (out_max) *out_max = NULL;
        return false;
    }

    // Cast a unsigned char* per l'aritmetica
    const unsigned char* pbase = (const unsigned char*)base;

    // Inizializza min e max al primo elemento (offset 0)
    const void* min_ptr = pbase; 
    const void* max_ptr = pbase;

    for (size_t i = 1; i < count; ++i) {
        // Calcola l'indirizzo dell'elemento corrente usando l'aritmetica
        const void* current_ptr = pbase + (i * elem_size);

        if (comparator(current_ptr, min_ptr) < 0) {
            min_ptr = current_ptr;
        }
        
        if (comparator(current_ptr, max_ptr) > 0) {
            max_ptr = current_ptr;
        }
    }

    *out_min = min_ptr;
    *out_max = max_ptr;
    return true;
}







int main(){

}