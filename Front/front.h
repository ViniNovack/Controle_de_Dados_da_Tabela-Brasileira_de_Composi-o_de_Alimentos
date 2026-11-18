#ifndef FRONT_H
#define FRONT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../Back/C/alimento.h"
#include "../Back/C/P2/categorias_lista/categorias_lista.h"
#include "../Back/C/P2/alimentos_lista/alimentos_lista.h"
#include "../Back/C/P2/arvore_energia/arvore_energia.h"
#include "../Back/C/P2/arvore_proteina/arvore_proteina.h"

/*
 * ============================================================================
 * MODULO: INTERFACE COM O USUARIO (FRONT-END DE CONSOLE DO PROGRAMA P2)
 * Arquivo: front.h
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento aos Requisitos da Interface Interativa (Requisito C.c):
 * "Forneca ao usuario uma interface com as seguintes opcoes em loop:
 *  1. Liste todas as categorias de alimentos na ordem constante na lista Categorias.
 *  2. Liste todos os alimentos de certa categoria na ordem da lista de alimentos.
 *  3. Liste alimentos de certa categoria em ordem decrescente de energia (via Arvore).
 *  4. Liste alimentos de certa categoria em ordem decrescente de proteina (via Arvore).
 *  5. Liste alimentos de certa categoria com energia entre min e max (via Arvore).
 *  6. Liste alimentos de certa categoria com proteina entre min e max (via Arvore).
 *  7. Remova uma categoria de alimentos (liberando memoria heap).
 *  8. Remova um alimento especifico (com reconstrucao das arvores binarias).
 *  9. Encerre o programa (gerando versao atualizada de dados.bin se modificado)."
 * ============================================================================
 */

/*
 * Funcao principal: executar_interface
 * Objetivo: Dispara o loop interativo do menu principal no terminal.
 * Parametros:
 *   - categorias: Ponteiro duplo para a cabeca da lista de categorias em memoria heap.
 */
void executar_interface(CategoriaNo **categorias);

/*
 * Funcao utilitaria: selecionar_categoria
 * Objetivo: Apresenta a lista numerada de categorias e permite ao usuario selecionar uma delas.
 * Parametros:
 *   - inicio_categorias: Ponteiro para o primeiro no da lista de categorias.
 * Retorno:
 *   - CategoriaNo*: Ponteiro para o no da categoria selecionada (ou NULL se invalido).
 */
CategoriaNo* selecionar_categoria(CategoriaNo *inicio_categorias);

/*
 * ============================================================================
 * DECLARACOES DAS OPCOES DO MENU (OPCOES 1 A 9)
 * ============================================================================
 */

/* Opcao 1: Lista todas as categorias de alimentos na ordem da lista principal */
void executar_opcao_1(CategoriaNo *categorias);

/* Opcao 2: Lista todos os alimentos de certa categoria em ordem alfabetica */
void executar_opcao_2(CategoriaNo *categorias);

/* Opcao 3: Lista alimentos de certa categoria em ordem decrescente de energia via Arvore */
void executar_opcao_3(CategoriaNo *categorias);
void listar_arvore_energia_decrescente(const ArvoreEnergiaNo *raiz, int *contador);

/* Opcao 4: Lista alimentos de certa categoria em ordem decrescente de proteina via Arvore */
void executar_opcao_4(CategoriaNo *categorias);
void exibir_arvore_proteina_decrescente(const ArvoreProteinaNo *raiz, int *contador);

/* Opcao 5: Filtra alimentos de certa categoria por faixa de energia [min, max] via Arvore */
void executar_opcao_5(CategoriaNo *categorias);
void buscar_arvore_energia_faixa(const ArvoreEnergiaNo *raiz, float valor_minimo, float valor_maximo, int *contador);

/* Opcao 6: Filtra alimentos de certa categoria por faixa de proteina [min, max] via Arvore */
void executar_opcao_6(CategoriaNo *categorias);
void buscar_arvore_proteina_faixa(const ArvoreProteinaNo *raiz, float valor_minimo, float valor_maximo, int *contador);

/* Opcao 7: Remove uma categoria inteira e libera toda a memoria alocada para ela */
void executar_opcao_7(CategoriaNo **categorias, bool *dados_modificados);

/* Opcao 8: Remove um alimento especifico e reconstroi as duas arvores binarias de indexacao */
void executar_opcao_8(CategoriaNo **categorias, bool *dados_modificados);

/* Opcao 9: Encerra o programa gravando os dados alterados em dados.bin se necessario */
void executar_opcao_9(CategoriaNo *categorias, bool dados_modificados, bool *executando);

/*
 * ============================================================================
 * FUNCOES AUXILIARES DE REMOCAO, RECONSTRUCAO DE INDICES E PERSISTENCIA
 * ============================================================================
 */
bool remover_categoria_da_lista(CategoriaNo **inicio, Categoria categoria_alvo);
bool remover_alimento_da_lista(AlimentoNo **inicio, int numero_alimento);
bool reconstruir_arvores_categoria(CategoriaNo *categoria);
bool salvar_dados_binario(CategoriaNo *categorias, const char *caminho_arquivo);

#endif /* FRONT_H */
