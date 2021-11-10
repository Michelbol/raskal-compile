%{

#include <stdio.h>
#include <string.h>

#include "util.h"
#include "sintatico.tab.h"

#define DEBUG 1

#ifdef DEBUG
  #define IMPRIME(nome) printf("<%s, '%s'> (linha: %d)\n", nome, yytext, nl);
#else
  #define IMPRIME(nome) {};
#endif

int nl = 1;

%}

%option noyywrap

pulo_linha [\n]
branco [\t ]+
ident [a-zA-Z][_a-zA-Z0-9]*
numero [0-9]+

%%

{pulo_linha} { nl++; }

{branco}

"program" { IMPRIME("T_PROGRAM");          return T_PROGRAM; }
"var"     { IMPRIME("T_VAR");              return T_VAR; }
"begin"   { IMPRIME("T_BEGIN");            return T_BEGIN; }
"end"     { IMPRIME("T_END");              return T_END; }
":="      { IMPRIME("T_ATRIBUICAO");       return T_ATRIBUICAO; }
";"       { IMPRIME("T_PONTO_E_VIRGULA");  return T_PONTO_E_VIRGULA; }
":"       { IMPRIME("T_DOIS_PONTOS");      return T_DOIS_PONTOS; }
","       { IMPRIME("T_VIRGULA");          return T_VIRGULA; }
"."       { IMPRIME("T_PONTO");            return T_PONTO; }
"("       { IMPRIME("T_ABRE_PARENTESES");  return T_ABRE_PARENTESES; }
")"       { IMPRIME("T_FECHA_PARENTESES"); return T_FECHA_PARENTESES; }

{ident}   { IMPRIME("T_IDENT"); yylval.str = string(yytext); return T_IDENT; }

.         { fprintf(stderr, "Erro: Token ilegal: '%s'\n", yytext); }
