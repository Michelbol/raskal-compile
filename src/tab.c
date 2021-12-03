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

Table appendAttribUltimoElemento(Table tabela, String id, AtribType tipo, AtribCategory categoria, int endereco) {
    Atributes atrib = malloc(sizeof(*atrib));
    atrib->atribCategoria = categoria;
    atrib->id = id;
    atrib->tipo = tipo;
    atrib->endereco = endereco;

    LstAtributes lstAtributes = malloc(sizeof(*lstAtributes));
    lstAtributes->atributes = atrib;

    if(tabela->ultimo->lstAtributes->atributes == NULL){
        tabela->ultimo->lstAtributes = lstAtributes;
        tabela->ultimo->lstAtributes->prox = NULL;
        return tabela;
    }

    lstAtributes->prox = tabela->ultimo->lstAtributes;
    tabela->ultimo->lstAtributes = lstAtributes;
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
    if(elementoJaExiste(tabela, identificador, escopo)){
        printf("\nElemento %s já existe\n", identificador);
        return NULL;
    }
    tabela->ultimo->next = newLine;
    tabela->ultimo = newLine;
    return tabela;
}

Table addProc(Table tabela, String id, int escopo, int endereco) {
    LstAtributes lstAtributes = malloc(sizeof(*lstAtributes));
    return addIdentificador(tabela, id, Proc, "", escopo, endereco, lstAtributes);
}

Table addProgram(Table tabela, String id){
    return addIdentificador(tabela, id, Program, "", 0, 0, NULL);
}

Table addTipo(Table tabela, String id){
    return addIdentificador(tabela, id, Type, "", 0, 0, NULL);
}

AtribType resolveTipo(String tipo){
    if(strcmp(tipo, "integer") == 0){
        return Int;
    }else/*(strcmp(tipo, "boolean") == 0)*/{
        return Bool;
    }
}

Table addVar(Table tabela, String id, String tipo, int escopo, int endereco){
    if(escopo == 0){
        return addIdentificador(tabela, id, Var, tipo, escopo, endereco, NULL);
    }else{                              /*Table tabela, String id, AtribType tipo, AtribCategory categoria*/
        return appendAttribUltimoElemento(tabela, id, resolveTipo(tipo), A_Var, endereco);
    }
}

Table addParam(Table tabela, String id, String tipo, int endereco) {
    return appendAttribUltimoElemento(tabela, id, resolveTipo(tipo), A_Param, endereco);
}

bool elementoJaExiste(Table tabela, String identificador, int escopo){
    return buscarElementoEscopo(tabela, identificador, escopo) != NULL;
}

TableLine buscarElementoEscopo(Table tabela, String identificador, int escopo) {
    TableLine elem = tabela->primeiro;
    while(elem != NULL){
        if(strcmp(elem->identificador, identificador) == 0){
            if(escopo == elem->escopo){
                return elem;
            }
        }
        elem = elem->next;
    }
    return NULL;
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

Atributes buscaUltimoElemento(Table tabela, String identificador) {
    LstAtributes lstAtributes = tabela->ultimo->lstAtributes;
    while (lstAtributes != NULL)
    {
        Atributes atrib = lstAtributes->atributes;
        if(strcmp(atrib->id, identificador) == 0){
            return atrib;
        }
        lstAtributes = lstAtributes->prox;
    }
}

String resolveAtributesType(AtribType type) {
    if(type == Int){
        return "integer";
    }else{
        return "boolean";
    }
}

String resolveAtributesCategory(AtribCategory category){
    if(category == A_Param){
        return "param";
    }else{
        return "var";
    }
}

String transformaAtrib(TableLine line) {
    char result[1000] = "";
    if(line->lstAtributes == NULL ){
        return result;
    }
    LstAtributes lstAtributes = line->lstAtributes;
    strcat(result, "{");
    while (lstAtributes != NULL)
    {
        //{Cat: parametro - p: integer,}
        strcat(result, "Cat: ");
        strcat(result, resolveAtributesCategory(lstAtributes->atributes->atribCategoria));
        strcat(result, " - ");
        strcat(result, lstAtributes->atributes->id);
        strcat(result,": ");
        strcat(result, resolveAtributesType(lstAtributes->atributes->tipo));
        lstAtributes = lstAtributes->prox;
        if(lstAtributes != NULL){
             strcat(result, ", ");
        }
    }
    strcat(result, "}");
    return result;
}

void imprimeTabela(Table tabela){
    printf("==============Inicio Tabela de Simbolos==============");
        
    TableLine linha = tabela->primeiro;
    while(linha != NULL){
        printf(
            "\n| Identificador: %s - Categoria: %i - Tipo: %s - Escopo: %i - endereco: %i - Atrib: %s", 
            linha->identificador,
            linha->categoria,
            linha->tipo,
            linha->escopo,
            linha->endereco,
            transformaAtrib(linha)
        );
        linha = linha->next;
    }
    printf("\n");
    printf("==============Fim Tabela de Simboloss=================\n");
}