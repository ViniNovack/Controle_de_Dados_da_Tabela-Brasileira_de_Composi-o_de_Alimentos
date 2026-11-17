#include "front.h"

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
        if (scanf("%d", &opcao_escolhida) == 1) {
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
 * IMPLEMENTACAO DAS FUNCOES DO BLOCO DO GUILHERME (Opcoes 4, 5 e 6)
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
        if (scanf("%f", &valor_minimo) == 1) {
            limpar_buffer_teclado();

            printf("Informe o valor MAXIMO de energia (em Kcal): ");
            if (scanf("%f", &valor_maximo) == 1) {
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
        if (scanf("%f", &valor_minimo) == 1) {
            limpar_buffer_teclado();

            printf("Informe o valor MAXIMO de proteina (em gramas): ");
            if (scanf("%f", &valor_maximo) == 1) {
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
 * ESQUELETOS PARA OS DEMAIS INTEGRANTES POPULAREM
 * ============================================================================
 */

/* Bloco do Kulik */
void executar_opcao_1(CategoriaNo *categorias) {
    (void)categorias;
    printf("\n[OPCAO 1 - KULIK] Listar todas as categorias na ordem constante na lista Categorias.\n");
    printf("(Espaco reservado para implementacao do colega Kulik)\n");
}

void executar_opcao_2(CategoriaNo *categorias) {
    (void)categorias;
    printf("\n[OPCAO 2 - KULIK] Listar todos os alimentos de certa categoria na ordem da lista.\n");
    printf("(Espaco reservado para implementacao do colega Kulik)\n");
}

void executar_opcao_3(CategoriaNo *categorias) {
    (void)categorias;
    printf("\n[OPCAO 3 - KULIK] Listar alimentos de certa categoria em ordem decrescente de energia (Arvore).\n");
    printf("(Espaco reservado para implementacao do colega Kulik)\n");
}

/* Bloco da Carol */
void executar_opcao_7(CategoriaNo **categorias) {
    (void)categorias;
    printf("\n[OPCAO 7 - CAROL] Remover uma categoria de alimentos.\n");
    printf("(Espaco reservado para implementacao da colega Carol)\n");
}

void executar_opcao_8(CategoriaNo **categorias) {
    (void)categorias;
    printf("\n[OPCAO 8 - CAROL] Remover um alimento especifico (atualizando as arvores).\n");
    printf("(Espaco reservado para implementacao da colega Carol)\n");
}

void executar_opcao_9(CategoriaNo *categorias, bool *executando) {
    (void)categorias;
    printf("\n[OPCAO 9 - CAROL] Encerrando o programa e atualizando dados.bin caso necessario...\n");
    *executando = false;
}

/*
 * ============================================================================
 * FUNCAO PRINCIPAL DA INTERFACE (LOOP DO MENU)
 * ============================================================================
 */
void executar_interface(CategoriaNo **categorias) {
    bool executando = true;

    /*
     * Laco de repeticao controlado estritamente por condicao booleana (executando),
     * sem uso de 'break' ou 'continue', respeitando a Regra 9 do Prof. Alcides.
     */
    while (executando) {
        printf("\n==============================================================================\n");
        printf("        PAINEL DE CONTROLE - TABELA BRASILEIRA DE ALIMENTOS (P2)             \n");
        printf("==============================================================================\n");
        printf(" [1] Listar todas as categorias de alimentos [Kulik]\n");
        printf(" [2] Listar alimentos de uma categoria em ordem alfabetica [Kulik]\n");
        printf(" [3] Listar alimentos de uma categoria por energia decrescente (Arvore) [Kulik]\n");
        printf("------------------------------------------------------------------------------\n");
        printf(" [4] Listar alimentos de uma categoria por proteina decrescente (Arvore) [Gui]\n");
        printf(" [5] Filtrar alimentos de uma categoria por faixa de energia (Arvore) [Gui]\n");
        printf(" [6] Filtrar alimentos de uma categoria por faixa de proteina (Arvore) [Gui]\n");
        printf("------------------------------------------------------------------------------\n");
        printf(" [7] Remover uma categoria de alimentos [Carol]\n");
        printf(" [8] Remover um alimento especifico [Carol]\n");
        printf(" [9] Encerrar o programa [Carol]\n");
        printf("==============================================================================\n");
        printf("Escolha uma opcao (1 a 9): ");

        int opcao = 0;
        if (scanf("%d", &opcao) == 1) {
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
                executar_opcao_7(categorias);
            } else if (opcao == 8) {
                executar_opcao_8(categorias);
            } else if (opcao == 9) {
                executar_opcao_9(*categorias, &executando);
            } else {
                printf("\n[ERRO] Opcao invalida! Digite um valor entre 1 e 9.\n");
            }
        } else {
            limpar_buffer_teclado();
            printf("\n[ERRO] Entrada invalida! Por favor, digite um numero.\n");
        }
    }

    printf("\nPrograma finalizado com sucesso.\n");
}
