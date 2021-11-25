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

A_CmdComp A_cmdComp(A_Cmd cmd) {
    A_CmdComp no = malloc(sizeof(*no));
    no->cmd = cmd;
    return no;
}

A_Cmd A_cmd(A_Atrib atrib) {
    A_Cmd no = malloc(sizeof(*no));
    no->atrib = atrib;
    return no;
}

A_Atrib A_atrib(String id, A_Express express) {
    A_Atrib no = malloc(sizeof(*no));
    no->id = id;
    no->express = express;
    return no;
}

A_Express A_express(A_Simp_Express simp_express) {
    A_Express no = malloc(sizeof(*no));
    no->simp_express = simp_express;
    return no;
}

A_LstDecVar A_lstDecVar(A_DecVar decVar, A_LstDecVar lstDecVar) {
    A_LstDecVar no = malloc(sizeof(*no));
    no->decVar = decVar;
    no->prox = lstDecVar;
    return no;
}

A_Simp_Express A_simp_Express_Mais(A_Termo primeiro_termo, A_Termo segundo_termo){
    A_Simp_Express no = malloc(sizeof(*no));
    no->primeiro_termo = primeiro_termo;
    no->operacao = "+";
    no->segundo_termo = segundo_termo;
    return no;
}

A_Simp_Express A_simp_Express_Menos(A_Termo primeiro_termo, A_Termo segundo_termo){
    A_Simp_Express no = malloc(sizeof(*no));
    no->primeiro_termo = primeiro_termo;
    no->operacao = "-";
    no->segundo_termo = segundo_termo;
    return no;
}

A_Termo A_termo(A_Fator fator){
    A_Termo no = malloc(sizeof(*no));
    no->fator = fator;
    return no;
}

A_Fator A_fator(int num){
    A_Fator no = malloc(sizeof(*no));
    no->num = num;
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

void printcmdComp(A_Cmd cmd) {
    printf("\nVai Atribuir pro id: %s\n", cmd->atrib->id);
    printf("Expressão: %i %s %i\n",
    cmd->atrib->express->simp_express->primeiro_termo->fator->num,
    cmd->atrib->express->simp_express->operacao,
    cmd->atrib->express->simp_express->segundo_termo->fator->num
    );
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
    String temCmdComp;
    if(program->bloco->cmdComp != NULL){
        temCmdComp = "x";
    }else{
        temCmdComp = "";
    }
    printf("\nDev Var: [%s] - Dec SubRot: [%s] - Comando: [%s]\n", temDeclVar, temDeclSubRot, temCmdComp);
    if(temDeclVar == "x"){
        printf("==============Inicio Declaração de Variaveis==============");
        printSecDecVar(program->bloco->secDecVar);
        printf("==============Fim Declaração de Variaveis=================\n");
    }
    if(temCmdComp){
        printf("==============Inicio Comando Composto==============");
        printcmdComp(program->bloco->cmdComp->cmd);
        printf("==============Fim Comando Composto=================\n");
    }
}