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

A_LstDecSub A_lstDecSub(A_DecProc decProc, A_LstDecSub lstDecSub) {
    if(lstDecSub == NULL){
        A_LstDecSub no = malloc(sizeof(*no));
        no->decProc = decProc;
        no->prox = NULL;
        return no;
    }
    A_LstDecSub no = malloc(sizeof(*no));
    no->decProc = decProc;
    no->prox = lstDecSub;
    return no;
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

A_Cmd A_cmdAtrib(A_Atrib atrib) {
    A_Cmd no = malloc(sizeof(*no));
    no->atrib = atrib;
    no->write = NULL;
    no->type = Atrib;
    return no;
}

A_Repeticao A_repeticao(A_Express expressao, A_CmdComp cmdComp) {
    A_Repeticao no = malloc(sizeof(*no));
    no->expressao = expressao;
    no->cmdComp = cmdComp;
    return no;
}

A_Condicional A_condicionalCmd(A_Express expressao, A_Cmd cmd, A_Cmd cmdElse) {
    A_Condicional no = malloc(sizeof(*no));
    no->expressao = expressao;
    no->cmdThen = cmd;
    no->cmdElse = cmdElse;
    no->condType = Comando;
    return no;
}

A_Condicional A_condicionalThenCmdComp(A_Express expressao, A_CmdComp cmdComp, A_Cmd cmdElse) {
    A_Condicional no = malloc(sizeof(*no));
    no->expressao = expressao;
    no->cmdCompThen = cmdComp;
    no->cmdElse = cmdElse;
    no->condType = ThenComandoComposto;
    return no;
}

A_Condicional A_condicionalElseCmdComp(A_Express expressao, A_Cmd cmd, A_CmdComp cmdCompElse) {
    A_Condicional no = malloc(sizeof(*no));
    no->expressao = expressao;
    no->cmdThen = cmd;
    no->cmdCompElse = cmdCompElse;
    no->condType = ElseComandoComposto;
    return no;
}

A_Condicional A_condicionalCmdComp(A_Express expressao, A_CmdComp cmdComp, A_CmdComp cmdCompElse) {
    A_Condicional no = malloc(sizeof(*no));
    no->expressao = expressao;
    no->cmdCompThen = cmdComp;
    no->cmdCompElse = cmdCompElse;
    no->condType = ComandoComposto;
    return no;
}

A_Cmd A_cmdCond(A_Condicional cond) {
    A_Cmd no = malloc(sizeof(*no));
    no->cond = cond;
    no->type = If;
    return no;
}

A_Cmd A_cmdRepeticao(A_Repeticao repet) {
    A_Cmd no = malloc(sizeof(*no));
    no->repet = repet;
    no->type = While;
    return no;
}

A_Cmd A_cmdWrite(A_Write write) {
    A_Cmd no = malloc(sizeof(*no));
    no->atrib = NULL;
    no->write = write;
    no->type = Write;
    return no;
}

A_Cmd A_cmdRead(A_Read read) {
    A_Cmd no = malloc(sizeof(*no));
    no->atrib = NULL;
    no->read = read;
    no->write = NULL;
    no->type = Read;
    return no;
}

A_Atrib A_atrib(String id, A_Express express) {
    A_Atrib no = malloc(sizeof(*no));
    no->id = id;
    no->express = express;
    return no;
}

A_Read A_read(A_LstIdent lstIdent){
    A_Read no = malloc(sizeof(*no));
    no->lstIdent = lstIdent;
    return no;
}

A_Write A_write(A_LstExpress lstExpress){
    A_Write no = malloc(sizeof(*no));
    no->lstExpressoes = lstExpress;
    return no;
}

A_LstExpress A_lstExpress(A_Express express, A_LstExpress lstExpress){
    if(lstExpress == NULL){
        A_LstExpress no = malloc(sizeof(*no));
        no->expressao = express;
        no->prox = NULL;
        return no;
    }
    A_LstExpress no = malloc(sizeof(*no));
    no->expressao = express;
    no->prox = lstExpress;
    return no;
}

A_Express A_express(A_Simp_Express simp_express) {
    A_Express no = malloc(sizeof(*no));
    no->simp_express = simp_express;
    no->relacao = ExpressaoSimples;
    return no;
}

A_Express A_expressRelacao(A_Simp_Express simp_express, Relacao relacao, A_Simp_Express simp_express2) {
    A_Express no = malloc(sizeof(*no));
    no->simp_express = simp_express;
    no->simp_express2 = simp_express2;
    no->relacao = relacao;
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

A_LstTermo A_lstTermoOr(A_Termo termo, A_LstTermo lstTermo) {
    return A_lstTermo(termo, Or, lstTermo);
}

A_LstTermo A_lstTermoSoma(A_Termo termo, A_LstTermo lstTermo) {
    return A_lstTermo(termo, Somar, lstTermo);
}

A_LstTermo A_lstTermoSubtrair(A_Termo termo, A_LstTermo lstTermo) {
    return A_lstTermo(termo, Subtrair, lstTermo);
}

A_LstTermo A_lstTermoNumero(A_Termo termo, A_LstTermo lstTermo) {
    return A_lstTermo(termo, Numero, lstTermo);
}

A_LstTermo A_lstTermo(A_Termo termo, TermoOperator operador, A_LstTermo lstTermo){
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

A_LstFator A_lstFatorAnd(A_Fator fator, A_LstFator lstFator){
    return A_lstFator(fator, And, lstFator);
}

A_LstFator A_lstFatorMulti(A_Fator fator, A_LstFator lstFator){
    return A_lstFator(fator, Multi, lstFator);
}

A_LstFator A_lstFatorDiv(A_Fator fator, A_LstFator lstFator){
    return A_lstFator(fator, Div, lstFator);
}
A_LstFator A_lstFatorFator(A_Fator fator, A_LstFator lstFator){
    return A_lstFator(fator, Fator, lstFator);
}

A_LstFator A_lstFator(A_Fator fator, FatorOperator operador, A_LstFator lstFator){
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
    no->type = Num;
    return no;
}

A_Fator A_fatorExpressao(A_Express expressao){
    A_Fator no = malloc(sizeof(*no));
    no->expressao = expressao;
    no->type = Expressao;
    return no;
}

A_Fator A_fatorId(String id){
    A_Fator no = malloc(sizeof(*no));
    no->id = id;
    no->type = Id;
    return no;
}

A_Fator A_fatorLogico(bool logico){
    A_Fator no = malloc(sizeof(*no));
    no->logico = logico;
    no->type = Logico;
    return no;
}

A_Fator A_fatorMenosFator(A_Fator fator){
    A_Fator no = malloc(sizeof(*no));
    no->fator = fator;
    no->type = Menos;
    return no;
}

A_Fator A_fatorNotFator(A_Fator fator) {
    A_Fator no = malloc(sizeof(*no));
    no->fator = fator;
    no->type = Not;
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