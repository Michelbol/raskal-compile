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
typedef struct A_Condicional_ *A_Condicional;
typedef struct A_Read_ *A_Read;
typedef struct A_Write_ *A_Write;
typedef struct A_LstExpress_ *A_LstExpress;
typedef struct A_Simp_Express_ *A_Simp_Express;
typedef struct A_LstTermo_ *A_LstTermo;
typedef struct A_Termo_ *A_Termo;
typedef struct A_LstFator_ *A_LstFator;
typedef struct A_Fator_ *A_Fator;
typedef struct A_DecParam_ *A_DecParam;
typedef enum FatorType_ {Id, Num, Logico, Expressao , Not, Menos} FatorType;
typedef enum CmdType_ { Atrib, Write, Read, If } CmdType;
typedef enum TermoOperator_ { Somar, Subtrair, Or, Numero} TermoOperator;
typedef enum FatorOperator_ { Multi, Div, And , Fator} FatorOperator;
typedef enum Relacao_ { Igual, Diferente, Menor, MenorIgual, Maior, MaiorIgual, ExpressaoSimples} Relacao;
typedef enum CondType_ { Comando, ComandoComposto, ThenComandoComposto, ElseComandoComposto } CondType;

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
A_Cmd A_cmd(A_Atrib atrib);
A_Fator A_fatorLogico(bool logico);
A_Fator A_fator(int num);
A_Fator A_fatorId(String id);
A_Fator A_fatorNotFator(A_Fator fator);
A_Fator A_fatorMenosFator(A_Fator fator);
A_Fator A_fatorExpressao(A_Express expressao);
A_LstFator A_lstFatorAnd(A_Fator fator, A_LstFator lstFator);
A_LstFator A_lstFatorMulti(A_Fator fator, A_LstFator lstFator);
A_LstFator A_lstFatorDiv(A_Fator fator, A_LstFator lstFator);
A_LstFator A_lstFatorFator(A_Fator fator, A_LstFator lstFator);
A_LstFator A_lstFator(A_Fator fator, FatorOperator operador, A_LstFator lstFator);
A_Termo A_termo(A_LstFator lstFator);
A_LstTermo A_lstTermoSubtrair(A_Termo termo, A_LstTermo lstTermo);
A_LstTermo A_lstTermoSoma(A_Termo termo, A_LstTermo lstTermo);
A_LstTermo A_lstTermoNumero(A_Termo termo, A_LstTermo lstTermo);
A_LstTermo A_lstTermoOr(A_Termo termo, A_LstTermo lstTermo);
A_LstTermo A_lstTermo(A_Termo termo, TermoOperator operador, A_LstTermo lstTermo);
A_Simp_Express A_simp_Express(A_LstTermo lstTermo);
A_LstExpress A_lstExpress(A_Express express, A_LstExpress lstExpress);
A_Condicional A_condicionalCmd(A_Express expressao, A_Cmd cmd, A_Cmd cmdElse);
A_Condicional A_condicionalThenCmdComp(A_Express expressao, A_CmdComp cmdComp, A_Cmd cmdElse);
A_Condicional A_condicionalElseCmdComp(A_Express expressao, A_Cmd cmd, A_CmdComp cmdCompElse);
A_Read A_read(A_LstIdent lstIdent);
A_Write A_write(A_LstExpress lstExpress);
A_Cmd A_cmdCond(A_Condicional cond);
A_Cmd A_cmdRead(A_Read read);
A_Cmd A_cmdWrite(A_Write write);
A_Cmd A_cmdAtrib(A_Atrib atrib);
A_LstCmd A_lstCmd(A_Cmd cmd, A_LstCmd lstCmd);
A_Atrib A_atrib(String id, A_Express express);
A_Express A_express(A_Simp_Express simp_express);
A_Express A_expressRelacao(A_Simp_Express simp_express, Relacao relacao, A_Simp_Express simp_express2);
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
    A_Write write;
    A_Read read;
    A_Condicional cond;
    CmdType type;
};

struct A_Atrib_ {
    String id;
    A_Express express;
};

struct A_Condicional_ {
    A_Express expressao;
    A_Cmd cmdThen;
    A_Cmd cmdElse;
    A_CmdComp cmdCompThen;
    A_CmdComp cmdCompElse;
    CondType condType;
};

struct A_Read_ {
    A_LstIdent lstIdent;
};

struct A_Write_ {
    A_LstExpress lstExpressoes;
};

struct A_LstExpress_ {
    A_Express expressao;
    A_LstExpress prox;
};

struct A_Express_ {
    A_Simp_Express simp_express;
    Relacao relacao;
    A_Simp_Express simp_express2;
};

struct A_Simp_Express_ {
    A_LstTermo lstTermo;
};

struct A_LstTermo_ {
    A_Termo termo;
    TermoOperator operador;
    A_LstTermo prox;
};

struct A_Termo_ {
    A_LstFator lstFator;
};

struct A_LstFator_ {
    A_Fator fator;
    FatorOperator operador;
    A_LstFator prox;
};

struct A_Fator_ {
    int num;
    String id;
    bool logico;
    A_Fator fator;
    A_Express expressao;
    FatorType type;
};

void imprimeArvore(A_Programa program);

#endif /* AST_H */