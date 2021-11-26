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
%x COMENTARIO STR

%%

{pulo_linha} { nl++; }

{branco}

"//"        { IMPRIME("T_COMENTARIO_LINHA"); BEGIN COMENTARIO;}
<COMENTARIO>{
    [\n]  { BEGIN(INITIAL); nl++;}
    .     {}
}



"program"   { IMPRIME("T_PROGRAM");          return T_PROGRAM; }
"var"       { IMPRIME("T_VAR");              return T_VAR; }
"procedure" { IMPRIME("T_PROCEDURE");        return T_PROCEDURE; }
"function"  { IMPRIME("T_FUNCTION");         return T_FUNCTION; }
"begin"     { IMPRIME("T_BEGIN");            return T_BEGIN; }
"end"       { IMPRIME("T_END");              return T_END; }
"if"        { IMPRIME("T_IF");               return T_IF; }
"then"      { IMPRIME("T_THEN");             return T_THEN; }
"else"      { IMPRIME("T_ELSE");             return T_ELSE; }
"while"     { IMPRIME("T_WHILE");            return T_WHILE; }
"do"        { IMPRIME("T_DO");               return T_DO; }
"read"      { IMPRIME("T_READ");             return T_READ; }
"write"     { IMPRIME("T_WRITE");            return T_WRITE; }
"and"       { IMPRIME("T_AND");              return T_AND; }
"or"        { IMPRIME("T_OR");               return T_OR; }
"not"       { IMPRIME("T_NOT");              return T_NOT; }
"div"       { IMPRIME("T_DIV");              return T_DIV; }
"("         { IMPRIME("T_ABRE_PARENTESES");  return T_ABRE_PARENTESES; }
")"         { IMPRIME("T_FECHA_PARENTESES"); return T_FECHA_PARENTESES; }
"."         { IMPRIME("T_PONTO");            return T_PONTO; }
","         { IMPRIME("T_VIRGULA");          return T_VIRGULA; }
";"         { IMPRIME("T_PONTO_E_VIRGULA");  return T_PONTO_E_VIRGULA; }
"+"         { IMPRIME("T_MAIS");             return T_MAIS; }
"-"         { IMPRIME("T_MENOS");            return T_MENOS; }
"*"         { IMPRIME("T_MULTIPLICACAO");    return T_MULTIPLICACAO; }
"="         { IMPRIME("T_IGUAL");            return T_IGUAL; }
"<>"        { IMPRIME("T_DIFERENTE");        return T_DIFERENTE; }
">"         { IMPRIME("T_MAIOR");            return T_MAIOR; }
"<"         { IMPRIME("T_MENOR");            return T_MENOR; }
">="        { IMPRIME("T_MAIOR_OU_IGUAL");   return T_MAIOR_OU_IGUAL; }
"<="        { IMPRIME("T_MENOR_OU_IGUAL");   return T_MENOR_OU_IGUAL; }
":="        { IMPRIME("T_ATRIBUICAO");       return T_ATRIBUICAO; }
":"         { IMPRIME("T_DOIS_PONTOS");      return T_DOIS_PONTOS; }


{ident}     { IMPRIME("T_IDENT"); yylval.str = string(yytext); return T_IDENT; }
{numero}    { IMPRIME("T_NUMERO"); yylval.num = atoi(yytext); return T_NUMERO; }

.           { fprintf(stderr, "Erro: Token ilegal: '%s'\n", yytext); }
