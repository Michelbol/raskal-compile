#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "mepa.h"


void analisaDecVars(A_LstDecVar listaVars, Table tabela, Commands mepa, int *countVar){
    while(listaVars != NULL){
        addVar(
            tabela,
            listaVars->decVar->id, 
            listaVars->decVar->tipo, 
            0, 
            *addVarMepa(mepa, countVar)
        );
        listaVars = listaVars->prox;
    }
}

void analisaDecSub(A_LstDecSub listSub){
    // implementar
}

void analisaCmdComp(A_CmdComp cmdComp){
    // implementar
}

void analisaBloco(A_Bloco bloco, Table tabela, Commands mepa, int *countVar){
    analisaDecVars(bloco->secDecVar, tabela, mepa, countVar);
    analisaDecSub(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

void analisaPrograma(A_Programa prog, Table tabela, Commands mepa){
    int countVar = 0;
    addProgram(tabela, prog->id);
    analisaBloco(prog->bloco, tabela, mepa, &countVar);
}