#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "P1_funcoes.h"
#include "../Alimento.h"


void converter_arquivo(void){
    FILE *arquivo_texto = fopen("../../Dados/alimentos.csv", "r");
    FILE *arquivo_binario = fopen("../../Dados/dados.bin", "wb");

    char linha[512];
    char categoria_texto[100];

    Alimento alimento;

    int quantidade = 0;

    while(fgets(linha, sizeof(linha), arquivo_texto) != NULL){     // fgets(arquivo_que_vai_ser_lido, numero_de_caracteres_a_serem_lidos, arquivo_em_que_os_dados_vão_ser_gravados);
        if(sscanf(linha,"%d;%99[^;];%f;%f;%99[^\r\n]",
        &alimento.numero,
        alimento.descricao,
        &alimento.energia,
        &alimento.proteina) == 5){
        
        converter_categoria(categoria_texto, &alimento.categoria);
        fwrite(&alimento, sizeof(Alimento), 1, arquivo_binario);
        quantidade++;
        
        }
    }
}