#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "mepa.h"

static int countVar = 0;

static int errors = 0;

static Table tabelaSimbolos;

static Commands lstMepa;

void analisaDecVars(A_LstDecVar listaVars){
    while(listaVars != NULL){
        Table tabela = addVar(
            tabelaSimbolos,
            listaVars->decVar->id, 
            listaVars->decVar->tipo, 
            0, 
            *addVarMepa(lstMepa, &countVar)-1
        );
        if(tabela == NULL){
            errors = errors+1;
        }
        listaVars = listaVars->prox;
    }
}

void analisaDecSub(A_LstDecSub listSub){
    // implementar
}

void analisaOperacao(String operacao){
    if(operacao == NULL){
        return;
    }
    if(strcmp(operacao, "+") == 0){
        addSomaMepa(lstMepa);
        return;
    }
    if(strcmp(operacao, "-") == 0){
        addSubtMepa(lstMepa);
        return;
    }
    errors = errors+1;
    printf("Operação %s desconhecida", operacao);
}

void analisaFator(A_Fator fator){
    if(fator->num > 0){
        addNumMepa(lstMepa, fator->num);
    }
}

void analisaTermo(A_Termo termo){
    analisaFator(termo->fator);
}

void analisaLstTermo(A_LstTermo lstTermo){
    bool primeiroTermo = true;
    while(lstTermo != NULL){
        if(lstTermo->prox != NULL){
            if(primeiroTermo){
                analisaTermo(lstTermo->termo);
                primeiroTermo = false;
            }
            analisaTermo(lstTermo->prox->termo);
        }
        analisaOperacao(lstTermo->operador);
        lstTermo = lstTermo->prox;
    }
}

void analisaSimpExpress(A_Simp_Express simp_express, bool recursivo){   
    analisaLstTermo(simp_express->lstTermo);
}

void analisaExpress(A_Express express){
    analisaSimpExpress(express->simp_express, false);
}

void analisaAtrib(A_Atrib atrib){
    TableLine variavel = buscarVariavel(tabelaSimbolos, atrib->id);
    if(variavel == NULL){
        printf("\nVariavel %s não existe\n", atrib->id);
        errors = errors +1;
    }
    analisaExpress(atrib->express);
    addAtribMepa(lstMepa, variavel->endereco, variavel->escopo);
}

void analisaCmd(A_Cmd cmd){
    analisaAtrib(cmd->atrib);
}

void analisaLstCmd(A_LstCmd lstCmd){
    while(lstCmd != NULL){
        analisaCmd(lstCmd->cmd);
        lstCmd = lstCmd->prox;
    }
}

void analisaCmdComp(A_CmdComp cmdComp){
    analisaLstCmd(cmdComp->lstCmd);
}

void analisaBloco(A_Bloco bloco){
    analisaDecVars(bloco->secDecVar);
    analisaDecSub(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

int analisaPrograma(A_Programa prog, Table tabela, Commands mepa){
    tabelaSimbolos = tabela;
    lstMepa = mepa;
    addProgram(tabelaSimbolos, prog->id);
    analisaBloco(prog->bloco);
    desalocaMemoriaMepa(lstMepa, countVar);
    return errors;
}