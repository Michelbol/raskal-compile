#include "tab.h"
#include "util.h"


Table addIdentificador(Table tabela, String identificador, String categoria, String tipo, String escopo){
    TableLine newLine = createLine(identificador, categoria, tipo, escopo);
    tabela->ultimo->next = newLine;
    tabela->ultimo = newLine;
    return tabela;
}

TableLine createLine(String identificador, String categoria, String tipo, String escopo){
    TableLine no = malloc(sizeof(*no));
    no->identificador = identificador;
    no->categoria = categoria;
    no->tipo = tipo;
    no->escopo = escopo;
    return no;
}