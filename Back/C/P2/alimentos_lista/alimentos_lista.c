#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "alimentos_lista.h"

/*
 * ============================================================================
 * MODULO: LISTA SIMPLESMENTE ENCADEADA DE ALIMENTOS
 * Arquivo: alimentos_lista.c
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.a.2: Cada categoria possui uma lista simplesmente encadeada de alimentos.
 * - Requisito 6: A ordem alfabetica de acordo com a descricao de cada alimento deve
 *   ser garantida pelo proprio algoritmo de construcao da lista (insercao ordenada).
 * - Requisito 4 e 5: Alocacao via malloc e liberacao recursiva/iterativa via free.
 * - Regra 9: Sem comandos break ou continue em lacos de repeticao.
 * ============================================================================
 */

/*
 * Funcao: inserir_alimento
 * Objetivo: Insere um novo registro de alimento na lista simplesmente encadeada de forma
 *           ordenada pela sua descricao alfabetica (strcmp), cumprindo o Requisito 6.
 * Parametros:
 *   - inicio: Ponteiro duplo para a cabeca da lista de alimentos da categoria.
 *   - alimento: Struct contendo os dados (numero, descricao, energia, proteina, categoria).
 * Retorno:
 *   - true: Alimento inserido com sucesso na posicao alfabetica correta.
 *   - false: Falha de alocacao dinamica (malloc).
 */
bool inserir_alimento(AlimentoNo **inicio, Alimento alimento) {
    bool inserido = false;

    if (inicio != NULL) {
        AlimentoNo *novo = malloc(sizeof(AlimentoNo));

        if (novo != NULL) {
            novo->alimento = alimento;
            novo->proximo = NULL;

            /* Insercao no inicio da lista (lista vazia ou novo elemento vem antes do primeiro) */
            if (*inicio == NULL || strcmp(alimento.descricao, (*inicio)->alimento.descricao) < 0) {
                novo->proximo = *inicio;
                *inicio = novo;
            } else {
                /* Percorre ate encontrar o ponto exato de insercao mantendo a ordem alfabetica */
                AlimentoNo *atual = *inicio;

                while (atual->proximo != NULL &&
                       strcmp(atual->proximo->alimento.descricao, alimento.descricao) <= 0) {
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

/*
 * Funcao: liberar_alimentos
 * Objetivo: Desaloca toda a memoria heap utilizada pela lista encadeada de alimentos.
 * Parametros:
 *   - inicio: Ponteiro para o no cabeca da lista de alimentos a ser liberada.
 */
void liberar_alimentos(AlimentoNo *inicio) {
    AlimentoNo *atual = inicio;

    while (atual != NULL) {
        AlimentoNo *remover = atual;
        atual = atual->proximo;
        free(remover);
    }
}
