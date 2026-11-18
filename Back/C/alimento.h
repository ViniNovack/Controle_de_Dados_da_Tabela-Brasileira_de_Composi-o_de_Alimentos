#ifndef ALIMENTO_H
#define ALIMENTO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
 * ============================================================================
 * MODULO: DEFINICAO DE TIPOS E DADOS DE ALIMENTOS
 * Arquivo: alimento.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento aos Requisitos do Trabalho (Prof. Alcides Calsavara):
 * - Requisito 1: "A representacao das categorias de alimentos deve ser
 *   implementada por meio de um enumerado."
 * - Requisito 3: Organizacao em arquivos de cabecalho (.h) com guardas
 *   de inclusao para evitar duplicacao de definicoes.
 * ============================================================================
 */

/*
 * Tipo: Categoria (enum)
 * Objetivo: Representa as 15 categorias oficiais catalogadas na Tabela Brasileira
 *           de Composicao de Alimentos (TACO - 4a edicao).
 *           O uso do tipo enumerado cumpre rigorosamente o Requisito 1.
 */
typedef enum {
    CEREAIS_E_DERIVADOS,                 /* Categoria 1: Cereais, farinhas e paes */
    VERDURAS_HORTALICAS_E_DERIVADOS,     /* Categoria 2: Verduras e hortalicas in natura/preparadas */
    FRUTAS_E_DERIVADOS,                  /* Categoria 3: Frutas frescas e polpas */
    GORDURAS_E_OLEOS,                    /* Categoria 4: Oleos vegetais, manteigas e margarinas */
    PESCADOS_E_FRUTOS_DO_MAR,            /* Categoria 5: Peixes de agua doce/salgada e frutos do mar */
    CARNES_E_DERIVADOS,                  /* Categoria 6: Carnes bovinas, suinas e aves */
    LEITE_E_DERIVADOS,                   /* Categoria 7: Leites, queijos e iogurtes */
    BEBIDAS,                             /* Categoria 8: Bebidas alcoolicas e nao alcoolicas */
    OVOS_E_DERIVADOS,                    /* Categoria 9: Ovos de galinha e derivados */
    PRODUTOS_ACUCARADOS,                 /* Categoria 10: Doces, chocolates e confeitos */
    MISCELANEAS,                         /* Categoria 11: Condimentos, caldos e misturas diversas */
    OUTROS_ALIMENTOS_INDUSTRIALIZADOS,   /* Categoria 12: Produtos ultraprocessados variados */
    ALIMENTOS_PREPARADOS,                /* Categoria 13: Pratos compostos e receitas culinarias */
    LEGUMINOSAS_E_DERIVADOS,             /* Categoria 14: Feijoes, lentilhas, grao-de-bico e soja */
    NOZES_E_SEMENTES                     /* Categoria 15: Castanhas, nozes e sementes oleaginosas */
} Categoria;

/*
 * Tipo: Alimento (struct)
 * Objetivo: Estrutura que encapsula os 5 atributos obrigatorios de cada alimento
 *           transcrito da tabela TACO para a memoria e para o arquivo binario.
 * Atributos:
 *   - numero: Codigo identificador unico sequencial do alimento na tabela TACO.
 *   - descricao: Nome descritivo completo do alimento (capacidade ate 99 caracteres + '\0').
 *   - energia: Valor energetico em Quilocalorias (Kcal).
 *   - proteina: Quantidade de proteinas em gramas (g).
 *   - categoria: Categoria a qual o alimento pertence (tipo enumerado Categoria).
 */
typedef struct {
    int numero;
    char descricao[100];
    float energia;
    float proteina;
    Categoria categoria;
} Alimento;

/*
 * Funcao: obter_nome_categoria
 * Objetivo: Mapeia um valor enumerado Categoria para sua string descritiva em portugues.
 * Parametros:
 *   - categoria: Valor do enum Categoria.
 * Retorno:
 *   - Ponteiro constante para a string textual da categoria.
 */
const char* obter_nome_categoria(Categoria categoria);

/*
 * Funcao: converter_categoria
 * Objetivo: Converte uma string textual lida do CSV na constante correspondente do enum Categoria.
 * Parametros:
 *   - texto: String contendo o nome da categoria vinda do arquivo de texto.
 *   - categoria: Ponteiro de saida onde o valor do enum sera armazenado.
 * Retorno:
 *   - true se a string correspondia a uma categoria valida, false caso contrario.
 */
bool converter_categoria(const char *texto, Categoria *categoria);

#endif /* ALIMENTO_H */
