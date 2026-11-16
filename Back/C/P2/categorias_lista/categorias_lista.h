#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef CATEGORIAS_LISTA_H
#define CATEGORIAS_LISTA_H

#include "../../alimento.h"
#include "../alimentos_lista/alimentos_lista.h"

typedef struct CatgoriaNo{
    Categoria categoria;             // Identifica a categoria por meio do [enum] já existente
    AlimentoNo *alimentos;           // Aponta para o início da lista de alimentos daquela categoria
    struct CategoriaNo *proxima;     // Aponta para a próxima categoria
} CategoriaNo;

#endif