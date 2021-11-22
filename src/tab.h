#ifndef TAB_H
#define TAB_H

#include "util.h"

typedef struct TableLine_ *TableLine;

typedef struct Table_ *Table;

Table addIdentificador(Table tabela, String identificador, String categoria, String tipo, int escopo);
TableLine createLine(String identificador, String categoria, String tipo, int escopo);
bool elementoJaExiste(Table tabela, String identificador);
TableLine buscarElemento(Table tabela, String identificador);
Table addVar(Table tabela, String id, String tipo, int escopo);
void imprimeTabela(Table tabela);
Table createTable();

struct TableLine_ {
   String       identificador;
   String       categoria;
   String       tipo;
   int          escopo;
   TableLine   next;
};

struct Table_ {
    TableLine primeiro;
    TableLine ultimo;
};

#endif