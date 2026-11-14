#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Alimento.h"


const char *obter_nome_categoria(Categoria categoria){
    const char *nome = "Categoria invalida";

    if (categoria == CEREAIS_E_DERIVADOS) {
        nome = "Cereais e derivados";
    } else if (categoria == VERDURAS_HORTALICAS_E_DERIVADOS) {
        nome = "Verduras, hortaliças e derivados";
    } else if (categoria == FRUTAS_E_DERIVADOS) {
        nome = "Frutas e derivados";
    } else if (categoria == GORDURAS_E_OLEOS) {
        nome = "Gorduras e óleos";
    } else if (categoria == PESCADOS_E_FRUTOS_DO_MAR) {
        nome = "Pescados e frutos do mar";
    } else if (categoria == CARNES_E_DERIVADOS) {
        nome = "Carnes e derivados";
    } else if (categoria == LEITE_E_DERIVADOS) {
        nome = "Leite e derivados";
    } else if (categoria == BEBIDAS) {
        nome = "Bebidas (alcoólicas e não alcoólicas)";
    } else if (categoria == OVOS_E_DERIVADOS) {
        nome = "Ovos e derivados";
    } else if (categoria == PRODUTOS_ACUCARADOS) {
        nome = "Produtos açucarados";
    } else if (categoria == MISCELANEAS) {
        nome = "Miscelâneas";
    } else if (categoria == OUTROS_ALIMENTOS_INDUSTRIALIZADOS) {
        nome = "Outros alimentos industrializados";
    } else if (categoria == ALIMENTOS_PREPARADOS) {
        nome = "Alimentos preparados";
    } else if (categoria == LEGUMINOSAS_E_DERIVADOS) {
        nome = "Leguminosas e derivados";
    } else if (categoria == NOZES_E_SEMENTES) {
        nome = "Nozes e sementes";
    }

    return nome;
}

bool converter_categoria(const char *texto, Categoria *categoria){
    bool encontrada = true;

    if (texto == NULL || categoria == NULL) {
        encontrada = false;
    } else if (strcmp(texto, "Cereais e derivados") == 0) {
        *categoria = CEREAIS_E_DERIVADOS;
    } else if (strcmp(texto, "Verduras, hortaliças e derivados") == 0) {
        *categoria = VERDURAS_HORTALICAS_E_DERIVADOS;
    } else if (strcmp(texto, "Frutas e derivados") == 0) {
        *categoria = FRUTAS_E_DERIVADOS;
    } else if (strcmp(texto, "Gorduras e óleos") == 0) {
        *categoria = GORDURAS_E_OLEOS;
    } else if (strcmp(texto, "Pescados e frutos do mar") == 0) {
        *categoria = PESCADOS_E_FRUTOS_DO_MAR;
    } else if (strcmp(texto, "Carnes e derivados") == 0) {
        *categoria = CARNES_E_DERIVADOS;
    } else if (strcmp(texto, "Leite e derivados") == 0) {
        *categoria = LEITE_E_DERIVADOS;
    } else if (strcmp(texto, "Bebidas (alcoólicas e não alcoólicas)") == 0) {
        *categoria = BEBIDAS;
    } else if (strcmp(texto, "Ovos e derivados") == 0) {
        *categoria = OVOS_E_DERIVADOS;
    } else if (strcmp(texto, "Produtos açucarados") == 0) {
        *categoria = PRODUTOS_ACUCARADOS;
    } else if (strcmp(texto, "Miscelâneas") == 0) {
        *categoria = MISCELANEAS;
    } else if (strcmp(texto, "Outros alimentos industrializados") == 0) {
        *categoria = OUTROS_ALIMENTOS_INDUSTRIALIZADOS;
    } else if (strcmp(texto, "Alimentos preparados") == 0) {
        *categoria = ALIMENTOS_PREPARADOS;
    } else if (strcmp(texto, "Leguminosas e derivados") == 0) {
        *categoria = LEGUMINOSAS_E_DERIVADOS;
    } else if (strcmp(texto, "Nozes e sementes") == 0) {
        *categoria = NOZES_E_SEMENTES;
    } else {
        encontrada = false;
    }

    return encontrada;
}

// Resultado	                 Significado
//     0	             As duas strings são iguais.
// Menor que 0	         A primeira string vem antes da segunda em ordem alfabética (ordem dos caracteres).
// Maior que 0	         A primeira string vem depois da segunda.