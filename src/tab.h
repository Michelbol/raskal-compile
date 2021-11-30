#ifndef TAB_H
#define TAB_H

#include "util.h"

typedef struct TableLine_ *TableLine;
typedef enum TableCategory_ { Program, Type, Var, Proc, Void } TableCategory;
typedef enum AtribCategory_ { A_Param, A_Var } AtribCategory;
typedef enum AtribType_ { Int, Bool } AtribType;

typedef struct Table_ *Table;
typedef struct Atributes_ *Atributes;
typedef struct LstAtributes_ *LstAtributes;

Table addIdentificador(Table tabela, String identificador, TableCategory categoria, String tipo, int escopo, int endereco, LstAtributes LstAtributes);
TableLine createLine(String identificador, TableCategory categoria, String tipo, int escopo, int endereco, LstAtributes lstAtrib);
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
   LstAtributes lstAtributes;
   TableLine   next;
};

struct Table_ {
    TableLine primeiro;
    TableLine ultimo;
};

struct LstAtributes_ {
    Atributes atributes;
    Atributes prox;
};

struct Atributes_ {
    String id;
    AtribCategory atribCategoria;
    AtribType tipo;
};

#endif