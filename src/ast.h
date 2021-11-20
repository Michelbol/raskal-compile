#ifndef AST_H
#define AST_H

#include "util.h"

typedef struct A_Programa_ *A_Programa;
typedef struct A_Bloco_ *A_Bloco;
typedef struct A_LstDecSub_ *A_LstDecSub;
typedef struct A_LstDecVar_ *A_LstDecVar;
typedef struct A_LstDecParam_ *A_LstDecParam;
typedef struct A_CmdComp_ *A_CmdComp;
typedef struct A_DecParam_ *A_DecParam;

typedef struct A_LstIdent_ *A_LstIdent;
typedef struct A_DecVar_ *A_DecVar;
typedef struct A_DecProc_ *A_DecProc;
typedef struct A_ParamFormal_ *A_ParamFormal;


A_Programa A_programa(String id, A_Bloco bloco);
A_Bloco A_bloco(A_LstDecVar secDecVar, A_LstDecSub secDecSub, A_CmdComp cmdComp);
A_LstIdent A_lstIdent(String id, A_LstIdent lstIdent);
A_DecVar A_decVar(String id, String tipo);
A_LstDecVar A_lstDecVar(A_DecVar decVar, A_LstDecVar lstDecVar);

A_LstDecVar concatLstDecVar(A_LstDecVar lst1, A_LstDecVar lst2);

struct A_Programa_ {
    String id;
    A_Bloco bloco;
};

struct A_Bloco_ {
    A_LstDecVar secDecVar;
    A_LstDecSub secDecSub;
    A_CmdComp cmdComp;
};

struct A_LstIdent_ {
    String id;
    A_LstIdent prox;
};

struct A_DecVar_ {
    String id;
    String tipo;
};

struct A_LstDecVar_ {
    A_DecVar decVar;
    A_LstDecVar prox;
};

struct A_LstDecSub_ {
    A_DecProc decProc;
    A_LstDecSub prox;
};

struct A_DecProc_{
    A_ParamFormal paramFormal;
};

struct A_ParamFormal_ {
    A_LstDecParam listDecParam;
};

struct A_LstDecParam_ {
    A_DecParam decParam;
    A_LstDecParam prox;
};

struct A_DecParam_ {
    A_LstIdent lst_ident;
    String tipo;
};

struct A_CmdComp_ {
    // implementar...
};

void imprimeArvore(A_Programa program);

#endif /* AST_H */