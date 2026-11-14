#ifndef ALIMENTO_H;
#define ALIMENTO_H;  // Ele define a constante alimento

typedef enum{
    CEREAIS_E_DERIVADOS,
    VERDURAS_HORTALICAS_E_DERIVADOS,
    FRUTAS_E_DERIVADOS,
    GORDURAS_E_OLEOS,
    PESCADOS_E_FRUTOS_DO_MAR,
    CARNES_E_DERIVADOS,
    LEITE_E_DERIVADOS,
    BEBIDAS,
    OVOS_E_DERIVADOS,
    PRODUTOS_ACUCARADOS,
    MISCELANEAS,
    OUTROS_ALIMENTOS_INDUSTRIALIZADOS,
    ALIMENTOS_PREPARADOS,
    LEGUMINOSAS_E_DERIVADOS,
    NOZES_E_SEMENTES
} Categoria;

typedef struct{
    int numero;
    char descricao[100];
    float energia;
    float proteina;
    Categoria categoria;
} Alimentos;

const char*obter_nome_categoria(Categoria categoria);

bool converter_categoria(const char *texto, Categoria *categoria);

#endif // ele informa o final da constante iniciada pelo "define" 