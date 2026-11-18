#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "P1_funcoes.h"
#include "../../alimento.h"

/*
 * ============================================================================
 * MODULO: CONVERSOR DE DADOS TEXTO -> BINARIO (PROGRAMA P1)
 * Arquivo: P1_funcoes.c
 * Disciplina: Programacao Imperativa - PUCPR
 * 
 * Regras do Professor Alcides Calsavara atendidas:
 * - Requisito B: Leitura de arquivo texto (CSV) e gravacao em arquivo binario (dados.bin).
 * - Requisito 9: Proibido o uso de break e continue em lacos de repeticao.
 * - Requisito 10: Tratamento de excecao com exit(1) em falha de abertura de arquivos.
 * - Requisito 12: Codigo extensamente documentado por meio de comentarios.
 * ============================================================================
 */

/*
 * Funcao: converter_arquivo
 * Objetivo: Realiza a carga sequencial dos dados de alimentos do arquivo texto alimentos.csv,
 *           faz a validacao e parsing dos campos e persiste em formato binario nativo (dados.bin).
 * 
 * Estrutura do arquivo de entrada (alimentos.csv):
 *   Numero;Descricao;Energia_Kcal;Proteina_g;Categoria
 *   1;Arroz, integral, cozido;124;2.6;Cereais e derivados
 * 
 * Regras de parsing utilizadas no sscanf:
 *   - %d: Le o codigo identificador inteiro do alimento.
 *   - ; : Consome o caractere delimitador ponto-e-virgula.
 *   - %99[^;]: Le a descricao do alimento (ate encontrar o proximo ';', max 99 chars).
 *   - %f: Le o valor de energia em Kcal.
 *   - %f: Le a quantidade de proteina em gramas.
 *   - %99[^\r\n]: Le o nome da categoria ate o final da linha.
 */
void converter_arquivo(void) {
    const char *caminho_csv = "../../Dados/alimentos.csv";
    const char *caminho_bin = "../../Dados/dados.bin";

    FILE *arquivo_texto = fopen(caminho_csv, "r");
    FILE *arquivo_binario = fopen(caminho_bin, "wb");

    /* Tratamento de excecao conforme Requisito 10 do professor */
    if (arquivo_texto == NULL || arquivo_binario == NULL) {
        printf("[ERRO CRITICO] Falha ao abrir os arquivos para conversao no Programa P1.\n");
        printf("Verifique se o arquivo '%s' existe no diretorio esperado.\n", caminho_csv);
        if (arquivo_texto != NULL) {
            fclose(arquivo_texto);
        }
        if (arquivo_binario != NULL) {
            fclose(arquivo_binario);
        }
        exit(1);
    }

    char linha[512];
    char categoria_texto[100];
    Alimento alimento;
    size_t total_convertidos = 0;

    /* Le e descarta a primeira linha (cabecalho das colunas do CSV) */
    if (fgets(linha, sizeof(linha), arquivo_texto) != NULL) {
        /*
         * Laco de repeticao sem 'break' ou 'continue' (Regra 9):
         * Processa linha por linha do CSV ate atingir o final do arquivo (NULL).
         */
        while (fgets(linha, sizeof(linha), arquivo_texto) != NULL) {
            /* Executa o parsing dos 5 campos da linha */
            if (sscanf(linha, "%d;%99[^;];%f;%f;%99[^\r\n]",
                       &alimento.numero,
                       alimento.descricao,
                       &alimento.energia,
                       &alimento.proteina,
                       categoria_texto) == 5) {

                /* Converte a string de categoria para o enumerado correspondente */
                if (converter_categoria(categoria_texto, &alimento.categoria)) {
                    /* Grava o registro completo da struct em binario no dados.bin */
                    fwrite(&alimento, sizeof(Alimento), 1, arquivo_binario);
                    total_convertidos++;
                }
            }
        }
    }

    /* Fecha os descritores de arquivo */
    fclose(arquivo_texto);
    fclose(arquivo_binario);

    printf("[P1] Conversao concluida com sucesso! Total de alimentos gravados em dados.bin: %zu\n", total_convertidos);
}
