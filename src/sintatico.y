%code requires {
#include "util.h"
#include "ast.h"
#include "tab.h"
}

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "ast.h"
#include "tab.h"

/* Esta é a função que opera o Analisador Léxico (AL) e já foi construída pelo Flex
   dentro dele. Como o Analisador Sintático (AS) é quem irá chamá-la no decorrer da análise, 
   ela também precisa estar declarada aqui.
*/
int yylex(void);

/* Esta função será executada caso algum erro sintático ocorra. 
   Caso esta função não tivesse sido definida pelo usuário, o Bison iria construí-la
   praticamente da forma com que a definimos aqui. Essa é uma oportunidade
   de customizá-la para as suas necessidades. Talvez criar um módulo único e independente
   para controlar as mensagens de erro também seja interessante.
*/
void yyerror(const char *s) {
  fprintf(stderr, "Erro sintático: %s", s);
}

extern A_Programa raiz_ast;
extern Table tabela_simbolos;

%}

/* A definição abaixo cria um tipo de dados (no formato de uma union)
   para os valores semânticos que podem ser associados aos símbolos da
   gramática, tanto terminais (tokens) quanto não-terminais.
   No caso dos tokens, o valor semântico pode ser preenchido durante a 
   própria análise léxica, por meio da variável global yylval.
   Novos campos deverão ser adicionados nesta union, permitindo
   armazenar os valores semânticos de outros tipos de tokens ou de símbolos
   não terminais da gramática. 
*/
%union {
   bool logic;
   String str;
   int num;
   A_Programa programa;
   A_Bloco bloco;
   A_LstDecSub lstDecSub;
   A_LstDecVar lstDecVar;
   A_CmdComp cmdComp;
   A_Cmd cmd;
   A_Atrib atrib;
   A_Express express;
   A_Simp_Express simpExpress;
   A_Termo termo;
   A_Fator fator;
   A_LstIdent lstIdent;
   A_DecProc decProc;
   A_LstCmd lstCmd;
   A_LstTermo lstTermos;
   A_LstFator lstFator;
   A_LstExpress lstExpress;
   A_Write write;
   A_Read read;
}

/* Os nomes associados aos tokens definidos aqui serão armazenados um uma 
   enum dentro do arquivo compilador.tab.h. Este arquivo deve ser incluido 
   no código do analisador léxico para que os tokens retornados por ele tenham 
   exatamente os mesmos códigos numéricos que foram associados pela enum.
*/

%token T_PROGRAM
%token T_VAR
%token T_PROCEDURE
%token T_FUNCTION
%token T_BEGIN
%token T_END
%token T_IF
%token T_THEN
%token T_ELSE
%token T_WHILE
%token T_DO
%token T_READ
%token T_WRITE
%token T_AND
%token T_OR
%token T_NOT
%token T_DIV
%token T_ABRE_PARENTESES
%token T_FECHA_PARENTESES
%token T_VIRGULA T_PONTO_E_VIRGULA T_PONTO
%token T_MAIS
%token T_MENOS
%token T_MULTIPLICACAO
%token T_IGUAL
%token T_DIFERENTE
%token T_MAIOR
%token T_MENOR
%token T_MAIOR_OU_IGUAL
%token T_MENOR_OU_IGUAL
%token T_ATRIBUICAO
%token T_DOIS_PONTOS


%token <str> T_IDENT
%token <num> T_NUMERO
%token <logic> T_TRUE
%token <logic> T_FALSE
/* str é o nome do campo semântico que será utilizado pelo token T_IDENT (identificador).
   Este campo foi definido na union acima e seu objetivo é armazenar uma
   string (char *), que no nosso caso será o valor semântido do identificador
   (seu próprio lexema), o qual foi carregado pelo analizador léxico por meio
   da ação que construimos: yylval.str = String(yytext);
   A definição do token T_NUMERO seguirá a mesma ideia, mas seu valor semântico se refere
   ao campo num da union.
*/

/* Também podemos associar uma string literal ao nome de um token escrevendo esta string no fim
   da declaração %token. Com isso você poderá utilizar a string associada na gramática em vez
   de ter que escrever o nome do token. Por exemplo, o token T_PROGRAM poderia ser definido assim:
   
   %token T_PROGRAM "program"
   
   Dessa forma, podemos referenciar este token dentro da gramática como "program" em vez de T_PROGRAM.
   
   Veja mais em:
   https://www.gnu.org/software/bison/manual/html_node/Token-Decl.html
*/

%type <programa> programa
%type <lstDecVar> secao_declara_vars lista_declara_vars declara_vars
%type <lstDecSub> secao_declara_subs declara_proc params_formais list_declara_param declara_param
%type <lstIdent> lista_ident
%type <cmdComp> comando_composto
%type <lstCmd> lista_comandos
%type <cmd> comandos
%type <atrib> atribuicao
%type <express> expressao
%type <read> leitura
%type <write> escrita
%type <lstExpress> lista_expressoes
%type <simpExpress> expressao_simples
%type <lstTermos> lista_termos
%type <termo> termo
%type <lstFator> lista_fator
%type <fator> fator
%type <bloco> bloco
%type <str> tipo
%type <logic> logico

%define parse.error verbose
%define parse.lac full

%start programa

%%

programa: T_PROGRAM T_IDENT T_PONTO_E_VIRGULA bloco T_PONTO { raiz_ast = A_programa($2, $4); }
;

bloco: secao_declara_vars secao_declara_subs comando_composto { $$ = A_bloco($1, $2, $3); }
   | secao_declara_vars comando_composto { $$ = A_bloco($1, NULL, $2); }
;

secao_declara_vars: T_VAR lista_declara_vars { $$ = $2; }
                  | /* vazio */ { $$ = NULL; }
;

lista_declara_vars: declara_vars lista_declara_vars { $$ = concatLstDecVar($1, $2); }
                  | declara_vars                    { $$ = $1; }
;

declara_vars: lista_ident T_DOIS_PONTOS tipo T_PONTO_E_VIRGULA { 
                                                                  String tipo = $3;
                                                                  A_LstDecVar lstDecVar = NULL;
                                                                  A_LstIdent lstIdent = $1;

                                                                  while (lstIdent != NULL) {
                                                                     lstDecVar = A_lstDecVar(A_decVar(lstIdent->id, tipo, tabela_simbolos), lstDecVar);
                                                                     lstIdent = lstIdent->prox;
                                                                  }
                                                                  $$ = lstDecVar;
                                                               }
;

lista_ident: lista_ident T_VIRGULA T_IDENT { $$ = A_lstIdent($3, $1); }
           | T_IDENT                       { $$ = A_lstIdent($1, NULL); }
;

tipo: T_IDENT { $$ = $1; } /* caso não fosse especificada, esta já seria a ação default */
;

secao_declara_subs: declara_proc T_PONTO_E_VIRGULA secao_declara_subs { $$ = NULL; }
                  | declara_proc T_PONTO_E_VIRGULA { $$ = NULL; }
                  /*| { $$ = NULL; }*/
;

declara_proc: T_PROCEDURE T_IDENT params_formais T_PONTO_E_VIRGULA { $$ = NULL; }
;

params_formais: T_ABRE_PARENTESES list_declara_param T_FECHA_PARENTESES { $$ = NULL; }
               | T_ABRE_PARENTESES T_FECHA_PARENTESES { $$ = NULL; }
;

list_declara_param: declara_param list_declara_param { $$ = NULL; }
                  | declara_param { $$ = NULL; }
;

declara_param: T_VAR lista_ident T_DOIS_PONTOS tipo { $$ = NULL; }
            |  lista_ident T_DOIS_PONTOS tipo { $$ = NULL; }
;


comando_composto: T_BEGIN lista_comandos T_END { $$ = A_cmdComp($2); }
;

lista_comandos: comandos T_PONTO_E_VIRGULA lista_comandos { $$ = A_lstCmd($1, $3); }
            |  comandos T_PONTO_E_VIRGULA { $$ = A_lstCmd($1, NULL); }
;

comandos: atribuicao { $$ = A_cmdAtrib($1); }
         | escrita { $$ = A_cmdWrite($1); }
         | leitura { $$ = A_cmdRead($1); }
;

atribuicao: T_IDENT T_ATRIBUICAO expressao { $$ = A_atrib($1, $3); }
;

leitura: T_READ T_ABRE_PARENTESES lista_ident T_FECHA_PARENTESES { $$ = A_read($3); }
;

escrita: T_WRITE T_ABRE_PARENTESES lista_expressoes T_FECHA_PARENTESES { $$ = A_write($3); }
;

lista_expressoes: expressao T_VIRGULA lista_expressoes { $$ = A_lstExpress($1, $3); }
                 | expressao { $$ = A_lstExpress($1, NULL); }
;

expressao: expressao_simples { $$ = A_express($1); }
;

expressao_simples: lista_termos { $$ = A_simp_Express($1); }
;

lista_termos: termo T_MAIS lista_termos { $$ = A_lstTermo($1, "+", $3); }
            | termo T_MENOS lista_termos { $$ = A_lstTermo($1, "-", $3); }
            | termo { $$ = A_lstTermo($1, NULL, NULL); }
;

termo: lista_fator { $$ = A_termo($1); }
;

lista_fator: fator T_MULTIPLICACAO lista_fator {$$ = A_lstFator($1, "*", $3); }
            | fator T_DIV lista_fator { $$ = A_lstFator($1, "div", $3); }
            | fator { $$ = A_lstFator($1, NULL, NULL); }
;

fator: T_IDENT { $$ = A_fatorId($1); }
      | T_NUMERO { $$ = A_fator($1); }
      | logico { $$ = A_fatorLogico($1); }
      | T_NOT fator{ $$ = A_fatorNotFator($2); }
;

logico: T_TRUE { $$ = true; }
      | T_FALSE { $$ = false; }
%%

/* Aqui poderia ser construída a função main com a lógica do compilador, que
   executaria a análise sintática e seguiria com o processo de compilação.
   Entretanto, para deixar nosso código mais organizado, o programa principal
   foi construído separadamente no arquivo compilador.c
*/