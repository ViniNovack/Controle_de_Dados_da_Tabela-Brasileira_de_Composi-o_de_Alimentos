#ifndef ARVORE_ENERGIA_H
#define ARVORE_ENERGIA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "../alimentos_lista/alimentos_lista.h"

typedef struct ArvoreEnergiaNo {
    float energia;
    AlimentoNo *alimento;

    struct ArvoreEnergiaNo *esquerda;
    struct ArvoreEnergiaNo *direita;

} ArvoreEnergiaNo;

bool inserir_arvore_energia(ArvoreEnergiaNo **raiz, AlimentoNo *alimento);
void liberar_arvore_energia(ArvoreEnergiaNo *raiz);

#endif
