#ifndef P1_FUNCOES_H
#define P1_FUNCOES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
 * ============================================================================
 * MODULO: CONVERSOR DE ARQUIVOS - PROGRAMA P1
 * Arquivo: P1_funcoes.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento ao Requisito B do Trabalho:
 * "Escreva um programa P1 na linguagem C que leia os dados sobre alimentos
 *  do arquivo construido na etapa A e armazene esses dados em formato binario
 *  num arquivo denominado dados.bin."
 * ============================================================================
 */

/*
 * Funcao: converter_arquivo
 * Objetivo: Le o arquivo de texto formatado (alimentos.csv) com os 597 alimentos da
 *           tabela TACO, realiza o parsing dos campos e grava os registros em
 *           formato binario estruturado no arquivo dados.bin.
 */
void converter_arquivo(void);

#endif /* P1_FUNCOES_H */
