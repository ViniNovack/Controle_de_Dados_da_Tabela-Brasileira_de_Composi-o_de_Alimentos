#ifndef ARVORE_PROTEINA_H
#define ARVORE_PROTEINA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../alimentos_lista/alimentos_lista.h"

typedef struct ArvoreProteinaNo {
    float proteina;
    AlimentoNo *alimento;

    struct ArvoreProteinaNo *esquerda;
    struct ArvoreProteinaNo *direita;

} ArvoreProteinaNo;

bool inserir_arvore_proteina(ArvoreProteinaNo **raiz, AlimentoNo *alimento);
void liberar_arvore_proteina(ArvoreProteinaNo *raiz);

#endif