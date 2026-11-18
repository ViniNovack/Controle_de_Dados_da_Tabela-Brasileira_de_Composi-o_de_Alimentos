#include <stdio.h>
#include <stdlib.h>

#include "categorias_lista/categorias_lista.h"
#include "../../../Front/front.h"

/*
 * ============================================================================
 * PROGRAMA P2 - SISTEMA DE CONSULTA E GERENCIAMENTO DA TABELA TACO
 * Arquivo: p2.c
 * 
 * Atendimento estrito ao Requisito 3:
 * "A funcao main do programa P2 deve ficar no arquivo P2.c.
 *  Os arquivos P1.c e P2.c nao devem possuir correspondentes arquivos de cabecalho.
 *  Desse modo, os arquivos P1.c e P2.c contem somente as respectivas funcoes main
 *  e incluem os arquivos de cabecalho necessarios e somente os necessarios!"
 * ============================================================================
 */

int main(void) {
    CategoriaNo *categorias = NULL;
    const char *caminho_dados_bin = "../../Dados/dados.bin";

    /*
     * Carrega todos os dados do arquivo binario gerado na Etapa B para a memoria heap,
     * organizando em listas ligadas ordenadas e arvores binarias de indexacao.
     */
    if (carregar_dados_binario(&categorias, caminho_dados_bin)) {
        /* Inicia o loop da interface de console com as opcoes de 1 a 9 */
        executar_interface(&categorias);
    } else {
        printf("[ERRO CRITICO] Falha ao abrir ou carregar os registros de '%s'.\n", caminho_dados_bin);
        printf("Verifique se o programa P1 foi executado previamente para gerar a base binaria.\n");
    }

    /*
     * Atendimento ao Requisito 5:
     * "Toda memoria alocada dinamicamente deve ser liberada antes do termino do programa."
     */
    liberar_categorias(categorias);

    return 0;
}
