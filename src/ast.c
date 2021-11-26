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

A_CmdComp A_cmdComp(A_LstCmd LstCmd) {
    A_CmdComp no = malloc(sizeof(*no));
    no->lstCmd = LstCmd;
    return no;
}

A_LstCmd A_lstCmd(A_Cmd cmd, A_LstCmd lstCmd){
    if(lstCmd == NULL){
        A_LstCmd no = malloc(sizeof(*no));
        no->cmd = cmd;
        no->prox = NULL;
        return no;
    }
    A_LstCmd no = malloc(sizeof(*no));
    no->cmd = cmd;
    no->prox = lstCmd;
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

A_Simp_Express A_simp_Express(A_LstTermo lstTermo){
    A_Simp_Express no = malloc(sizeof(*no));
    no->lstTermo = lstTermo;
    return no;
}

A_LstTermo A_lstTermo(A_Termo termo, String operador, A_LstTermo lstTermo){
    if(lstTermo == NULL){
        A_LstTermo no = malloc(sizeof(*no));
        no->termo = termo;
        no->operador = operador;
        no->prox = NULL;
        return no;
    }
    A_LstTermo no = malloc(sizeof(*no));
    no->termo = termo;
    no->operador = operador;
    no->prox = lstTermo;
    return no;
}

A_LstFator A_lstFator(A_Fator fator, String operador, A_LstFator lstFator){
    if(lstFator == NULL){
        A_LstFator no = malloc(sizeof(*no));
        no->fator = fator;
        no->operador = operador;
        no->prox = NULL;
        return no;
    }
    A_LstFator no = malloc(sizeof(*no));
    no->fator = fator;
    no->operador = operador;
    no->prox = lstFator;
    return no;
}

A_Termo A_termo(A_LstFator lstFator){
    A_Termo no = malloc(sizeof(*no));
    no->lstFator = lstFator;
    return no;
}

A_Fator A_fator(int num){
    A_Fator no = malloc(sizeof(*no));
    no->num = num;
    no->id = NULL;
    return no;
}

A_Fator A_fatorId(String id){
    A_Fator no = malloc(sizeof(*no));
    no->id = id;
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
    // Segundo termo pode ser nulo agora e foi adicionado a possibilidade de ser uma expressão
    // printf("Expressão: %i %s %i\n",
    // cmd->atrib->express->simp_express->primeiro_termo->fator->num,
    // cmd->atrib->express->simp_express->operacao,
    // cmd->atrib->express->simp_express->segundo_termo->fator->num
    // );
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
        printcmdComp(program->bloco->cmdComp->lstCmd->cmd);
        printf("==============Fim Comando Composto=================\n");
    }
}