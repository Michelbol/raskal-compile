#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "sintatico.tab.h"
#include "tab.h"
#include "analisador.h"
#include "mepa.h"

A_Programa raiz_ast;
Table tabela_simbolos;
Commands mepa;
int errors = 0;


/* Compilar:
   $ make
   
   Executar:
   $ ./compilador arquivo.ras
*/

int main(int argc, char** argv) {
    FILE* fp;
    extern FILE* yyin;

    if (argc < 2 || argc > 2) {
        fprintf(stderr, "Erro: número inválido de parâmetros\n");
        fprintf(stderr, "Uso: compilador <arquivo>\n");
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Erro: não foi possível ler o arquivo '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }
    yyin = fp;
    if (yyparse() == 0) {
        fprintf(stderr, "\nSucesso!\n");
    } else {
        fprintf(stderr, "\nAnálise com erros!\n");
    }
    
    tabela_simbolos = createTable();
    
    mepa = startMepa();
    int errors = analisaPrograma(raiz_ast, tabela_simbolos, mepa);
    if(errors > 0){
        printf("Quantidade de erros: %i\n", errors);
        return;
    }
    mepa = finishMepa(mepa);

    printMepa(mepa);
    
     //imprimeArvore(raiz_ast);
    imprimeTabela(tabela_simbolos);
    
    // raiz_ast está apontando para o nó raiz da AST (programa) caso o parsing foi bem sucedido.

    return EXIT_SUCCESS;
}