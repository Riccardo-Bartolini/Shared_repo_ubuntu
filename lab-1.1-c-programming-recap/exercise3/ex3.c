#include <stdio.h>
#include <stddef.h>  // Per size_t e NULL
#include <stdint.h>  // Per int32_t
#include <stdbool.h> // Per bool


/*
 * ============================================================================
 * Esercizio 3.0: run_pipeline (Il "Motore")
 * ============================================================================
 */

/**
 * @brief Esegue una pipeline di 'n_stages' sul valore puntato da 'x'.
 * * @param x Puntatore al dato da processare.
 * @param stages Array di puntatori a funzioni (gli "stage").
 * @param users Array di puntatori void* (le "configurazioni" per ogni stage).
 * @param n_stages Numero di stage nella pipeline.
 * @return true se l'intera pipeline è stata eseguita, false se uno stage
 * ha richiesto un'interruzione (restituendo false).
 */

 typedef bool (*stage_fn)(int32_t* x, void* user);

bool run_pipeline(int32_t* x, stage_fn const* stages, void* const* users, size_t n_stages) {
    
    // Itera su ogni stage definito
    for (size_t i = 0; i < n_stages; ++i) {
        
        // Prendi la funzione dello stage corrente
        stage_fn current_stage_func = stages[i];
        
        // Prendi i dati di configurazione per lo stage corrente
        void* current_user_data = users[i];

        // Esegui lo stage corrente, passando il dato 'x' e la sua configurazione
        bool continue_pipeline = current_stage_func(x, current_user_data);

        // Controlla la logica di "early stop"
        if (continue_pipeline == false) {
            printf("--- Interruzione pipeline allo stage %zu ---\n", i);
            return false; // Interrompi e restituisci fallimento
        }
    }

    // Se siamo arrivati qui, tutti gli stage sono stati eseguiti con successo
    return true;
}


/*
 * ============================================================================
 * Esercizio 3.1: Stage 'add_k'
 * ============================================================================
 */

/**
 * @brief Stage 1: Aggiunge 'k' a *x.
 * Si aspetta che 'user' sia un puntatore a un int32_t (il valore 'k').
 */
bool add_k(int32_t* x, void* user) {
    // Gestione robusta: se non viene fornita configurazione, non facciamo nulla
    if (user == NULL) {
        return true; // L'operazione "non fare nulla" è riuscita
    }

    // 1. Sappiamo che 'user' è un puntatore a 'k'.
    //    Facciamo il cast da void* al tipo corretto (int32_t*).
    int32_t* k_ptr = (int32_t*)user;

    // 2. Dereferenziamo il puntatore per ottenere il valore 'k'.
    int32_t k = *k_ptr;

    // 3. Applichiamo la logica dello stage
    *x += k;

    // 4. Segnaliamo di continuare la pipeline
    return true;
}

/*
 * ============================================================================
 * Esercizio 3.2: Stage 'clamp'
 * ============================================================================
 */

// Per passare due valori (lo, hi), abbiamo bisogno di una struct
typedef struct {
    int32_t lo;
    int32_t hi;
} ClampConfig;

/**
 * @brief Stage 2: Limita *x tra 'lo' e 'hi'.
 * Si aspetta che 'user' sia un puntatore a una struct ClampConfig.
 */
bool clamp(int32_t* x, void* user) {
    if (user == NULL) {
        return true; // Impossibile eseguire, ma non fermiamo la pipeline
    }

    // 1. Sappiamo che 'user' è un puntatore a ClampConfig.
    //    Facciamo il cast da void* al tipo corretto (ClampConfig*).
    ClampConfig* config = (ClampConfig*)user;

    // 2. Applichiamo la logica dello stage
    if (*x < config->lo) {
        *x = config->lo;
    } else if (*x > config->hi) {
        *x = config->hi;
    }

    return true;
}

/*
 * ============================================================================
 * Esercizio 3.3: Stage 'map_if'
 * ============================================================================
 */

// Definiamo i tipi di funzione che 'map_if' userà
typedef bool (*predicate_fn)(int32_t);
typedef int32_t (*map_fn)(int32_t);

// Per passare due PUNTATORI A FUNZIONE, usiamo un'altra struct
typedef struct {
    predicate_fn predicate;
    map_fn       map;
} MapIfConfig;

/**
 * @brief Stage 3: Se predicate(*x) è vero, applica *x = map(*x).
 * Si aspetta che 'user' sia un puntatore a una struct MapIfConfig.
 */
bool map_if(int32_t* x, void* user) {
    if (user == NULL) {
        return true;
    }
    
    // 1. Cast di 'user' al tipo di struct corretto
    MapIfConfig* config = (MapIfConfig*)user;

    // Controllo di robustezza: assicuriamoci che i puntatori a funzione
    // dentro la struct non siano NULL.
    if (config->predicate == NULL || config->map == NULL) {
        return true; // Impossibile eseguire
    }

    // 2. Applichiamo la logica
    //    Usiamo i puntatori a funzione salvati nella config
    if (config->predicate(*x) == true) {
        *x = config->map(*x);
    }

    return true;
}

/*
 * ============================================================================
 * Funzioni Helper per il Test di 'map_if'
 * ============================================================================
 */
bool is_even(int32_t v) {
    return (v % 2) == 0;
}
int32_t divide_by_2(int32_t v) {
    return v / 2;
}

/*
 * ============================================================================
 * Stage Helper per il Test di "Early Stop"
 * ============================================================================
 */
/**
 * @brief Stage di test: ferma la pipeline se *x è negativo.
 */
bool fail_if_negative(int32_t* x, void* user) {
    (void)user; // Ignoriamo 'user' (buona pratica per evitare warning)
    
    if (*x < 0) {
        return false; // FERMA LA PIPELINE!
    }
    return true; // Continua
}



/*
 * ============================================================================
 * Funzioni Helper per il Test di "Early Stop"
 * ============================================================================
 */
bool is_negative(int32_t v) {
    return v < 0;
}





