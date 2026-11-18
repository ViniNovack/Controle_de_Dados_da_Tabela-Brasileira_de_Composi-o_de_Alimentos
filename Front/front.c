#include "front.h"
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#endif

/*
 * ============================================================================
 * MODULO DE INTERFACE COM O USUARIO (FRONT-END DE CONSOLE)
 * Arquivo: front.c
 * 
 * Regras do Professor Alcides Calsavara rigorosamente atendidas:
 * 1. Regra 9: Proibido o uso dos comandos 'break' e 'continue' para controle de lacos.
 * 2. Regra 10: Preferencialmente apenas um comando 'return' por funcao.
 * 3. Regra 11: Identificadores bem significativos para variaveis, tipos e funcoes.
 * 4. Regra 12: Codigo fartamente documentado por meio de comentarios explicativos.
 * 5. Regra 5: Liberacao completa de memoria heap em todas as operacoes de remocao.
 * ============================================================================
 */

/*
 * Funcao auxiliar: limpar_buffer_teclado
 * Objetivo: Esvazia o buffer de entrada do teclado (stdin) consumindo todos os
 *           caracteres residuais ate encontrar a quebra de linha ('\n') ou fim de arquivo (EOF).
 *           Evita que sobras de operacoes anteriores interfiram nas leituras seguintes.
 */
static void limpar_buffer_teclado(void) {
    int caractere = getchar();
    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }
}

/*
 * Funcao auxiliar: pausar_tela
 * Objetivo: Pausa a execucao e aguarda o usuario pressionar a tecla ENTER.
 *           Garante que relatorios extensos (como listagem de categorias ou alimentos)
 *           permaneçam visiveis na tela do terminal antes da reimpressao do menu principal.
 */
static void pausar_tela(void) {
    printf("\n[Pressione ENTER para voltar ao menu principal...]");
    fflush(stdout);
    int caractere = getchar();
    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }
}

/*
 * Funcao: selecionar_categoria
 * Objetivo: Apresenta a lista numerada de categorias cadastradas em ordem alfabetica
 *           e solicita ao usuario que escolha uma delas pelo indice.
 * Parametros:
 *   - inicio_categorias: Ponteiro para o no cabeca da lista ligada de categorias.
 * Retorno:
 *   - CategoriaNo*: Ponteiro para o no da categoria selecionada, ou NULL em caso de
 *                   lista vazia, entrada invalida ou indice fora dos limites.
 */
CategoriaNo* selecionar_categoria(CategoriaNo *inicio_categorias) {
    CategoriaNo *categoria_selecionada = NULL;

    if (inicio_categorias == NULL) {
        printf("\n[AVISO] Nenhuma categoria cadastrada no momento.\n");
    } else {
        printf("\n--- SELECAO DE CATEGORIA ---\n");
        int indice = 1;
        CategoriaNo *atual = inicio_categorias;

        /* Percorre a lista encadeada e exibe cada categoria com seu indice sequencial */
        while (atual != NULL) {
            printf(" [%2d] %s\n", indice, obter_nome_categoria(atual->categoria));
            indice++;
            atual = atual->proxima;
        }

        int opcao_escolhida = 0;
        printf("Digite o numero da categoria desejada (1 a %d): ", indice - 1);
        if (scanf(" %d", &opcao_escolhida) == 1) {
            limpar_buffer_teclado();

            /* Localiza o no correspondente ao indice numerico selecionado */
            if (opcao_escolhida >= 1 && opcao_escolhida < indice) {
                int contador = 1;
                atual = inicio_categorias;
                while (contador < opcao_escolhida && atual != NULL) {
                    atual = atual->proxima;
                    contador++;
                }
                categoria_selecionada = atual;
            } else {
                printf("[ERRO] Numero de categoria invalido! Escolha entre 1 e %d.\n", indice - 1);
            }
        } else {
            limpar_buffer_teclado();
            printf("[ERRO] Entrada invalida. Por favor, digite um valor numerico.\n");
        }
    }

    return categoria_selecionada;
}

/*
 * ============================================================================
 * IMPLEMENTACAO DAS OPCOES 1, 2 E 3 (LISTAGENS GERAIS E ENERGIA)
 * ============================================================================
 */

/*
 * Funcao: executar_opcao_1
 * Objetivo: Atende ao requisito C.c.1 do trabalho:
 *           "Liste todas as categorias de alimentos na ordem constante na lista Categorias."
 * Algoritmo: Percorre sequencialmente a lista simplesmente encadeada de categorias,
 *            a qual ja se encontra em ordem alfabetica rigorosa desde a carga inicial.
 * Parametros:
 *   - categorias: Ponteiro para a cabeca da lista de categorias.
 */
void executar_opcao_1(CategoriaNo *categorias) {
    CategoriaNo *atual = categorias;
    int contador = 1;

    printf("\n==============================================================================\n");
    printf(" OPCAO 1: Listar todas as categorias de alimentos\n");
    printf("==============================================================================\n");

    if (atual == NULL) {
        printf("[AVISO] Nenhuma categoria cadastrada no sistema.\n");
    } else {
        while (atual != NULL) {
            printf("  %2d. %s\n", contador, obter_nome_categoria(atual->categoria));
            atual = atual->proxima;
            contador++;
        }
        printf("------------------------------------------------------------------------------\n");
        printf("Total de categorias cadastradas: %d\n", contador - 1);
    }

    pausar_tela();
}

/*
 * Funcao: executar_opcao_2
 * Objetivo: Atende ao requisito C.c.2 do trabalho:
 *           "Liste todos os alimentos de certa categoria na ordem constante na lista
 *            de alimentos dessa categoria."
 * Algoritmo: Solicita a selecao da categoria desejada e varre a lista encadeada interna
 *            de alimentos, exibindo codigo, descricao (truncada a 50 chars), Kcal e proteina.
 * Parametros:
 *   - categorias: Ponteiro para a cabeca da lista de categorias.
 */
void executar_opcao_2(CategoriaNo *categorias) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 2: Listar alimentos de certa categoria em ordem alfabetica\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(categorias);

    if (categoria != NULL) {
        AlimentoNo *alimento_atual = categoria->alimentos;
        printf("\nALIMENTOS: %s\n", obter_nome_categoria(categoria->categoria));
        printf("------------------------------------------------------------------------------\n");
        printf("%-5s | %-50s | %-12s | %-10s\n", "NUM", "DESCRICAO", "ENERGIA", "PROTEINA");
        printf("------------------------------------------------------------------------------\n");

        int total = 0;
        if (alimento_atual == NULL) {
            printf(" [Nenhum alimento cadastrado nesta categoria]\n");
        } else {
            while (alimento_atual != NULL) {
                printf("%-5d | %-50.50s | %8.2f kcal | %7.2f g\n",
                       alimento_atual->alimento.numero,
                       alimento_atual->alimento.descricao,
                       alimento_atual->alimento.energia,
                       alimento_atual->alimento.proteina);
                alimento_atual = alimento_atual->proximo;
                total++;
            }
        }
        printf("------------------------------------------------------------------------------\n");
        printf("Total de alimentos listados: %d\n", total);
        pausar_tela();
    }
}

/*
 * Funcao: listar_arvore_energia_decrescente
 * Objetivo: Realiza o percurso em ordem decrescente (visita subarvore direita -> no raiz ->
 *           subarvore esquerda) na Arvore Binaria de Busca indexada por energia (Kcal).
 * Complexidade: O(N) para visitar todos os N nós da arvore da categoria.
 * Parametros:
 *   - raiz: Ponteiro para o no corrente da ArvoreEnergiaNo.
 *   - contador: Ponteiro para acumulador da quantidade de itens listados.
 */
void listar_arvore_energia_decrescente(const ArvoreEnergiaNo *raiz, int *contador) {
    if (raiz != NULL) {
        /* 1. Visita os maiores valores primeiro (subarvore direita) */
        listar_arvore_energia_decrescente(raiz->direita, contador);

        /* 2. Processa o no atual */
        if (raiz->alimento != NULL) {
            (*contador)++;
            printf("%-5d | %-50.50s | %8.2f kcal | %7.2f g\n",
                   raiz->alimento->alimento.numero,
                   raiz->alimento->alimento.descricao,
                   raiz->energia,
                   raiz->alimento->alimento.proteina);
        }

        /* 3. Visita os menores valores (subarvore esquerda) */
        listar_arvore_energia_decrescente(raiz->esquerda, contador);
    }
}

/*
 * Funcao: executar_opcao_3
 * Objetivo: Atende ao requisito C.c.3 do trabalho:
 *           "Liste todos os alimentos de certa categoria em ordem decrescente com
 *            respeito a energia (em Kcal) dos alimentos. (A implementacao dessa
 *            operacao deve utilizar a correspondente arvore binaria de indexacao.)"
 * Parametros:
 *   - categorias: Ponteiro para a cabeca da lista de categorias.
 */
void executar_opcao_3(CategoriaNo *categorias) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 3: Listar alimentos de certa categoria por energia decrescente (Arvore)\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(categorias);

    if (categoria != NULL) {
        printf("\nALIMENTOS POR ENERGIA (DECRESCENTE): %s\n", obter_nome_categoria(categoria->categoria));
        printf("------------------------------------------------------------------------------\n");
        printf("%-5s | %-50s | %-12s | %-10s\n", "NUM", "DESCRICAO", "ENERGIA", "PROTEINA");
        printf("------------------------------------------------------------------------------\n");

        int total_exibidos = 0;
        if (categoria->arvore_energia != NULL) {
            listar_arvore_energia_decrescente(categoria->arvore_energia, &total_exibidos);
        } else {
            printf(" [Nenhum alimento cadastrado nesta categoria]\n");
        }

        printf("------------------------------------------------------------------------------\n");
        printf("Total de alimentos listados: %d\n", total_exibidos);
        pausar_tela();
    }
}

/*
 * ============================================================================
 * IMPLEMENTACAO DAS OPCOES 4, 5 E 6 (PROTEINA E BUSCA POR INTERVALO NA ARVORE)
 * ============================================================================
 */

/*
 * Funcao: exibir_arvore_proteina_decrescente
 * Objetivo: Realiza o percurso em ordem decrescente na Arvore Binaria de Busca indexada
 *           por proteina (gramas), visitando subarvore direita -> raiz -> subarvore esquerda.
 * Parametros:
 *   - raiz: Ponteiro para o no corrente da ArvoreProteinaNo.
 *   - contador: Ponteiro para acumulador da quantidade de itens listados.
 */
void exibir_arvore_proteina_decrescente(const ArvoreProteinaNo *raiz, int *contador) {
    if (raiz != NULL) {
        /* 1. Visita recursivamente os maiores valores (subarvore direita) */
        exibir_arvore_proteina_decrescente(raiz->direita, contador);

        /* 2. Processa o no corrente */
        if (raiz->alimento != NULL) {
            (*contador)++;
            printf(" %3d | %-50.50s | Proteina: %6.2f g | Energia: %6.1f Kcal\n",
                   raiz->alimento->alimento.numero,
                   raiz->alimento->alimento.descricao,
                   raiz->proteina,
                   raiz->alimento->alimento.energia);
        }

        /* 3. Visita recursivamente os menores valores (subarvore esquerda) */
        exibir_arvore_proteina_decrescente(raiz->esquerda, contador);
    }
}

/*
 * Funcao: executar_opcao_4
 * Objetivo: Atende ao requisito C.c.4 do trabalho:
 *           "Liste todos os alimentos de certa categoria em ordem decrescente com
 *            respeito a quantidade de proteina (em gramas) dos alimentos. (A implementacao
 *            dessa operacao deve utilizar a correspondente arvore binaria de indexacao.)"
 * Parametros:
 *   - categorias: Ponteiro para a cabeca da lista de categorias.
 */
void executar_opcao_4(CategoriaNo *categorias) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 4: Listar alimentos por ordem decrescente de proteina (via Arvore)\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(categorias);

    if (categoria != NULL) {
        printf("\n>> Categoria selecionada: %s\n", obter_nome_categoria(categoria->categoria));
        printf("------------------------------------------------------------------------------\n");
        printf(" COD | %-50.50s |  PROTEINA   |    ENERGIA   \n", "DESCRICAO DO ALIMENTO");
        printf("------------------------------------------------------------------------------\n");

        int total_exibidos = 0;
        if (categoria->arvore_proteina != NULL) {
            exibir_arvore_proteina_decrescente(categoria->arvore_proteina, &total_exibidos);
        } else {
            printf(" [Nenhum alimento cadastrado nesta categoria]\n");
        }

        printf("------------------------------------------------------------------------------\n");
        printf("Total de alimentos listados: %d\n", total_exibidos);
        pausar_tela();
    }
}

/*
 * Funcao: buscar_arvore_energia_faixa
 * Objetivo: Realiza busca com poda de ramos (range query) na Arvore Binaria de Busca de energia.
 *           Evita visitar subarvores que estejam comprovadamente fora do intervalo [min, max],
 *           garantindo desempenho eficiente na arvore indexada.
 * Parametros:
 *   - raiz: Ponteiro para o no corrente da ArvoreEnergiaNo.
 *   - valor_minimo: Limite inferior da faixa de energia (em Kcal).
 *   - valor_maximo: Limite superior da faixa de energia (em Kcal).
 *   - contador: Ponteiro para acumulador de itens encontrados.
 */
void buscar_arvore_energia_faixa(const ArvoreEnergiaNo *raiz, float valor_minimo, float valor_maximo, int *contador) {
    if (raiz != NULL) {
        /* Poda a esquerda: so visita subarvore esquerda se houver chance de valores >= valor_minimo */
        if (raiz->energia > valor_minimo) {
            buscar_arvore_energia_faixa(raiz->esquerda, valor_minimo, valor_maximo, contador);
        }

        /* Processa o no atual caso esteja contido na faixa [min, max] */
        if (raiz->energia >= valor_minimo && raiz->energia <= valor_maximo) {
            if (raiz->alimento != NULL) {
                (*contador)++;
                printf(" %3d | %-50.50s | Energia: %6.1f Kcal | Proteina: %6.2f g\n",
                       raiz->alimento->alimento.numero,
                       raiz->alimento->alimento.descricao,
                       raiz->energia,
                       raiz->alimento->alimento.proteina);
            }
        }

        /* Poda a direita: como chaves repetidas/maiores vao para a direita, visita se raiz->energia <= max */
        if (raiz->energia <= valor_maximo) {
            buscar_arvore_energia_faixa(raiz->direita, valor_minimo, valor_maximo, contador);
        }
    }
}

/*
 * Funcao: executar_opcao_5
 * Objetivo: Atende ao requisito C.c.5 do trabalho:
 *           "Liste todos os alimentos de certa categoria cuja energia esteja entre um
 *            valor minimo e um valor maximo escolhidos pelo usuario. (Arvore)"
 * Parametros:
 *   - categorias: Ponteiro para a cabeca da lista de categorias.
 */
void executar_opcao_5(CategoriaNo *categorias) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 5: Filtrar alimentos por faixa de energia (Kcal) (via Arvore)\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(categorias);

    if (categoria != NULL) {
        float valor_minimo = 0.0f;
        float valor_maximo = 0.0f;

        printf("\nInforme o valor MINIMO de energia (em Kcal): ");
        if (scanf(" %f", &valor_minimo) == 1) {
            limpar_buffer_teclado();

            printf("Informe o valor MAXIMO de energia (em Kcal): ");
            if (scanf(" %f", &valor_maximo) == 1) {
                limpar_buffer_teclado();

                /* Ajusta limites caso o usuario tenha digitado em ordem invertida */
                if (valor_minimo > valor_maximo) {
                    float temporario = valor_minimo;
                    valor_minimo = valor_maximo;
                    valor_maximo = temporario;
                    printf("[INFO] Valores ajustados automaticamente: Min = %.1f, Max = %.1f\n",
                           valor_minimo, valor_maximo);
                }

                printf("\n>> Categoria: %s | Faixa de Energia: [%.1f Kcal ate %.1f Kcal]\n",
                       obter_nome_categoria(categoria->categoria), valor_minimo, valor_maximo);
                printf("------------------------------------------------------------------------------\n");
                printf(" COD | %-50.50s |    ENERGIA   |  PROTEINA   \n", "DESCRICAO DO ALIMENTO");
                printf("------------------------------------------------------------------------------\n");

                int total_encontrados = 0;
                if (categoria->arvore_energia != NULL) {
                    buscar_arvore_energia_faixa(categoria->arvore_energia, valor_minimo, valor_maximo, &total_encontrados);
                }

                printf("------------------------------------------------------------------------------\n");
                printf("Total de alimentos encontrados na faixa: %d\n", total_encontrados);
                pausar_tela();
            } else {
                limpar_buffer_teclado();
                printf("[ERRO] Entrada invalida para o valor maximo.\n");
                pausar_tela();
            }
        } else {
            limpar_buffer_teclado();
            printf("[ERRO] Entrada invalida para o valor minimo.\n");
            pausar_tela();
        }
    }
}

/*
 * Funcao: buscar_arvore_proteina_faixa
 * Objetivo: Realiza busca com poda de ramos (range query) na Arvore Binaria de Busca de proteina.
 * Parametros:
 *   - raiz: Ponteiro para o no corrente da ArvoreProteinaNo.
 *   - valor_minimo: Limite inferior da faixa de proteina (em gramas).
 *   - valor_maximo: Limite superior da faixa de proteina (em gramas).
 *   - contador: Ponteiro para acumulador de itens encontrados.
 */
void buscar_arvore_proteina_faixa(const ArvoreProteinaNo *raiz, float valor_minimo, float valor_maximo, int *contador) {
    if (raiz != NULL) {
        /* Poda a esquerda */
        if (raiz->proteina > valor_minimo) {
            buscar_arvore_proteina_faixa(raiz->esquerda, valor_minimo, valor_maximo, contador);
        }

        /* Processa o no corrente caso pertenca ao intervalo [min, max] */
        if (raiz->proteina >= valor_minimo && raiz->proteina <= valor_maximo) {
            if (raiz->alimento != NULL) {
                (*contador)++;
                printf(" %3d | %-50.50s | Proteina: %6.2f g | Energia: %6.1f Kcal\n",
                       raiz->alimento->alimento.numero,
                       raiz->alimento->alimento.descricao,
                       raiz->proteina,
                       raiz->alimento->alimento.energia);
            }
        }

        /* Poda a direita */
        if (raiz->proteina <= valor_maximo) {
            buscar_arvore_proteina_faixa(raiz->direita, valor_minimo, valor_maximo, contador);
        }
    }
}

/*
 * Funcao: executar_opcao_6
 * Objetivo: Atende ao requisito C.c.6 do trabalho:
 *           "Liste todos os alimentos de certa categoria cuja proteina esteja entre um
 *            valor minimo e um valor maximo escolhidos pelo usuario. (Arvore)"
 * Parametros:
 *   - categorias: Ponteiro para a cabeca da lista de categorias.
 */
void executar_opcao_6(CategoriaNo *categorias) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 6: Filtrar alimentos por faixa de proteina (g) (via Arvore)\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(categorias);

    if (categoria != NULL) {
        float valor_minimo = 0.0f;
        float valor_maximo = 0.0f;

        printf("\nInforme o valor MINIMO de proteina (em gramas): ");
        if (scanf(" %f", &valor_minimo) == 1) {
            limpar_buffer_teclado();

            printf("Informe o valor MAXIMO de proteina (em gramas): ");
            if (scanf(" %f", &valor_maximo) == 1) {
                limpar_buffer_teclado();

                /* Ajusta limites caso invertidos */
                if (valor_minimo > valor_maximo) {
                    float temporario = valor_minimo;
                    valor_minimo = valor_maximo;
                    valor_maximo = temporario;
                    printf("[INFO] Valores ajustados automaticamente: Min = %.2f, Max = %.2f\n",
                           valor_minimo, valor_maximo);
                }

                printf("\n>> Categoria: %s | Faixa de Proteina: [%.2f g ate %.2f g]\n",
                       obter_nome_categoria(categoria->categoria), valor_minimo, valor_maximo);
                printf("------------------------------------------------------------------------------\n");
                printf(" COD | %-50.50s |  PROTEINA   |    ENERGIA   \n", "DESCRICAO DO ALIMENTO");
                printf("------------------------------------------------------------------------------\n");

                int total_encontrados = 0;
                if (categoria->arvore_proteina != NULL) {
                    buscar_arvore_proteina_faixa(categoria->arvore_proteina, valor_minimo, valor_maximo, &total_encontrados);
                }

                printf("------------------------------------------------------------------------------\n");
                printf("Total de alimentos encontrados na faixa: %d\n", total_encontrados);
                pausar_tela();
            } else {
                limpar_buffer_teclado();
                printf("[ERRO] Entrada invalida para o valor maximo.\n");
                pausar_tela();
            }
        } else {
            limpar_buffer_teclado();
            printf("[ERRO] Entrada invalida para o valor minimo.\n");
            pausar_tela();
        }
    }
}

/*
 * ============================================================================
 * IMPLEMENTACAO DAS OPCOES 7, 8 E 9 (REMOCOES E ENCERRAMENTO COM PERSISTENCIA)
 * ============================================================================
 */

/*
 * Funcao: remover_categoria_da_lista
 * Objetivo: Remove um no de categoria da lista simplesmente encadeada de categorias,
 *           liberando toda a memoria heap alocada para sua lista de alimentos e suas
 *           duas arvores binarias de indexacao (energia e proteina).
 * Retorno: true se a categoria foi encontrada e removida, false caso contrario.
 */
bool remover_categoria_da_lista(CategoriaNo **inicio, Categoria categoria_alvo) {
    bool removido = false;

    if (inicio != NULL && *inicio != NULL) {
        CategoriaNo *anterior = NULL;
        CategoriaNo *atual = *inicio;

        while (atual != NULL && atual->categoria != categoria_alvo) {
            anterior = atual;
            atual = atual->proxima;
        }

        if (atual != NULL) {
            if (anterior == NULL) {
                *inicio = atual->proxima;
            } else {
                anterior->proxima = atual->proxima;
            }

            /* Libera todos os recursos dinamicos alocados para esta categoria */
            liberar_arvore_energia(atual->arvore_energia);
            liberar_arvore_proteina(atual->arvore_proteina);
            liberar_alimentos(atual->alimentos);
            free(atual);

            removido = true;
        }
    }

    return removido;
}

/*
 * Funcao: remover_alimento_da_lista
 * Objetivo: Remove um no de alimento da lista simplesmente encadeada de alimentos
 *           de uma determinada categoria com base no seu codigo numerico.
 * Retorno: true se o alimento foi localizado e removido, false caso contrario.
 */
bool remover_alimento_da_lista(AlimentoNo **inicio, int numero_alimento) {
    bool removido = false;

    if (inicio != NULL && *inicio != NULL) {
        AlimentoNo *anterior = NULL;
        AlimentoNo *atual = *inicio;

        while (atual != NULL && atual->alimento.numero != numero_alimento) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual != NULL) {
            if (anterior == NULL) {
                *inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            removido = true;
        }
    }

    return removido;
}

/*
 * Funcao: reconstruir_arvores_categoria
 * Objetivo: Cumpre o requisito C.c.8: atualiza as arvores binarias de indexacao da
 *           categoria afetada, liberando as arvores antigas e gerando novas estruturas
 *           a partir da lista de alimentos atualizada.
 * Retorno: true se a reconstrucao foi concluida com exito, false em caso de falha de alocacao.
 */
bool reconstruir_arvores_categoria(CategoriaNo *categoria) {
    bool sucesso = true;

    if (categoria != NULL) {
        /* 1. Libera a memoria das arvores binarias anteriores */
        liberar_arvore_energia(categoria->arvore_energia);
        liberar_arvore_proteina(categoria->arvore_proteina);
        categoria->arvore_energia = NULL;
        categoria->arvore_proteina = NULL;

        /* 2. Reinsere cada alimento remanescente nas novas arvores */
        AlimentoNo *alimento_atual = categoria->alimentos;

        while (alimento_atual != NULL && sucesso) {
            bool energia_inserida = inserir_arvore_energia(&categoria->arvore_energia, alimento_atual);
            bool proteina_inserida = false;

            if (energia_inserida) {
                proteina_inserida = inserir_arvore_proteina(&categoria->arvore_proteina, alimento_atual);
            }

            if (!energia_inserida || !proteina_inserida) {
                sucesso = false;
            }

            alimento_atual = alimento_atual->proximo;
        }
    }

    return sucesso;
}

/*
 * Funcao: salvar_dados_binario
 * Objetivo: Cumpre o requisito C.c.9: grava em formato binario (dados.bin) todos os
 *           alimentos remanescentes em memoria, garantindo a persistencia das alteracoes.
 * Retorno: true em caso de gravacao correta de todos os registros, false em erro de I/O.
 */
bool salvar_dados_binario(CategoriaNo *categorias, const char *caminho_arquivo) {
    bool sucesso = true;
    FILE *arquivo = fopen(caminho_arquivo, "wb");

    if (arquivo == NULL) {
        sucesso = false;
    } else {
        CategoriaNo *categoria_atual = categorias;

        while (categoria_atual != NULL && sucesso) {
            AlimentoNo *alimento_atual = categoria_atual->alimentos;

            while (alimento_atual != NULL && sucesso) {
                if (fwrite(&alimento_atual->alimento, sizeof(Alimento), 1, arquivo) != 1) {
                    sucesso = false;
                }
                alimento_atual = alimento_atual->proximo;
            }

            categoria_atual = categoria_atual->proxima;
        }

        fclose(arquivo);
    }

    return sucesso;
}

/*
 * Funcao: executar_opcao_7
 * Objetivo: Atende ao requisito C.c.7 do trabalho:
 *           "Remova uma categoria de alimentos."
 */
void executar_opcao_7(CategoriaNo **categorias, bool *dados_modificados) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 7: Remover uma categoria de alimentos\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(*categorias);

    if (categoria != NULL) {
        Categoria categoria_alvo = categoria->categoria;
        char nome_categoria[100];
        strncpy(nome_categoria, obter_nome_categoria(categoria_alvo), sizeof(nome_categoria) - 1);
        nome_categoria[sizeof(nome_categoria) - 1] = '\0';

        printf("\nATENCAO: Todos os alimentos pertencentes a '%s' tambem serao removidos!\n", nome_categoria);
        printf("Confirmar remocao? (1 - Sim / 2 - Nao): ");

        int confirmacao = 0;
        if (scanf(" %d", &confirmacao) == 1) {
            limpar_buffer_teclado();

            if (confirmacao == 1) {
                bool removido = remover_categoria_da_lista(categorias, categoria_alvo);
                if (removido) {
                    *dados_modificados = true;
                    printf("\n[SUCESSO] Categoria '%s' e seus alimentos foram removidos com sucesso!\n", nome_categoria);
                } else {
                    printf("\n[ERRO] Falha ao remover a categoria.\n");
                }
            } else {
                printf("\n[INFO] Operacao de remocao cancelada pelo usuario.\n");
            }
        } else {
            limpar_buffer_teclado();
            printf("\n[ERRO] Opcao invalida. Operacao cancelada.\n");
        }
        pausar_tela();
    }
}

/*
 * Funcao: executar_opcao_8
 * Objetivo: Atende ao requisito C.c.8 do trabalho:
 *           "Remova um alimento especifico. (Essa operacao implica na atualizacao
 *            das arvores binarias de indexacao da correspondente categoria.
 *            Essa atualizacao pode ser feita por meio da criacao novas arvores.)"
 */
void executar_opcao_8(CategoriaNo **categorias, bool *dados_modificados) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 8: Remover um alimento especifico (atualizando as arvores)\n");
    printf("==============================================================================\n");

    CategoriaNo *categoria = selecionar_categoria(*categorias);

    if (categoria != NULL) {
        if (categoria->alimentos == NULL) {
            printf("\n[AVISO] A categoria '%s' nao possui alimentos cadastrados.\n", obter_nome_categoria(categoria->categoria));
            pausar_tela();
        } else {
            printf("\n--- ALIMENTOS DA CATEGORIA '%s' ---\n", obter_nome_categoria(categoria->categoria));
            AlimentoNo *atual = categoria->alimentos;
            while (atual != NULL) {
                printf(" COD: %3d | %-50.50s | %.1f kcal | %.2f g\n",
                       atual->alimento.numero,
                       atual->alimento.descricao,
                       atual->alimento.energia,
                       atual->alimento.proteina);
                atual = atual->proximo;
            }

            printf("\nDigite o CODIGO (numero) do alimento que deseja remover: ");
            int codigo_alimento = 0;
            if (scanf(" %d", &codigo_alimento) == 1) {
                limpar_buffer_teclado();

                bool removido = remover_alimento_da_lista(&categoria->alimentos, codigo_alimento);

                if (removido) {
                    bool arvores_ok = reconstruir_arvores_categoria(categoria);
                    *dados_modificados = true;

                    if (arvores_ok) {
                        printf("\n[SUCESSO] Alimento (Cod: %d) removido e arvores binarias atualizadas com sucesso!\n", codigo_alimento);
                    } else {
                        printf("\n[AVISO] Alimento removido, mas ocorreu uma falha ao reconstruir as arvores binarias.\n");
                    }
                } else {
                    printf("\n[ERRO] Nenhum alimento com o codigo %d foi encontrado nesta categoria.\n", codigo_alimento);
                }
            } else {
                limpar_buffer_teclado();
                printf("\n[ERRO] Codigo invalido. Operacao cancelada.\n");
            }
            pausar_tela();
        }
    }
}

/*
 * Funcao: executar_opcao_9
 * Objetivo: Atende ao requisito C.c.9 do trabalho:
 *           "Encerre o programa, fazendo com que uma versao atualizada do arquivo
 *            dados.bin seja gerada caso alguma categoria ou algum alimento
 *            tenha sido removido."
 */
void executar_opcao_9(CategoriaNo *categorias, bool dados_modificados, bool *executando) {
    printf("\n==============================================================================\n");
    printf(" OPCAO 9: Encerrar o programa\n");
    printf("==============================================================================\n");

    if (dados_modificados) {
        printf("[INFO] Foram detectadas alteracoes nos dados em memoria.\n");
        printf("Atualizando o arquivo '../../Dados/dados.bin'...\n");

        bool sucesso = salvar_dados_binario(categorias, "../../Dados/dados.bin");

        if (sucesso) {
            printf("[SUCESSO] Versao atualizada do arquivo 'dados.bin' gravada com sucesso!\n");
        } else {
            printf("[ERRO] Falha ao gravar o arquivo 'dados.bin'.\n");
        }
    } else {
        printf("[INFO] Nenhuma alteracao foi realizada durante a sessao.\n");
        printf("[INFO] O arquivo 'dados.bin' foi mantido inalterado.\n");
    }

    *executando = false;
}

/*
 * ============================================================================
 * FUNCAO PRINCIPAL DA INTERFACE (LOOP DO MENU)
 * ============================================================================
 */
void executar_interface(CategoriaNo **categorias) {
#ifdef _WIN32
    if (_isatty(_fileno(stdout))) {
        SetConsoleOutputCP(65001);
    }
#endif

    bool executando = true;
    bool dados_modificados = false;

    /*
     * Laco de repeticao controlado estritamente por condicao booleana (executando),
     * sem uso de 'break' ou 'continue', respeitando a Regra 9 do Prof. Alcides.
     */
    while (executando) {
        printf("\n==============================================================================\n");
        printf("        PAINEL DE CONTROLE - TABELA BRASILEIRA DE ALIMENTOS (P2)             \n");
        printf("==============================================================================\n");
        printf(" [1] Listar todas as categorias de alimentos\n");
        printf(" [2] Listar alimentos de uma categoria em ordem alfabetica\n");
        printf(" [3] Listar alimentos de uma categoria por energia decrescente (Arvore)\n");
        printf("------------------------------------------------------------------------------\n");
        printf(" [4] Listar alimentos de uma categoria por proteina decrescente (Arvore)\n");
        printf(" [5] Filtrar alimentos de uma categoria por faixa de energia (Arvore)\n");
        printf(" [6] Filtrar alimentos de uma categoria por faixa de proteina (Arvore)\n");
        printf("------------------------------------------------------------------------------\n");
        printf(" [7] Remover uma categoria de alimentos\n");
        printf(" [8] Remover um alimento especifico\n");
        printf(" [9] Encerrar o programa\n");
        printf("==============================================================================\n");
        printf("Escolha uma opcao (1 a 9): ");
        fflush(stdout);

        int opcao = 0;
        int status_leitura = scanf(" %d", &opcao);
        if (status_leitura == 1) {
            limpar_buffer_teclado();

            if (opcao == 1) {
                executar_opcao_1(*categorias);
            } else if (opcao == 2) {
                executar_opcao_2(*categorias);
            } else if (opcao == 3) {
                executar_opcao_3(*categorias);
            } else if (opcao == 4) {
                executar_opcao_4(*categorias);
            } else if (opcao == 5) {
                executar_opcao_5(*categorias);
            } else if (opcao == 6) {
                executar_opcao_6(*categorias);
            } else if (opcao == 7) {
                executar_opcao_7(categorias, &dados_modificados);
            } else if (opcao == 8) {
                executar_opcao_8(categorias, &dados_modificados);
            } else if (opcao == 9) {
                executar_opcao_9(*categorias, dados_modificados, &executando);
            } else {
                printf("\n[ERRO] Opcao invalida! Digite um valor entre 1 e 9.\n");
                pausar_tela();
            }
        } else {
            if (status_leitura == EOF) {
                executando = false;
            } else {
                limpar_buffer_teclado();
                printf("\n[ERRO] Entrada invalida! Por favor, digite um numero valido entre 1 e 9.\n");
                pausar_tela();
            }
        }
    }

    printf("\nPrograma finalizado com sucesso.\n");
}
