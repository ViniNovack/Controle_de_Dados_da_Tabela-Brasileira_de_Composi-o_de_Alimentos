#ifndef ARVORE_PROTEINA_H
#define ARVORE_PROTEINA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../alimentos_lista/alimentos_lista.h"

/*
 * ============================================================================
 * MODULO: ARVORE BINARIA DE BUSCA PARA INDEXACAO DE PROTEINA (g)
 * Arquivo: arvore_proteina.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.b.2: Indexacao de proteina dos alimentos por Arvore Binaria de Busca.
 * - Requisito 8: Cada no contem chave (float proteina) e apontador para o no do
 *   alimento correspondente na lista encadeada (AlimentoNo*).
 * - Requisito 4 e 5: Alocacao via malloc e liberacao recursiva via free.
 * ============================================================================
 */

/*
 * Tipo: ArvoreProteinaNo (struct ArvoreProteinaNo)
 * Objetivo: Representa um no da Arvore Binaria de Busca que indexa alimentos por proteina.
 * Campos:
 *   - proteina: Chave de indexacao numerica correspondente a proteina em gramas (g).
 *   - alimento: Ponteiro para o no do alimento na lista encadeada da categoria.
 *   - esquerda: Ponteiro para a subarvore esquerda (valores estritamente menores).
 *   - direita: Ponteiro para a subarvore direita (valores maiores ou iguais).
 */
typedef struct ArvoreProteinaNo {
    float proteina;
    AlimentoNo *alimento;
    struct ArvoreProteinaNo *esquerda;
    struct ArvoreProteinaNo *direita;
} ArvoreProteinaNo;

/*
 * Funcao: inserir_arvore_proteina
 * Objetivo: Insere ordenadamente um no na Arvore Binaria de Busca de proteina.
 * Parametros:
 *   - raiz: Ponteiro duplo para a raiz da arvore de proteina.
 *   - alimento: Ponteiro para o no correspondente na lista encadeada de alimentos.
 * Retorno:
 *   - true se a insercao foi bem-sucedida, false em caso de falha de alocacao (malloc).
 */
bool inserir_arvore_proteina(ArvoreProteinaNo **raiz, AlimentoNo *alimento);

/*
 * Funcao: liberar_arvore_proteina
 * Objetivo: Desaloca recursivamente toda a memoria heap ocupada pelos nos da arvore.
 * Parametros:
 *   - raiz: Ponteiro para a raiz da arvore binaria de proteina a ser liberada.
 */
void liberar_arvore_proteina(ArvoreProteinaNo *raiz);

#endif /* ARVORE_PROTEINA_H */
