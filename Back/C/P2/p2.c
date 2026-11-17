#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "categorias_lista/categorias_lista.h"
#include "../../../Front/front.h"


bool carregar_dados(CategoriaNo **categorias){
    bool sucesso = true;

    FILE *arquivo = fopen("../../Dados/dados.bin", "rb");

    if (arquivo == NULL){
        sucesso = false;
    } else {
        Alimento alimento;

        while (sucesso && fread(&alimento, sizeof(Alimento), 1, arquivo) == 1){
            sucesso = inserir_alimento_categoria(categorias, alimento);
        }

        if (ferror(arquivo)){
            sucesso = false;
        }

        fclose(arquivo);
    }

    if (sucesso){
        sucesso = construir_arvores(*categorias);
    }

    if (!sucesso){
        liberar_categorias(*categorias);
        *categorias = NULL;
    }

    return sucesso;
}


int main() {
    CategoriaNo *categorias = NULL;

    size_t total_categorias = 0;
    size_t total_alimentos = 0;

    if (carregar_dados(&categorias)) {
        CategoriaNo *categoria_atual = categorias;

        while (categoria_atual != NULL) {
            total_categorias++;

            AlimentoNo *alimento_atual = categoria_atual->alimentos;

            while (alimento_atual != NULL) {
                total_alimentos++;
                alimento_atual = alimento_atual->proximo;
            }

            categoria_atual = categoria_atual->proxima;
        }

        printf("Dados carregados com sucesso!\n");
        printf("Total de categorias: %zu\n", total_categorias);
        printf("Total de alimentos: %zu\n", total_alimentos);

        /* Inicia a interface do usuario em terminal com o loop de opcoes */
        executar_interface(&categorias);
    } else {
        printf("Erro ao carregar os dados.\n");
    }

    liberar_categorias(categorias);

    return 0;
}
