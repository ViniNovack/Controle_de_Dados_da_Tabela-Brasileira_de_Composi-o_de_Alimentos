#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>~

#include "categorias_lista/categorias_lista.h"

bool carregar_dados(CategoriaNo **categorias) {
    bool sucesso = true;

    FILE *arquivo = fopen("../../Dados/dados.bin", "rb");

    if (arquivo == NULL){
        sucesso = false;
    } else{
        Alimento alimento;

        while (fread(&alimento, sizeof(Alimento), 1, arquivo) == 1){
            if (!inserir_alimento_categoria(categorias, alimento)){
                sucesso = false;
                break;
            }
        }

        if (ferror(arquivo)){
            sucesso = false;
        }

        fclose(arquivo);
    }

    if (!sucesso){
        liberar_categorias(*categorias);
        *categorias = NULL;
    }

    return sucesso;
}

int main(){
    CategoriaNo *categorias = NULL;

    if (carregar_dados(&categorias)) {
        printf("Dados carregados com sucesso!\n");
    } else{
        printf("Erro ao carregar os dados.\n");
    }

    liberar_categorias(categorias);

    return 0;
}
