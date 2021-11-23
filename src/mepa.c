#include "mepa.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>


int* addVarMepa(Commands mepa, int *countVar){
    addCmdMepa(mepa, createNewCmdMepa("AMEM 1"));
    *countVar = *countVar+1;
    return countVar;
}

Command createNewCmdMepa(String instrucao){
    Command cmd = malloc(sizeof(*cmd));
    cmd->command = instrucao;
    cmd->next = NULL;
    return cmd;
}

void addCmdMepa(Commands mepa, Command cmd){
    mepa->ultimo->next = cmd;
    mepa->ultimo = cmd;
}

Commands startMepa(){
    Commands mepa = malloc(sizeof(*mepa));
    mepa->primeiro = createNewCmdMepa("INPP");
    mepa->ultimo = mepa->primeiro;
    return mepa;
}

Commands finishMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("PARA"));
}

void limpaArquivo(String name){
    fclose(fopen(name, "w"));
}

void printMepa(Commands mepa){
    printf("Comecei a impressão da MEPA\n");
    FILE *file;
    limpaArquivo("mepa.out");
    file = fopen("mepa.out", "a");
    if(file == NULL){
        printf("\nErro na abertura do arquivo\n");
        return;
    }

    Command instrucao = mepa->primeiro;

    while(instrucao != NULL){
        fprintf(file, "%s\n", instrucao->command);
        instrucao = instrucao->next;
    }
    printf("Mepa Impressa com sucesso\n");
}
