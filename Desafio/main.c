#include <stdio.h>
#include <math.h>
#include "desafio.h"

#define N_BITS 17

/* Mostra os últimos bits de um número. */
void mostraBits (unsigned int n, int tamanho) {
    int i;
    for (i = 1; i <= tamanho; i++)
        printf ("%d", 1 & n >> (tamanho-i));
    printf("\n");
}

int main () {
    unsigned int i;
    int contagem = 0;
    /* Gera e testa todas as sequências possíveis com N_BITS. */
    for (i = 0; i < pow (2, N_BITS); i++) {
        if (codigoValido (i, N_BITS)) {
            contagem++;
            mostraBits (i, N_BITS);
        }
    }
    printf ("%d sequencias encontradas.\n", contagem);
    return (0);
}
