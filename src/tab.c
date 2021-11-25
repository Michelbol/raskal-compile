#include "tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>

TableLine createLine(String identificador, String categoria, String tipo, int escopo, int endereco){
    TableLine linha = malloc(sizeof(*linha));
    linha->identificador = identificador;
    linha->categoria = categoria;
    linha->tipo = tipo;
    linha->escopo = escopo;
    linha->endereco = endereco;
    return linha;
}

Table createTable(){
    Table tabela = malloc(sizeof(*tabela));
    tabela->primeiro = NULL;
    tabela->ultimo = NULL;
    printf("\nTabela de simbolos criada com sucesso\n");
    return tabela;
}

Table addIdentificador(Table tabela, String identificador, String categoria, String tipo, int escopo, int endereco){
    TableLine newLine = createLine(identificador, categoria, tipo, escopo, endereco);
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
        printf("\nElemento %s já existe\n", identificador);
        return NULL;
    }
    tabela->ultimo->next = newLine;
    tabela->ultimo = newLine;
    return tabela;
}

Table addProgram(Table tabela, String id){
    return addIdentificador(tabela, id, "program", "", 0, 0);
}

Table addVar(Table tabela, String id, String tipo, int escopo, int endereco){
    return addIdentificador(tabela, id, "var", tipo, escopo, endereco);
}

bool elementoJaExiste(Table tabela, String identificador){
    return buscarElemento(tabela, identificador, NULL) != NULL;
}

TableLine buscarElemento(Table tabela, String identificador, String categoria){
    TableLine elem = tabela->primeiro;
    while(elem != NULL){
        if(strcmp(elem->identificador, identificador) == 0){
            if(categoria == NULL){
                return elem;
            }else{
                if(strcmp(categoria, elem->categoria) == 0){
                    return elem;
                }
            }
        }
        elem = elem->next;
    }
    return NULL;
}

TableLine buscarVariavel(Table tabela, String identificador){
    return buscarElemento(tabela, identificador, "var");
}

void imprimeTabela(Table tabela){
    printf("==============Inicio Tabela de Simbolos==============");
        
    TableLine linha = tabela->primeiro;
    while(linha != NULL){
        printf(
            "\n| Identificador: %s - Categoria: %s - Tipo: %s - Escopo: %i - endereco: %i", 
            linha->identificador,
            linha->categoria,
            linha->tipo,
            linha->escopo,
            linha->endereco
        );
        linha = linha->next;
    }
    printf("\n");
    printf("==============Fim Tabela de Simboloss=================\n");
}