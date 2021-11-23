#ifndef ANALISADOR_H
#define ANALISADOR_H

#include "util.h"
#include "ast.h"
#include "mepa.h"


void analisaPrograma(A_Programa prog, Table tabela, Commands mepa);
void analisaBloco(A_Bloco bloco, Table tabela, Commands mepa);
void analisaDecVars(A_LstDecVar listaVars, Table tabela, Commands mepa, int *countVar);
void analisaDecSub(A_LstDecSub listSub);
void analisaCmdComp(A_CmdComp cmdComp);


#endif /* ANALISADOR_H */