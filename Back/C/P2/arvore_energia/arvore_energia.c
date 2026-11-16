#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "arvore_energia.h"

bool inserir_arvore_energia(ArvoreEnergiaNo **raiz, AlimentoNo *alimento){
    bool inserido = false;

    if (raiz != NULL && alimento != NULL){
        ArvoreEnergiaNo **posicao = raiz;

        while (*posicao != NULL) {
            if (alimento->alimento.energia < (*posicao)->energia){
                posicao = &(*posicao)->esquerda;
            } else{
                posicao = &(*posicao)->direita;
            }
        }

        ArvoreEnergiaNo *novo = malloc(sizeof(ArvoreEnergiaNo));

        if (novo != NULL){
            novo->energia = alimento->alimento.energia;
            novo->alimento = alimento;
            novo->esquerda = NULL;
            novo->direita = NULL;

            *posicao = novo;
            inserido = true;
        }
    }

    return inserido;
}

void liberar_arvore_energia(ArvoreEnergiaNo *raiz) {
    if (raiz != NULL){
        liberar_arvore_energia(raiz->esquerda);
        liberar_arvore_energia(raiz->direita);

        free(raiz);
    }
}
