#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "alimento.h"

/*
 * ============================================================================
 * MODULO: IMPLEMENTACAO DE UTILITARIOS DE CATEGORIA E ALIMENTOS
 * Arquivo: alimento.c
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Regras do Professor Alcides Calsavara atendidas:
 * - Regra 10: Retorno unico ao final de cada funcao (sem multiplos returns dispersos).
 * - Regra 11: Nomenclatura clara e significativa.
 * - Regra 12: Codigo integralmente documentado com comentarios.
 * ============================================================================
 */

/*
 * Funcao: obter_nome_categoria
 * Objetivo: Converte o valor enumerado Categoria em sua representacao textual formatada
 *           em lingua portuguesa, com acentuacao conforme a tabela TACO.
 * Parametros:
 *   - categoria: Constante do enum Categoria.
 * Retorno:
 *   - const char*: Ponteiro para string literal com o nome legivel da categoria.
 */
const char *obter_nome_categoria(Categoria categoria) {
    const char *nome = "Categoria invalida";

    if (categoria == CEREAIS_E_DERIVADOS) {
        nome = "Cereais e derivados";
    } else if (categoria == VERDURAS_HORTALICAS_E_DERIVADOS) {
        nome = "Verduras, hortaliças e derivados";
    } else if (categoria == FRUTAS_E_DERIVADOS) {
        nome = "Frutas e derivados";
    } else if (categoria == GORDURAS_E_OLEOS) {
        nome = "Gorduras e óleos";
    } else if (categoria == PESCADOS_E_FRUTOS_DO_MAR) {
        nome = "Pescados e frutos do mar";
    } else if (categoria == CARNES_E_DERIVADOS) {
        nome = "Carnes e derivados";
    } else if (categoria == LEITE_E_DERIVADOS) {
        nome = "Leite e derivados";
    } else if (categoria == BEBIDAS) {
        nome = "Bebidas (alcoólicas e não alcoólicas)";
    } else if (categoria == OVOS_E_DERIVADOS) {
        nome = "Ovos e derivados";
    } else if (categoria == PRODUTOS_ACUCARADOS) {
        nome = "Produtos açucarados";
    } else if (categoria == MISCELANEAS) {
        nome = "Miscelâneas";
    } else if (categoria == OUTROS_ALIMENTOS_INDUSTRIALIZADOS) {
        nome = "Outros alimentos industrializados";
    } else if (categoria == ALIMENTOS_PREPARADOS) {
        nome = "Alimentos preparados";
    } else if (categoria == LEGUMINOSAS_E_DERIVADOS) {
        nome = "Leguminosas e derivados";
    } else if (categoria == NOZES_E_SEMENTES) {
        nome = "Nozes e sementes";
    }

    /* Retorno unico no final da funcao (Regra 10) */
    return nome;
}

/*
 * Funcao: converter_categoria
 * Objetivo: Interpreta o campo de categoria lido do arquivo texto (CSV) e faz o
 *           parsing para a constante correta do enumerado Categoria.
 * Parametros:
 *   - texto: Ponteiro para a string lida do arquivo alimentos.csv.
 *   - categoria: Ponteiro de saida onde a categoria identificada sera atribuida.
 * Retorno:
 *   - true se a string coincidiu com alguma das 15 categorias da TACO;
 *   - false caso a string seja nula ou nao corresponda a nenhuma categoria cadastrada.
 */
bool converter_categoria(const char *texto, Categoria *categoria) {
    bool encontrada = true;

    if (texto == NULL || categoria == NULL) {
        encontrada = false;
    } else if (strcmp(texto, "Cereais e derivados") == 0) {
        *categoria = CEREAIS_E_DERIVADOS;
    } else if (strcmp(texto, "Verduras, hortaliças e derivados") == 0) {
        *categoria = VERDURAS_HORTALICAS_E_DERIVADOS;
    } else if (strcmp(texto, "Frutas e derivados") == 0) {
        *categoria = FRUTAS_E_DERIVADOS;
    } else if (strcmp(texto, "Gorduras e óleos") == 0) {
        *categoria = GORDURAS_E_OLEOS;
    } else if (strcmp(texto, "Pescados e frutos do mar") == 0) {
        *categoria = PESCADOS_E_FRUTOS_DO_MAR;
    } else if (strcmp(texto, "Carnes e derivados") == 0) {
        *categoria = CARNES_E_DERIVADOS;
    } else if (strcmp(texto, "Leite e derivados") == 0) {
        *categoria = LEITE_E_DERIVADOS;
    } else if (strcmp(texto, "Bebidas (alcoólicas e não alcoólicas)") == 0) {
        *categoria = BEBIDAS;
    } else if (strcmp(texto, "Ovos e derivados") == 0) {
        *categoria = OVOS_E_DERIVADOS;
    } else if (strcmp(texto, "Produtos açucarados") == 0) {
        *categoria = PRODUTOS_ACUCARADOS;
    } else if (strcmp(texto, "Miscelâneas") == 0) {
        *categoria = MISCELANEAS;
    } else if (strcmp(texto, "Outros alimentos industrializados") == 0) {
        *categoria = OUTROS_ALIMENTOS_INDUSTRIALIZADOS;
    } else if (strcmp(texto, "Alimentos preparados") == 0) {
        *categoria = ALIMENTOS_PREPARADOS;
    } else if (strcmp(texto, "Leguminosas e derivados") == 0) {
        *categoria = LEGUMINOSAS_E_DERIVADOS;
    } else if (strcmp(texto, "Nozes e sementes") == 0) {
        *categoria = NOZES_E_SEMENTES;
    } else {
        encontrada = false;
    }

    /* Retorno unico no final da funcao (Regra 10) */
    return encontrada;
}
