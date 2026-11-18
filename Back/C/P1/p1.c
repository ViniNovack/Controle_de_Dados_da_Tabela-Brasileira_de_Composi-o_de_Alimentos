#include <stdio.h>
#include <stdlib.h>

#include "funcoes/P1_funcoes.h"

/*
 * ============================================================================
 * PROGRAMA P1 - CONVERSOR DE DADOS DA TABELA TACO (TEXTO PARA BINARIO)
 * Arquivo: p1.c
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Atendimento estrito ao Requisito 3 do Professor Alcides Calsavara:
 * "A funcao main do programa P1 deve ficar no arquivo P1.c.
 *  Os arquivos P1.c e P2.c nao devem possuir correspondentes arquivos de cabecalho.
 *  Desse modo, os arquivos P1.c e P2.c contem somente as respectivas funcoes main
 *  e incluem os arquivos de cabecalho necessarios e somente os necessarios!"
 * ============================================================================
 */

int main(void) {
    /*
     * Dispara o processo de conversao de alimentos.csv para dados.bin
     * isolado no modulo P1_funcoes.
     */
    converter_arquivo();

    return 0;
}
