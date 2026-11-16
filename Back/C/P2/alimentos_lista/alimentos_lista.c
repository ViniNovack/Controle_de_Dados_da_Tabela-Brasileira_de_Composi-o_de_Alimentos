#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "alimentos_lista.h"

bool inserir_alimento(AlimentoNo **inicio, Alimento alimento) {
    bool inserido = false;

    if (inicio != NULL){
        AlimentoNo *novo = malloc(sizeof(AlimentoNo));

        if (novo != NULL){
            novo->alimento = alimento;
            novo->proximo = NULL;

            if (*inicio == NULL || strcmp(alimento.descricao, (*inicio)->alimento.descricao) < 0){
                novo->proximo = *inicio;
                *inicio = novo;
            } else{
                AlimentoNo *atual = *inicio;

                while (atual->proximo != NULL && strcmp(atual->proximo->alimento.descricao, alimento.descricao) <= 0){
                    atual = atual->proximo;
                }
                novo->proximo = atual->proximo;
                atual->proximo = novo;
            }
            inserido = true;
        }
    }

    return inserido;
}
