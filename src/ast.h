#ifndef AST_H
#define AST_H

#include "util.h"
#include "tab.h"

typedef struct A_Programa_ *A_Programa;
typedef struct A_Bloco_ *A_Bloco;
typedef struct A_LstDecSub_ *A_LstDecSub;
typedef struct A_LstDecVar_ *A_LstDecVar;
typedef struct A_LstDecParam_ *A_LstDecParam;
typedef struct A_CmdComp_ *A_CmdComp;
typedef struct A_Cmd_ *A_Cmd;
typedef struct A_LstCmd_ *A_LstCmd;
typedef struct A_Atrib_ *A_Atrib;
typedef struct A_Express_ *A_Express;
typedef struct A_Simp_Express_ *A_Simp_Express;
typedef struct A_LstTermo_ *A_LstTermo;
typedef struct A_Termo_ *A_Termo;
typedef struct A_LstFator_ *A_LstFator;
typedef struct A_Fator_ *A_Fator;
typedef struct A_DecParam_ *A_DecParam;
typedef enum FatorType_ {Id, Num, Logico} FatorType;

typedef struct A_LstIdent_ *A_LstIdent;
typedef struct A_DecVar_ *A_DecVar;
typedef struct A_DecProc_ *A_DecProc;
typedef struct A_ParamFormal_ *A_ParamFormal;


A_Programa A_programa(String id, A_Bloco bloco);
A_Bloco A_bloco(A_LstDecVar secDecVar, A_LstDecSub secDecSub, A_CmdComp cmdComp);
A_LstIdent A_lstIdent(String id, A_LstIdent lstIdent);
A_DecVar A_decVar(String id, String tipo, Table tabela);
A_LstDecVar A_lstDecVar(A_DecVar decVar, A_LstDecVar lstDecVar);
A_CmdComp A_cmdComp(A_LstCmd LstCmd);
A_Cmd A_cmd(A_Atrib attr);
A_Atrib A_atrib(String id, A_Express express);
A_Express A_express(A_Simp_Express simp_express);
A_Simp_Express A_simp_Express_Mais(A_Termo primeiro_termo, A_Termo segundo_termo, A_Simp_Express expressao);

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
    A_LstCmd lstCmd;
};

struct A_LstCmd_ {
    A_Cmd cmd;
    A_LstCmd prox;
};

struct A_Cmd_ {
    A_Atrib atrib;
};

struct A_Atrib_ {
    String id;
    A_Express express;
};

struct A_Express_ {
    A_Simp_Express simp_express;
};

struct A_Simp_Express_ {
    A_LstTermo lstTermo;
};

struct A_LstTermo_ {
    A_Termo termo;
    String operador;
    A_LstTermo prox;
};

struct A_Termo_ {
    A_LstFator lstFator;
};

struct A_LstFator_ {
    A_Fator fator;
    String operador;
    A_LstFator prox;
};

struct A_Fator_ {
    int num;
    String id;
    bool logico;
    FatorType type;
};

void imprimeArvore(A_Programa program);

#endif /* AST_H */