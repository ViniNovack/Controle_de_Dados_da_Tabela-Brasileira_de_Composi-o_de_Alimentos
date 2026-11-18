#ifndef ALIMENTOS_LISTA_H
#define ALIMENTOS_LISTA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../../alimento.h"

/*
 * ============================================================================
 * MODULO: LISTA SIMPLESMENTE ENCADEADA DE ALIMENTOS
 * Arquivo: alimentos_lista.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.a.2: Sublista encadeada de alimentos em cada categoria.
 * - Requisito 6: Insercao ordenada alfabeticamente pela descricao do alimento.
 * - Requisito 4 e 5: Alocacao heap com malloc e desalocacao completa com free.
 * ============================================================================
 */

/*
 * Tipo: AlimentoNo (struct AlimentoNo)
 * Objetivo: Representa um no individual da lista simplesmente encadeada de alimentos.
 * Campos:
 *   - alimento: Struct contendo os 5 atributos (numero, descricao, energia, proteina, categoria).
 *   - proximo: Ponteiro para o proximo alimento da lista encadeada daquela categoria.
 */
typedef struct AlimentoNo {
    Alimento alimento;
    struct AlimentoNo *proximo;
} AlimentoNo;

/*
 * Funcao: inserir_alimento
 * Objetivo: Insere ordenadamente um registro de alimento na lista simplesmente encadeada
 *           de acordo com a ordem alfabetica da sua descricao (Requisito 6).
 * Parametros:
 *   - inicio: Ponteiro duplo para a cabeca da lista de alimentos.
 *   - alimento: Struct com os dados do alimento a ser inserido.
 * Retorno:
 *   - true se alocado e inserido com sucesso; false em falha de memoria.
 */
bool inserir_alimento(AlimentoNo **inicio, Alimento alimento);

/*
 * Funcao: liberar_alimentos
 * Objetivo: Percorre e desaloca com free() todos os nos da lista encadeada de alimentos (Requisito 5).
 * Parametros:
 *   - inicio: Ponteiro para o primeiro no da lista de alimentos a ser liberada.
 */
void liberar_alimentos(AlimentoNo *inicio);

#endif /* ALIMENTOS_LISTA_H */
