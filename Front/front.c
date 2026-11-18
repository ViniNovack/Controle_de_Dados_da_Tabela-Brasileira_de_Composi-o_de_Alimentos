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
 * Regras do Professor Alcides Calsavara seguidas:
 * 1. Proibido o uso dos comandos break e continue para controle de lacos.
 * 2. Preferencialmente apenas um comando return por funcao.
 * 3. Identificadores significativos para variaveis, tipos e funcoes.
 * 4. Codigo documentado detalhadamente com comentarios.
 * ============================================================================
 */

/*
 * Funcao auxiliar: Limpa o buffer de entrada do teclado (stdin)
 * Evita problemas com sobras de quebra de linha (\n) do scanf.
 */
static void limpar_buffer_teclado(void) {
    int caractere = getchar();
    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }
}

/*
 * Funcao: selecionar_categoria
 * Objetivo: Apresenta a lista numerada de categorias cadastradas e permite
 *           que o usuario escolha uma delas pelo indice.
 * Retorno: Ponteiro para o no da categoria selecionada (CategoriaNo*),
 *          ou NULL caso a lista esteja vazia ou a opcao seja invalida.
 */
CategoriaNo* selecionar_categoria(CategoriaNo *inicio_categorias) {
    CategoriaNo *categoria_selecionada = NULL;

    if (inicio_categorias == NULL) {
        printf("\n[AVISO] Nenhuma categoria cadastrada no momento.\n");
    } else {
        printf("\n--- SELECAO DE CATEGORIA ---\n");
        int indice = 1;
        CategoriaNo *atual = inicio_categorias;

        /* Percorre a lista de categorias e exibe com numeracao sequencial */
        while (atual != NULL) {
            printf(" [%2d] %s\n", indice, obter_nome_categoria(atual->categoria));
            indice++;
            atual = atual->proxima;
        }

        int opcao_escolhida = 0;
        printf("Digite o numero da categoria desejada (1 a %d): ", indice - 1);
        if (scanf(" %d", &opcao_escolhida) == 1) {
            limpar_buffer_teclado();

            /* Localiza o no correspondente ao indice informado */
            if (opcao_escolhida >= 1 && opcao_escolhida < indice) {
                int contador = 1;
                atual = inicio_categorias;
                while (contador < opcao_escolhida && atual != NULL) {
                    atual = atual->proxima;
                    contador++;
                }
                categoria_selecionada = atual;
            } else {
                printf("[ERRO] Numero de categoria invalido!\n");
            }
        } else {
            limpar_buffer_teclado();
            printf("[ERRO] Entrada invalida. Por favor, digite um numero.\n");
        }
    }

    return categoria_selecionada;
}

/*
 * ============================================================================
 * IMPLEMENTACAO DAS OPCOES 4, 5 e 6
 * ============================================================================
 */

/*
 * Funcao: exibir_arvore_proteina_decrescente
 * Objetivo: Realiza o percurso em ordem decrescente na arvore binaria de proteina.
 *           Como a arvore armazena valores menores a esquerda e maiores/iguais
 *           a direita, o percurso decrescente visita primeiro a subarvore direita,
 *           depois o no atual (raiz) e por fim a subarvore esquerda.
 * Parametros:
 *   - raiz: Ponteiro para a raiz da arvore binaria de proteina.
 *   - contador: Ponteiro para acumulador da quantidade de itens exibidos.
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
 * Objetivo: Cumpre o requisito C.c.4 do trabalho:
 *           "Liste todos os alimentos de certa categoria em ordem decrescente
 *            com respeito a quantidade de proteina (em gramas) dos alimentos.
 *            (A implementacao dessa operacao deve utilizar a correspondente
 *            arvore binaria de indexacao.)"
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
        }

        printf("------------------------------------------------------------------------------\n");
        printf("Total de alimentos listados: %d\n", total_exibidos);
    }
}

/*
 * Funcao: buscar_arvore_energia_faixa
 * Objetivo: Realiza busca por faixa [valor_minimo, valor_maximo] na arvore
 *           binaria de energia, aproveitando a propriedade de ordenacao da BST
 *           para podar subarvores que estejam fora dos limites.
 * Parametros:
 *   - raiz: Ponteiro para o no da arvore binaria de energia.
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

        /* Verifica se o valor do no atual esta dentro do intervalo desejado [min, max] */
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

        /* Poda a direita: como valores maiores ou iguais vao para a direita,
           visita a subarvore direita se raiz->energia <= valor_maximo */
        if (raiz->energia <= valor_maximo) {
            buscar_arvore_energia_faixa(raiz->direita, valor_minimo, valor_maximo, contador);
        }
    }
}

/*
 * Funcao: executar_opcao_5
 * Objetivo: Cumpre o requisito C.c.5 do trabalho:
 *           "Liste todos os alimentos de certa categoria cuja energia esteja
 *            entre um valor minimo e um valor maximo escolhidos pelo usuario.
 *            (A implementacao dessa operacao deve utilizar a correspondente
 *            arvore binaria de indexacao.)"
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
                    printf("[INFO] Valores invertidos ajustados automaticamente: Min = %.1f, Max = %.1f\n",
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
            } else {
                limpar_buffer_teclado();
                printf("[ERRO] Entrada invalida para o valor maximo.\n");
            }
        } else {
            limpar_buffer_teclado();
            printf("[ERRO] Entrada invalida para o valor minimo.\n");
        }
    }
}

/*
 * Funcao: buscar_arvore_proteina_faixa
 * Objetivo: Realiza busca por faixa [valor_minimo, valor_maximo] na arvore
 *           binaria de proteina com poda de ramos desnecessarios.
 * Parametros:
 *   - raiz: Ponteiro para o no da arvore binaria de proteina.
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

        /* Processa o no se estiver no intervalo */
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
 * Objetivo: Cumpre o requisito C.c.6 do trabalho:
 *           "Liste todos os alimentos de certa categoria cuja proteina esteja
 *            entre um valor minimo e um valor maximo escolhidos pelo usuario.
 *            (A implementacao dessa operacao deve utilizar a correspondente
 *            arvore binaria de indexacao.)"
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
                    printf("[INFO] Valores invertidos ajustados automaticamente: Min = %.2f, Max = %.2f\n",
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
            } else {
                limpar_buffer_teclado();
                printf("[ERRO] Entrada invalida para o valor maximo.\n");
            }
        } else {
            limpar_buffer_teclado();
            printf("[ERRO] Entrada invalida para o valor minimo.\n");
        }
    }
}

/*
 * ============================================================================
 * IMPLEMENTACAO DAS OPCOES 1, 2 e 3
 * ============================================================================
 */

/*
 * Funcao: executar_opcao_1
 * Objetivo: Cumpre o requisito C.c.1 do trabalho:
 *           "Liste todas as categorias de alimentos na ordem constante na lista Categorias."
 */
void executar_opcao_1(CategoriaNo *categorias) {
    CategoriaNo *atual = categorias;
    int contador = 1;

    printf("\n==============================================================================\n");
    printf(" OPCAO 1: Listar todas as categorias de alimentos\n");
    printf("==============================================================================\n");
    while (atual != NULL) {
        printf(" %2d. %s\n", contador, obter_nome_categoria(atual->categoria));
        atual = atual->proxima;
        contador++;
    }
    printf("------------------------------------------------------------------------------\n");
    printf("Total de categorias: %d\n", contador - 1);
}

/*
 * Funcao: executar_opcao_2
 * Objetivo: Cumpre o requisito C.c.2 do trabalho:
 *           "Liste todos os alimentos de certa categoria na ordem constante na lista de alimentos dessa categoria."
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
        while (alimento_atual != NULL) {
            printf("%-5d | %-50.50s | %8.2f kcal | %7.2f g\n",
                   alimento_atual->alimento.numero,
                   alimento_atual->alimento.descricao,
                   alimento_atual->alimento.energia,
                   alimento_atual->alimento.proteina);
            alimento_atual = alimento_atual->proximo;
            total++;
        }
        printf("------------------------------------------------------------------------------\n");
        printf("Total de alimentos: %d\n", total);
    }
}

/*
 * Funcao: listar_arvore_energia_decrescente
 * Objetivo: Realiza o percurso decrescente na arvore binaria de energia (Direita -> Raiz -> Esquerda).
 */
void listar_arvore_energia_decrescente(const ArvoreEnergiaNo *raiz) {
    if (raiz != NULL) {
        listar_arvore_energia_decrescente(raiz->direita);
        if (raiz->alimento != NULL) {
            printf("%-5d | %-50.50s | %8.2f kcal | %7.2f g\n",
                   raiz->alimento->alimento.numero,
                   raiz->alimento->alimento.descricao,
                   raiz->energia,
                   raiz->alimento->alimento.proteina);
        }
        listar_arvore_energia_decrescente(raiz->esquerda);
    }
}

/*
 * Funcao: executar_opcao_3
 * Objetivo: Cumpre o requisito C.c.3 do trabalho:
 *           "Liste todos os alimentos de certa categoria em ordem decrescente
 *            com respeito a energia (em Kcal) dos alimentos. (Arvore)"
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
        listar_arvore_energia_decrescente(categoria->arvore_energia);
        printf("------------------------------------------------------------------------------\n");
    }
}

/*
 * ============================================================================
 * IMPLEMENTACAO DAS OPCOES 7, 8 e 9 E FUNCOES AUXILIARES
 * ============================================================================
 */

/*
 * Funcao: remover_categoria_da_lista
 * Objetivo: Remove um no de categoria da lista simplesmente encadeada de categorias,
 *           liberando toda a memoria alocada para sua lista de alimentos e suas
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

            /* Libera todos os recursos alocados para esta categoria */
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
 *           de uma categoria com base no seu codigo numerico.
 * Retorno: true se o alimento foi encontrado e removido, false caso contrario.
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
 * Objetivo: Atualiza as arvores binarias de indexacao (energia e proteina) de uma
 *           determinada categoria apos a remocao de um alimento, liberando as
 *           arvores antigas e reconstruindo novas arvores a partir da lista
 *           encadeada atualizada de alimentos.
 * Retorno: true se a reconstrucao foi bem-sucedida, false em caso de falha de alocacao.
 */
bool reconstruir_arvores_categoria(CategoriaNo *categoria) {
    bool sucesso = true;

    if (categoria != NULL) {
        /* Libera as arvores anteriores */
        liberar_arvore_energia(categoria->arvore_energia);
        liberar_arvore_proteina(categoria->arvore_proteina);
        categoria->arvore_energia = NULL;
        categoria->arvore_proteina = NULL;

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
 * Objetivo: Grava todos os alimentos atualmente em memoria em formato binario
 *           no arquivo especificado (dados.bin).
 * Retorno: true em caso de sucesso na gravacao, false caso ocorra falha de I/O.
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
 * Objetivo: Cumpre o requisito C.c.7 do trabalho:
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
                    printf("\n[SUCESSO] Categoria '%s' e todos os seus alimentos foram removidos com sucesso!\n", nome_categoria);
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
    }
}

/*
 * Funcao: executar_opcao_8
 * Objetivo: Cumpre o requisito C.c.8 do trabalho:
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
        }
    }
}

/*
 * Funcao: executar_opcao_9
 * Objetivo: Cumpre o requisito C.c.9 do trabalho:
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
            printf("[SUCESSO] Versao atualizada do arquivo 'dados.bin' foi gravada com sucesso!\n");
        } else {
            printf("[ERRO] Nao foi possivel gravar o arquivo 'dados.bin'.\n");
        }
    } else {
        printf("[INFO] Nenhuma alteracao foi realizada durante a execucao.\n");
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
            }
        } else {
            if (status_leitura == EOF) {
                executando = false;
            } else {
                limpar_buffer_teclado();
                printf("\n[ERRO] Entrada invalida! Por favor, digite um numero.\n");
            }
        }
    }

    printf("\nPrograma finalizado com sucesso.\n");
}
