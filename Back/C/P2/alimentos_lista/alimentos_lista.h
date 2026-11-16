#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef ALIMENTOS_LISTA_H
#define ALIMENTOS_LISTA_H

#include "../../alimento.h"

typedef struct AlimentoNo{          // Representa um nó da lista ligada
    Alimento alimento;              // Guarda todos os dados do alimento
    struct AlimentoNo *proximo;     // Aponta para o próximo alimento da lista
} AlimentoNo;

bool inserir_alimento(AlimentoNo **inicio, Alimento alimento);

#endif