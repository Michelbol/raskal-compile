#ifndef TAB_H
#define TAB_H

#include "util.h"

typedef struct TableLine_ *TableLine;
typedef enum TableCategory_ { Program, Type, Var, Proc, Void } TableCategory;

typedef struct Table_ *Table;

Table addIdentificador(Table tabela, String identificador, TableCategory categoria, String tipo, int escopo, int endereco);
TableLine createLine(String identificador, TableCategory categoria, String tipo, int escopo, int endereco);
bool elementoJaExiste(Table tabela, String identificador);
TableLine buscarElemento(Table tabela, String identificador, TableCategory categoria);
TableLine buscarVariavel(Table tabela, String identificador);
Table addVar(Table tabela, String id, String tipo, int escopo, int endereco);
Table addProgram(Table tabela, String id);
void imprimeTabela(Table tabela);
Table createTable();

struct TableLine_ {
   String       identificador;
   TableCategory categoria;
   String       tipo;
   int          endereco;
   int          escopo;
   TableLine   next;
};

struct Table_ {
    TableLine primeiro;
    TableLine ultimo;
};

#endif