#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "P1_funcoes.h"
#include "../../Alimento.h"


void converter_arquivo(void){
    FILE *arquivo_texto = fopen("../../Dados/alimentos.csv", "r");
    FILE *arquivo_binario = fopen("../../Dados/dados.bin", "wb");

    char linha[512];
    char categoria_texto[100];

    Alimento alimento;

    fgets(linha, sizeof(linha), arquivo_texto); // Essa linha se le apenas colunas
    while(fgets(linha, sizeof(linha), arquivo_texto) != NULL){   // Essa linha se le todos os alimentos  // fgets(arquivo_que_vai_ser_lido, numero_de_caracteres_a_serem_lidos, arquivo_em_que_os_dados_vão_ser_gravados);
        if(sscanf(linha,"%d;%99[^;];%f;%f;%99[^\r\n]",
        &alimento.numero,
        alimento.descricao,
        &alimento.energia,
        &alimento.proteina,
        categoria_texto) == 5){
        
        if(converter_categoria(categoria_texto, &alimento.categoria)){
            fwrite(&alimento, sizeof(Alimento), 1, arquivo_binario);
        }
        }
    }

    fclose(arquivo_texto);
    fclose(arquivo_binario);
}

// sscanf() vai interpretar as linhas seguindo as seguintes regras:
// Parte	                        Significado	                                              Resultado
//  %d	                       Lê um número inteiro	                                               1
//  ;	                  Espera encontrar um ponto e vírgula	                                   ;
// %99[^;]	            Lê até encontrar ;, limitando a 99 caracteres	              Arroz, integral, cozido
//  ;	                        Espera encontrar ;	                                               ;
//  %f	                       Lê um número decimal	                                              124
//  ;	                         Espera encontrar ;	                                               ;
//  %f	                      Lê outro número decimal	                                          2.6
//  ;	                         Espera encontrar ;	                                               ;
// %99[^\r\n]	         Lê até encontrar uma quebra de linha, limitando a 99 caracteres        Cereais e derivados