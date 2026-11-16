#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "arvore_proteina.h"

bool inserir_arvore_proteina(ArvoreProteinaNo **raiz, AlimentoNo *alimento){
    bool inserido = false;

    if (raiz != NULL && alimento != NULL){
        ArvoreProteinaNo **posicao = raiz;

        while (*posicao != NULL) {
            if (alimento->alimento.proteina < (*posicao)->proteina){
                posicao = &(*posicao)->esquerda;
            } else {
                posicao = &(*posicao)->direita;
            }
        }

        ArvoreProteinaNo *novo = malloc(sizeof(ArvoreProteinaNo));

        if (novo != NULL){
            novo->proteina = alimento->alimento.proteina;
            novo->alimento = alimento;
            novo->esquerda = NULL;
            novo->direita = NULL;

            *posicao = novo;
            inserido = true;
        }
    }

    return inserido;
}

void liberar_arvore_proteina(ArvoreProteinaNo *raiz){
    if (raiz != NULL){
        liberar_arvore_proteina(raiz->esquerda);
        liberar_arvore_proteina(raiz->direita);

        free(raiz);
    }
}