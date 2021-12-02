#ifndef MEPA_H
#define MEPA_H

#include "util.h"

typedef struct Command_ *Command;

typedef struct Commands_ *Commands;

Command createNewCmdMepa(String instrucao);
Commands startMepa();
Commands finishMepa(Commands mepa);
void addCmdMepa(Commands mepa, Command cmd);
void printMepa(Commands mepa);
int* addVarMepa(Commands mepa, int *countVar);
void addSomaMepa(Commands mepa);
void addNumMepa(Commands mepa, int numero);
void addAtribMepa(Commands mepa, int endereco, int escopo);
void desalocaMemoriaMepa(Commands mepa, int qtd);
void recuperaVariavel(Commands mepa, int endereco, int escopo);
void addReadMepa(Commands mepa, int endereco, int escopo);
void addWriteMepa(Commands mepa);
void addLogicoMepa(Commands mepa, int numero);
void addNotLogicoMepa(Commands mepa);
void addInvertSinalMepa(Commands mepa);
void LoadVarMepa(Commands mepa, int endereco, int escopo);
void addDiferenteMepa(Commands mepa);
void addMenorMepa(Commands mepa);
void addMenorIgualMepa(Commands mepa);
void addMaiorMepa(Commands mepa);
void addMaiorIgualMepa(Commands mepa);
void addIgualMepa(Commands mepa);
void addOrMepa(Commands mepa);
void addAndMepa(Commands mepa);
void addMultMepa(Commands mepa);
void addSubtMepa(Commands mepa);
void addDivMepa(Commands mepa);
void addAtribMepa(Commands mepa, int endereco, int escopo);
void desalocaMemoriaMepa(Commands mepa, int qtd);
void addDesvio(Commands mepa, int desvio);
void addDesvioCond(Commands mepa, int desvio);
void addNadaLabel(Commands mepa, int *desvio);
void addEntraProc(Commands mepa, int escopo, int countProc);
void addRetornaProc(Commands mepa, int escopo, int countProc);
void limpaArquivo(String name);

struct Command_ {
   String       command;
   Command      next;
};

struct Commands_ {
    Command primeiro;
    Command ultimo;
};

#endif