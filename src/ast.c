#include <stdlib.h>
#include "ast.h"
#include <stdio.h>

A_Programa A_programa(String id, A_Bloco bloco) {
    A_Programa programa = malloc(sizeof(*programa));
    programa->id = id;
    programa->bloco = bloco;
    return programa;
}

A_Bloco A_bloco(A_LstDecVar secDecVar, A_LstDecSub secDecSub, A_CmdComp cmdComp) {
    A_Bloco bloco = malloc(sizeof(*bloco));
    bloco->secDecSub = secDecSub;
    bloco->secDecVar = secDecVar;
    bloco->cmdComp = cmdComp;
    return bloco;
}

A_LstIdent A_lstIdent(String id, A_LstIdent lstIdent) {
    A_LstIdent no = malloc(sizeof(*no));
    no->id = id;
    no->prox = lstIdent;
    return no;
}

A_DecVar A_decVar(String id, String tipo, Table tabela) {
    A_DecVar decVar = malloc(sizeof(*decVar));
    decVar->id = id;
    decVar->tipo = tipo;
    return decVar;
}

A_LstDecVar A_lstDecVar(A_DecVar decVar, A_LstDecVar lstDecVar) {
    A_LstDecVar no = malloc(sizeof(*no));
    no->decVar = decVar;
    no->prox = lstDecVar;
    return no;
}

A_LstDecVar concatLstDecVar(A_LstDecVar lst1, A_LstDecVar lst2) {
    A_LstDecVar lstConcat = lst1;
    if (lst1 != NULL) {
        while (lst1->prox != NULL) {
            lst1 = lst1->prox;
        }
        lst1->prox = lst2;
    }
    return lstConcat;
}


void printSecDecVar(A_LstDecVar sec){
    while(sec != NULL){
        printf("\n| Variavel: %s - Tipo: %s |", 
                sec->decVar->id, sec->decVar->tipo
        );
        sec = sec->prox;
    }
    printf("\n");
}

void imprimeArvore(A_Programa program){
    printf("Raiz: %s", program->id);
    String temDeclVar;
    if(program->bloco->secDecVar != NULL){
        temDeclVar = "x";
    }else{
        temDeclVar = "";
    }
    String temDeclSubRot;
    if(program->bloco->secDecSub != NULL){
        temDeclSubRot = "x";
    }else{
        temDeclSubRot = "";
    }
    printf("\nDev Var: [%s] - Dec SubRot: [%s] - Comando: [x]\n", temDeclVar, temDeclSubRot);
    if(temDeclVar == "x"){
        printf("==============Inicio Declaração de Variaveis==============");
        printSecDecVar(program->bloco->secDecVar);
        printf("==============Fim Declaração de Variaveis=================\n");
    }
}