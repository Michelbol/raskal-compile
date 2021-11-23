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
int addVarMepa(Commands mepa, int countVar);

struct Command_ {
   String       command;
   Command      next;
};

struct Commands_ {
    Command primeiro;
    Command ultimo;
};

#endif