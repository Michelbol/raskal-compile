#include "tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

TableLine createLine(String identificador, String categoria, String tipo, int escopo){
    TableLine linha = malloc(sizeof(*linha));
    linha->identificador = identificador;
    linha->categoria = categoria;
    linha->tipo = tipo;
    linha->escopo = escopo;
    return linha;
}

Table createTable(){
    Table tabela = malloc(sizeof(*tabela));
    tabela->primeiro = NULL;
    tabela->ultimo = NULL;
    return tabela;
}

Table addIdentificador(Table tabela, String identificador, String categoria, String tipo, int escopo){
    TableLine newLine = createLine(identificador, categoria, tipo, escopo);
    if(tabela == NULL){
        printf("ATENÇÃO: A tabela precisa ser criada");
        return tabela;
    }
    if(tabela->primeiro == NULL){
        tabela->primeiro = newLine;
        tabela->ultimo = newLine;
        return tabela;
    }
    tabela->ultimo->next = newLine;
    tabela->ultimo = newLine;
    return tabela;
}

Table addVar(Table tabela, A_DecVar var, int escopo){
    addIdentificador(tabela, var->id, "var", var->tipo, escopo);
}

void imprimeTabela(Table tabela){
    printf("Alo mundo da impressão de tabela");
}