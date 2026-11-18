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
 * MODULO DE INTERFACE COM O USUARIO (FRONT-END DE CONSOLE)
 * Trabalho do RA2 - Programacao Imperativa - PUCPR
 * ============================================================================
 */

/* Funcao principal que inicia o loop do menu interativo */
void executar_interface(CategoriaNo **categorias);

/* Funcao utilitaria para selecao de categoria pelo usuario */
CategoriaNo* selecionar_categoria(CategoriaNo *inicio_categorias);

/*
 * Opcoes 1, 2 e 3: Listagem de categorias e alimentos
 */
void executar_opcao_1(CategoriaNo *categorias);
void executar_opcao_2(CategoriaNo *categorias);
void executar_opcao_3(CategoriaNo *categorias);

/*
 * Opcoes 4, 5 e 6: Consultas com arvores binarias de proteina e energia
 */
/* Opcao 4: Listar alimentos de uma categoria em ordem decrescente de proteina */
void executar_opcao_4(CategoriaNo *categorias);
void exibir_arvore_proteina_decrescente(const ArvoreProteinaNo *raiz, int *contador);

/* Opcao 5: Listar alimentos de uma categoria por faixa de energia [min, max] */
void executar_opcao_5(CategoriaNo *categorias);
void buscar_arvore_energia_faixa(const ArvoreEnergiaNo *raiz, float valor_minimo, float valor_maximo, int *contador);

/* Opcao 6: Listar alimentos de uma categoria por faixa de proteina [min, max] */
void executar_opcao_6(CategoriaNo *categorias);
void buscar_arvore_proteina_faixa(const ArvoreProteinaNo *raiz, float valor_minimo, float valor_maximo, int *contador);

/*
 * Opcoes 7, 8 e 9: Remocoes e encerramento
 */
void executar_opcao_7(CategoriaNo **categorias);
void executar_opcao_8(CategoriaNo **categorias);
void executar_opcao_9(CategoriaNo *categorias, bool *executando);

#endif /* FRONT_H */
