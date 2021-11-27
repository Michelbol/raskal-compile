#include "mepa.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* addVarMepa(Commands mepa, int *countVar){
    addCmdMepa(mepa, createNewCmdMepa("AMEM 1"));
    *countVar = *countVar+1;
    return countVar;
}

void addNumMepa(Commands mepa, int numero){
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("CRCT ", numero)));
}

void recuperaVariavel(Commands mepa, int endereco, int escopo){
    String comando = concatStringInt("ARMZ ", escopo);
    comando = strcat(comando, ",");
    comando = concatStringInt(comando, endereco);
    addCmdMepa(mepa, createNewCmdMepa(comando));
}

void addReadMepa(Commands mepa, int endereco, int escopo){
    addCmdMepa(mepa, createNewCmdMepa("LEIT"));
    recuperaVariavel(mepa, endereco, escopo);
}

void addWriteMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("IMPR"));
}

void addLogicoMepa(Commands mepa, int numero){
    int value = numero ? 1 : 0;
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("CRCT ", value)));
}

void addNotLogicoMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("NEGA"));
}
void addInvertSinalMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("INVR"));
}

void LoadVarMepa(Commands mepa, int endereco, int escopo){
    String comando = concatStringInt("CRVL ", escopo);
    comando = strcat(comando, ",");
    comando = concatStringInt(comando, endereco);
    addCmdMepa(mepa, createNewCmdMepa(comando));
}

void addSomaMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("SOMA"));
}

void addMultMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("MULT"));
}

void addSubtMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("SUBT"));
}

void addDivMepa(Commands mepa){
    addCmdMepa(mepa, createNewCmdMepa("DIVI"));
}

void addAtribMepa(Commands mepa, int endereco, int escopo){
    recuperaVariavel(mepa, endereco, escopo);
}

void desalocaMemoriaMepa(Commands mepa, int qtd){
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("DMEM ", qtd)));
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
