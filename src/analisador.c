#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "mepa.h"

static int countVar = 0;

void analisaDecVars(A_LstDecVar listaVars, Table tabela, Commands mepa){
    while(listaVars != NULL){
        addVar(
            tabela,
            listaVars->decVar->id, 
            listaVars->decVar->tipo, 
            0, 
            *addVarMepa(mepa, &countVar)
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

void analisaBloco(A_Bloco bloco, Table tabela, Commands mepa){
    analisaDecVars(bloco->secDecVar, tabela, mepa);
    analisaDecSub(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

void analisaPrograma(A_Programa prog, Table tabela, Commands mepa){
    addProgram(tabela, prog->id);
    analisaBloco(prog->bloco, tabela, mepa);
}