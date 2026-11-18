#ifndef CATEGORIAS_LISTA_H
#define CATEGORIAS_LISTA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../../alimento.h"
#include "../alimentos_lista/alimentos_lista.h"

/*
 * ============================================================================
 * MODULO: LISTA SIMPLESMENTE ENCADEADA DE CATEGORIAS
 * Arquivo: categorias_lista.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.a.1: Lista encadeada denominada Categorias, ordenada alfabeticamente.
 * - Requisito 7: A ordenacao alfabetica segue a insercao ordenada direta (sem sort posterior).
 * - Requisito C.b: Cada categoria contem duas arvores binarias (energia e proteina).
 * - Requisito 4 e 5: Alocacao via malloc e liberacao completa de heap via free.
 * ============================================================================
 */

/*
 * Tipo: CategoriaNo (struct CategoriaNo)
 * Objetivo: Representa um no da lista principal de categorias em memoria heap.
 * Campos:
 *   - categoria: Identificador do enumerado Categoria.
 *   - alimentos: Ponteiro para a cabeca da sublista encadeada de alimentos.
 *   - proxima: Ponteiro para o no da proxima categoria na lista principal.
 *   - arvore_energia: Ponteiro para a raiz da Arvore Binaria de indexacao de energia.
 *   - arvore_proteina: Ponteiro para a raiz da Arvore Binaria de indexacao de proteina.
 */
typedef struct CategoriaNo {
    Categoria categoria;
    AlimentoNo *alimentos;
    struct CategoriaNo *proxima;

    struct ArvoreEnergiaNo *arvore_energia;
    struct ArvoreProteinaNo *arvore_proteina;
} CategoriaNo;

/*
 * Funcao: inserir_alimento_categoria
 * Objetivo: Localiza a categoria do alimento na lista (ou cria um novo no se necessario,
 *           mantendo a ordem alfabetica de categorias) e insere o alimento na sublista.
 * Parametros:
 *   - inicio: Ponteiro duplo para o primeiro no da lista de categorias.
 *   - alimento: Struct com os dados do alimento a ser inserido.
 * Retorno:
 *   - true se a operacao foi concluida com sucesso, false em falha de memoria.
 */
bool inserir_alimento_categoria(CategoriaNo **inicio, Alimento alimento);

/*
 * Funcao: liberar_categorias
 * Objetivo: Desaloca toda a memoria heap do sistema: arvores de energia e proteina,
 *           sublistas de alimentos e todos os nos da lista de categorias (Requisito 5).
 * Parametros:
 *   - inicio: Ponteiro para a cabeca da lista de categorias a ser liberada.
 */
void liberar_categorias(CategoriaNo *inicio);

/*
 * Funcao: construir_arvores
 * Objetivo: Percorre todas as categorias e alimentos em memoria, construindo as respectivas
 *           arvores binarias de busca de energia e de proteina (Requisito C.b).
 * Parametros:
 *   - inicio: Ponteiro para a cabeca da lista de categorias.
 * Retorno:
 *   - true em caso de sucesso na montagem de todas as arvores; false em falha de heap.
 */
bool construir_arvores(CategoriaNo *inicio);

/*
 * Funcao: carregar_dados_binario
 * Objetivo: Le os registros persistidos no arquivo binario dados.bin e monta em memoria
 *           a hierarquia completa de listas encadeadas e arvores binarias.
 * Parametros:
 *   - categorias: Ponteiro duplo para a cabeca da lista de categorias.
 *   - caminho_arquivo: String contendo o caminho relativo/absoluto para o arquivo dados.bin.
 * Retorno:
 *   - true se a leitura e montagem foram concluidas com exito; false em falha de I/O ou heap.
 */
bool carregar_dados_binario(CategoriaNo **categorias, const char *caminho_arquivo);

#endif /* CATEGORIAS_LISTA_H */
