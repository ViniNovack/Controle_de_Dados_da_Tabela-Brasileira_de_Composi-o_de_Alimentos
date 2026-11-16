#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "categorias_lista.h"
#include "../arvore_energia/arvore_energia.h"
#include "../arvore_proteina/arvore_proteina.h"

bool inserir_alimento_categoria(CategoriaNo **inicio, Alimento alimento) {
    bool inserido = false;
    bool nova_categoria = false;

    if (inicio != NULL) {
        CategoriaNo **posicao = inicio;
        const char *nome_categoria = obter_nome_categoria(alimento.categoria);

        while (*posicao != NULL &&
               strcmp(obter_nome_categoria((*posicao)->categoria), nome_categoria) < 0) {

            posicao = &(*posicao)->proxima;
        }

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

        if (*posicao != NULL && (*posicao)->categoria == alimento.categoria) {
            inserido = inserir_alimento(&(*posicao)->alimentos, alimento);

            if (!inserido && nova_categoria) {
                CategoriaNo *remover = *posicao;

                *posicao = remover->proxima;
                free(remover);
            }
        }
    }

    return inserido;
}

void liberar_categorias(CategoriaNo *inicio) {
    CategoriaNo *atual = inicio;

    while (atual != NULL) {
        CategoriaNo *remover = atual;
        atual = atual->proxima;

        liberar_arvore_energia(remover->arvore_energia);
        liberar_arvore_proteina(remover->arvore_proteina);

        liberar_alimentos(remover->alimentos);

        free(remover);
    }
}

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