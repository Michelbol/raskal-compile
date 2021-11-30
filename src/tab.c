#include "tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>

TableLine createLine(String identificador, TableCategory categoria, String tipo, int escopo, int endereco, LstAtributes lstAtrib) {
    TableLine linha = malloc(sizeof(*linha));
    linha->identificador = identificador;
    linha->categoria = categoria;
    linha->tipo = tipo;
    linha->escopo = escopo;
    linha->endereco = endereco;
    linha->lstAtributes = lstAtrib;
    return linha;
}

Table createTable(){
    Table tabela = malloc(sizeof(*tabela));
    tabela->primeiro = NULL;
    tabela->ultimo = NULL;
    printf("\nTabela de simbolos criada com sucesso\n");
    return tabela;
}

Table addIdentificador(Table tabela, String identificador, TableCategory categoria, String tipo, int escopo, int endereco, LstAtributes LstAtributes) {
    TableLine newLine = createLine(identificador, categoria, tipo, escopo, endereco, LstAtributes);
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
    return addIdentificador(tabela, id, Program, "", 0, 0, NULL);
}

Table addTipo(Table tabela, String id){
    return addIdentificador(tabela, id, Type, "", 0, 0, NULL);
}

Table addVar(Table tabela, String id, String tipo, int escopo, int endereco){
    return addIdentificador(tabela, id, Var, tipo, escopo, endereco, NULL);
}

bool elementoJaExiste(Table tabela, String identificador){
    return buscarElemento(tabela, identificador, Void) != NULL;
}

TableLine buscarElemento(Table tabela, String identificador, TableCategory categoria){
    TableLine elem = tabela->primeiro;
    while(elem != NULL){
        if(strcmp(elem->identificador, identificador) == 0){
            if(categoria == Void){
                return elem;
            }else{
                if(categoria == elem->categoria){
                    return elem;
                }
            }
        }
        elem = elem->next;
    }
    return NULL;
}

TableLine buscarVariavel(Table tabela, String identificador){
    return buscarElemento(tabela, identificador, Var);
}

void imprimeTabela(Table tabela){
    printf("==============Inicio Tabela de Simbolos==============");
        
    TableLine linha = tabela->primeiro;
    while(linha != NULL){
        printf(
            "\n| Identificador: %s - Categoria: %i - Tipo: %s - Escopo: %i - endereco: %i", 
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