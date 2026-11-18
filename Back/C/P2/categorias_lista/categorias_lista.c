#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "categorias_lista.h"
#include "../arvore_energia/arvore_energia.h"
#include "../arvore_proteina/arvore_proteina.h"

/*
 * ============================================================================
 * MODULO: LISTA SIMPLESMENTE ENCADEADA DE CATEGORIAS
 * Arquivo: categorias_lista.c
 * 
 * Atendimento aos Requisitos do Trabalho:
 * - Requisito C.a.1: Lista encadeada denominada Categorias, ordenada alfabeticamente.
 * - Requisito 7: A ordenacao alfabetica segue a mesma estrategia de insercao ordenada.
 * - Requisito C.b: Inicializacao e construcao das arvores binarias de cada categoria.
 * - Requisito 4 e 5: Alocacao heap com malloc e desalocacao completa com free.
 * - Regra 9: Sem comandos break ou continue em lacos de repeticao.
 * ============================================================================
 */

/*
 * Funcao: inserir_alimento_categoria
 * Objetivo: Localiza a categoria do alimento na lista encadeada (ou cria uma nova categoria
 *           na posicao alfabetica correta) e insere o alimento na respectiva sublista ordenada.
 * Parametros:
 *   - inicio: Ponteiro duplo para o inicio da lista de categorias.
 *   - alimento: Struct contendo os dados do alimento a ser catalogado.
 * Retorno:
 *   - true se a categoria e o alimento foram inseridos com sucesso, false caso ocorra falha.
 */
bool inserir_alimento_categoria(CategoriaNo **inicio, Alimento alimento) {
    bool inserido = false;
    bool nova_categoria = false;

    if (inicio != NULL) {
        CategoriaNo **posicao = inicio;
        const char *nome_categoria = obter_nome_categoria(alimento.categoria);

        /* Busca a posicao alfabetica da categoria na lista */
        while (*posicao != NULL &&
               strcmp(obter_nome_categoria((*posicao)->categoria), nome_categoria) < 0) {
            posicao = &(*posicao)->proxima;
        }

        /* Se a categoria ainda nao existe na lista, cria um novo no */
        if (*posicao == NULL || (*posicao)->categoria != alimento.categoria) {
            CategoriaNo *novo = malloc(sizeof(CategoriaNo));

            if (novo != NULL) {
                novo->categoria = alimento.categoria;
                novo->alimentos = NULL;
                novo->proxima = *posicao;

                novo->arvore_energia = NULL;
                novo->arvore_proteina = NULL;

                *posicao = novo;
                nova_categoria = true;
            }
        }

        /* Insere o alimento na sublista encadeada da categoria */
        if (*posicao != NULL && (*posicao)->categoria == alimento.categoria) {
            inserido = inserir_alimento(&(*posicao)->alimentos, alimento);

            /* Em caso de falha ao inserir o alimento em nova categoria, desfaz a alocacao da categoria */
            if (!inserido && nova_categoria) {
                CategoriaNo *remover = *posicao;
                *posicao = remover->proxima;
                free(remover);
            }
        }
    }

    return inserido;
}

/*
 * Funcao: liberar_categorias
 * Objetivo: Desaloca toda a memoria ocupada pela lista de categorias, incluindo
 *           suas sublistas de alimentos e todas as arvores binarias de indexacao.
 * Parametros:
 *   - inicio: Ponteiro para o no cabeca da lista de categorias.
 */
void liberar_categorias(CategoriaNo *inicio) {
    CategoriaNo *atual = inicio;

    while (atual != NULL) {
        CategoriaNo *remover = atual;
        atual = atual->proxima;

        /* Libera as duas arvores binarias de indexacao da categoria */
        liberar_arvore_energia(remover->arvore_energia);
        liberar_arvore_proteina(remover->arvore_proteina);

        /* Libera a lista simplesmente encadeada de alimentos da categoria */
        liberar_alimentos(remover->alimentos);

        /* Libera o proprio no de categoria */
        free(remover);
    }
}

/*
 * Funcao: construir_arvores
 * Objetivo: Para cada categoria da lista, percorre sua lista de alimentos e constroi
 *           duas estruturas de arvore binaria de busca: uma indexada por energia (Kcal)
 *           e outra indexada por proteina (gramas), conforme o Requisito C.b.
 * Parametros:
 *   - inicio: Ponteiro para o inicio da lista de categorias.
 * Retorno:
 *   - true se todas as arvores de todas as categorias foram construidas com sucesso.
 */
bool construir_arvores(CategoriaNo *inicio) {
    bool sucesso = true;
    CategoriaNo *categoria_atual = inicio;

    while (categoria_atual != NULL && sucesso) {
        AlimentoNo *alimento_atual = categoria_atual->alimentos;

        while (alimento_atual != NULL && sucesso) {
            bool energia_inserida = inserir_arvore_energia(
                &categoria_atual->arvore_energia,
                alimento_atual
            );

            bool proteina_inserida = false;

            if (energia_inserida) {
                proteina_inserida = inserir_arvore_proteina(
                    &categoria_atual->arvore_proteina,
                    alimento_atual
                );
            }

            if (!energia_inserida || !proteina_inserida) {
                sucesso = false;
            }

            alimento_atual = alimento_atual->proximo;
        }

        categoria_atual = categoria_atual->proxima;
    }

    /* Em caso de falha em qualquer no, desfaz todas as arvores alocadas */
    if (!sucesso) {
        categoria_atual = inicio;

        while (categoria_atual != NULL) {
            liberar_arvore_energia(categoria_atual->arvore_energia);
            liberar_arvore_proteina(categoria_atual->arvore_proteina);

            categoria_atual->arvore_energia = NULL;
            categoria_atual->arvore_proteina = NULL;

            categoria_atual = categoria_atual->proxima;
        }
    }

    return sucesso;
}

/*
 * Funcao: carregar_dados_binario
 * Objetivo: Le todos os registros do arquivo binario gerado na Etapa B (dados.bin)
 *           e constroi em memoria heap a estrutura de listas encadeadas (Categorias e Alimentos),
 *           alem de disparar a construcao das respectivas arvores binarias de indexacao.
 * Parametros:
 *   - categorias: Ponteiro duplo para a cabeca da lista de categorias.
 *   - caminho_arquivo: Caminho relativo ou absoluto do arquivo binario a ser lido.
 * Retorno:
 *   - true se todos os dados foram lidos e estruturados com sucesso, false caso ocorra falha.
 */
bool carregar_dados_binario(CategoriaNo **categorias, const char *caminho_arquivo) {
    bool sucesso = true;

    FILE *arquivo = fopen(caminho_arquivo, "rb");

    if (arquivo == NULL) {
        sucesso = false;
    } else {
        Alimento alimento;

        while (sucesso && fread(&alimento, sizeof(Alimento), 1, arquivo) == 1) {
            sucesso = inserir_alimento_categoria(categorias, alimento);
        }

        if (ferror(arquivo)) {
            sucesso = false;
        }

        fclose(arquivo);
    }

    if (sucesso) {
        sucesso = construir_arvores(*categorias);
    }

    if (!sucesso) {
        liberar_categorias(*categorias);
        *categorias = NULL;
    }

    return sucesso;
}
