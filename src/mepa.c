#include "mepa.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static String labelPrefix = "L";

int* addVarMepa(Commands mepa, int *countVar) {
    addAmemMepa(mepa, 1);
    *countVar = *countVar+1;
    return countVar;
}

void addAmemMepa(Commands mepa, int qtdVar) {
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("AMEM ", qtdVar)));
}

void addNumMepa(Commands mepa, int numero) {
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("CRCT ", numero)));
}

void recuperaVariavel(Commands mepa, int endereco, int escopo) {
    String comando = concatStringInt("ARMZ ", escopo);
    comando = strcat(comando, ",");
    comando = concatStringInt(comando, endereco);
    addCmdMepa(mepa, createNewCmdMepa(comando));
}

void addReadMepa(Commands mepa, int endereco, int escopo) {
    addCmdMepa(mepa, createNewCmdMepa("LEIT"));
    recuperaVariavel(mepa, endereco, escopo);
}

void addWriteMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("IMPR"));
}

void addLogicoMepa(Commands mepa, int numero){ 
    int value = numero ? 1 : 0;
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("CRCT ", value)));
}

void addNotLogicoMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("NEGA"));
}
void addInvertSinalMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("INVR"));
}

void LoadVarMepa(Commands mepa, int endereco, int escopo) {
    String comando = concatStringInt("CRVL ", escopo);
    comando = strcat(comando, ",");
    comando = concatStringInt(comando, endereco);
    addCmdMepa(mepa, createNewCmdMepa(comando));
}

void addDiferenteMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CMDG"));
}

void addMenorMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CMME"));
}

void addMenorIgualMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CMEG"));
}

void addMaiorMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CMMA"));
}

void addMaiorIgualMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CMAG"));
}

void addIgualMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CMIG"));
}

void addSomaMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("SOMA"));
}

void addOrMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("DISJ"));
}

void addAndMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("CONJ"));
}

void addMultMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("MULT"));
}

void addSubtMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("SUBT"));
}

void addDivMepa(Commands mepa) {
    addCmdMepa(mepa, createNewCmdMepa("DIVI"));
}

void addEntraProc(Commands mepa, int escopo, int countProc) {
    String result = concatStringInt("R", countProc);
    String cmd = concatStringInt(": ENPR ", escopo);
    strcat(result, cmd);
    addCmdMepa(mepa, createNewCmdMepa(result));
}

void addChamadaProcMepa(Commands mepa, int escopo, int countProc) {
    String label = concatStringInt("R", countProc);
    char cmd[20] = "CHPR ";
    strcat(cmd, label);
    // CHPR R1
    strcat(cmd, ", ");
    // CHPR R1, 
    String result = concatStringInt(string(cmd), escopo);
    // CHPR R01, 1
    addCmdMepa(mepa, createNewCmdMepa(result));
}

void addRetornaProc(Commands mepa, int escopo, int countParam) {
    String label = concatStringInt("", escopo);
    char cmd[20] = "RTPR ";
    strcat(cmd, label);
    // RTPR 1
    strcat(cmd, ", ");
    // RTPR 1, 
    String result = concatStringInt(string(cmd), countParam);
    // RTPR 1, 1
    addCmdMepa(mepa, createNewCmdMepa(result));
}

void addAtribMepa(Commands mepa, int endereco, int escopo) {
    recuperaVariavel(mepa, endereco, escopo);
}

void desalocaMemoriaMepa(Commands mepa, int qtd) {
    addCmdMepa(mepa, createNewCmdMepa(concatStringInt("DMEM ", qtd)));
}

Command createNewCmdMepa(String instrucao) {
    Command cmd = malloc(sizeof(*cmd));
    cmd->command = instrucao;
    cmd->next = NULL;
    return cmd;
}

void addDesvioCond(Commands mepa, int desvio) {
    String label = concatStringInt("L", desvio);
    char cmd[15] = "DSVF ";
    strcat(cmd, label);
    addCmdMepa(mepa, createNewCmdMepa(string(cmd)));
}

void addDesvio(Commands mepa, int desvio) {
    String label = concatStringInt("L", desvio);
    char cmd[15] = "DSVS ";
    strcat(cmd, label);
    addCmdMepa(mepa, createNewCmdMepa(string(cmd)));
}

void addNadaLabel(Commands mepa, int *desvio) {
    String label = concatStringInt(labelPrefix, *desvio);
    addCmdMepa(mepa, createNewCmdMepa(strcat(label, ": NADA")));
    *desvio = *desvio+1;
}

void addNadaLabelInicioMain(Commands mepa) {
    String label = concatStringInt(labelPrefix, 0);
    addCmdMepa(mepa, createNewCmdMepa(strcat(label, ": NADA")));
}

void addCmdMepa(Commands mepa, Command cmd) {
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
    //printf("Comecei a impressão da MEPA\n");
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
    //printf("Mepa Impressa com sucesso\n");
}
