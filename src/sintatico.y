%code requires {
#include "util.h"
#include "ast.h"
}

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "ast.h"

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
   String str;
   int num;
   A_Programa programa;
   A_Bloco bloco;
   A_LstDecSub secDecVar;
   A_LstDecVar secDecSub;
   A_CmdComp cmdComp;
}

/* Os nomes associados aos tokens definidos aqui serão armazenados um uma 
   enum dentro do arquivo compilador.tab.h. Este arquivo deve ser incluido 
   no código do analisador léxico para que os tokens retornados por ele tenham 
   exatamente os mesmos códigos numéricos que foram associados pela enum.
*/

%token T_PROGRAM
%token T_BEGIN
%token T_END
%token T_VAR
%token T_ABRE_PARENTESES
%token T_FECHA_PARENTESES
%token T_ATRIBUICAO
%token T_VIRGULA T_PONTO_E_VIRGULA T_DOIS_PONTOS T_PONTO

%token <str> T_IDENT 
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
%type <secDecVar> secao_declara_vars
%type <secDecSub> secao_declara_subs
%type <cmdComp> comando_composto
%type <bloco> bloco
%type <str> tipo

%define parse.error verbose
%define parse.lac full

%start programa

%%

programa: T_PROGRAM T_IDENT T_PONTO_E_VIRGULA bloco T_PONTO { raiz_ast = A_programa($2, $4); }
;

bloco: secao_declara_vars secao_declara_subs comando_composto { $$ = A_bloco($1, $2, $3); }
;

secao_declara_vars: T_VAR declara_vars /* implementar ação */ { $$ = NULL; }
                  | /* vazio */ { $$ = NULL; }
;

secao_declara_subs: /* colocar regras e implementar ação */ { $$ = NULL; }
;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var: lista_ident T_DOIS_PONTOS tipo T_PONTO_E_VIRGULA
;

lista_ident: lista_ident T_VIRGULA T_IDENT
           | T_IDENT
;

tipo: T_IDENT { $$ = $1; } /* caso não fosse especificada, esta já seria a ação default */
;

comando_composto: T_BEGIN comandos T_END /* implementar ação */ { $$ = NULL; }
;

comandos: 
;

%%

/* Aqui poderia ser construída a função main com a lógica do compilador, que
   executaria a análise sintática e seguiria com o processo de compilação.
   Entretanto, para deixar nosso código mais organizado, o programa principal
   foi construído separadamente no arquivo compilador.c
*/