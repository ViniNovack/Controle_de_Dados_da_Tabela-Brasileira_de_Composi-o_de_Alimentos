#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "arvore_energia.h"

/*
 * ============================================================================
 * MODULO: ARVORE BINARIA DE BUSCA PARA INDEXACAO DE ENERGIA (Kcal)
 * Arquivo: arvore_energia.c
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.b.1: Cada categoria possui uma arvore binaria indexando os dados
 *   sobre energia (Kcal) dos seus respectivos alimentos.
 * - Requisito 8: Cada no da arvore contem a chave (float energia) e um apontador
 *   para o no do alimento correspondente na lista simplesmente encadeada.
 * - Requisito 4 e 5: Alocacao via malloc e liberacao recursiva via free.
 * - Regra 9: Sem comandos break ou continue em lacos de repeticao.
 * ============================================================================
 */

/*
 * Funcao: inserir_arvore_energia
 * Objetivo: Insere ordenadamente um novo no na Arvore Binaria de Busca (ABB) de energia.
 *           Valores de energia estritamente menores que o no corrente sao direcionados
 *           para a subarvore esquerda; valores maiores ou iguais sao direcionados para a direita.
 * Parametros:
 *   - raiz: Ponteiro duplo para a raiz da arvore binaria de energia da categoria.
 *   - alimento: Ponteiro para o no da lista encadeada (AlimentoNo) que contem os dados do alimento.
 * Retorno:
 *   - true: Insercao concluida com sucesso e memoria alocada.
 *   - false: Falha de alocacao (malloc) ou parametros nulos.
 */
bool inserir_arvore_energia(ArvoreEnergiaNo **raiz, AlimentoNo *alimento) {
    bool inserido = false;

    if (raiz != NULL && alimento != NULL) {
        ArvoreEnergiaNo **posicao = raiz;

        /* Percorre a arvore binaria ate encontrar a posicao folha disponivel */
        while (*posicao != NULL) {
            if (alimento->alimento.energia < (*posicao)->energia) {
                posicao = &(*posicao)->esquerda;
            } else {
                posicao = &(*posicao)->direita;
            }
        }

        /* Aloca o novo no de indexacao na heap */
        ArvoreEnergiaNo *novo = malloc(sizeof(ArvoreEnergiaNo));

        if (novo != NULL) {
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

/*
 * Funcao: liberar_arvore_energia
 * Objetivo: Desaloca recursivamente toda a memoria dinâmica heap ocupada pelos nos da
 *           arvore binaria de energia utilizando percurso pos-ordem (esquerda -> direita -> raiz).
 * Parametros:
 *   - raiz: Ponteiro para a raiz da arvore binaria de energia a ser liberada.
 */
void liberar_arvore_energia(ArvoreEnergiaNo *raiz) {
    if (raiz != NULL) {
        liberar_arvore_energia(raiz->esquerda);
        liberar_arvore_energia(raiz->direita);

        free(raiz);
    }
}
