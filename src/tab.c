#include "tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>

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
    if(elementoJaExiste(tabela, identificador)){
        return NULL;
    }
    tabela->ultimo->next = newLine;
    tabela->ultimo = newLine;
    return tabela;
}

Table addVar(Table tabela, String id, String tipo, int escopo){
    return addIdentificador(tabela, id, "var", tipo, escopo);
}

bool elementoJaExiste(Table tabela, String identificador){
    return buscarElemento(tabela, identificador) != NULL;
}

TableLine buscarElemento(Table tabela, String identificador){
    TableLine elem = tabela->primeiro;
    while(elem != NULL){
        if(strcmp(elem->identificador,identificador) == 0){
            return elem;
        }
        elem = elem->next;
    }
    return NULL;
}

void imprimeTabela(Table tabela){
    printf("==============Inicio Tabela de Simbolos==============");
        
    TableLine linha = tabela->primeiro;
    while(linha != NULL){
        printf(
            "\n| Identificador: %s - Categoria: %s - Tipo: %s - Escopo %i ", 
            linha->identificador,
            linha->categoria,
            linha->tipo,
            linha->escopo
        );
        linha = linha->next;
    }
    printf("\n");
    printf("==============Fim Tabela de Simboloss=================\n");
}