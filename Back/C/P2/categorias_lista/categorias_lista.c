#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "categorias_lista.h"

bool inserir_alimento_categoria(CategoriaNo **inicio, Alimento alimento) {
    bool inserido = false;
    bool nova_categoria = false;

    if (inicio != NULL) {
        CategoriaNo **posicao = inicio;
        const char *nome_categoria = obter_nome_categoria(alimento.categoria);

        while (*posicao != NULL &&
               strcmp(obter_nome_categoria((*posicao)->categoria), nome_categoria) < 0) {

            posicao = &(*posicao)->proxima;
        }

        if (*posicao == NULL || (*posicao)->categoria != alimento.categoria) {
            CategoriaNo *novo = malloc(sizeof(CategoriaNo));

            if (novo != NULL) {
                novo->categoria = alimento.categoria;
                novo->alimentos = NULL;
                novo->proxima = *posicao;

                *posicao = novo;
                nova_categoria = true;
            }
        }

        if (*posicao != NULL && (*posicao)->categoria == alimento.categoria) {
            inserido = inserir_alimento(&(*posicao)->alimentos, alimento);

            if (!inserido && nova_categoria) {
                CategoriaNo *remover = *posicao;

                *posicao = remover->proxima;
                free(remover);
            }
        }
    }

    return inserido;
}
