#ifndef TAB_H
#define TAB_H

typedef struct TableLine_ *TableLine;

typedef struct Table_ *Table;

Table addIdentificador(Table tabela, String identificador, String categoria, String tipo, String escopo);
TableLine createLine(String identificador, String categoria, String tipo, String escopo);

struct TableLine_ {
   String       identificador;
   String       categoria;
   String       tipo;
   int          escopo;
   TableLine   next;
};

struct Table_ {
    TableLine linha;
    TableLine ultimo;
};

#endif