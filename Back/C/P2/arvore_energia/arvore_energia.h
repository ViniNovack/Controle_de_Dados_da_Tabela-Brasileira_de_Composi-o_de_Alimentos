#ifndef ARVORE_ENERGIA_H
#define ARVORE_ENERGIA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../alimentos_lista/alimentos_lista.h"

/*
 * ============================================================================
 * MODULO: ARVORE BINARIA DE BUSCA PARA INDEXACAO DE ENERGIA (Kcal)
 * Arquivo: arvore_energia.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.b.1: Indexacao de energia dos alimentos por Arvore Binaria de Busca.
 * - Requisito 8: Cada no contem chave (float energia) e apontador para o no do
 *   alimento correspondente na lista encadeada (AlimentoNo*).
 * - Requisito 4 e 5: Alocacao via malloc e liberacao recursiva via free.
 * ============================================================================
 */

/*
 * Tipo: ArvoreEnergiaNo (struct ArvoreEnergiaNo)
 * Objetivo: Representa um no da Arvore Binaria de Busca que indexa alimentos por energia.
 * Campos:
 *   - energia: Chave de indexacao numerica correspondente as calorias (Kcal).
 *   - alimento: Ponteiro para o no do alimento na lista encadeada da categoria.
 *   - esquerda: Ponteiro para a subarvore esquerda (valores estritamente menores).
 *   - direita: Ponteiro para a subarvore direita (valores maiores ou iguais).
 */
typedef struct ArvoreEnergiaNo {
    float energia;
    AlimentoNo *alimento;
    struct ArvoreEnergiaNo *esquerda;
    struct ArvoreEnergiaNo *direita;
} ArvoreEnergiaNo;

/*
 * Funcao: inserir_arvore_energia
 * Objetivo: Insere ordenadamente um no na Arvore Binaria de Busca de energia.
 * Parametros:
 *   - raiz: Ponteiro duplo para a raiz da arvore de energia.
 *   - alimento: Ponteiro para o no correspondente na lista encadeada de alimentos.
 * Retorno:
 *   - true se a insercao foi bem-sucedida, false em caso de falha de alocacao (malloc).
 */
bool inserir_arvore_energia(ArvoreEnergiaNo **raiz, AlimentoNo *alimento);

/*
 * Funcao: liberar_arvore_energia
 * Objetivo: Desaloca recursivamente toda a memoria heap ocupada pelos nos da arvore.
 * Parametros:
 *   - raiz: Ponteiro para a raiz da arvore binaria de energia a ser liberada.
 */
void liberar_arvore_energia(ArvoreEnergiaNo *raiz);

#endif /* ARVORE_ENERGIA_H */
