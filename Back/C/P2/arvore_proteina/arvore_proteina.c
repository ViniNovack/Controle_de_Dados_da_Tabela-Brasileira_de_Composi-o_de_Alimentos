#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "arvore_proteina.h"

/*
 * ============================================================================
 * MODULO: ARVORE BINARIA DE BUSCA PARA INDEXACAO DE PROTEINA (g)
 * Arquivo: arvore_proteina.c
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.b.2: Cada categoria possui uma arvore binaria indexando os dados
 *   sobre proteina (gramas) dos seus respectivos alimentos.
 * - Requisito 8: Cada no da arvore contem a chave (float proteina) e um apontador
 *   para o no do alimento correspondente na lista simplesmente encadeada.
 * - Requisito 4 e 5: Alocacao via malloc e liberacao recursiva via free.
 * - Regra 9: Sem comandos break ou continue em lacos de repeticao.
 * ============================================================================
 */

/*
 * Funcao: inserir_arvore_proteina
 * Objetivo: Insere ordenadamente um novo no na Arvore Binaria de Busca (ABB) de proteina.
 *           Valores de proteina estritamente menores sao direcionados para a subarvore
 *           esquerda; valores maiores ou iguais sao direcionados para a direita.
 * Parametros:
 *   - raiz: Ponteiro duplo para a raiz da arvore binaria de proteina da categoria.
 *   - alimento: Ponteiro para o no da lista encadeada (AlimentoNo) que contem os dados do alimento.
 * Retorno:
 *   - true: Insercao concluida com sucesso e memoria alocada.
 *   - false: Falha de alocacao (malloc) ou parametros nulos.
 */
bool inserir_arvore_proteina(ArvoreProteinaNo **raiz, AlimentoNo *alimento) {
    bool inserido = false;

    if (raiz != NULL && alimento != NULL) {
        ArvoreProteinaNo **posicao = raiz;

        /* Percorre a arvore binaria ate encontrar a posicao folha disponivel */
        while (*posicao != NULL) {
            if (alimento->alimento.proteina < (*posicao)->proteina) {
                posicao = &(*posicao)->esquerda;
            } else {
                posicao = &(*posicao)->direita;
            }
        }

        /* Aloca o novo no de indexacao na heap */
        ArvoreProteinaNo *novo = malloc(sizeof(ArvoreProteinaNo));

        if (novo != NULL) {
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

/*
 * Funcao: liberar_arvore_proteina
 * Objetivo: Desaloca recursivamente toda a memoria dinâmica heap ocupada pelos nos da
 *           arvore binaria de proteina utilizando percurso pos-ordem (esquerda -> direita -> raiz).
 * Parametros:
 *   - raiz: Ponteiro para a raiz da arvore binaria de proteina a ser liberada.
 */
void liberar_arvore_proteina(ArvoreProteinaNo *raiz) {
    if (raiz != NULL) {
        liberar_arvore_proteina(raiz->esquerda);
        liberar_arvore_proteina(raiz->direita);

        free(raiz);
    }
}
